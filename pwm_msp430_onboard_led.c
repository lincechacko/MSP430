#include <msp430.h>


int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    //P1.0 as PWM output
    P1DIR |= BIT1;
    P1SEL0 &= ~BIT1;
    P1SEL1 |= BIT1;


    TA0CCR0 = 1000-1; //Set the period in the Timer A0 Capture/Compare 0 register to 1000 us.
    TA0CCTL1 = OUTMOD_7;
    TA0CCR1 = 1000; //The period in microseconds that the power is ON. It's half the time, which translates to a 50% duty cycle.
    TA0CTL = TASSEL_2 + MC_1; //TASSEL_2 selects SMCLK as the clock source, and MC_1 tells it to count up to the value in


    while (1)
    {

    }

}


/* for multiple pin pwm 
#include <msp430.h>
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= BIT1 | BIT2;                     // P1.1 and P1.2 output
    P1SEL1 |= BIT1 | BIT2;                    // P1.1 and P1.2 options select
    P1DIR |= BIT4 + BIT5;
    P1SEL1 |= BIT4 + BIT5;

    TA0CCR0 = 1000-1;                         // PWM Period
    TA1CCR0 = 1000-1;                         // PWM Period

    TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set LED2_WW
    TA1CCTL1 = OUTMOD_7;
    TA0CCTL2 = OUTMOD_7;
    TA1CCTL2 = OUTMOD_7;


    TA0CTL = TASSEL__SMCLK | MC__UP | TACLR;  // SMCLK, up mode, clear TAR
    TA1CTL = TASSEL__SMCLK | MC__UP | TACLR;  // SMCLK, up mode, clear TAR

    TA0CCR1 = 100;
    TA0CCR2 = 100;
    TA1CCR1 = 100;
    TA1CCR2 = 100;

    while (1)
    {

    }
}
*/
