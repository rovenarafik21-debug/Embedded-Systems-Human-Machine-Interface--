#ifndef LCD_H
#define LCD_H

/* Four-bit LCD interface. Pin mapping is in LCD.c. */
void LCD_Init(void);
void LCD_Command(unsigned char command);
void LCD_Character(unsigned char character);
void LCD_Text(const char text[]);

#endif
