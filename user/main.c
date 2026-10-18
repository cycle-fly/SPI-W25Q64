#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"
int main(void){
   OLED_Init();
	 W25Q64_Init();
	 uint8_t a;
	 uint16_t b;
	 W25Q64_GetID(&a,&b);
	 W25Q64_EraseSector(0x000000);
	 uint8_t dataArray[4]={0xAA,0x01,0x01,0x02};
	 uint8_t ReceivedataArray[4]={0x00};
	 W25Q64_PageProgram(0x000000,dataArray,4);
	 W25Q64_ReadData(0x000000,ReceivedataArray,4);
   while(1){
	   OLED_ShowHexNum(1,1,a,4);
		 OLED_ShowHexNum(1,6,b,4);
		 OLED_ShowHexNum(2,1,ReceivedataArray[0],2);
		 OLED_ShowHexNum(2,4,ReceivedataArray[1],2);
		 OLED_ShowHexNum(2,7,ReceivedataArray[2],2);
		 OLED_ShowHexNum(2,10,ReceivedataArray[3],2);
	}
}
