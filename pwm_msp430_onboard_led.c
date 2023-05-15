#include <msp430.h>


int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    //P1.0 as PWM output
    P1DIR |= BIT1;
    P1SEL0 &= ~BIT1;
    P1SEL1 |= BIT1;


    TA0CCR0 = 1000; //Set the period in the Timer A0 Capture/Compare 0 register to 1000 us.
    TA0CCTL1 = OUTMOD_7;
    TA0CCR1 = 1000; //The period in microseconds that the power is ON. It's half the time, which translates to a 50% duty cycle.
    TA0CTL = TASSEL_2 + MC_1; //TASSEL_2 selects SMCLK as the clock source, and MC_1 tells it to count up to the value in


    while (1)
    {

    }

}
