/*
 *  
 * Copyright (c) 2019 Seeed Technology Co., Ltd.
 * Website    : www.seeed.cc
 * Author     : downey
 * Create Time: Jan 2019
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "platform_basic_func.h"
#include <stdlib.h>


static int32_t i2c_fd = -1;

/********************************************************************/
/*******************************gpio*********************************/
/********************************************************************/

void power_reset(void)
{
    digitalWrite(RESET_PIN, LOW);
    usleep(10000);
    digitalWrite(RESET_PIN, HIGH);
    usleep(50000);
}


void gpio_config(void)
{
    pinMode(TRANS_PIN,PUD_UP);
    pinMode(RESET_PIN,OUTPUT);

    power_reset();

}



/********************************************************************/
/*******************************i2c*********************************/
/********************************************************************/


int32_t i2c_init(char *path)
{
    if(i2c_fd < 0){
        i2c_fd = open(path,O_RDWR);
        if(i2c_fd < 0)
        {
            return -1;
        }
        return 0;
    }
    return 0;
}


int32_t i2c_config(void)
{
    if (ioctl(i2c_fd, I2C_SLAVE, MG3030_DEFAULE_I2C_ADDR) < 0) {
		return -1;
    }
    return 0;
}


int32_t i2c_read_block_data(uint8_t *data)
{
    return read(i2c_fd, data, MAX_RECV_LEN); 
}


int32_t i2c_send_msg(void *data,uint32_t len)
{
    if(NULL == data){
        return -1;
    }
    usleep(10000);
    int ret = write(i2c_fd, data, len);
    usleep(10000);

    return ret;
}



int32_t basic_init(void)
{
    
    if(i2c_init("/dev/i2c-1")){
        // printf("0-------------\n");
        return -1;
    }
    if(i2c_config()){
        // printf("1-------------\n");
        close(i2c_fd);
        return -2;
    }
    fdatasync(i2c_fd);

    wiringPiSetupGpio();
    gpio_config();
    return 0;
}

void mgc_exit(void)
{
    close(i2c_fd);
    endwin();
    exit(0);
}



