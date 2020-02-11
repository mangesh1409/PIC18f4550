#include<p18f4550.h>

#define rs PORTBbits.RB0
#define en PORTBbits.RB1
#define out PORTD


void delay(unsigned int);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_init();
void conversion();

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
  lcd_cmd(0x80);
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

void conversion()
{  
   	unsigned int a,b,c,d,e,f,g,h,i,j,c1;
	a=ADRESL;
	b=ADRESH;

	j=b<<8;
	c=a|j;

	c1=c*0.488;
	d=c1/1000;
	e=c1%1000;
	f=e/100;
	g=e%100;
	h=g/10;
	i=g%10;

    lcd_cmd(0xC5);
	lcd_data(f+0x30);
	lcd_data('.');
	lcd_data(h+0x30);
	lcd_data(i+0x30);
	lcd_data('V');
}

void main(void)
{
	unsigned char a[]={"ADC Reading"};
	unsigned char b[]={"Vout="};
	int i,j;

	ADCON0=0X01;
	ADCON1=0X0E;
	ADCON2=0X96;
	
	TRISA=0xFF;
	TRISB=0x00;
	TRISD=0x00;

	lcd_init();
    delay(10);

    lcd_cmd(0x80);
	  for(i=0;i<=10;i++)
	    {
		   lcd_data(a[i]);
			delay(10);
        }
    
	lcd_cmd(0xC0);
	  for(j=0;j<=4;j++)
	    {
		  lcd_data(b[j]);
		  delay(10);
        }


	while(1)
	{
		ADCON0bits.GO=1;
		while(ADCON0bits.GO==1);
		conversion();
	}
}
