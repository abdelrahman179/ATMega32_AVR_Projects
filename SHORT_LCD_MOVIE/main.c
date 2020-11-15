/*************************************************************/
/*  AUTHOR     : AbdElrahman Ibrahim Zaki                    */
/*  DATE       :  											 */
/*  VERSION	   : V0.1										 */
/*  DESCRIPTION: LCD Driver                                  */
/*                                                           */
/*************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_interface.h"
#include<util/delay.h>  // built in library 
#include<stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	DIO_voidSetPortDirection(PORTA , 0XFF);  // All PINs are output
	DIO_voidSetPortDirection(PORTD , 0XFF);

	LCD_Ini();
	_delay_ms(1000);
	
	while (1)
    {// Display a full Arabic name "ÚÈÏå"  on LCD

    	LCD_writeCMD(0X40); // store the custom char in CGROM
    	LCD_writeChar(0b00111);
    	LCD_writeChar(0b00100);
    	LCD_writeChar(0b00100);
    	LCD_writeChar(0b11111);
    	LCD_writeChar(0b00000);
    	LCD_writeChar(0b00000);
    	LCD_writeChar(0b00000);
    	LCD_writeChar(0b00000);


    	LCD_writeCMD(0X48); // store the custom char in CGROM
    	LCD_writeChar(0b00001);
    	LCD_writeChar(0b00001);
    	LCD_writeChar(0b00001);
    	LCD_writeChar(0b11111);
    	LCD_writeChar(0b00100);
    	LCD_writeChar(0b00000);
    	LCD_writeChar(0b00000);
    	LCD_writeChar(0b00000);

    	LCD_writeCMD(0X50); // store the custom char in CGROM
        LCD_writeChar(0b00001);
        LCD_writeChar(0b00001);
        LCD_writeChar(0b00001);
        LCD_writeChar(0b00111);
        LCD_writeChar(0b00000);
        LCD_writeChar(0b00000);
        LCD_writeChar(0b00000);
        LCD_writeChar(0b00000);

    	LCD_writeCMD(0X58); // store the custom char in CGROM
        LCD_writeChar(0b00100);
        LCD_writeChar(0b01010);
        LCD_writeChar(0b10001);
        LCD_writeChar(0b01010);
        LCD_writeChar(0b00100);
        LCD_writeChar(0b00000);
        LCD_writeChar(0b00000);
        LCD_writeChar(0b00000);

    	LCD_writeCMD(0X80); // DDRAM call
    	Cursor_Pos(0,15);
    	LCD_writeChar(0);  // Display the 1st bit of the CGROM
    	Cursor_Pos(0,14);
    	LCD_writeChar(1);  // Display the 2nd bit of the CGROM
    	Cursor_Pos(0,13);
    	LCD_writeChar(2);  // Display the 3rd bit of the CGROM
    	Cursor_Pos(0,12);
    	LCD_writeChar(3);  // Display the 3rd bit of the CGROM

    	// --------------------- Short Story -------------------------------
        /*Cursor_Pos(0,1);
    	LCD_writeString ("LETS INTRODUCE");
    	_delay_ms(1000);
    	LCD_writeCMD(0X01);

    	Cursor_Pos(0,2);
    	LCD_writeString ("THE GREATEST");
    	_delay_ms(1000);
    	LCD_writeCMD(0X01);

    	Cursor_Pos(0,5);
    	LCD_writeString ("PLAYER");
    	_delay_ms(1000);
    	LCD_writeCMD(0X01);

    	Cursor_Pos(0,2);
    	LCD_writeString ("of All TIME");
    	_delay_ms(1000);
    	LCD_writeCMD(0X01);

    	Cursor_Pos(0,3);
    	LCD_writeString ("Leo Messii");

    	for (u8 i=0 ; i<4 ; i++)
    	{
        	Cursor_Pos(1,8);
        	LCD_writeChar(1);  // Display the 2nd bit of the CGROM
        	_delay_ms(500);
        	Cursor_Pos(1,8);
        	LCD_writeChar(0);  // Display the 1st bit of the CGROM
        	_delay_ms(500);
    	}

    	Cursor_Pos(1,8);
    	LCD_writeChar(2);
    	for (u8 j=9; j<16 ;j++)
    	{
    		Cursor_Pos(1,j);
    		LCD_writeChar(3);
    		_delay_ms(100);
    		Cursor_Pos(1,j);
    		LCD_writeChar(4);
    		_delay_ms(100);
    	}
    	LCD_writeCMD(0X01);

    	Cursor_Pos(0,0);
    	LCD_writeString ("Messi");
    	_delay_ms(1000);

    	Cursor_Pos(1,5);
    	LCD_writeString ("Messi");
    	_delay_ms(1000);

    	Cursor_Pos(0,11);
    	LCD_writeString ("Messi");
    	_delay_ms(1000);

    	LCD_writeCMD(0X01);

    	Cursor_Pos(0,4);
    	LCD_writeString ("THE GOAT");

    	for (u8 k=0; k<8 ;k++)
    	{
    		Cursor_Pos(1,8);
      		LCD_writeChar(5);
      		_delay_ms(250);
      		Cursor_Pos(1,8);
      		LCD_writeChar(6);
      		_delay_ms(250);

      	}
    	LCD_writeCMD(0X01);*/

    }
    return 0;
}
