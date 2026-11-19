#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "dio.h"
#include "LCD.h"

/* LCD RS=D7, E=D6; LCD D4..D7 connect to Uno D5,D4,D3,D2.
   LCD RW is physically connected to GND. */
#define LCD_RS 7
#define LCD_E  6
/* Send four bits and pulse Enable. Private to this module.
   Preserve the conservative timing that worked on the user's LCD. */
static void LCD_SendFourBits(unsigned char value)
{
    DIO_SetPinState('d', LCD_E, 'l');
    DIO_SetPinState('d', 5, ((value >> 0) & 1) ? 'h' : 'l');
    DIO_SetPinState('d', 4, ((value >> 1) & 1) ? 'h' : 'l');
    DIO_SetPinState('d', 3, ((value >> 2) & 1) ? 'h' : 'l');
    DIO_SetPinState('d', 2, ((value >> 3) & 1) ? 'h' : 'l');
    _delay_ms(1);
    DIO_SetPinState('d', LCD_E, 'h');
    _delay_ms(1);
    DIO_SetPinState('d', LCD_E, 'l');
    _delay_ms(1);
}
/* Send an instruction, upper four bits first. */
void LCD_Command(unsigned char command)
{
    DIO_SetPinState('d', LCD_RS, 'l');
    LCD_SendFourBits(command >> 4);
    LCD_SendFourBits(command & 15);
    _delay_ms(2);
}
/* Send one display character. */
void LCD_Character(unsigned char character)
{
    DIO_SetPinState('d', LCD_RS, 'h');
    LCD_SendFourBits(character >> 4);
    LCD_SendFourBits(character & 15);
    _delay_ms(2);
}
/* Print text until its ending zero. */
void LCD_Text(const char text[])
{
    unsigned char i = 0;
    while (text[i] != '\0')
    {
        LCD_Character(text[i]);
        i++;
    }
}
/* Configure the pins and initialize the LCD in four-bit, two-row mode. */
void LCD_Init(void)
{
    unsigned char pin;
    for (pin = 2; pin <= 7; pin++)
    {
        DIO_SetPinState('d', pin, 'l');
        DIO_SetPinDirection('d', pin, 'o');
    }
    _delay_ms(50);
    LCD_SendFourBits(3);
    _delay_ms(5);
    LCD_SendFourBits(3);
    _delay_ms(5);
    LCD_SendFourBits(3);
    _delay_ms(5);
    LCD_SendFourBits(2);
    _delay_ms(5);
    LCD_Command(0x28);
    LCD_Command(0x08);
    LCD_Command(0x01);
    LCD_Command(0x06);
    LCD_Command(0x0C);
}
