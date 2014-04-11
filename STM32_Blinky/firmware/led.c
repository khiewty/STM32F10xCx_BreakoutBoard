
#include "stm32f10x.h"

void LED_Configuration(void) {
    /* initialize leds mounted on target board */
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);		// enable port C & port D
    GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);		// remap PD0 & PD1 as GPIO

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);		// set PC14 & PC15 a output pin

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOD, &GPIO_InitStructure);		// set PD0 & PD1 a output pin

    GPIO_SetBits(GPIOC, GPIO_Pin_14);	// set output as high
    GPIO_ResetBits(GPIOC, GPIO_Pin_15);	// set output as low
    GPIO_ResetBits(GPIOD, GPIO_Pin_0);	// set output as low
    GPIO_SetBits(GPIOD, GPIO_Pin_1);	// set output as high
}
