/*
 -----------------------------------------------------------
 * Module: APP
 *
 * File: smart_home.c
 *
 * Description: APP Source File
 *
 * Author: Bodz
 -----------------------------------------------------------
 */

#include "ldr_sensor.h"
#include "led.h"
#include "lm35_sensor.h"
#include "dc_motor.h"
#include "lcd.h"
#include "buzzer.h"
#include "flame_sensor.h"

#include "std_types.h"

int main(void)
{
	uint16 ldr_intensity;
	uint8 temp_value;
	DcMotor_State dc_state = CW;
	LEDS_init();
	DcMotor_Init();
	FlameSensor_init();
	LCD_init();
	Buzzer_init();
	while (1)
	{
		ldr_intensity = LDR_getLightIntensity();
		if (ldr_intensity > 70)
		{
			LED_off(LED_RED);
			LED_off(LED_GREEN);
			LED_off(LED_BLUE);
		}
		else if (ldr_intensity > 51)
		{
			LED_on(LED_RED);
			LED_off(LED_GREEN);
			LED_off(LED_BLUE);
		}
		else if (ldr_intensity > 16)
		{
			LED_on(LED_RED);
			LED_on(LED_GREEN);
			LED_off(LED_BLUE);
		}
		else
		{
			LED_on(LED_RED);
			LED_on(LED_GREEN);
			LED_on(LED_BLUE);
		}
		LCD_displayStringRowColumn(1, 0, "Temp=");
		temp_value = LM35_getTemperature();
		LCD_intgerToString(temp_value);
		LCD_displayCharacter(' ');
		LCD_displayString("LDR=");
		LCD_intgerToString(ldr_intensity);
		LCD_displayString("%  ");

		if (temp_value >= 40)
		{
			dc_state = CW;
			DcMotor_Rotate(dc_state, 100);
		}
		else if (temp_value >= 35)
		{
			dc_state = CW;
			DcMotor_Rotate(dc_state, 75);
		}
		else if (temp_value >= 30)
		{
			dc_state = CW;
			DcMotor_Rotate(dc_state, 50);
		}
		else if (temp_value >= 25)
		{
			dc_state = CW;
			DcMotor_Rotate(dc_state, 25);
		}
		else
		{
			dc_state = OFF;
			DcMotor_Rotate(dc_state, 0);
		}
		if (dc_state)
		{
			LCD_displayStringRowColumn(0, 4, "FAN is ON ");
		}
		else
		{
			LCD_displayStringRowColumn(0, 4, "FAN is OFF");
		}
		if (FlameSensor_getValue())
		{
			LCD_clearScreen();
			LCD_displayString("Critical alert!");
			Buzzer_on();
			while (FlameSensor_getValue())
				;
			LCD_clearScreen();
		}
		else
		{
			Buzzer_off();
		}

	}
}

