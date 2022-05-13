#include "Lcd_16x2_Driver.h"

void delay(int ms)
{
    int i,j;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<1000;j++);
    }
}

void lcd_enable()
{
    EN=1;
    delay(10);
    EN=0;
    delay(10);
}
#ifdef LCD_4BIT
void lcd_command(char a) //char or int 
{
    RS=0; //command
    LCD=(a&0xf0)|(LCD&0x0f);
    lcd_enable();
    LCD=((a<<4)&(0xf0))|(LCD&0x0f);//4 bit mode
    lcd_enable();
    delay(10);
}

void lcd_data(char a) //char or int
{
    RS=1; //data
    LCD=(a&0xf0)|(LCD&0x0f);
    lcd_enable();
    LCD=((a<<4)&(0xf0))|(LCD&0x0f);//4 bit mode
    lcd_enable();
    delay(10);
}
#elif defined(LCD_8BIT)
void lcd_command(char a) //char or int 
{

   LCD=a;
   //delay(10);
   RS=0; //command
   lcd_enable();
}

void lcd_data(char a) //char or int
{
    LCD=a;
    delay(10);
    RS=1; //data
    lcd_enable();
}
#else
  #error "LCD bit is not defined"
#endif

void lcd_string(char *a)
{
    while(*a!='\0')
    {
        lcd_data(*a);
        a++;        
    }
}

void lcd_numbers(int a) //for numbers
{
    if(a>=0)
    {
        lcd_data(a+48);//decimal (48 is for 0 in ascii table)
    }
    else
    {
        lcd_data('-');
        lcd_data(abs(a)+48);
    }
}

void lcd_position(int row,int column)
{
    switch(row)
    {
        case 0:
            lcd_command(0x80+column);
            break;
         
        case 1:
            lcd_command(0xC0+column);
            break;
            
    }
}
void lcd_displayon_cursoron()
{
    lcd_command(0x0E);
}
void lcd_displayon_cursoroff()
{
    lcd_command(0x0C);
}
void lcd_displayoff_cursoron()
{
    lcd_command(0x0A);
}
void lcd_displayoff_cursoroff()
{
    lcd_command(0x08);
}
void lcd_clear(void)
{
    lcd_command(0x01);
}
void lcd_initialize(void)
{
    RW=0; //for write operation
    #ifdef LCD_8BIT
    lcd_command(0x38); //8 bit mode
    #elif defined (LCD_4BIT)
    lcd_command(0x02);//4bit mode
    lcd_command(0x28);//4bit mode
#else
#error "LCD Bit Not defined"
#endif
    lcd_displayon_cursoron();
    //lcd_command(0x06);  //auto increment 
    lcd_position(0,0); 
}

void string_rev(char *a)
{
    int i,j=0;
    char b[10];
    
    for(i=0;a[i]!='\0';i++);
    i--;
    while(i>=0)
    {
    b[j]=a[i];
    i--;
    j++;
    }  
    for(i=0;b[i]!='\0';i++)
    {
        a[i]=b[i];
    }
}

int digit_split_a(char *b,int a)
{
    int mod;
    int i=0;
    while(a>0)
    {
        mod=a%10;
        b[i]=mod+48;
        i++;
        a=a/10;
    }
    string_rev(b);
    b[i]='\0';
    return i;
}