#pragma once
#include "hardware.h"

#define Bank5_SDRAM_ADDR                         ((uint32_t)(0XC0000000))          // SDRAM start address
#define SDRAM_SIZE                               ((uint16_t)0x80000)

// external sdram
// #define LVGL_RENDERING_BUF1_SIZE                 (Bank5_SDRAM_ADDR)
// #define LVGL_RENDERING_BUF2_SIZE                 (0xC001d200)

// SDRAM configuration parameters
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

void    sdram_init_sequence(SDRAM_HandleTypeDef *hsdram);
uint8_t sdram_send_cmd(uint8_t bank_index, uint8_t cmd, uint8_t refresh, uint8_t reg_val);
void    sdram_read_buff(uint8_t *buff, uint32_t addr, uint32_t len);
void    sdram_write_buff(uint8_t *buff, uint32_t addr, uint32_t len);
