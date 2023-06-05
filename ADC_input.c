
#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
unsigned int ADC_value=1;
void configureUART()
{
    // Configure UART pins (P1.2 = RX, P1.3 = TX)
    P1SEL0 |= BIT4 | BIT5;
    P1SEL1 &= ~(BIT4 | BIT5);

    // Configure USCI_A0 module for UART mode
    UCA0CTLW0 |= UCSWRST;       // Put USCI in reset mode
    UCA0CTLW0 |= UCSSEL__SMCLK; // Select SMCLK as the clock source
    UCA0BRW = 6;                // Set the Baud rate (9600 with SMCLK = 1 MHz)
    UCA0MCTLW |= UCOS16 | UCBRF_8 | 0x8000; // Configure modulation

    UCA0CTLW0 &= ~UCSWRST;      // Initialize USCI
    UCA0IE |= UCRXIE;           // Enable RX interrupt
}
void transmitByte(unsigned char data)
{
    // Wait for the transmit buffer to be ready
    while (!(UCA0IFG & UCTXIFG));

    // Write data to the transmit buffer
    UCA0TXBUF = data;
}

void transmitString(const char* str)
{
    // Iterate through the string until the null terminator is reached
    while (*str != '\0')
    {
        // Transmit each character of the string
        transmitByte(*str);
        str++;
    }
}
char str[20];
int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode to activate
    P1SEL1 |= BIT2;
    P1SEL0 |= BIT2;

    configureUART();            // Configure UART

    __bis_SR_register(GIE);     // Enable global interrupts

    ADCCTL0 &= ~ADCSHT1;       //set conv clock cycles = 16 (10)
    ADCCTL0 |= ADCSHT_2;
    ADCCTL0 |= ADCON;         //TURN ON ADC

    ADCCTL1  |= ADCSSEL_2;    //choose smclk
    ADCCTL1 |= ADCSHP;        //sample signal source = sampling timer

    ADCCTL2 &= ~ADCRES;       //clear resolution
    ADCCTL2 |= ADCRES_1;      //12 bit resolution

    ADCMCTL0 |= ADCINCH_2;

    while(1)
    {
        ADCCTL0 |= ADCENC | ADCSC;

        while( (ADCIFG & ADCIFG0)==0 );

        ADC_value = ADCMEM0;
        sprintf(str,"analog value is %d\r\n",ADC_value);
        transmitString(str);
        __delay_cycles(1000000);
    }
}


