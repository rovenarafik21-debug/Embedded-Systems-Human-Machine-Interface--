#include <avr/io.h>
#include "dio.h"
#include "ADC.h"

/* Select ADC0, AVCC reference and 125 kHz ADC clock at 16 MHz. */
void ADC_Init(void)
{
    DIO_SetPinDirection('c', 0, 'i');
    DIO_SetPinState('c', 0, 'l');
    DIDR0 |= (1 << ADC0D);
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) |
             (1 << ADPS1) | (1 << ADPS0);
    ADC_Read(); /* Discard the first conversion. */
}
/* Start a conversion, wait for completion and return 0..1023. */
unsigned int ADC_Read(void)
{
    ADCSRA |= (1 << ADSC);
    while ((ADCSRA & (1 << ADSC)) != 0) { }
    return ADC;
}