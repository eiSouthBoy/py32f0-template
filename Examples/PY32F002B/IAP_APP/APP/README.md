# PY32F002B IAP_APP Firmware v0.0.1


## configuration

1. copy project file

```bash
cp -r ${workspaceFolder}/Examples/PY32F002B/IAP_APP/APP/* ${workspaceFolder}/User
```

2. comment file content

file path: 
- `${workspaceFolder}/Libraries/PY32F002B_LL_BSP/Inc/py32f002b_bsp_printf.h`
- `${workspaceFolder}/Libraries/PY32F002B_LL_BSP/Inc/py32f002b_bsp_printf.c`


change content:
- comment BSP_USART_Config(uint32_t baudRate) declaration in py32f002b_bsp_printf.h
- comment BSP_USART_Config(uint32_t baudRate) definition py32f002b_bsp_printf.c


3. modify py32f002bx5.ld

file path: `${workspaceFolder}/Libraries/LDScripts/py32f002bx5.ld`

change content:
- `ORIGIN = 0x08000000` to `ORIGIN = 0x08001000` 
- `LENGTH = 24K` to `LENGTH = 20K`

```bash
/* Specify the memory areas */
MEMORY
{
  RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 3K
  FLASH (rx)     : ORIGIN = 0x08001000, LENGTH = 20K
}
```

4. modify Makefile

file path: `${workspaceFolder}/Makefile`
```bash
# MCU types: 
MCU_TYPE		= PY32F002Bx5

# Use LL library instead of HAL, y:yes, n:no
USE_LL_LIB ?= y

```

## build and flash

build log:
```bash
zh@ubuntu-z:~/py32/py32-example$ make clean && make
rm -rf ./Build/*
  CC    User/main.c
  CC    User/py32f002b_it.c
  CC    User/py32f002bxx_ll_Start_Kit.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_crc.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_adc.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_rcc.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_flash.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_exti.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_usart.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_pwr.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_tim.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_i2c.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_lptim.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_utils.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_gpio.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_spi.c
  CC    Libraries/PY32F002B_LL_Driver/Src/py32f002b_ll_comp.c
  CC    Libraries/PY32F002B_LL_BSP/Src/py32f002b_bsp_printf.c
  CC    Libraries/PY32F002B_LL_BSP/Src/py32f002b_bsp_clock.c
  CC    Libraries/CMSIS/Device/PY32F0xx/Source/system_py32f002b.c
  AS    Libraries/CMSIS/Device/PY32F0xx/Source/gcc/startup_py32f002b.s
  LD    Libraries/LDScripts/py32f002bx5.ld -> Build/app.elf
Memory region         Used Size  Region Size  %age Used
             RAM:         808 B         3 KB     26.30%
           FLASH:        1716 B        20 KB      8.38%
  OBJCP BIN     Build/app.bin
  OBJCP HEX     Build/app.hex
  OBJDP LST     Build/app.lst
```

flash log:
```bash
zh@ubuntu-z:~/py32/py32-example$ make flash
pyocd erase -t py32f002bx5 --chip --config ./Misc/pyocd.yaml
0000346 I Erasing chip... [eraser]
0000536 I Chip erase complete [eraser]
pyocd load Build/app.elf -t py32f002bx5 --config ./Misc/pyocd.yaml
0000325 I Loading /home/zh/py32/py32-example/Build/app.elf [load_cmd]
[==================================================] 100%
0001449 I Erased 4096 bytes (1 sector), programmed 1792 bytes (14 pages), skipped 0 bytes (0 pages) at 1.56 kB/s [loader]
```
