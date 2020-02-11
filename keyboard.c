#include<p18f4550.h>

#define data PORTD
#define rs PORTCbits.RC0
#define rw PORTCbits.RC1
#define en PORTCbits.RC2


/*The following lines of code perform interrupt vector relocation to work with the USB bootloader. These must be used with every application program to run as a USB application.*/

extern void _startup (void);
#pragma code _RESET_INTERRUPT_VECTOR = 0x1000
void _reset (void) 
{
	_asm goto _startup _endasm
}
#pragma code

#pragma code _HIGH_INTERRUPT_VECTOR = 0x1008
void high_ISR (void)
{
}
#pragma code

#pragma code _LOW_INTERRUPT_VECTOR = 0x1018
void low_ISR (void)
{
}
#pragma code

/*End of interrupt vector relocation*/
/*Start of main program*/

void delay(unsigned int);
void lcd_init(void);
void lcd_cmd(unsigned int);
void lcd_data(unsigned int);

void delay (unsigned int time)
{	unsigned int i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 200; j++);   /*Calibrated for a 1 ms delay in MPLAB*/
}

void lcd_init(void)
{
  	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x06);
    lcd_cmd(0x0E);
    lcd_cmd(0x80);
}

void lcd_cmd(unsigned int x)
{
   data=x;
   rs=0;
   rw=0;
   en=1;
   delay(50);
   en=0;
   delay(50);
}

void lcd_data(unsigned int y)
{
   data=y;
   rs=1;
   rw=0;
   en=1;
   delay(50);
   en=0;
   delay(50);
}

void main()
{
	unsigned char a[]={"Press Any Key="},i;
	int j;

	TRISB=0xF0;
	TRISD=0x00;
	TRISC=0x00;
    
	INTCON2bits.RBPU=0;
	ADCON1=0x0f;

	lcd_init();
	delay(50);

	for(i=0;i<=12;i++)
		{
			lcd_data(a[i]);
			delay(50);
		}
	
	while(1)
	{                           
		
		for(j=0;j<4;j++)
		{
			PORTB=(0xF7<<j)|0xF0;
			delay(50);
			
			lcd_cmd(0xC0);

		if(PORTB==0xEE)
			lcd_data('0');

			else if(PORTB==0xDE)
			lcd_data('1');
			
			else if(PORTB==0xBE)
			lcd_data('2');
	
			else if(PORTB==0x7E)
			lcd_data('3');
	
			else if(PORTB==0XED)
			lcd_data('4');
	
			else if(PORTB==0xDD)
			lcd_data('5');
	
			else if(PORTB==0xBD)
			lcd_data('6');
	
			else if(PORTB==0x7D)
			lcd_data('7');
	
			else if(PORTB==0xEB)
			lcd_data('8');
	
			else if(PORTB==0xDB)
			lcd_data('9');
	
			else if(PORTB==0xBB)
			lcd_data('A');
	
			else if(PORTB==0x7B)
			lcd_data('B');
	
			else if(PORTB==0xE7)
			lcd_data('C');
	
			else if(PORTB==0xD7)
			lcd_data('D');
	
			else if(PORTB==0xB7)
			lcd_data('E');
	
			else if(PORTB==0x77)
			lcd_data('F');

		else
			if(i=4)
				{
					i=0;
				}
		}
	}
}