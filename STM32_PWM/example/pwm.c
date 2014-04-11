
#include "stm32f10x.h"

// prescaler = ((24E6)/24E5)-1 = 9
// prescaler = ((24E5)/10E3)-1 = 239
#define MAX_PWM		239

// timer 3 as 10kHz PWM output
void PWM_TIM3_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	uint16_t PrescalerValue = (uint16_t)((SystemCoreClock) / 2400000) - 1;
	uint16_t PeriodValue = (uint16_t) (2400000 / 10000) - 1;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	// enable timer 3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);		// enable port A & port B

	/*GPIO Configuration: TIM3 channel1, 2, 3 and 4 on PA6, PA7, PB0, PB1*/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = PeriodValue;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel2 */
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel3 */
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel4 */
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3, ENABLE);

	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);

	TIM_CtrlPWMOutputs(TIM3, ENABLE);
}

void setTim3PWM1(uint16_t pwm) {
	if (pwm < 0) pwm = 0;
	else if (pwm > MAX_PWM) pwm = MAX_PWM;

	TIM3->CCR1 = pwm;
}

void setTim3PWM2(uint16_t pwm) {
	if (pwm < 0) pwm = 0;
	else if (pwm > MAX_PWM) pwm = MAX_PWM;

	TIM3->CCR2 = pwm;
}

void setTim3PWM3(uint16_t pwm) {
	if (pwm < 0) pwm = 0;
	else if (pwm > MAX_PWM) pwm = MAX_PWM;

	TIM3->CCR3 = pwm;
}

void setTim3PWM4(uint16_t pwm) {
	if (pwm < 0) pwm = 0;
	else if (pwm > MAX_PWM) pwm = MAX_PWM;

	TIM3->CCR4 = pwm;
}


