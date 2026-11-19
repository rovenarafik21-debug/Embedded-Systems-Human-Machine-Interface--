#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "dio.h"
#include "LCD.h"
#include "ADC.h"
#include "LM35.h"

#if !defined(__AVR_ATmega328P__) || F_CPU != 16000000UL
#error "Select Arduino Uno / ATmega328P at 16 MHz."
#endif

/* Uno D8=PB0, D9=PB1, D10=PB2. */
#define ALERT_LED   0
#define HIGH_BUTTON 1
#define LOW_BUTTON  2

static unsigned char low_limit = 20;
static unsigned char high_limit = 27;
static unsigned char high_pressed = 0;
static unsigned char low_pressed = 0;

/* Debounce by rechecking each changed input after 20 ms.
   Update once per press. Release before pressing again.
   LH cycles from LL+1 to 100; LL cycles from 0 to LH-1. */
static unsigned char Buttons_Check(void)
{
    unsigned char high_now;
    unsigned char low_now;
    unsigned char changed = 0;

    high_now = DIO_ReadPin('b', HIGH_BUTTON) == 0;
    if (high_now != high_pressed)
    {
        _delay_ms(20);
        high_now = DIO_ReadPin('b', HIGH_BUTTON) == 0;
        if (high_now != high_pressed)
        {
            high_pressed = high_now;
            if (high_pressed == 1)
            {
                if (high_limit < 100) high_limit++;
                else high_limit = low_limit + 1;
                changed = 1;
            }
        }
    }

    low_now = DIO_ReadPin('b', LOW_BUTTON) == 0;
    if (low_now != low_pressed)
    {
        _delay_ms(20);
        low_now = DIO_ReadPin('b', LOW_BUTTON) == 0;
        if (low_now != low_pressed)
        {
            low_pressed = low_now;
            if (low_pressed == 1)
            {
                if (low_limit + 1 < high_limit) low_limit++;
                else low_limit = 0;
                changed = 1;
            }
        }
    }
    return changed;
}

/* Format application values on the LCD, overwriting both complete rows.
   The old LCD_Number function is removed; digits are printed here. */
static void Display_Update(unsigned int temperature, unsigned char alert)
{
    unsigned int whole = temperature / 10;
    LCD_Command(0x80);
    LCD_Text("T:");
    LCD_Character('0' + whole / 100);
    LCD_Character('0' + (whole / 10) % 10);
    LCD_Character('0' + whole % 10);
    LCD_Character('.');
    LCD_Character('0' + temperature % 10);
    LCD_Text("C ");
    if (alert == 1) LCD_Text("ALERT  ");
    else LCD_Text("OK     ");

    LCD_Command(0xC0);
    LCD_Text("LL:");
    LCD_Character('0' + low_limit / 100);
    LCD_Character('0' + (low_limit / 10) % 10);
    LCD_Character('0' + low_limit % 10);
    LCD_Text(" LH:");
    LCD_Character('0' + high_limit / 100);
    LCD_Character('0' + (high_limit / 10) % 10);
    LCD_Character('0' + high_limit % 10);
    LCD_Text("   ");
}

/* Integrate the modules: read temperature, adjust limits, update alert. */
int main(void)
{
    unsigned int temperature;
    unsigned char alert;
    unsigned char changed;
    unsigned char refresh = 20;

    DIO_init();
    LCD_Init();
    ADC_Init();

    while (1)
    {
        changed = Buttons_Check();
        temperature = LM35_ReadTemperature();
        alert = temperature < (unsigned int)low_limit * 10 ||
                temperature > (unsigned int)high_limit * 10;
        DIO_SetPinState('b', ALERT_LED, alert ? 'h' : 'l');

        if (refresh >= 20 || changed == 1)
        {
            Display_Update(temperature, alert);
            refresh = 0;
        }
        _delay_ms(10);
        refresh++;
    }
    return 0;
}
