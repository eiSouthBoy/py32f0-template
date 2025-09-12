# ws2812

## configuration

1. copy project file

```bash
cp -r ${workspaceFolder}/Examples/PY32F002B/HAL/WS2812/* ${workspaceFolder}/User
```

2. modify py32f002b_bsp_printf.h

file path: 
- `Libraries/PY32F002B_HAL_BSP/Inc/py32f002b_bsp_printf.h`
- `Libraries/PY32F002B_HAL_BSP/Inc/py32f002b_bsp_printf.c`

py32f002b_bsp_printf.h change content:
```bash
diff --git a/Libraries/PY32F002B_HAL_BSP/Inc/py32f002b_bsp_printf.h b/Libraries/PY32F002B_HAL_BSP/Inc/py32f002b_bsp_printf.h
index 6c54a4a..c8f1900 100644
--- a/Libraries/PY32F002B_HAL_BSP/Inc/py32f002b_bsp_printf.h
+++ b/Libraries/PY32F002B_HAL_BSP/Inc/py32f002b_bsp_printf.h
@@ -42,12 +42,12 @@ extern "C" {
 
 #define DEBUG_USART_RX_GPIO_PORT                GPIOA
 #define DEBUG_USART_RX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
-#define DEBUG_USART_RX_PIN                      GPIO_PIN_3
+#define DEBUG_USART_RX_PIN                      GPIO_PIN_4
 #define DEBUG_USART_RX_AF                       GPIO_AF1_USART1
 
 #define DEBUG_USART_TX_GPIO_PORT                GPIOA
 #define DEBUG_USART_TX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
-#define DEBUG_USART_TX_PIN                      GPIO_PIN_2
+#define DEBUG_USART_TX_PIN                      GPIO_PIN_3
 #define DEBUG_USART_TX_AF                       GPIO_AF1_USART1
 
 #define DEBUG_USART_IRQHandler                  USART1_IRQHandler
```

py32f002b_bsp_printf.c change content:
```bash
diff --git a/Libraries/PY32F002B_HAL_BSP/Src/py32f002b_bsp_printf.c b/Libraries/PY32F002B_HAL_BSP/Src/py32f002b_bsp_printf.c
index 6dba40d..26e445d 100644
--- a/Libraries/PY32F002B_HAL_BSP/Src/py32f002b_bsp_printf.c
+++ b/Libraries/PY32F002B_HAL_BSP/Src/py32f002b_bsp_printf.c
@@ -32,8 +32,8 @@ void BSP_USART_Config(void)
   DEBUG_USART_TX_GPIO_CLK_ENABLE();
 
   /**USART GPIO Configuration
-    PA2     ------> USART2_TX
-    PA3     ------> USART2_RX
+    PA3     ------> USART1_TX
+    PA4     ------> USART1_RX
     */
   GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN;
   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
```


3. modify Makefile

file path: `${workspaceFolder}/Makefile`
```bash
# MCU types: 
MCU_TYPE		= PY32F002Bx5
```

## build and flash

build log:
```bash
zh@ubuntu-z:~/py32/py32-example$ make clean && make
rm -rf ./Build/*
  CC    User/main.c
User/main.c:115:13: warning: 'led_rgb_cycle_change' defined but not used [-Wunused-function]
  115 | static void led_rgb_cycle_change(void)
      |             ^~~~~~~~~~~~~~~~~~~~
  CC    User/ws2812_spi.c
  CC    User/py32f002b_hal_msp.c
  CC    User/py32f002b_it.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_rcc.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_pwr.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_exti.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_rcc_ex.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_cortex.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_comp.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_tim.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_tim_ex.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_spi.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_iwdg.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_crc.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_gpio.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_flash.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_i2c.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_usart.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_adc.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_uart.c
  CC    Libraries/PY32F002B_HAL_Driver/Src/py32f002b_hal_lptim.c
  CC    Libraries/PY32F002B_HAL_BSP/Src/py32f002b_bsp_printf.c
  CC    Libraries/PY32F002B_HAL_BSP/Src/py32f002b_bsp_clock.c
  CC    Libraries/CMSIS/Device/PY32F0xx/Source/system_py32f002b.c
  AS    Libraries/CMSIS/Device/PY32F0xx/Source/gcc/startup_py32f002b.s
  LD    Libraries/LDScripts/py32f002bx5.ld -> Build/app.elf
Memory region         Used Size  Region Size  %age Used
             RAM:        1536 B         3 KB     50.00%
           FLASH:       10064 B        24 KB     40.95%
  OBJCP BIN     Build/app.bin
  OBJCP HEX     Build/app.hex
  OBJDP LST     Build/app.lst
```

flash log:
```bash
zh@ubuntu-z:~/py32/py32-example$ make flash
pyocd erase -t py32f002bx5 --chip --config ./Misc/pyocd.yaml
0000312 I Erasing chip... [eraser]
0000490 I Chip erase complete [eraser]
pyocd load Build/app.elf -t py32f002bx5 --config ./Misc/pyocd.yaml
0000322 I Loading /home/zh/py32/py32-example/Build/app.elf [load_cmd]
[==================================================] 100%
0004568 I Erased 12288 bytes (3 sectors), programmed 10112 bytes (79 pages), skipped 0 bytes (0 pages) at 2.33 kB/s [loader]
```