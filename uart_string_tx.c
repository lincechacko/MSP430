#include <msp430.h>

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

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    configureUART();            // Configure UART

    __bis_SR_register(GIE);     // Enable global interrupts

    while (1)
    {
        // Your application code here

        // Example: Transmit a string ("Hello, World!") every second
        transmitString("Hello, World! UART IS WORKING\r\n");
        __delay_cycles(1000000);
    }
}
