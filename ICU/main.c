/*****************************************************/
/* Author      : AbdElrahman I.Zaki                  */
/* Version     : v01                                 */
/* Description : ICU								 */
/*****************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "EXT_INT_int.h"
#include "INT_Config.h"
#include "GIE_int.h"
#include "LCD_Interface.h"
#include "TIMER0_int.h"
#include "TIMER0_config.h"
#include "TIMER2_int.h"
#include "TIMER2_config.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile u8 flag = 0;
int Ovf = 0;
float Ton = 0;
float Toff = 0;

void Tov_App(void)
{
  Ovf++;
}

void EXT0_App(void)
{
	 if (flag == 0) // 1st Snap
	 {
		 // Set TCNT0 = 0 on "Start of Ton"
		 TIMER0_SetTimerReg(0);
		 Ovf = 0;
		 flag = 1;
		 // Set the EXT Interrupt on Falling edge "12 = FALLING" End of Ton
		 EXT_INT_voidInit(12);


	 }else if (flag == 1) // 2nd Snap
	 {
		 // Get Ton Value
		 /* - Float Casting to get the value of Ton in float
		  * - TIMER0_GetTimerReg() to get the value of TCNT0
		  * - Ovf * 256 to number of overflows * 256 to get number of COUNTS added to the current value of TCNT0
		  * - Since Ton = Tick * Counts
		  * - Tick = Prescaler / FCPU = 1024 / 8MHz  */
		 Ton = (float) (((TIMER0_GetTimerReg() + (Ovf * 256))) * ((float) ((float)1024 / 8000000)));
		 // Clear TCNT0 "Start of Toff"
		 TIMER0_SetTimerReg(0);
		 flag = 2;
		 // Clear Ovf
		 Ovf = 0;
		 // Set the EXT Interrupt on Rising edge "13 = RISING" // End of Toff
		 EXT_INT_voidInit(13);


	 }else if (flag == 2)
	 {
		 // Get Toff Value
		 /* - Float Casting to get the value of Ton in float
		  * - TIMER0_GetTimerReg() to get the value of TCNT0
		  * - Ovf * 256 to number of overflows * 256 to get number of COUNTS added to the current value of TCNT0
		  * - Since T = Tick * Counts
		  * - Tick = Prescaler / FCPU = 1024 / 8MHz  */
		 Toff = (float) (((TIMER0_GetTimerReg() + (Ovf * 256))) * ((float) ((float)1024 / 8000000)));
		 // Clear TCNT0 "Start of Toff"
		 TIMER0_SetTimerReg(0);
		 flag = 0;
		 Ovf = 0;
		 // Set the EXT Interrupt on Falling edge "12 = FALLING" End of Ton2
		 EXT_INT_voidInit(12);
	 }
}


int main()
{
	// Timer0 Overflow interrupt callback function
	TIMER0_voidSetOVCallBack(Tov_App);
	// EXT0 interrupt callback function
	EXT0_INT_voidSetCallBack(EXT0_App);

	// LCD Data
	DIO_voidSetPortDirection(PORTC , 0XFF);
	// LCD Control
	DIO_voidSetPortDirection(PORTA , 0XFF);
	// OC2
	DIO_voidSetPinDirection(PORTD , PIN7 , OUTPUT);
	// EXT0
	DIO_voidSetPinDirection(PORTD , PIN2 , INPUT);


	int duty = 0, frequency = 0;
	float f = 0;

	TIMER0_Init();
	TIMER2_Init();
	// Duty = 50%  - Prescaler = 1024
	TIMER2_SetCompareVal(127);

	GIE_voidEnable();
	EXT_INT_voidEnable();
	TIMER0_EnableOVInt();

	LCD_Ini();


	while(1)
	{
      duty = (100 * Ton) / (Ton + Toff);
      f = 1 / (Ton + Toff);
      frequency = (int) f;

      Cursor_Pos(0,0);
      LCD_writeString("Freq=");
      Cursor_Pos(0,6);
      LCD_vidWriteNumber(frequency);
      /*LCD_writeChar((frequency/100)+48);
      LCD_writeChar(((frequency/10)%10)+48);
      LCD_writeChar((frequency%10)+48);*/

      Cursor_Pos(0,13);
      LCD_writeString("Hz");

      Cursor_Pos(1,0);
      LCD_writeString("Duty=");
      Cursor_Pos(1,6);
      LCD_vidWriteNumber(duty);
      /*LCD_writeChar((duty/10)+48);
      LCD_writeChar((frequency%10)+48);*/
      Cursor_Pos(1,13);
      LCD_writeChar('%');

	}
	return 0;
}












