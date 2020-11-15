/*************************************************************/
/*  AUTHOR     : AbdElrahman Ibrahim Zaki                    */
/*  DATE       :  											 */
/*  VERSION	   : V0.1										 */
/*  DESCRIPTION: Traffic Lights using 7-Segment              */
/*                                                           */
/*************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include <util/delay.h>

/ Traffic Light (LED's and 7 Segment)
int main()
{
	// Segment PORT Direction
    DIO_voidSetPortDirection(PORTA , 0XFF);

    // LEDs PORT Direction
    DIO_voidSetPortDirection(PORTC , 0XFF);

  while (1)
  {
	  // Counter
	  int Seg_Arr[] = {0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XD8,0X80,0X90};
	    u8 i = 0 , j = 0;

	    /* --------- LEFT SEGMENT COUNTING --------- */
	   		     for (i = 0 ; i < 10 ; i++)
	   		     {
	   		    	 DIO_voidSetPortValue(PORTC , Seg_Arr[i]);

	   		    	 /* --------- RIGHT SEGMENT COUNTING --------- */
	   		    	 for (j = 0 ; j < 10 ; j++)
	   		    	  {
	   		    		 DIO_voidSetPortValue(PORTA , Seg_Arr[j]);
	   		    	     _delay_ms(500);
	   		    	     // Right Segment OFF
	   		    	     DIO_voidSetPortValue(PORTA , 0X00);
	   		    	     _delay_ms(10);
	   		    	  }

	   		    	 // LEFT Segment OFF
	   		    	 DIO_voidSetPortValue(PORTC , 0X00);
	   		    	 _delay_ms(10);
	   		     }
  }
  return 0;
}
