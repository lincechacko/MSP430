#include <msp430.h>
#include <stdio.h>
// Variable to be stored in FRAM
unsigned int my_variable = 42;

int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    my_variable = 99;
    my_variable = *(unsigned int *)0x1800;
    //my_variable = *(unsigned int *)0x1800;
    // Initialize FRAM module
    FRCTL0 = FRCTLPW | NWAITS_1; // Configure FRAM waitstates for MCLK frequency

    // Enable write access to FRAM
    SYSCFG0 = FRWPPW | PFWP;

    // Store variable in FRAM
    *(unsigned int *)0x1800 = my_variable; // Store variable at address 0x1800 in FRAM

    my_variable=55;

    // Disable write access to FRAM
    SYSCFG0 &= ~(FRWPPW | PFWP);

    // Wait for power to be removed

    // Restore variable from FRAM
    my_variable = *(unsigned int *)0x1800; // Restore variable from address 0x1800 in FRAM

    printf("%d",my_variable);
    // Use restored variable

    return 0;
}
