/*
防水ds18b20传感器接法：
红线接5v,黑线接gnd地线，黄线信号线接方案板TX脚
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
#include "pwm.h"     //引入PWM头文件
#include "ds18b20.h" //引入s18b20温度传感器头文件
static const char *TAG = "app_main";
// ds18b20温度传感器读取任务
uint16_t wendu;
void Task_ds18b20(void *p)
{

   char dht11_buff[50] = {0};

   while (1)
   {
      wendu = floatReadDs18B20(); // 读取ds18b20温度传感器值
      if (wendu > 125)
      {
         wendu = 0;
      }
      sprintf(dht11_buff, "T=%02dC", wendu); // 格式化输出
      ESP_LOGI(TAG, "%s.\r\n", dht11_buff);  // usb口打印
      vTaskDelay(1000 / portTICK_PERIOD_MS); // 每一秒读取一次温度值
   }
}
static void myapp(lv_timer_t *timer)
{
   if (wendu > 125)
   {
      wendu = 0;
   }

   lv_label_set_text_fmt(ui_Label2, "%02d", wendu);
}
void app_main(void)
{

   // 1.方案板参数配置初始化
   sys_int();
   // 2.方案板LVGL接口初始化
   lvgl_init();
   // 3.LVGL应用层,用户程序
   pwm_init(); // 2,PWM背光调试初始化
   // ds18b20温度传感器读取任务
   xTaskCreate(Task_ds18b20, "Task_ds18b20", 4096, NULL, 3, NULL);

   lv_port_sem_take();
   ui_init();                          // 调用UI软件生成的代码入口函数
   lv_timer_create(myapp, 1000, NULL); // 定时1分钟更新温度数据
   lv_port_sem_give();
}
