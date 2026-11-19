#include <avr/io.h>
#include "dio.h"
/* Based on dio(1).ino. Use ~ to clear a bit, not logical !. */
/* Choose whether a pin is an input ('i') or output ('o').
   Change only the selected DDR bit and leave the other pins unchanged. */
void DIO_SetPinDirection(unsigned char port, int pin, unsigned char direction)
{
    if (pin < 0 || pin > 7)
    {
        return;
    }
    if (port == 'b') {
        if (direction == 'o')
        {
            DDRB = DDRB | (1 << pin);
        }
        else if (direction == 'i')
        {
            DDRB = DDRB & ~(1 << pin);
        }
    } else if (port == 'c') {
        if (direction == 'o')
        {
            DDRC = DDRC | (1 << pin);
        }
        else if (direction == 'i')
        {
            DDRC = DDRC & ~(1 << pin);
        }
    } else if (port == 'd') {
        if (direction == 'o')
        {
            DDRD = DDRD | (1 << pin);
        }
        else if (direction == 'i')
        {
            DDRD = DDRD & ~(1 << pin);
        }
    }
}
/* Set a pin high ('h') or low ('l').
   On an input pin, high enables its internal pull-up resistor. */
void DIO_SetPinState(unsigned char port, int pin, unsigned char state)
{
    if (pin < 0 || pin > 7)
    {
        return;
    }
    if (port == 'b') {
        if (state == 'h')
        {
            PORTB = PORTB | (1 << pin);
        }
        else if (state == 'l')
        {
            PORTB = PORTB & ~(1 << pin);
        }
    } else if (port == 'c') {
        if (state == 'h')
        {
            PORTC = PORTC | (1 << pin);
        }
        else if (state == 'l')
        {
            PORTC = PORTC & ~(1 << pin);
        }
    } else if (port == 'd') {
        if (state == 'h')
        {
            PORTD = PORTD | (1 << pin);
        }
        else if (state == 'l')
        {
            PORTD = PORTD & ~(1 << pin);
        }
    }
}
/* Read one pin and return its electrical level: 0 = low, 1 = high. */
unsigned char DIO_ReadPin(unsigned char port, int pin)
{
    if (pin < 0 || pin > 7)
    {
        return 0;
    }
    if (port == 'b')
    {
        return (PINB >> pin) & 1;
    }
    if (port == 'c')
    {
        return (PINC >> pin) & 1;
    }
    if (port == 'd')
    {
        return (PIND >> pin) & 1;
    }
    return 0;
}
/* Configure this temperature project's LED and two buttons.
   D2 is used by the LCD, so the previous project's D2 input is removed. */
void DIO_init(void)
{
    DIO_SetPinState('b', 0, 'l');
    DIO_SetPinDirection('b', 0, 'o'); /* D8: alert LED. */
    DIO_SetPinDirection('b', 1, 'i'); /* D9: high-limit button. */
    DIO_SetPinState('b', 1, 'h');
    DIO_SetPinDirection('b', 2, 'i'); /* D10: low-limit button. */
    DIO_SetPinState('b', 2, 'h');
}
