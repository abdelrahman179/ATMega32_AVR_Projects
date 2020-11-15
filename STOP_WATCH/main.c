/*************************************************************/
/*  AUTHOR     : AbdElrahman Ibrahim Zaki                    */
/*  DATE       :  											                     */
/*  VERSION	   : V0.1										                     */
/*  DESCRIPTION: COUNTER Application                         */
/*************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "EXT0_int.h"
#include "EXT1_int.h"
#include "GIE_int.h"
#include "TIMER0_int.h"
#include "TIMER0_reg.h"
#include "TIMER0_config.h"
#include <util/delay.h>


   /* ------------- SEGMENT TRUTH TABLE ------------------ */
  u8 u,t;  // units and tens
  int Seg_Arr[10] = {0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XD8,0X80,0X90};



void RESET_COUNTER(void)
{
	  // Buzzer On
	  DIO_voidSetPinValue(PORTB , PIN7 , HIGH);
	  _delay_ms(100);
	  // Buzzer Off
	  DIO_voidSetPinValue(PORTB , PIN7 , LOW);

	  TCNT0 = 0;
}



int main ()
{


	   /* -------------- SEGMENT DIO INITIALIZATION -------------------- */

	   // Right Segment
       DIO_voidSetPortDirection(PORTA , 0XFF);
       // Left Segment
       DIO_voidSetPortDirection(PORTC , 0XFF);

       /* -------------- BUZZER DIO INITIALIZATION -------------------- */

       // BUZZER
       DIO_voidSetPinDirection(PORTB , PIN7 , OUTPUT);

       /* -------------- INTERRUPT DIO INITIALIZATION -------------------- */

       // TIMER0 as a COUNTER0  "COUNT BUTTON"
   	   DIO_voidSetPinDirection(PORTB , PIN0 , INPUT);
   	   // pull up resistor for PB0
   	   DIO_voidSetPinValue(PORTB , PIN0 , HIGH);

       // External INT0  "RESET COUNTER BUTTON"
   	   DIO_voidSetPinDirection(PORTD , PIN2 , INPUT);
   	   // pull up resistor for D1
   	   DIO_voidSetPinValue(PORTD , PIN2 , HIGH);



   	   /* ------------------- Interrupt / Timer Initialization ------------------------ */
       TIMER0_Init();
   	   GIE_voidEnable();

       EXT0_voidInit();
       EXT0_voidEnable();

       EXT0_voidSetCallBack(RESET_COUNTER);

       // Begin with displaying zeros
       	DIO_voidSetPortValue(PORTA , Seg_Arr[0]);
       	DIO_voidSetPortValue(PORTC , Seg_Arr[0]);

   while (1)
   {
    	   	_delay_ms(5);
    	   	u = TCNT0%10;
    	    t = (TCNT0/10)%10;

    	   if ((TCNT0 > 0) && (TCNT0 <9))
    	    {
    	   	   DIO_voidSetPortValue(PORTA , Seg_Arr[u]);

    	    }else if ((TCNT0 > 9) && (TCNT0 <100))
    	   	{
    	   	   DIO_voidSetPortValue(PORTA , Seg_Arr[u]);
    	   	   DIO_voidSetPortValue(PORTC , Seg_Arr[t]);
    	   	}else
    	   	{
    	   	   TCNT0 = 0;
    	   	   DIO_voidSetPortValue(PORTA , Seg_Arr[0]);
    	   	   DIO_voidSetPortValue(PORTC , Seg_Arr[0]);
    	   	}

   }
   return 0;
}
