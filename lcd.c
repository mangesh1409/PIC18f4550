#include<p18f4550.h>

#define rs PORTBbits.RB0
#define en PORTBbits.RB1
#define out PORTD

void delay(unsigned int);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_init();

unsigned char a[]={"Wish You Many Many"};
unsigned char b[]={"Happy Returns Of The"};
unsigned char c[]={"Day"};

unsigned char d[]={"!Chota   Bheem!"};
int i,j,k,l;

extern void _startup(void);
#pragma code _RESET_INTERRUPT_VECTOR=0x1000
void_reset(void) 
{
	_asm goto _startup _endasm
}
	
#pragma code
#pragma code _HIGH_INTERRUPT_VECTOR=0x1008

void high_ISR (void)
{
}

#pragma code
#pragma code _LOW_INTERRUPT_VECTOR=0x1018
	
void low_ISR (void)
{
}

#pragma code

void delay(unsigned int time)
{
   unsigned int i,j;
   for (i=0;i<time;i++)
   for (j=0;j<710;j++);
}

void lcd_init(void)
{
  lcd_cmd(0x38);
  lcd_cmd(0x06);
  lcd_cmd(0x01);
  lcd_cmd(0x0E);
}

void lcd_cmd(unsigned char x)
{
  out=x;
  rs=0;
  en=1;
  delay(10);
  en=0;
  delay(10);
} 

void lcd_data(unsigned char y)
{
  out=y;
  rs=1;
  en=1;
  delay(10);
  en=0;
  delay(10);
} 

void main()
{
	TRISB = 0x00;
	TRISD = 0x00;
    
	INTCON2bits.RBPU=0;
	ADCON1=0x0F;

	lcd_init();
	delay(50);

	while(1)
	{
		lcd_cmd(0x81);
		for(i=0;i<=17;i++)
		{
			lcd_data(a[i]);
			delay(10);
		}
		lcd_cmd(0xC0);
		for(j=0;j<=19;j++)
		{
			lcd_data(b[j]);
			delay(10);
		}
		lcd_cmd(0x9C);
		for(k=0;k<=2;k++)
		{
			lcd_data(c[k]);
			delay(10);
		}
		lcd_cmd(0xD6);
		for(l=0;l<=14;l++)
		{
			lcd_data(d[l]);
			delay(10);
		}
		delay(1000);
		lcd_cmd(0x01);
	}
}

 