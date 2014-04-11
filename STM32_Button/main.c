
// ********************************************************************************************************
// author: Khiew TY
// target: stm32f100c6 breakout board
// sites: https://sites.google.com/site/myprojectq/microcontroller/st-microelectronics/stm32f10xcx
//
// this example code will detect whether the button is being press or not.
// if the button is press, LED 1 and 4 will light up.
// if not, LED 2 and 3 will light up.
// ********************************************************************************************************

#include "stm32f10x.h"

#define ON		1
#define OFF		0
#define LED1(n)		GPIO_WriteBit(GPIOC, GPIO_Pin_14, (BitAction)(n))
#define LED2(n)		GPIO_WriteBit(GPIOC, GPIO_Pin_15, (BitAction)(n))
#define LED3(n)		GPIO_WriteBit(GPIOD, GPIO_Pin_0, (BitAction)(n))
#define LED4(n)		GPIO_WriteBit(GPIOD, GPIO_Pin_1, (BitAction)(n))

#define PRESS		1
#define NOT_PRESS	0
#define BUTTON0		GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)

void HSI_24MHz_Configuration(void);
void LED_Configuration(void);
void Button_Configuration(void);

int main(void) {

	HSI_24MHz_Configuration();		// configure hsi as main oscillator
	LED_Configuration();	// configure led
	Button_Configuration();	// configure button

	while(1) {
		if (BUTTON0 == PRESS) {
			LED1(ON); LED4(ON);
			LED2(OFF); LED3(OFF);
		}
		else {
			LED1(OFF); LED4(OFF);
			LED2(ON); LED3(ON);
		}
	}
}

void HSI_24MHz_Configuration(void) {
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();
	/* Enable Prefetch Buffer */
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	/* Flash 2 wait state */
	FLASH_SetLatency(FLASH_Latency_2);
	/* HCLK = SYSCLK */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	/* PCLK2 = HCLK */
	RCC_PCLK2Config(RCC_HCLK_Div1);
	/* PCLK1 = HCLK/2 */
	RCC_PCLK1Config(RCC_HCLK_Div2);
	/* ADCCLK = PCLK2/6 10.67MHz */
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);
	/* PLLCLK = 4MHz * 6 = 24 MHz */
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_6);
	/* Enable PLL */
	RCC_PLLCmd(ENABLE);
	/* Wait till PLL is ready */
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	/* Select PLL as system clock source */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	/* Wait till PLL is used as system clock source */
	while(RCC_GetSYSCLKSource() != 0x08);
}
