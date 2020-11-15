/*************************************************************/
/*  AUTHOR     : AbdElrahman Ibrahim Zaki                    */
/*  DATE       :  											 */
/*  VERSION	   : V0.1										 */
/*  DESCRIPTION: Stepper Motor                               */
/*                                                           */
/*************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include <util/delay.h>
#define  F_CPU    8000000UL

int main()
{

	DIO_voidSetPortDirection(PORTA , OUTPUT);

    u16 var = 0;
	u8 speed = 1 ;
	while(1)
	{

		for (var = 0 ; var < 512 ; var++)
		{
		/* coil 1 */

		DIO_voidSetPinValue(PORTA , PIN0 , HIGH);
		DIO_voidSetPinValue(PORTA , PIN1 , LOW);
		DIO_voidSetPinValue(PORTA , PIN2 , LOW);
		DIO_voidSetPinValue(PORTA , PIN3 , LOW);
		_delay_ms(speed);

		/* coil 2 & 1 */

		DIO_voidSetPinValue(PORTA , PIN0 , HIGH);
		DIO_voidSetPinValue(PORTA , PIN1 , HIGH);
		DIO_voidSetPinValue(PORTA , PIN2 , LOW);
		DIO_voidSetPinValue(PORTA , PIN3 , LOW);
		_delay_ms(speed);

		/* coil 2 */

		DIO_voidSetPinValue(PORTA , PIN0 , LOW);
		DIO_voidSetPinValue(PORTA , PIN1 , HIGH);
	    DIO_voidSetPinValue(PORTA , PIN2 , LOW);
		DIO_voidSetPinValue(PORTA , PIN3 , LOW);
		_delay_ms(speed);

		/* coil 2 & 3 */

		DIO_voidSetPinValue(PORTA , PIN0 , LOW);
		DIO_voidSetPinValue(PORTA , PIN1 , HIGH);
	    DIO_voidSetPinValue(PORTA , PIN2 , HIGH);
		DIO_voidSetPinValue(PORTA , PIN3 , LOW);
		_delay_ms(speed);

		/* coil 3 */

		DIO_voidSetPinValue(PORTA , PIN0 , LOW);
		DIO_voidSetPinValue(PORTA , PIN1 , LOW);
	    DIO_voidSetPinValue(PORTA , PIN2 , HIGH);
		DIO_voidSetPinValue(PORTA , PIN3 , LOW);
		_delay_ms(speed);

		/* coil 3 & 4 */

		DIO_voidSetPinValue(PORTA , PIN0 , LOW);
		DIO_voidSetPinValue(PORTA , PIN1 , LOW);
	    DIO_voidSetPinValue(PORTA , PIN2 , HIGH);
	    DIO_voidSetPinValue(PORTA , PIN3 , HIGH);
		_delay_ms(speed);

		/* coil 4 */

		DIO_voidSetPinValue(PORTA , PIN0 , LOW);
	    DIO_voidSetPinValue(PORTA , PIN1 , LOW);
	    DIO_voidSetPinValue(PORTA , PIN2 , LOW);
	    DIO_voidSetPinValue(PORTA , PIN3 , HIGH);
		_delay_ms(speed);
	    }

	}
}
