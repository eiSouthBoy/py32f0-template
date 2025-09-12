/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "py32f002b_bsp_printf.h"
#include "py32f002b_bsp_clock.h"
#include "ws2812_spi.h"

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef Spi1Handle = {0};
/* Private user code ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void APP_SPI_Config(void);
static void led_rgb_cycle_change(void);
static void led_rgb_marquee_change(void);

/**
  * @brief  Application Entry Function.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  BSP_HSI_24MHzClockConfig();

  BSP_USART_Config();
  printf("PY32F002B WS2812 Example\r\nClock: %ld\r\n", SystemCoreClock);
  
  APP_SPI_Config();
  while (1)
  {
    // led_rgb_marquee_change();
    // HAL_Delay(100);
    led_rgb_cycle_change();
  }
}

static void APP_SPI_Config(void)
{
  Spi1Handle.Instance               = SPI1;
  /* The frequency after prescale should be below 8.25MHz */
  Spi1Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  Spi1Handle.Init.Direction         = SPI_DIRECTION_2LINES;
  Spi1Handle.Init.CLKPolarity       = SPI_POLARITY_LOW;
  Spi1Handle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  Spi1Handle.Init.DataSize          = SPI_DATASIZE_8BIT;
  Spi1Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  Spi1Handle.Init.NSS               = SPI_NSS_SOFT;
  Spi1Handle.Init.Mode = SPI_MODE_MASTER;
  // Spi1Handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  if (HAL_SPI_DeInit(&Spi1Handle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  if (HAL_SPI_Init(&Spi1Handle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

static void led_rgb_marquee_change(void)
{
  /* red marquee */
  for (int i = 0; i < WS2812_NUM_LEDS; i++) 
  {
    ws2812_pixel_all(0x00, 0x00, 0x00);
    ws2812_pixel(i, 0xFF, 0x00, 0x00);
    ws2812_send_spi();
    HAL_Delay(100);
  }
  
  /* green marquee */
  for (int i = 0; i < WS2812_NUM_LEDS; i++) 
  {
    ws2812_pixel_all(0x00, 0x00, 0x00);
    ws2812_pixel(i, 0x00, 0xFF, 0x00);
    ws2812_send_spi();
    HAL_Delay(100);
  }
  
  /* blue marquee */
  for (int i = 0; i < WS2812_NUM_LEDS; i++) 
  {
    ws2812_pixel_all(0x00, 0x00, 0x00);
    ws2812_pixel(i, 0x00, 0x00, 0xFF);
    ws2812_send_spi();
    HAL_Delay(100);
  }
}

static void led_rgb_cycle_change(void)
{
  static uint8_t color_state = 0; // 0=red, 1=green, 2=blue
  uint8_t r = 0x0, g = 0x0, b = 0x0;
  switch(color_state) {
    case 0:
      r = 0xFF;
      g = 0x00;
      b = 0x00;
      break;
    case 1:
      r = 0x00;
      g = 0xFF;
      b = 0x00;
      break;
    case 2:
      r = 0x00;
      g = 0x00;
      b = 0xFF;
      break;
  }
  
  ws2812_pixel_all(r, g, b);
  ws2812_send_spi();
  color_state = (color_state + 1) % 3;
  HAL_Delay(1000);
}

/**
  * @brief  Error executing function.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* Users can add their own printing information as needed,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/