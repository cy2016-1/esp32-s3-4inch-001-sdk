/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"

#include "lvgl.h"
#include "bsp_board.h" //1.方案板参数配置初始化必须包含的头文件
#include "lvgl_init.h" //2.方案板LVGL接口初始化必须包含的头文件
#include "lv_demos.h"
#include <string.h>
#include <sys/param.h>
#include "driver/i2c.h"
#include "gui_app/ui.h"

static const char *TAG = "app_main";

void app_main(void)
{

    // 1.方案板参数配置初始化
    sys_int();
    // 2.方案板LVGL接口初始化
    lvgl_init();
    // 3.LVGL应用层,用户程序
    lv_port_sem_take();
    ui_init();//调用UI软件生成的代码入口函数
    lv_port_sem_give();

 
  
}
