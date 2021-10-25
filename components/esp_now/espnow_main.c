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
char buffer[250];
char send_buffer[250];
uint8_t esp_2[6] = {0xc4, 0xdd, 0x57, 0x5b, 0xf3, 0x84}; //my esp
uint8_t esp_1[6] = {0xec, 0x94, 0xcb, 0x66, 0x68, 0xcc};

uint8_t *data_g;
int len_g = 0;
TaskHandle_t send;
TaskHandle_t recv;
char *r;
char *mac_to_str(char *buffer, uint8_t *mac)
{
    sprintf(buffer, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return buffer;
}

void espnow_task_recv(void)
{
    if (len_g != 0)
    {
        printf("\nReceived: %.*s\n", len_g, data_g);
    }
    vTaskDelete(recv);
}
static void espnow_task_send(void)
{
    ESP_ERROR_CHECK(esp_now_send(NULL, (uint8_t *)send_buffer, strlen(send_buffer)));
    vTaskDelay(pdMS_TO_TICKS(1000));

    vTaskDelete(send);
}
void on_sent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    vTaskResume(console);
}

void on_receive(const uint8_t *mac_addr, const uint8_t *data, int len)
{

    data_g = data;
    len_g = len;
    xTaskCreate(espnow_task_recv, "espnow_task_recv", 5000, NULL, 5, &recv);
}
void espnow_start(void)
{
    if (xQueueReceive(console_to_espnow_send, &r, portMAX_DELAY) != pdTRUE)
    {
        ESP_LOGI(TAG, "failed to receive from the queue");
    }
    memcpy(send_buffer, r, 100);
    xTaskCreate(espnow_task_send, "espnow_task_send", 5000, NULL, 5, &send);
}
void espnowinit(void)
{
    uint8_t my_mac[6];
    esp_efuse_mac_get_default(my_mac);
    char my_mac_str[13];
    ESP_LOGI(TAG, "My mac %s", mac_to_str(my_mac_str, my_mac));
    bool is_current_esp1 = memcmp(my_mac, esp_1, 6) == 0;
    uint8_t *peer_mac = is_current_esp1 ? esp_2 : esp_1;
    //initialize wifi in default configuration
    nvs_flash_init();
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    //initialize espnow 
    ESP_ERROR_CHECK(esp_now_init());
    //register send and recive callback function
    ESP_ERROR_CHECK(esp_now_register_send_cb(on_sent));
    ESP_ERROR_CHECK(esp_now_register_recv_cb(on_receive));
    //setup the peer list 
    esp_now_peer_info_t peer;
    memset(&peer, 0, sizeof(esp_now_peer_info_t));
    memcpy(peer.peer_addr, peer_mac, 6);
    esp_now_add_peer(&peer);
}
