#ifndef DIO_H
#define DIO_H
/* Existing DIO interface, reused for the temperature project. */
void DIO_init(void);
void DIO_SetPinDirection(unsigned char port, int pin, unsigned char direction);
void DIO_SetPinState(unsigned char port, int pin, unsigned char state);
unsigned char DIO_ReadPin(unsigned char port, int pin);
#endif
