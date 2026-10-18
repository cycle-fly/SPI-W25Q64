#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"
void W25Q64_Init(void){
  MySPI_Init();
}
uint8_t W25Q64_SwapByte(uint8_t byte){
	uint8_t tmp=0x00;
  MySPI_Start();
	tmp=MySPI_SwapByte(byte);
	MySPI_Stop();
	return tmp;
}
void W25Q64_GetID(uint8_t* a,uint16_t*b){
  MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);
	*a=MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*b=MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*b=*b<<8;
	*b|=MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	MySPI_Stop();
}
void W25Q64_WriteEnable(){
  MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}
void W25Q64_WaitBUSY(){
  MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE)&0x01)==0x01){
	 
	}
	MySPI_Stop();
}
void W25Q64_EraseSector(uint32_t addr){
	W25Q64_WriteEnable();
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(addr>>16);
	MySPI_SwapByte(addr>>8);
	MySPI_SwapByte(addr);
	MySPI_Stop();
	W25Q64_WaitBUSY();
}
void W25Q64_PageProgram(uint32_t addr,uint8_t* dataArray,uint32_t count){
	W25Q64_WriteEnable();
  MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(addr>>16);
	MySPI_SwapByte(addr>>8);
	MySPI_SwapByte(addr);
	for(uint32_t i=0;i<count;i++){
	  MySPI_SwapByte(dataArray[i]);
	}
	MySPI_Stop();
	W25Q64_WaitBUSY();
}
void W25Q64_ReadData(uint32_t addr,uint8_t* dataArray,uint32_t count){
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(addr>>16);
	MySPI_SwapByte(addr>>8);
	MySPI_SwapByte(addr);
	for(uint32_t i=0;i<count;i++){
	  dataArray[i]=MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
}
