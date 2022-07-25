# esp_box_opl3

https://github.com/skiphansen/esp_box_opl3

This was an experiment with running an opl2/opl3 software emulator on an esp32
processor. Specifically the ESP32-S3 based [esp-box](https://github.com/espressif/esp-box).

<img src="https://github.com/espressif/esp-box/blob/master/docs/_static/esp32_s3_box.png" width="200px" />

When I started this experiment I didn't notice that the woody-opl emulator
used double precision floating point.  Since the ESP32 S3 processor only 
has hardware floating for single precision floating point double precision 
floating operations are emulated in software and are very slow.  

This branch configures woody-opl to use float instead of double for the 
floating point calculations so that the ESP32 processors hardware floating 
will be used.

The profiling code shows that woody-opl is generating on average 52k 
sample/sec while playing doom_000.dro.

## Building

1. Install esp-idf version 4.4 or later.
2. Clone this repository.
3. Change directory into esp_box_opl3.
4. Run idf.py build.

````
skip@Dell-7040:~$ git clone https://github.com/skiphansen/esp_box_opl3.git
Cloning into 'esp_box_opl3'...
remote: Enumerating objects: 51, done.
remote: Counting objects: 100% (51/51), done.
remote: Compressing objects: 100% (40/40), done.
remote: Total 51 (delta 11), reused 51 (delta 11), pack-reused 0
Unpacking objects: 100% (51/51), 812.69 KiB | 2.59 MiB/s, done.
skip@Dell-7040:~$ cd esp_box_opl3/
skip@Dell-7040:~/esp_box_opl3$ idf.py build
[Lots of output deleted]

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

## Acknowledgement and Thanks
This project uses code from several other projects including:
 - [esp-box BSP and example code](https://github.com/espressif/esp-box.git)
 - [Woody opl2/opl3 emulator](https://github.com/rofl0r/woody-opl.git)
 - [Greg Taylor's DRO sample files](https://github.com/gtaylormb/opl3_fpga)

