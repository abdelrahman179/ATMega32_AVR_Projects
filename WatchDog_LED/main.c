/*************************************************************/
/*  AUTHOR     : AbdElrahman Ibrahim Zaki                    */
/*  DATE       :  					     */
/*  VERSION    : V0.1				             */
/*  DESCRIPTION: Watch_Dog LED                               */
/*                                                           */
/*************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include <util/delay.h>

#define WDTCR    *((volatile u8 *) 0X41)

int main()
{
	DIO_voidSetPortDirection(PORTA , 0XFF);

	// WDT On
	SET_BIT(WDTCR , 0);
	SET_BIT(WDTCR , 1);
	SET_BIT(WDTCR , 2);

	DIO_voidSetPinValue(PORTA , PIN0 , HIGH);
	_delay_ms(1000);

	// WDT Off "Refresh"
	WDTCR = 0XFF;
	WDTCR = 0X00;

	DIO_voidSetPinValue(PORTA , PIN0 , LOW);
	_delay_ms(1000);

	/* without disabling the WDT the system will remain reset and the led will remain toggle */

	while (1)
	{

		DIO_voidSetPinValue(PORTA , PIN1 , HIGH);
			_delay_ms(1000);
		DIO_voidSetPinValue(PORTA , PIN1 , LOW);
			_delay_ms(1000);

	}

     return 0;
}
