/**
 * Debouncing F5529
 * Created by TI
 * Edited by Bradley Anderson
 * Last Edited 10/11/2017
 */

#include <msp430.h> 
#define LED_0   BIT0
#define BUTTON1  BIT1

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer


            P1DIR |= LED_0;       //sets bit 0 of P1 as the output
            P2REN |= BUTTON1;       //Enables Pullup resistor on Button1
            P2OUT |= BUTTON1;       //Makes pullup resistor for button1

            P2IES &= BUTTON1;     //interrupts when button is pressed
            P2IE |= BUTTON1;       //enables interupt for button
            P2IFG &= ~BUTTON1;     //ands the interupt flag with 0 to clear it

                TA0CCTL0 = CCIE;  //enables CCR0
                TA0CCR0 = 40000;           // Control Capture Reg value
                TA0CTL = TASSEL_2 + MC_0 + TACLR; // SMCLK, Stop Clock. clear TA0R

                __enable_interrupt();   // interrupts get enabled
                __bis_SR_register(LPM0 + GIE); // LPM0 with general interrupts enabled

            for (;;){}   //Initializes a continuous loop
}

//Port 1 ISR
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){

    P1OUT ^= LED_0;                     //Toggle LED
    P2IE &= ~BUTTON1;                   //Disables Interrupt
    TA0CTL = TASSEL_2 + MC_1 + TACLR;   //Uses SMCLK in Up count mode and Clears TA0R
    P2IFG &= ~BUTTON1;                  //Resets Interrupt Flag
}

//Timer A0 Interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void) {
    TA0CTL = MC_0; // Pauses timer
    P2IE |= BUTTON1; //enables interrupt
    P2IFG &= ~BUTTON1; //Resets Interrupt Flag
}











