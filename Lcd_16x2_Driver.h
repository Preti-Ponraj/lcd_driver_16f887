#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <xc.h>
#include <math.h>
#include <stdlib.h>

#define EN RE0
#define RW RE1
#define RS RE2
#define LCD PORTB
#define LCD_4BIT 
void delay(int ms);
void lcd_enable();
void lcd_command(char a);
void lcd_data(char a);
void lcd_string(char *a);
void lcd_numbers(int a); //for numbers
void lcd_position(int row,int column);
void lcd_displayon_cursoron();
void lcd_displayon_cursoroff();
void lcd_displayoff_cursoron();
void lcd_displayoff_cursoroff();
void lcd_clear(void);
void lcd_initialize(void);
void string_rev(char *a);
int digit_split_a(char *b,int a);

#endif
