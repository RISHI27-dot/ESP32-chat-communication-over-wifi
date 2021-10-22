/* Console example — various system commands

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "esp_log.h"
#include "esp_console.h"
#include "esp_system.h"
#include "esp_sleep.h"
#include "esp_spi_flash.h"
#include "driver/rtc_io.h"
#include "driver/uart.h"
#include "argtable3/argtable3.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cmd_system.h"
#include "sdkconfig.h"
#include "data_transfer.h"
#include "chat_espnow.h"

#ifdef CONFIG_FREERTOS_USE_STATS_FORMATTING_FUNCTIONS
#define WITH_TASKS_INFO 1
#endif

static const char *TAG = "cmd_system";
static void register_restart(void);
static void register_espnow_send(void);
static void register_initialize_chat(void);

#if WITH_TASKS_INFO
static void register_tasks(void);
#endif

void register_system(void)
{
    register_restart();
    register_espnow_send();
    register_initialize_chat();
#if WITH_TASKS_INFO
    register_tasks();
#endif
}
/** 'restart' command restarts the program */
static int restart(int argc, char **argv)
{
    ESP_LOGI(TAG, "Restarting");
    esp_restart();
}

static void register_restart(void)
{
    const esp_console_cmd_t cmd = {
        .command = "restart",
        .help = "Software reset of the chip",
        .hint = NULL,
        .func = &restart,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd));
}

/*initialize chat system*/
void start_chat_communication(void)
{
    espnow_start();
    while (1)
    {
        char line[50];
        scanf("%s", line);
        printf("the messagae you entered is %s\n", line);
        if (xQueueSend(console_to_espnow_send, &line, portMAX_DELAY) != pdTRUE)
        {
            ESP_LOGW(TAG, "Send data to esp now failed.........");
        }
        ESP_LOGI(TAG, "data sent to espnow is %s", line);
    }
}
static void register_initialize_chat(void)
{
    const esp_console_cmd_t start_chat = {
        .command = "start",
        .help = "starts the chat system..",
        .hint = NULL,
        .func = &start_chat_communication,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&start_chat));
}
/*send the chat form console to esp now commandS*/
static int espnow_send(int argc, char **argv)
{
    // printf("the argc is : %d and the argv1 is %s",argc,argv[1]);
    char *asdf = argv[1];
    if (xQueueSend(console_to_espnow_send, &asdf, portMAX_DELAY) != pdTRUE)
    {
        ESP_LOGW(TAG, "Send data to esp now failed.........");
    }
    ESP_LOGI(TAG, "data sent to espnow is %s", asdf);
    espnow_start();
    return 0;
}
static void register_espnow_send(void)
{
    const esp_console_cmd_t espnow_send_cmd = {
        .command = "send",
        .help = "send data to esp now",
        .hint = NULL,
        .func = &espnow_send,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&espnow_send_cmd));
}

/** 'tasks' command prints the list of tasks and related information */
#if WITH_TASKS_INFO

static int tasks_info(int argc, char **argv)
{
    const size_t bytes_per_task = 40; /* see vTaskList description */
    char *task_list_buffer = malloc(uxTaskGetNumberOfTasks() * bytes_per_task);
    if (task_list_buffer == NULL)
    {
        ESP_LOGE(TAG, "failed to allocate buffer for vTaskList output");
        return 1;
    }
    fputs("Task Name\tStatus\tPrio\tHWM\tTask#", stdout);
#ifdef CONFIG_FREERTOS_VTASKLIST_INCLUDE_COREID
    fputs("\tAffinity", stdout);
#endif
    fputs("\n", stdout);
    vTaskList(task_list_buffer);
    fputs(task_list_buffer, stdout);
    free(task_list_buffer);
    return 0;
}

static void register_tasks(void)
{
    const esp_console_cmd_t cmd = {
        .command = "tasks",
        .help = "Get information about running tasks",
        .hint = NULL,
        .func = &tasks_info,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&cmd));
}
#endif
