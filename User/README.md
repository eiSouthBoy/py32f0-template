# PY32F002B IAP_APP Firmware v0.0.1

I am very grateful to IOsetting and nicekwell for their open source projects, which enabled me to develop the second one.


environment:
- OS: Ubuntu 22.04.5 LTS
- gcc: arm-none-eabi-gcc (Arm GNU Toolchain 12.2.MPACBTI-Rel1 (Build arm-12-mpacbti.34)) 12.2.1 20230214
- Board: 野火_普冉PY32F002BF15U6TR核心板_原理图_V1.0
- Isp Tool: [stm32ISP](https://github.com/nicekwell/stm32ISP) 

> Note: 
> 1. This Isp tool (stm32ISP) cannot be used directly for PY32F002B, and the code needs to be modified for adaptation. Of course, you can also use the PY32 official ISP tool (PY32IspTool)
> 2. [PY32F002B IAP Docs](https://www.puyasemi.com/download_path/%E5%B7%A5%E5%85%B7/MCU%20%E5%BE%AE%E5%A4%84%E7%90%86%E5%99%A8/PY32F002B_IAP_APP_Firmware_V0.0.1.zip)

## configuration

1. copy project file

```bash
cp -r ${workspaceFolder}/Examples/PY32F002B/IAP_APP/IAP/* ${workspaceFolder}/User
```

2. comment file content

file path: 
- `${workspaceFolder}/Libraries/PY32F002B_LL_BSP/Inc/py32f002b_bsp_printf.h`
- `${workspaceFolder}/Libraries/PY32F002B_LL_BSP/Inc/py32f002b_bsp_printf.c`


change content:
- comment BSP_USART_Config(uint32_t baudRate) declaration in py32f002b_bsp_printf.h
- comment BSP_USART_Config(uint32_t baudRate) definition py32f002b_bsp_printf.c

3. modify system_py32f002b.c

file path: `${workspaceFolder}/Libraries/CMSIS/Device/PY32F0xx/Source/system_py32f002b.c`

file change:
```bash
diff --git a/Libraries/CMSIS/Device/PY32F0xx/Source/system_py32f002b.c b/Libraries/CMSIS/Device/PY32F0xx/Source/system_py32f002b.c
index 4087259..a8a7837 100644
--- a/Libraries/CMSIS/Device/PY32F0xx/Source/system_py32f002b.c
+++ b/Libraries/CMSIS/Device/PY32F0xx/Source/system_py32f002b.c
@@ -62,15 +62,16 @@
 */
 uint32_t SystemCoreClock = HSI_VALUE;
 
-const uint32_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
-const uint32_t APBPrescTable[8] =  {0, 0, 0, 0, 1, 2, 3, 4};
-#if defined(RCC_HSI48M_SUPPORT)
-const uint32_t HSIFreqTable[8] = {0U, 0U, 0U, 0U, 24000000U, 48000000U, 0U, 0U};
-#else
-const uint32_t HSIFreqTable[8] = {0U, 0U, 0U, 0U, 24000000U, 0U, 0U, 0U};
-#endif
+// const uint32_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};^M
+// const uint32_t APBPrescTable[8] =  {0, 0, 0, 0, 1, 2, 3, 4};^M
+// #if defined(RCC_HSI48M_SUPPORT)^M
+// const uint32_t HSIFreqTable[8] = {0U, 0U, 0U, 0U, 24000000U, 48000000U, 0U, 0U};^M
+// #else^M
+// const uint32_t HSIFreqTable[8] = {0U, 0U, 0U, 0U, 24000000U, 0U, 0U, 0U};^M
+// #endif^M
 
 /* Private function prototypes -----------------------------------------------*/
+#define SWD_DELAY^M
 #ifndef SWD_DELAY
 static void DelayTime(uint32_t mdelay);
 #endif /* SWD_DELAY */
@@ -80,40 +81,40 @@ static void DelayTime(uint32_t mdelay);
  * @param  none
  * @return none
  */
-void SystemCoreClockUpdate(void)             /* Get Core Clock Frequency      */
-{
-  uint32_t tmp;
-  uint32_t hsidiv;
-  uint32_t hsifs;
-
-  /* Get SYSCLK source -------------------------------------------------------*/
-  switch (RCC->CFGR & RCC_CFGR_SWS)
-  {
-  case RCC_CFGR_SWS_0:  /* HSE used as system clock */
-    SystemCoreClock = HSE_VALUE;
-    break;
-
-  case (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0):  /* LSI used as system clock */
-    SystemCoreClock = LSI_VALUE;
-    break;
-#if defined(RCC_LSE_SUPPORT)
-  case RCC_CFGR_SWS_2:  /* LSE used as system clock */
-    SystemCoreClock = LSE_VALUE;
-    break;
-#endif /* RCC_LSE_SUPPORT */
-  case 0x00000000U:  /* HSI used as system clock */
-  default:                /* HSI used as system clock */
-    hsifs = ((READ_BIT(RCC->ICSCR, RCC_ICSCR_HSI_FS)) >> RCC_ICSCR_HSI_FS_Pos);
-    hsidiv = (1UL << ((READ_BIT(RCC->CR, RCC_CR_HSIDIV)) >> RCC_CR_HSIDIV_Pos));
-    SystemCoreClock = (HSIFreqTable[hsifs] / hsidiv);
-    break;
-  }
-  /* Compute HCLK clock frequency --------------------------------------------*/
-  /* Get HCLK prescaler */
-  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos)];
-  /* HCLK clock frequency */
-  SystemCoreClock >>= tmp;
-}
+// void SystemCoreClockUpdate(void)             /* Get Core Clock Frequency      */^M
+// {^M
+//   uint32_t tmp;^M
+//   uint32_t hsidiv;^M
+//   uint32_t hsifs;^M
+^M
+//   /* Get SYSCLK source -------------------------------------------------------*/^M
+//   switch (RCC->CFGR & RCC_CFGR_SWS)^M
+//   {^M
+//   case RCC_CFGR_SWS_0:  /* HSE used as system clock */^M
+//     SystemCoreClock = HSE_VALUE;^M
+//     break;^M
+^M
+//   case (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0):  /* LSI used as system clock */^M
+//     SystemCoreClock = LSI_VALUE;^M
+//     break;^M
+// #if defined(RCC_LSE_SUPPORT)^M
+//   case RCC_CFGR_SWS_2:  /* LSE used as system clock */^M
+//     SystemCoreClock = LSE_VALUE;^M
+//     break;^M
+// #endif /* RCC_LSE_SUPPORT */^M
+//   case 0x00000000U:  /* HSI used as system clock */^M
+//   default:                /* HSI used as system clock */^M
+//     hsifs = ((READ_BIT(RCC->ICSCR, RCC_ICSCR_HSI_FS)) >> RCC_ICSCR_HSI_FS_Pos);^M
+//     hsidiv = (1UL << ((READ_BIT(RCC->CR, RCC_CR_HSIDIV)) >> RCC_CR_HSIDIV_Pos));^M
+//     SystemCoreClock = (HSIFreqTable[hsifs] / hsidiv);^M
+//     break;^M
+//   }^M
+//   /* Compute HCLK clock frequency --------------------------------------------*/^M
+//   /* Get HCLK prescaler */^M
+//   tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos)];^M
+//   /* HCLK clock frequency */^M
+//   SystemCoreClock >>= tmp;^M
+// }^M
 
 /**
  * @brief  Setup the microcontroller system.
```

4. modify Makefile

file path: `${workspaceFolder}/Makefile`
```bash
##### Project #####

PROJECT			?= iap

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
  CC    User/flash.c
  CC    User/main.c
  CC    User/bootloader.c
  CC    User/wdg.c
  CC    User/py32f002b_it.c
  CC    User/usart.c
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
  LD    Libraries/LDScripts/py32f002bx5.ld -> Build/iap.elf
Memory region         Used Size  Region Size  %age Used
             RAM:        1192 B         3 KB     38.80%
           FLASH:        2960 B        24 KB     12.04%
  OBJCP BIN     Build/iap.bin
  OBJCP HEX     Build/iap.hex
  OBJDP LST     Build/iap.lst
```

flash log:
```bash
zh@ubuntu-z:~/py32/py32-example$ make flash
pyocd erase -t py32f002bx5 --chip --config ./Misc/pyocd.yaml
0000339 I Erasing chip... [eraser]
0000535 I Chip erase complete [eraser]
pyocd load Build/iap.elf -t py32f002bx5 --config ./Misc/pyocd.yaml
0000351 I Loading /home/zh/py32/py32-example/Build/iap.elf [load_cmd]
[==================================================] 100%
0002032 I Erased 4096 bytes (1 sector), programmed 3072 bytes (24 pages), skipped 0 bytes (0 pages) at 1.79 kB/s [loader]
```

stm32ISP log:
```bash
zh@ubuntu-z:~/Downloads/stm32ISP$ ./stm32isp /dev/ttyUSB0 app1_0x08001000.bin
syncing...sync ok
get bootloader version: 10
get 6 supported commands: 00 02 11 21 31 44 
get PID: 0064
erasing flash...
erase flash done
starting download...
writing address: 08001000
writing address: 08001100
writing address: 08001200
writing address: 08001300
writing address: 08001400
writing address: 08001500
writing address: 08001600
download success
starting verify...
verifying address: 08001000
verifying address: 08001100
verifying address: 08001200
verifying address: 08001300
verifying address: 08001400
verifying address: 08001500
verifying address: 08001600
verify success
use 1.00 s

```
