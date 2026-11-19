#ifndef ADC_H
#define ADC_H

/* This project reads A0 (ADC0) using the AVCC reference. */
void ADC_Init(void);
unsigned int ADC_Read(void);

#endif
