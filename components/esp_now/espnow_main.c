#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_now.h"
#include "esp_crc.h"
#include "chat_espnow.h"
#include "data_transfer.h"

#define TAG "ESP_NOW"
TaskHandle_t send_task_handle = NULL;
TaskHandle_t recive_task_handle = NULL;
uint8_t esp_1[6] = {0x30, 0xae, 0xa4, 0x25, 0x15, 0xc8};
uint8_t esp_2[6] = {0x24, 0x6f, 0x28, 0x95, 0xa7, 0xb0};
const uint8_t *data_recived;
int data_len_recived = 0;
char *mac_to_str(char *buffer, uint8_t *mac)
{
    sprintf(buffer, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return buffer;
}

void on_sent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    char buffer[13];
    switch (status)
    {
    case ESP_NOW_SEND_SUCCESS:
        ESP_LOGI(TAG, "message sent to %s", mac_to_str(buffer, (uint8_t *)mac_addr));
        break;
    case ESP_NOW_SEND_FAIL:
        ESP_LOGE(TAG, "message sent to %s failed", mac_to_str(buffer, (uint8_t *)mac_addr));
        break;
    }
}

void on_receive(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    printf("inside recive callback data recived");
    data_recived = data;
}
void send_task(void*p)
{
    char *r;
    if (xQueueReceive(console_to_espnow_send, &r, portMAX_DELAY) != pdTRUE)
    {
        ESP_LOGI(TAG, "failed to recive from the queue");
    }
    ESP_LOGI(TAG, "the message recived form console is ::: %s ::", r);
    char send_buffer[250];
    memcpy(send_buffer, r, 100);
    while (1)
    {
        ESP_ERROR_CHECK(esp_now_send(NULL, (uint8_t *)send_buffer, strlen(send_buffer)));
        printf("send done probably\n");
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}
void recive_task(void*p)
{
    while (1)
    {
        char buffer[13];
        // ESP_LOGI(TAG, "got message from %s", mac_to_str(buffer, (uint8_t *)mac_addr));
        if(data_len_recived != 0)
        {
            printf("message: %.*s\n", data_len_recived, data_recived);
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void espnow_start(void)
{

    uint8_t my_mac[6];
    esp_efuse_mac_get_default(my_mac);
    // char my_mac_str[13];
    // ESP_LOGI(TAG, "My mac %s", mac_to_str(my_mac_str, my_mac));
    bool is_current_esp1 = memcmp(my_mac, esp_1, 6) == 0;
    uint8_t *peer_mac = is_current_esp1 ? esp_2 : esp_1;

    nvs_flash_init();
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_send_cb(on_sent));
    ESP_ERROR_CHECK(esp_now_register_recv_cb(on_receive));
    esp_now_peer_info_t peer;
    memset(&peer, 0, sizeof(esp_now_peer_info_t));
    memcpy(peer.peer_addr, peer_mac, 6);
    esp_now_add_peer(&peer);

    xTaskCreate(
        send_task,
        "send_task",
        4096,
        NULL,
        4,
        &send_task_handle);
    xTaskCreate(
        recive_task,
        "recive_task",
        4096,
        NULL,
        4,
        &recive_task_handle);

    // ESP_ERROR_CHECK(esp_now_deinit());
    // ESP_ERROR_CHECK(esp_wifi_stop());
}