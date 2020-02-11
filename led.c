#include<p18f4550.h>


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

void main()
{   
	TRISA=0x00;
	TRISB=0x00;
	TRISC=0x00;
	TRISD=0x00;
	TRISE=0x07;
		
	//INTCON2bits.RBPU=0;
    //ADCON1=0x0f;
	
    while(1)
    {
         PORTA=0x00;
		 PORTB=0x00;
		 PORTC=0x00;
		 PORTD=0x00;
		 PORTE=0x00;
		 delay(100); 
		 PORTA=0xFF;
		 PORTB=0xFF;
		 PORTC=0xFF;
		 PORTD=0xFF;
		 PORTE=0xFF;
		 delay(100);
	}
}

