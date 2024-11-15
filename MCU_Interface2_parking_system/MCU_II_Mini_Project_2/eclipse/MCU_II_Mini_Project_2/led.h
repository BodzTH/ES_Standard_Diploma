/*
 -----------------------------------------------------------
 * Module: LED
 *
 * File: led.h
 *
 * Description: LED Driver Header File
 *
 * Author: Bodz
 -----------------------------------------------------------
 */

#ifndef LED_H_
#define LED_H_

/*
 -------------------------------------------------------------
 | 	 	 	 	 	 	 Definitions					       	 |
 -------------------------------------------------------------
 */
#define POSITIVE_LOGIC 1
#define NEGATIVE_LOGIC 0
#define LOGIC_CONNECTION POSITIVE_LOGIC

#define LED_RED   LED_0
#define LED_GREEN LED_1
#define LED_BLUE  LED_2

#define LED_PORT_SELECT LED_PORTC

/*
 -------------------------------------------------------------
 | 	 	 	 	 	 	 Types Declaration					 |
 -------------------------------------------------------------
 */
typedef enum
{
	LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7
} LED_ID;
typedef enum
{
	LED_PORTA, LED_PORTB, LED_PORTC, LED_PORTD
} LED_PORT;

/*
 -------------------------------------------------------------
 | 	 	 	 	 	 	 Functions Prototypes				 |
 -------------------------------------------------------------
 */

/*----------------------------------------------------------*/

/* Initialize LEDs
 *
 * Description: Initializes all LEDs (red, green, blue) pins direction.
 * Turn off all the LEDs
 *
 * Return: void
 *
 */
void LEDS_init(void);

/*----------------------------------------------------------*/

/* Turns on LED
 *
 * Description: Turns on the specified LED.
 *
 * Pram: ID of the LED PIN
 *
 * Return: void
 *
 */
void LED_on(LED_ID id);

/*----------------------------------------------------------*/

/* Turns on LED
 *
 * Description: Turns off the specified LED.
 *
 * Pram: ID of the LED PIN
 *
 * Return: void
 *
 */
void LED_off(LED_ID id);

/*----------------------------------------------------------*/

#endif /* LED_H_ */
