#include<p18f4550.h>

/*The following lines of code perform interrupt vector relocation to work
 with the USB bootloader. These must be used with every application
 program to run as a USB application.*/

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
	
void delay(unsigned int time)
{
	unsigned int i,j;
	for (i=0;i<time;i++)
	for (j=0;j<710;j++);		/*Calibrated for a 1 ms delay in MPLAB*/
}

void main()
{
  unsigned int a[10]={0xC0,0xF9,0xA4,0xB0,0X99,0X92,
                      0X82,0XF8,0X80,0X90},i,j;

  TRISD=0x00;                  //PORTD use as OUTPUT port
  
	while(1)
     {
       for(i=0;i<=9;i++)
          {
             PORTD=a[i];
             delay(300);
		  }
	}
}