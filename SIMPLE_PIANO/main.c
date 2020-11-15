#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "TIMER0_int.h"
#include "TIMER0_config.h"
#include "Kepad_interface.h"
#include <util/delay.h>


int main()
{

	// Keypad C0 - C3
	DIO_voidSetPinDirection(PORTA , PIN0 , OUTPUT);
	DIO_voidSetPinDirection(PORTA , PIN1 , OUTPUT);
	DIO_voidSetPinDirection(PORTA , PIN2 , OUTPUT);
	DIO_voidSetPinDirection(PORTA , PIN3 , OUTPUT);

	// Keypad R0 - R3
	DIO_voidSetPinDirection(PORTA , PIN4 , INPUT);
	DIO_voidSetPinDirection(PORTA , PIN5 , INPUT);
	DIO_voidSetPinDirection(PORTA , PIN6 , INPUT);
	DIO_voidSetPinDirection(PORTA , PIN7 , INPUT);

	// Pull up resistors
	DIO_voidSetPinValue(PORTA , PIN4 , HIGH);
	DIO_voidSetPinValue(PORTA , PIN5 , HIGH);
	DIO_voidSetPinValue(PORTA , PIN6 , HIGH);
	DIO_voidSetPinValue(PORTA , PIN7 , HIGH);

	DIO_voidSetPinDirection(PORTB , PIN3 , OUTPUT);



	TIMER0_Init();


	u8 Tune = 0;

	while (1)
	{
		Tune = keypad_u8GetPressedKey();
		TIMER0_SetCompareVal(Tune);
		_delay_ms(5);
		Tune = 0;
		TIMER0_SetCompareVal(Tune);
	     if (Tune != 0)
		   {
			TIMER0_SetCompareVal(Tune);
			_delay_ms(100);
			Tune = 0;
		   }
	}
	return 0;
}
