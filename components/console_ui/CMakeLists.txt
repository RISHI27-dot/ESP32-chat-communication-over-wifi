idf_component_register(SRCS "cmd_wifi.c"
                            "console_example_main.c"
                            "cmd_system.c"
                    REQUIRES console nvs_flash
                    INCLUDE_DIRS ".")
