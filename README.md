
# Cloning

If you want to use the ST HAL as a submodule then do a recursive clone (`--recursive`)

If you want to use the HAL installed when using STCubeIDE then modify the `CMakeLists.txt` file, from
```
# set(STM32Cube_PATH $ENV{HOME}/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.1)
set(STM32Cube_PATH ${CMAKE_SOURCE_DIR}/Drivers/STM32CubeH7)
```

to
```
set(STM32Cube_PATH $ENV{HOME}/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.1)
# set(STM32Cube_PATH ${CMAKE_SOURCE_DIR}/Drivers/STM32CubeH7)
```

Ths assumes the HAL has been installed at the default location, and is version 1.11.1

# Building

The build shell script uses CMake and Ninja. It assumes these are in the current PATH

```
$ ./build.sh
```

# Flashing the target

## st-flash

```
st-flash write ./Debug/StmTextCMake.elf 0x08000000
```

## OpenOCD

```
openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c "program ./Debug/StmTextCMake.elf reset exit"
```

## st-util/gdb

* Launch **st-util** in a terminal window. This command will start the `st-util` server:
```
$ st-util
```

* Open another terminal window and navigate to the directory containing the binary file you want to flash.
* Use **arm-none-eabi-gdb** to connect to the st-util server and flash your binary. Here's an example command:

```
arm-none-eabi-gdb ./Debug/StmTextCMake.elf
```


* In the **arm-none-eabi-gdb** prompt, connect to the server with the following command:
```
target extended-remote :4242
```

* Load the binary file and flash it to the board:
```
(gdb) load
Loading section .isr_vector, size 0x2cc lma 0x8000000
Loading section .text, size 0xa7644 lma 0x80002d0
Loading section .rodata, size 0x31920 lma 0x80a7920
Loading section .ARM.extab, size 0x79d8 lma 0x80d9240
Loading section .ARM, size 0x65c0 lma 0x80e0c18
Loading section .init_array, size 0xc lma 0x80e71d8
Loading section .fini_array, size 0x4 lma 0x80e71e4
Loading section .data, size 0x254 lma 0x80e71e8
Start address 0x08075304, load size 947244
Transfer rate: 37 KB/sec, 14800 bytes/write.
(gdb) 
```

* This will flash the target; you should see (in the st-util window) something similar to:
```
st-util
2023-10-30T13:22:51 INFO usb.c: Unable to match requested speed 1800 kHz, using 1000 kHz
2023-10-30T13:22:51 INFO common.c: H72x/H73x: 128 KiB SRAM, 1024 KiB flash in at least 128 KiB pages.
2023-10-30T13:22:51 INFO gdb-server.c: Listening at *:4242...
2023-10-30T13:23:22 INFO common.c: H72x/H73x: 128 KiB SRAM, 1024 KiB flash in at least 128 KiB pages.
2023-10-30T13:23:22 INFO gdb-server.c: Found 8 hw breakpoint registers
2023-10-30T13:23:22 INFO gdb-server.c: Chip clidr: 09000003, I-Cache: on, D-Cache: on
2023-10-30T13:23:22 INFO gdb-server.c:  cache: LoUU: 1, LoC: 1, LoUIS: 0
2023-10-30T13:23:22 INFO gdb-server.c:  cache: ctr: 8303c003, DminLine: 32 bytes, IminLine: 32 bytes
2023-10-30T13:23:22 INFO gdb-server.c: D-Cache L0: 2023-10-30T13:23:22 INFO gdb-server.c: f01fe019 LineSize: 8, ways: 4, sets: 256 (width: 13)
2023-10-30T13:23:22 INFO gdb-server.c: I-Cache L0: 2023-10-30T13:23:22 INFO gdb-server.c: f03fe009 LineSize: 8, ways: 2, sets: 512 (width: 14)
2023-10-30T13:23:22 INFO gdb-server.c: GDB connected.
2023-10-30T13:23:29 INFO common.c: H72x/H73x: 128 KiB SRAM, 1024 KiB flash in at least 128 KiB pages.
2023-10-30T13:23:29 INFO gdb-server.c: flash_erase: block 08000000 -> 100000
2023-10-30T13:23:29 INFO gdb-server.c: flash_erase: page 08000000
2023-10-30T13:23:30 INFO gdb-server.c: flash_erase: page 08020000
2023-10-30T13:23:31 INFO gdb-server.c: flash_erase: page 08040000
2023-10-30T13:23:32 INFO gdb-server.c: flash_erase: page 08060000
2023-10-30T13:23:33 INFO gdb-server.c: flash_erase: page 08080000
2023-10-30T13:23:33 INFO gdb-server.c: flash_erase: page 080a0000
2023-10-30T13:23:34 INFO gdb-server.c: flash_erase: page 080c0000
2023-10-30T13:23:35 INFO gdb-server.c: flash_erase: page 080e0000
2023-10-30T13:23:36 INFO common.c: Starting Flash write for H7
2023-10-30T13:23:36 INFO gdb-server.c: flash_do: block 08000000 -> 100000
2023-10-30T13:23:36 INFO gdb-server.c: flash_do: page 08000000
2023-10-30T13:23:38 INFO gdb-server.c: flash_do: page 08020000
2023-10-30T13:23:41 INFO gdb-server.c: flash_do: page 08040000
2023-10-30T13:23:43 INFO gdb-server.c: flash_do: page 08060000
2023-10-30T13:23:45 INFO gdb-server.c: flash_do: page 08080000
2023-10-30T13:23:47 INFO gdb-server.c: flash_do: page 080a0000
2023-10-30T13:23:49 INFO gdb-server.c: flash_do: page 080c0000
2023-10-30T13:23:51 INFO gdb-server.c: flash_do: page 080e0000
```

* You can use other GDB commands to debug or monitor the execution of your firmware. To run the program, in the GDB window type:
```
(gdb) c
```

Please note that the exact commands might vary slightly depending on your specific setup and the file you are trying to flash. Ensure that the paths and filenames provided are accurate.

Always refer to the official documentation for st-util and the STM32H735 for the most up-to-date information.

This has been tested on
* MacOS running Somona 14.1 (23B74)
    * gcc version 12.3.1 20230626 (Arm GNU Toolchain 12.3.Rel1 (Build arm-12.35)) 
    * cmake version 3.23.5
    * ninja version 1.11.1