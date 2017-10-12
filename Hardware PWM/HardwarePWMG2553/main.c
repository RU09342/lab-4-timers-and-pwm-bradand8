//Hardware PWM G2553
//Updated 10/11/2017
//Brad Anderson

#include <msp430.h> 


/**
 * main.c
 */

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    TA0CTL = TASSEL_2 + MC_1; //1M Hz clock, Up count mode,
    TA0CCR0 = 1000; //1K Hz signal max
    TA0CCR1 = 500;  //50% duty cycle for Cap/Comp register


    TA1CTL = TASSEL_2 + MC_1 + ID_3; //1M Hz clock, Up count divided by 81MHz/8=125kHz
    TA1CCTL0 = CCIE; //enable interrupt CC1

    TA0CCTL1 = OUTMOD_4; // Toggles when CCR1 value reached

    P1DIR &= ~BIT6; //Button Input

    P1REN |= BIT6; //enable resister

    P1OUT |= BIT6; //becomes pullup resistor


    P1IE |= BIT6; //enable interrupt on button

    P1IES |= BIT6; //interrupt edge select

    P1IFG &= ~BIT6; //clears interrupt  flag


    P1DIR |= BIT0;  //LED becomes output

    P1OUT &= ~(BIT0); //starts LED off

    __enable_interrupt();


    for(){}

  }

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) //ISR for the button press
{
    TA1CTL = TASSEL_2 + MC_1 + ID_3;  //1M Hz Clock, Up count, clock divider 8
    P1IE &= ~BIT6;   //Enables button interrupt
    P1IES ^= BIT6; //Toggle interrupt rising edge
    P1IFG &= ~BIT6;  // Clears interrupt flag for button


    if(!(P1IES & BIT6)  = BIT6){
        TA0CCR1 = (TA0CCR1 + 100);
        P1OUT ^= BIT0; //Toggles LED
        if(TA0CCR1 > 1000){
            TA0CCR1 = 0;
            P1OUT ^= BIT0; //Toggles LED
        else
        }
    }
}
//ISR for Timer
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer_A1(void)
{
    P1IE |= BIT6;   //Enable Button Interrupt
    TA1CTL = TASSEL_2 + MC_0 +ID_3 + TACLR;
    P1IFG &= BIT6; //enables interrupt flag
}
