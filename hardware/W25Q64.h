#ifndef __W25Q64_H
#define __W25Q64_H
#include "stm32f10x.h"                  // Device header

void W25Q64_Init(void);
uint8_t W25Q64_SwapByte(uint8_t byte);
void W25Q64_GetID(uint8_t* a,uint16_t*b);
void W25Q64_WriteEnable(void);
void W25Q64_WaitBUSY(void);
void W25Q64_EraseSector(uint32_t addr);
void W25Q64_PageProgram(uint32_t addr,uint8_t* dataArray,uint32_t count);
void W25Q64_ReadData(uint32_t addr,uint8_t* dataArray,uint32_t count);
#endif
