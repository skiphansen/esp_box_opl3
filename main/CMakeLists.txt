idf_component_register(
    SRCS "esp32_opl3.c"
)

spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)

