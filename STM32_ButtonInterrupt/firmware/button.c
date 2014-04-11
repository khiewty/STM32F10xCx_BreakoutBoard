
#include "stm32f10x.h"

#define TRUE	1
#define FALSE	0
#define PRESS		1
#define NOT_PRESS	0
#define BUTTON0		GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)

static volatile uint8_t button0Flag = 0;

void Button_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC, ENABLE);		// enable port C

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);

  	/* Connect Button EXTI Line to Key Button GPIO Pin */
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13 );

	/* Configure Button EXTI Line to generate an interrupt on falling edge */
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI15_10_IRQHandler(void) {
	uint16_t i;

	if(EXTI_GetITStatus(EXTI_Line13) != RESET) {
		EXTI_ClearITPendingBit(EXTI_Line13);	// Clear the Button EXTI line pending bit

		for (i = 0; i < 25000; i++);			// eliminate debouncing
		if (BUTTON0 == PRESS) button0Flag = PRESS;
		else button0Flag = NOT_PRESS;
	}
}

uint8_t readButton0(void) {
	if(button0Flag == PRESS) {
		while(BUTTON0 == PRESS) asm volatile ("nop");
		button0Flag = NOT_PRESS;
		return TRUE;
	}
	else {
		return FALSE;
	}
}
