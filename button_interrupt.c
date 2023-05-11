#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR=0x01;

	P2REN |= 0x08;                 // Enable internal pull-up/down resistors
	P2OUT |= 0x08;
	P2IE=0x08;
	P2IES=0x08;
	P2IFG=0x00;
	_enable_interrupt();

	while(1)
	{

	}

}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P1OUT^=0x01;
    P2IFG=0x00;
}
