
// ********************************************************************************************************
// author: Khiew TY
// target: stm32f100c6 breakout board
// sites: https://sites.google.com/site/myprojectq/microcontroller/st-microelectronics/stm32f10xcx
//
// this example code will blink the LED at certain time interval.
// ********************************************************************************************************

#include "stm32f10x.h"

void HSI_24MHz_Configuration(void);
void LED_Configuration(void);

int main(void) {
	int i, j;

	HSI_24MHz_Configuration();		// configure hsi as main oscillator
	LED_Configuration();	// configure led

    while (1) {		// forever loop
        /* Toggle LEDs */
        GPIOC->ODR ^= GPIO_Pin_14;		// toggle led
        GPIOC->ODR ^= GPIO_Pin_15;		// toggle led
        GPIOD->ODR ^= GPIO_Pin_0;		// toggle led
        GPIOD->ODR ^= GPIO_Pin_1;		// toggle led

        /* delay */
        for(i = 0; i < 5; i++) for(j = 0; j < 0x10000; j++);
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
