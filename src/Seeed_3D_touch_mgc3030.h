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
#ifndef SEEED_3D_TOUCH_MGC3030_H
#define SEEED_3D_TOUCH_MGC3030_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "platform_basic_func.h"


#define SET_RUNTIME_PARAM_CMD     0xA2
#define SENSOR_OUTPUT_DATA        0x91


#define GESTIC_XYZ_DATA			16
#define GESTIC_GESTURE_DATA    	6 
#define GESTIC_TOUCH_DATA      	10 

#define RUNTIME_PARAM_ID_DATA_OUTPUT_LOCK_MASK          0xA1
#define ENABLE_MASK_BIT                                 0xA0


#define RUNTIME_PARAM_ID_CALIBRATION_OPERATION_MODE     0x80
#define SELECT_AIR_WHEEL_FUNCTION_ID                    0x90
#define SELECT_GESTURE_FUNCTION_ID                      0x85
#define SELECT_DETECTION_FUNCTION_ID                    0x97

#define SELECT_APPROACH_DETECTION_FUNCTION_ID           0x97

typedef enum{
    DISABLE,
    ENABLE,
}Enable_t;

typedef enum{
    ENABLE_ALL_GESTURE,
    ENABLE_ONLY_FLICK_GESTURE,
    ENABLE_IN_ADDITION_CIRCLES,
    DISABLE_ALL_GESTURE,
}Gesture_select_t;



/**Set runtime param
 * @param run_time_id This id indicate the function that should be set.
 * @param arg0        This arg indicates which function to set.
 * @param arg1        This arg indicates which function to set.
 * @return return 0 if successed.else error.
*/
int32_t mg3030_set_runtime_param(uint16_t run_time_id,uint32_t arg0,uint32_t arg1);
/**Parse msg receiced from sensor.
 * @param data        The msg received.
 * @return return 0 if successed.else error.
*/
int32_t parse_sensor_msg(uint8_t *data);

/**Read data from sensor.
 * @param data        The data buf that store the msg received.
 * @return The msg len.
*/
int32_t mg3030_read_data(void *data);

/**Reset some global runtime param.
 * 
*/
void mgc3030_init(void);
/**Set sensor calibration function.
 * @param flag ENABLE or DISABLE
 * 
*/
int32_t calibration_select(Enable_t flag);

int32_t set_lock_mask(void);


/** Read sensor version info.At start-up,MGC3X30 sends the Fw_Version_Info message to the host interface to show that the chip
 * is live and ready for operation.Host MUST read this message ,and then,to setting the sensor.  
 * @param data version data.
 * @return return 0 if successed.else error.
 * **/
int32_t read_version_info(void *data);


void show_location(int32_t x,int32_t y ,int32_t z);


void show_airwheel_angle(int32_t airwheel_angle);

void show_touch(uint8_t gesture);

void show_gesture(char *ges_str);

int32_t output_enable_mask_select(Enable_t flag);

typedef enum
{
    GESTURE_NOT_DEFINED,
    GESTURE_GARBAGE,
    GESTURE_WEST_TO_EAST,
    GESTURE_EAST_TO_WEST,
    GESTURE_SOUTH_TO_NORTH,
    GESTURE_NORTH_TO_SOUTH,
    CIRCLE_CLK_WISE,
    CIRCLE_CNT_CLK_WISE,    
}Gest_t;


typedef enum
{
    TOUCH_SOUTH_ELECTRODE, 
	TOUCH_WEST_ELECTRODE,
	TOUCH_NORTH_ELECTRODE,
	TOUCH_EAST_ELECTRODE,
	TOUCH_CENTER_ELECTRODE,
	TAP_SOUTH_ELECTRODE,
	TAP_WEST_ELECTRODE,
	TAP_NORTH_ELECTRODE,
	TAP_EAST_ELECTRODE,
	TAP_CENTER_ELECTRODE,
	DOUBLE_TAP_SOUTH_ELECTRODE,
	DOUBLE_TAP_WEST_ELECTRODE,
	DOUBLE_TAP_NORTH_ELECTRODE,
	DOUBLE_TAP_EAST_ELECTRODE,
	DOUBLE_TAP_CENTER_ELECTRODE,
	TOUCH_NOT_DEFINED,
}Touch_t;


typedef enum 
{
    GARBAGE_MODEL,
    POSITION,
    CIRCULAR,
    UNDEFINED,
}Gest_category_t;

typedef struct 
{
    Gest_t gesture;
    Touch_t touch;
    int32_t angle;
}Sensor_info_t;

#endif






