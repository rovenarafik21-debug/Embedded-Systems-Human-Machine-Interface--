#ifndef LM35_H
#define LM35_H

/* Nominal AVCC voltage in millivolts; update after measurement if needed. */
#define LM35_REFERENCE_MV 5000UL
/* Returns tenths of a degree Celsius: 254 means 25.4 C.
   ADC_Init must be called first. Intended for positive temperatures. */
unsigned int LM35_ReadTemperature(void);
#endif
