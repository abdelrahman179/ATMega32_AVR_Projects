/*************************************************************/
/*  AUTHOR     : AbdElrahman Ibrahim Zaki                    */
/*  DATE       :  											 */
/*  VERSION	   : V0.1										 */
/*  DESCRIPTION: Calculator Keypad/LCD                       */
/*                                                           */
/*************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "Kepad_interface.h"
#include <util/delay.h>

u8 op;
u16 Num[32];

// Operation cases
u16 operation(u16 a, u16 b)
{
	u16 result;
	switch(op)
	 case '+' : a + b; break;
	 case '-' : a - b; break;
	 case '*' : a * b; break;
	 case '/' : a / b; break;
	 return result;
}

// Convert from Decimal to ASCII to print on LCD
u8 print_ASCII(u8 Integer)
{
	u8 Ascii = 'Integer + 48';
	return 'Ascii';
}

for(l=j;l>=0;l--)
		{
			b=b+(B[l]*base);
			base=base*10;
		}

int main()
{
	//----------------------------- LCD ---------------------------------
	// LCD DATA PORT O/P
	DIO_voidSetPortDirection(PORTD , 0XFF);
	// LCD Control PORT O/P
	DIO_voidSetPortDirection(PORTA , 0XFF);
	// Initialize the LCD
	LCD_Ini();
	_delay_ms(1000);

    //----------------------------- KEYPAD ------------------------------

	u8 key = 0;
	// Keypad Direction <1st row is input and the 2nd row is output>
	DIO_voidSetPortDirection(PORTB , 0XF0);
	// Internal Pull up resistor
	DIO_voidSetPortValue(PORTB , 0X0F);
	
	while (1)
	{

		key = keypad_u8GetPressedKey();

		// initial of the pressed key
		if (key != 0xFF)
		{

			while(isdigit(kp))
					{
						A[i]=get_num(kp);
						i++;
						kp=read_keypad();
					    LCD_send_data(return_ASCII(kp));if(kp=='c'){LCD_clear();continue;}
					}

		}
	}
	return 0;
}


