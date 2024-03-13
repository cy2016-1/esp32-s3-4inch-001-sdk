#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "lvgl.h"
#include "bsp_board.h" //1.方案板参数配置初始化必须包含的头文件
#include "lvgl_init.h" //2.方案板LVGL接口初始化必须包含的头文件
#include "nvs_flash.h"
#include "espnow_lite.h"
#include "lv_example_scroll.h"

static const char *TAG = "main";

void espnow_start()
{
    uint8_t broadcast_mac[ESP_NOW_ETH_ALEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

#if 0
    esp_now_peer_info_t* peer = malloc(sizeof(esp_now_peer_info_t));
    espnow_payload_t* send_data = malloc(sizeof(espnow_payload_t));
#else
    esp_now_peer_info_t *peer = heap_caps_malloc(sizeof(esp_now_peer_info_t), MALLOC_CAP_SPIRAM);
    espnow_payload_t *send_data = heap_caps_malloc(sizeof(espnow_payload_t), MALLOC_CAP_SPIRAM);
#endif
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);
    espnow_wifi_init();
    espnow_init();
}

void app_main()
{
    // 1.方案板参数配置初始化
    sys_int();
    // 2.方案板LVGL接口初始化
    lvgl_init();
    // 3.LVGL应用层,用户程序

    lv_port_sem_take();
    lv_example_86box(); // 调用UI软件生成的代码入口函数
    lv_port_sem_give();
    espnow_start();
}
