/**
 * Source code from: 
 *   https://www.newinnovations.nl/post/controlling-ws2812-and-ws2812b-using-only-stm32-spi/
*/
#include <string.h>
#include "ws2812_spi.h"

/*
 * py32f002b,frequency: 24Mhz, frequency division: 4, spi frequency: 6MHz (0.1667us)
 *
 * '0': high level is 0.35us, 0.35/0.1667 = 2.1, 2 bit high level, as 1100 0000 (0xc0)
 * '1': high level is 0.65us, 0.65/0.1667 = 3.9, 4 bit high level, as 1111 0000 (0xf0)
 * 
 * 0xfc: 0x1111 1100
 * 0x80: 0x1000 0000
*/
#define WS2812_FILL_BUFFER(COLOR) \
    for( uint8_t mask = 0x80; mask; mask >>= 1 ) { \
        if( COLOR & mask ) { *ptr++ = 0xf0; } \
        else { *ptr++ = 0xc0; }}

uint8_t ws2812_buffer[WS2812_BUFFER_SIZE];

void ws2812_init(void) {
    memset(ws2812_buffer, 0, WS2812_BUFFER_SIZE);
    ws2812_send_spi();
}

void ws2812_send_spi(void) {
    HAL_SPI_Transmit(&WS2812_SPI_HANDLE, ws2812_buffer, WS2812_BUFFER_SIZE, HAL_MAX_DELAY);
}

void ws2812_pixel(uint16_t led_no, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t temp = g;
    g = b;
    b = temp;
    uint8_t * ptr = &ws2812_buffer[24 * led_no];
    /* ws2812 define color sequence, must be "green -> red -> blue" */
    WS2812_FILL_BUFFER(g);
    WS2812_FILL_BUFFER(r);
    WS2812_FILL_BUFFER(b);
}

void ws2812_pixel_all(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t temp = g;
    g = b;
    b = temp;
    uint8_t * ptr = ws2812_buffer;
    for( uint16_t i = 0; i < WS2812_NUM_LEDS; ++i) {
        /* ws2812 define color sequence, must be "green -> red -> blue" */
        WS2812_FILL_BUFFER(g);
        WS2812_FILL_BUFFER(r);
        WS2812_FILL_BUFFER(b);
    }
}