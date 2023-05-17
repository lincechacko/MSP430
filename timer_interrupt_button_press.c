#include <msp430.h> 
int counterbutton=0;

/**
 * main.c
 */
int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR=BIT0|BIT1;

    P2REN |= 0x08 | 0x80;                 // Enable internal pull-up/down resistors
    P2OUT |= 0x08 | 0x80;

    TA0CTL = TASSEL_2 | ID__8| MC__UP;   // Select SMCLK as the timer clock source , Set the input divider to divide by 1
    TA0CCR0 = 6250 - 1;
    TA0CCTL0 = CCIE;
    _enable_interrupt();

    while(1)
    {

    }

}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void)
{

    if((P2IN & 0x08)!=0x08)
    {

        if(counterbutton==100)
           {
               P1OUT^=BIT1;

           }
        counterbutton++;

    }
    else
    {
        if(counterbutton>100 )
        {
            counterbutton=0;
        }
        else if(counterbutton>1 )
        {
            P1OUT^=BIT0;
            counterbutton=0;
        }

    }


}

