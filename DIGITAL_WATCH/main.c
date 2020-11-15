/*************************************************************/
/*  AUTHOR     : AbdElrahman Ibrahim Zaki                    */
/*  DATE       :  										                    	 */
/*  VERSION	   : V0.1										                     */
/*  DESCRIPTION: Digital Watch Application                   */
/*  Using > LCD, BUZZER, TIMER, Interrupt                    */
/*************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "EXT_INT_int.h"
#include "GIE_int.h"
#include "INT_Config.h"
#include "LCD_interface.h"
#include "TIMER0_int.h"
#include "TIMER1_int.h"
#include "TIMER2_int.h"
#include "TIMER2_reg.h"
#include "TIMER0_reg.h"
#include "TIMER0_config.h"
#include "TIMER2_config.h"
#include "TIMER1_reg.h"
#include "TIMER1_config.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile u8 count0 = 0;
volatile u8 count2 = 0;
u16 Hrs = 0 , Min = 0 , Sec = 0 , AS = 30 , AM = 2;

void CK_LCD_DIS_ISR (void)
{
	count0 ++;

   if (count0 == 31)
   {
	   // TIMER0 Pre-load
	   TIMER0_SetTimerReg(0X80);
	   Sec ++;
	   Cursor_Pos(0,14);
	   LCD_u8writeINT(Sec);
               if (Sec == 59)
                {
                  Sec = 0;
                  Min++;
    	          Cursor_Pos(0,11);
    	          LCD_u8writeINT(Min);
    	                if (Min == 59)
    	                  {
    	                    Min = 0;
    	                    Hrs++;
    	                    Cursor_Pos(0,8);
    	                    LCD_u8writeINT(Hrs);
    	                        if (Hrs == 23)
    		                      {
                                   Hrs = 0;
                                   Cursor_Pos(0,8);
                                   LCD_u8writeINT(Hrs);
                                   TIMER0_SetTimerReg(0X00);
    		                      }
    	                  }
                 }
    }

}


void ALARM_BUZZER(void)
{
	count2 ++;
	/* Toggle Buzzer after 2 Min & 30 Seconds
	 * 31 no of overflows * 150 secs "2Min:30Sec"  = 4650*/

	if (count2 == 4650)
	  {
		// TIMER2 Pre-load
		TIMER2_SetTimerReg(0X80);
		// Ring 4 times
		for (int i = 0; i < 4 ; i++)
		{
			DIO_voidSetPinValue(PORTD , PIN7 , HIGH);
			_delay_ms(100);
			DIO_voidSetPinValue(PORTD , PIN7 , LOW);
			_delay_ms(100);
		}
	  }
	// disable TIMER2
	TIMER2_DisableOVInt();
	TIMER2_SetTimerReg(0X00);
}

int main()
{
	// DIO Direction Setting  "LCD Output"
	DIO_voidSetPortDirection(PORTA , 0XFF);
	DIO_voidSetPortDirection(PORTC , 0XFF);
	// OC2 output direction
	DIO_voidSetPortDirection(PORTD , 0XFF);

	// LCD Initialization
	LCD_Ini();
	_delay_ms(1000);

	// TIMER0 Initialization
	TIMER0_Init();

	//TIMER2 Initialization
    TIMER2_Init();

    // Clock TIMER0
	/* TOV = Pre-scaler  1024 / 8 MHz * 256 = 0.03276 sec , Required Time = 1 Sec
	 * no of overflows = 1 sec / 0.03276 sec = 30.5 overflows to reach 1 sec
	 * 30.5 * 256 = 7808   &&   30 * 256 = 7680 */
	/* Pre-load = 7808 - 7680 = 128 = 0X80 */
	TIMER0_SetTimerReg(0X80);

	// ALARM TIMER2
	TIMER2_SetTimerReg(0X80);


	// Interrupt GIE Enable
	GIE_voidEnable();
	// Enable TIMER0 Overflow Interrupt
	TIMER0_EnableOVInt();
	// Enable TIMER2 Overflow Interrupt
	TIMER2_EnableOVInt();
	TIMER0_voidSetOVCallBack(CK_LCD_DIS_ISR);
	TIMER2_voidSetOVCallBack(ALARM_BUZZER);


     while (1)
     {
    	 Cursor_Pos(0,0);
    	 LCD_writeString ("C/K=");

    	 Cursor_Pos(0,10);
    	 LCD_writeChar(':');
    	 Cursor_Pos(0,13);
    	 LCD_writeChar(':');



    	 Cursor_Pos(1,0);
    	 LCD_writeString ("ALARM=");

    	 Cursor_Pos(1,8);
    	 LCD_u8writeINT(00);

    	 Cursor_Pos(1,10);
    	 LCD_writeChar (':');

    	 Cursor_Pos(1,11);
    	 LCD_u8writeINT(AM);

    	 Cursor_Pos(1,13);
    	 LCD_writeChar (':');

    	 Cursor_Pos(1,14);
    	 LCD_u8writeINT(AS);
     }



	return 0;
}
