idf_component_register(
    SRCS "esp32_opl3.c" "../woody-opl/opl.c" "imfplay.c"
    INCLUDE_DIRS "../woody-opl"
)

spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)

