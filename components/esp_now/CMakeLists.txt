idf_component_register(SRCS "espnow_main.c"
                    INCLUDE_DIRS "."
                    REQUIRES console esp_wifi nvs_flash cmd_system)
