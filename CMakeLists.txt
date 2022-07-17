cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(EXTRA_COMPONENT_DIRS 
        esp-box/components/bsp 
        esp-box/components/iot_button 
        esp-box/components/i2c_bus
        esp-box/components/i2c_devices
)

project(esp32_opl3)
