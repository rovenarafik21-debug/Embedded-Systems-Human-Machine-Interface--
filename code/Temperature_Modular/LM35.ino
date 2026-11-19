#include "ADC.h"
#include "LM35.h"

/* LM35 gives 10 mV/C, so 1 mV represents 0.1 C.
   Convert ADC reading to millivolts using nominal AVCC.
   unsigned long prevents overflow on the AVR's 16-bit int. */
unsigned int LM35_ReadTemperature(void)
{
    unsigned int reading = ADC_Read();
    return ((unsigned long)reading * LM35_REFERENCE_MV + 512UL) / 1024UL;
}
