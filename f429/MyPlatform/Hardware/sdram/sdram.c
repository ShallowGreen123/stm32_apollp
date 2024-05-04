#include "sdram.h"

void sdram_init_sequence(SDRAM_HandleTypeDef *hsdram)
{
    uint32_t tmp;
    sdram_send_cmd(0, FMC_SDRAM_CMD_CLK_ENABLE, 1, 0);
    HAL_Delay(1);                                                     // 至少延时200us
    sdram_send_cmd(0, FMC_SDRAM_CMD_PALL, 1, 0);                      // 对所有存储区预充电
    sdram_send_cmd(0, FMC_SDRAM_CMD_AUTOREFRESH_MODE, 8, 0);          // 设置自刷新次数
    // 配置模式寄存器,SDRAM的bit0~bit2为指定突发访问的长度，
    // bit3为指定突发访问的类型，bit4~bit6为CAS值，bit7和bit8为运行模式
    // bit9为指定的写突发模式，bit10和bit11位保留位
    tmp = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 |               // 设置突发长度:1(可以是1/2/4/8)
          SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |                  // 设置突发类型:连续(可以是连续/交错)
          SDRAM_MODEREG_CAS_LATENCY_3 |                          // 设置CAS值:3(可以是2/3)
          SDRAM_MODEREG_OPERATING_MODE_STANDARD |                // 设置操作模式:0,标准模式
          SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;                  // 设置突发写模式:1,单点访问
    sdram_send_cmd(0, FMC_SDRAM_CMD_LOAD_MODE, 1, tmp);          // 设置SDRAM的模式寄存器
}

uint8_t sdram_send_cmd(uint8_t bank_index, uint8_t cmd, uint8_t refresh, uint8_t reg_val)
{
    uint32_t                 target_bank = 0;
    FMC_SDRAM_CommandTypeDef Command;

    if (bank_index == 0)
        target_bank = FMC_SDRAM_CMD_TARGET_BANK1;
    else if (bank_index == 1)
        target_bank = FMC_SDRAM_CMD_TARGET_BANK2;
    Command.CommandMode            = cmd;                                     // 命令
    Command.CommandTarget          = target_bank;                             // 目标SDRAM存储区域
    Command.AutoRefreshNumber      = refresh;                                 // 自刷新次数
    Command.ModeRegisterDefinition = reg_val;                                 // 要写入模式寄存器的值
    if (HAL_SDRAM_SendCommand(&hsdram1, &Command, 0X1000) == HAL_OK)          // 向SDRAM发送命令
    {
        return 0;
    } else
        return 1;
}

void sdram_read_buff(uint8_t *buff, uint32_t addr, uint32_t len)
{
    for (; len != 0; len--) {
        *buff++ = *(volatile uint8_t *)(Bank5_SDRAM_ADDR + addr);
        addr++;
    }
}

void sdram_write_buff(uint8_t *buff, uint32_t addr, uint32_t len)
{
    for (; len != 0; len--) {
        *(volatile uint8_t *)(Bank5_SDRAM_ADDR + addr) = *buff;
        addr++;
        buff++;
    }
}