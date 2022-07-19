# esp_box_opl3

https://github.com/skiphansen/esp_box_opl3

This was an experiment with running an opl2/opl3 software emulator on an esp32
processor. Specifically the ESP32-S3 based [esp-box](https://github.com/espressif/esp-box).

<img src="https://github.com/espressif/esp-box/blob/master/docs/_static/esp32_s3_box.png" width="200px" />

While the experiment was successful in the terms of "working" it's a bit of a 
disappointment since I was only able to achieve a 8Khz sampling rate.  

When I started this experiment I didn't notice that the woody-opl emulator
used double precision floating point.  Since the ESP32 S3 processor only 
has hardware floating for single precision floating point double precision 
floating operations are emulated in software and are very slow.  

## Building

1. Install esp-idf version 4.4 or later.
2. Clone this repository.
3. Change directory into esp_box_opl3.
4. Update the submodules (git submodule init;git submodule update).
5. Run idf.py build.

````
skip@Dell-7040:~$ git clone https://github.com/skiphansen/esp_box_opl3.git
Cloning into 'esp_box_opl3'...
remote: Enumerating objects: 51, done.
remote: Counting objects: 100% (51/51), done.
remote: Compressing objects: 100% (40/40), done.
remote: Total 51 (delta 11), reused 51 (delta 11), pack-reused 0
Unpacking objects: 100% (51/51), 812.69 KiB | 2.59 MiB/s, done.
skip@Dell-7040:~$ cd esp_box_opl3/
skip@Dell-7040:~/esp_box_opl3$ git submodule init
Submodule 'esp-box' (https://github.com/espressif/esp-box.git) registered for path 'esp-box'
Submodule 'woody-opl' (https://github.com/rofl0r/woody-opl.git) registered for path 'woody-opl'
skip@Dell-7040:~/esp_box_opl3$ git submodule update
Cloning into '/home/skip/esp_box_opl3/esp-box'...
Cloning into '/home/skip/esp_box_opl3/woody-opl'...
Submodule path 'esp-box': checked out 'db4453e78c4742cadf871b4ab67e74cc0062a1af'
Submodule path 'woody-opl': checked out 'c3f6674e4394fd9a83fe52722cfc63e1a9a8e29c'
skip@Dell-7040:~/esp_box_opl3$ idf.py build
Executing action: all (aliases: build)
Running cmake in directory /home/skip/esp_box_opl3/build
Executing "cmake -G Ninja -DPYTHON_DEPS_CHECKED=1 -DESP_PLATFORM=1 -DIDF_TARGET=esp32s3 -DCCACHE_ENABLE=0 /home/skip/esp_box_opl3"...
-- Found Git: /usr/bin/git (found version "2.25.1") 
-- The C compiler identification is GNU 8.4.0
-- The CXX compiler identification is GNU 8.4.0
...
[Lots of output deleted]
...
esp32_opl3.bin binary size 0x4a320 bytes. Smallest app partition is 0x180000 bytes. 0x135ce0 bytes (81%) free.

Project build complete. To flash, run this command:
/home/skip/.espressif/python_env/idf4.4_py3.8_env/bin/python ../esp/esp-idf/components/esptool_py/esptool/esptool.py -p /dev/ttyACM0 -b 460800 --before default_reset --after hard_reset --chip esp32s3 --no-stub write_flash --flash_mode dio --flash_size detect --flash_freq 80m 0x0 build/bootloader/bootloader.bin 0x8000 build/partition_table/partition-table.bin 0x10000 build/esp32_opl3.bin 0x190000 build/storage.bin
or run 'idf.py -p /dev/ttyACM0 flash'
skip@Dell-7040:~/esp_box_opl3$ 
````

## Running

Flash the esp-box in the usual way (idf.py flash monitor).
The code will play doom_000.dro from flash and then stop.  

There are lots of other DRO files which are copied to flash which are not 
played currently.  

When I discovered that I couldn't achieve a reasonable sampling rate with a 
reasonable CPU load I stopped development.

## Acknowledgement and Thanks
This project uses code from several other projects including:
 - [esp-box BSP and example code](https://github.com/espressif/esp-box.git)
 - [Woody opl2/opl3 emulator](https://github.com/rofl0r/woody-opl.git)
 - [Greg Taylor's DRO sample files](https://github.com/gtaylormb/opl3_fpga)

