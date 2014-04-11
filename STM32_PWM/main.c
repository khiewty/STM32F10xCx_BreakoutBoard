
// ********************************************************************************************************
// author: Khiew TY
// target: stm32f100c6 breakout board
// sites: https://sites.google.com/site/myprojectq/microcontroller/st-microelectronics/stm32f10xcx
//
// this example code will demonstrate fading the LED using PWM.
// ********************************************************************************************************

#include "stm32f10x.h"

#define ON		1
#define OFF		0
#define LED1(n)		GPIO_WriteBit(GPIOC, GPIO_Pin_14, (BitAction)(n))
#define LED2(n)		GPIO_WriteBit(GPIOC, GPIO_Pin_15, (BitAction)(n))
#define LED3(n)		GPIO_WriteBit(GPIOD, GPIO_Pin_0, (BitAction)(n))
#define LED4(n)		GPIO_WriteBit(GPIOD, GPIO_Pin_1, (BitAction)(n))

void soft_delay(void);
void init_HSI_24MHz(void);
void LED_Configuration(void);
void PWM_TIM3_Configuration(void);
void setTim3PWM1(uint16_t pwm);
void setTim3PWM2(uint16_t pwm);
void setTim3PWM3(uint16_t pwm);
void setTim3PWM4(uint16_t pwm);

int main(void) {
	int brightness = 0;
	init_HSI_24MHz();

	LED_Configuration();
	PWM_TIM3_Configuration();



	while(1) {
		for (brightness = 0; brightness < 120; brightness++) {
			setTim3PWM1(brightness);
			soft_delay();
		}
		for (brightness = 119; brightness >= 0; brightness--) {
			setTim3PWM1(brightness);
			soft_delay();
		}

	}
}

void soft_delay(void) {
	int i, j;
	for(i = 0; i < 5; i++) for(j = 0; j < 0x1200; j++);
}


void init_HSI_24MHz(void) {
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
