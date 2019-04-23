#include <curses.h>
#include "src/platform_basic_func.h"
#include "src/Seeed_3D_touch_mgc3030.h"

extern Sensor_info_t mgc_info;

void draw_rectangle(void)
{
    mvaddstr(1,1,"************************************************************");
    for(int i=2;i<20;i++){
        move(i,1);
        addch('*');
        move(i,60);
        addch('*');
    }
    mvaddstr(20,1,"************************************************************");
}

void curse_init(void)
{
    initscr();
    cbreak();                    
    noecho();
    curs_set(0);
    draw_rectangle();
    refresh();
    // keypad(stdscr, true);
}

uint8_t ges_cnt;
uint8_t pos_cnt;
uint8_t air_wheel_cnt;
uint8_t touch_cnt;


void clear_data_periodly(void)
{
    static uint32_t debug_cnt = 0;
    char debug_buf[6] = {0};

    ges_cnt++;
    pos_cnt++;
    air_wheel_cnt++;
    touch_cnt++;

    debug_cnt++;
    uint8_t act_flag = 0;

    if(ges_cnt >= 10 ){
        ges_cnt = 0;
         show_gesture("Gesture :                ");
         act_flag = 1;
    }
    if(pos_cnt >= 10){
        // pos_cnt = 0;
        //  show_location(0,0,0);
        //  act_flag = 1;
    }
    if(air_wheel_cnt >= 10){
        // air_wheel_cnt = 0;
        // show_airwheel_angle(mgc_info.angle);
        // act_flag = 1;
    }
    if(touch_cnt >= 10){
        touch_cnt = 0;
        mvaddstr(11,3,"Touch electrode :                                         ");
        mvaddstr(12,3,"Tap electrode :                                           ");
        mvaddstr(13,3,"Double Tap electrode :                                    ");
        act_flag = 1;
    }
    if(act_flag){
        refresh();
    }
}

void curse_init_show(void)
{
    show_gesture("Gesture :                ");
    show_location(0,0,0);
    show_airwheel_angle(mgc_info.angle);
    mvaddstr(11,3,"Touch electrode :                  ");
    mvaddstr(12,3,"Tap electrode :                    ");
    mvaddstr(13,3,"Double Tap electrode :             ");
    refresh();
}


static uint8_t data[MAX_RECV_LEN];
int main(void)
{
    int32_t ret = 0;
    
    curse_init();
    /*Draw a init gragh.*/
    curse_init_show();

    /*hardware init(i2c gpio...)*/
    if(basic_init()){
        printf("Basic init failed!!\n");
        return -1;
    }

    
    read_version_info(data);

    if(calibration_select(DISABLE)){
        printf("Select calibration failed!\n");
        mgc_exit();
        return -1;
    }


    if(set_lock_mask()){
        printf("Set lock mask failed!\n");
        mgc_exit();
        return -1;
    }
    mgc3030_init();

    while(1){
        if(mg3030_read_data(data) < 3)
        {
            usleep(50000);
            clear_data_periodly();
            continue;
        }
        parse_sensor_msg(data);
        memset(data,0,sizeof(data));
        usleep(50000);
        clear_data_periodly();
    }

    return 1;
}
