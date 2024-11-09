/*
 -----------------------------------------------------------
 * Module: ZPWM TIMER0
 *
 * File: pwm_timer0.c
 *
 * Description: PWM TIMER0 Driver Source File
 *
 * Author: Bodz
 -----------------------------------------------------------
 */

#include "pwm_timer0.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>

/* Initialize Timer0 in PWM mode
 *
 * Description: Initializes Timer0 in PWM mode and sets the required duty cycle
 * Prescaler: F_CPU/1024
 * Non-inverting mode
 * The function configures OC0 as the output pin.
 *
 * Pram: Adjusting PWM duty cycle
 *
 * Return: void
 *
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	CLEAR_BIT(TCCR0, FOC0);
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);

#if PWM_TIMER0_MODE == PWM_MODE_NON_INVERTING
	SET_BIT(TCCR0, COM01);
	CLEAR_BIT(TCCR0, COM00);
#elif PWM_TIMER0_MODE == PWM_MODE_INVERTING
	SET_BIT(TCCR0, COM01);
	SET_BIT(TCCR0, COM00);
#else
        #error "Invalid PWM_MODE setting"
    #endif

#if PWM_TIMER0_PRESCALER == PWM_TIMER0_PRESCALER_NO
	CLEAR_BIT(TCCR0, CS02);
	CLEAR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS00);
#elif PWM_TIMER0_PRESCALER == PWM_TIMER0_PRESCALER_8
        CLEAR_BIT(TCCR0, CS02);
        SET_BIT(TCCR0, CS01);
        CLEAR_BIT(TCCR0, CS00);
    #elif PWM_TIMER0_PRESCALER == PWM_TIMER0_PRESCALER_64
        CLEAR_BIT(TCCR0, CS02);
        SET_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS00);
    #elif PWM_TIMER0_PRESCALER == PWM_TIMER0_PRESCALER_256
        SET_BIT(TCCR0, CS02);
        CLEAR_BIT(TCCR0, CS01);
        CLEAR_BIT(TCCR0, CS00);
    #elif PWM_TIMER0_PRESCALER == PWM_TIMER0_PRESCALER_1024
	SET_BIT(TCCR0, CS02);
	CLEAR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS00);
#else
#error "Invalid PWM_PRESCALER setting"
#endif

	GPIO_setupPinDirection(PWM_TIMER0_PORT, PWM_TIMER0_PIN, PIN_OUTPUT);

	TCNT0 = 0;
	if (duty_cycle > MAX_DUTY_CYCLE)
	{
		duty_cycle = MAX_DUTY_CYCLE;
	}
	else if (duty_cycle < MIN_DUTY_CYCLE)
	{
		duty_cycle = MIN_DUTY_CYCLE;
	}
#if PWM_TIMER0_MODE == PWM_MODE_NON_INVERTING
	OCR0 = (uint8) (((uint16) duty_cycle * TIMER0_MAX_COUNT) / MAX_DUTY_CYCLE);
#else
	OCR0 = (uint8) (TIMER0_MAX_COUNT - (((uint16) duty_cycle * TIMER0_MAX_COUNT) / MAX_DUTY_CYCLE));
#endif

}
