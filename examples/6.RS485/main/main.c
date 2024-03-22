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
#include "pwm.h"     //引入PWM头文件
#include "ds18b20.h" //引入s18b20温度传感器头文件
static const char *TAG = "app_main";
#include "uart_rs485.h"//引入rs485头文件,通信波特率9600
//发指令在ui_events.c文件内
void uart0_rx_task()
{
   uint8_t *data = (uint8_t *)malloc(RX_BUF_SIZE + 1);
   while (1)
   {
      // 获取RS485接收的数据
      const int rxBytes = uart_read_bytes(UART_NUM_0, data, RX_BUF_SIZE, 10);
      if (rxBytes > 0)
      {

         data[rxBytes] = 0;
         ESP_LOGI(TAG, "%s\r\n", (char *)data);  // usb口打印
         // // 将接收到的数据发出去
         // uart_write_bytes(UART_NUM_0, (char *)data, rxBytes);

         // // 要发送的16进制指令
         // uint8_t hex_cmd[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};

         // // 发送16进制指令
         // uart_write_bytes(UART_NUM_0, (const char *)hex_cmd, sizeof(hex_cmd));
      }
   }
   free(data);
}
// ds18b20温度传感器读取任务
uint16_t wendu=0;
void Task_ds18b20(void *p)
{

   char dht11_buff[50] = {0};

   while (1)
   {
      wendu = floatReadDs18B20();            // 读取ds18b20温度传感器值
      // sprintf(dht11_buff, "T=%02dC", wendu); // 格式化输出
      // ESP_LOGI(TAG, "%s.\r\n", dht11_buff);  // usb口打印
      vTaskDelay(1000 / portTICK_PERIOD_MS); // 每一秒读取一次温度值
   }
}
static void myapp(lv_timer_t *timer)
{
if (wendu>100)
{
   wendu=0;
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
   uart_init(UART_NUM_0);// rs485串口初始化
   // rs485接收任务
   xTaskCreate(uart0_rx_task, "uart0_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES, NULL);

   lv_port_sem_take();
   ui_init();                          // 调用UI软件生成的代码入口函数
   lv_timer_create(myapp, 1000, NULL); // 定时1分钟更新温度数据
   lv_port_sem_give();
}
