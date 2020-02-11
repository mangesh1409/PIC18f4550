#include<p18f4550.h>

void delay(unsigned int);

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
	TRISCbits.TRISC2=0;     //make CCP1 pin as output
	ADCON1=0x0F;	
	INTCON2bits.RBPU=0;	

	while(1)
	{
		PR2=124;
		CCPR1L=93;			//for 25% duty cycle
		CCP1CON=0x0C;	    //select pwm mode and for 25% duty
                            //cycle write DCxB1:DCxB0=0:1
		T2CON=0x01;			//select prescale 16
		TMR2=0;			    //load Timmer 2 with 0 
		T2CONbits.TMR2ON=1;	//start timmer
	
		while(1)
			{
				PIR1bits.TMR2IF=0;				//clear Timmer 2 Interrput flag
    			while(PIR1bits.TMR2IF==0);		//wait for overflow
    		}
	}
}