#include "stm32f10x.h"                  // Device header
void SS(uint8_t val){
  GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction) val);
}
void SCL(uint8_t val){  
  GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction) val);
}
void MOSI(uint8_t val){
  GPIO_WriteBit(GPIOA, GPIO_Pin_6, (BitAction) val);
}
uint8_t MISO(){
  return  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
}
void MySPI_Init(void){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4 |GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7; //上拉输入，对于MISO
	SS(1);
	SCL(0);
}
uint8_t MySPI_SwapByte(uint8_t byte){
	uint8_t ReceiveByte=0x00;
  for(uint8_t i=0;i<8;i++){
	  MOSI(byte&0x80);
		byte=byte<<1;
		SCL(1);
		if(MISO())
		  ReceiveByte|=0x01;
		if(i!=7)
		 ReceiveByte=ReceiveByte<<1;
		SCL(0);
	}
	return ReceiveByte;
 
}
void MySPI_Stop(void){
  SS(1);
}
void MySPI_Start(void){
  SS(0);
}
