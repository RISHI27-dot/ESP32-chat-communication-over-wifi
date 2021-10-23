
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"

xQueueHandle console_to_espnow_send;
void task_console();
TaskHandle_t console;