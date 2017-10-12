//Hardware PWM FR5994
//Updated 10/11/2017
//Brad Anderson

#include <msp430.h> 


/**
 * main.c
 */

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //needed for  FR5994

    TA0CTL = TASSEL_2 + MC_1; //1M Hz clock, Up count mode,
    TA0CCR0 = 1000; //1K Hz signal max
    TA0CCR1 = 500;  //50% duty cycle for Cap/Comp register


    TA1CTL = TASSEL_2 + MC_1 + ID_3; //1M Hz clock, Up count divided by 81MHz/8=125kHz
    TA1CCTL0 = CCIE; //enable interrupt CC1

    TA0CCTL1 = OUTMOD_4; // Toggles when CCR1 value reached

    P5DIR &= ~BIT5; //Button Input

    P5REN |= BIT5; //enable resister

    P5OUT |= BIT5; //becomes pullup resistor


    P5IE |= BIT5; //enable interrupt on button

    P5IES |= BIT5; //interrupt edge select

    P5IFG &= ~BIT5; //clears interrupt  flag


    P1DIR |= BIT0;  //LED becomes output

    P1OUT &= ~(BIT0); //starts LED off

    __enable_interrupt();


    for(){}

  }

#pragma vector = PORT5_VECTOR
__interrupt void Port_5(void) //ISR for the button press
{
    TA1CTL = TASSEL_2 + MC_1 + ID_3;  //1M Hz Clock, Up count, clock divider 8
    P5IE &= ~BIT5;   //Enables button interrupt
    P5IES ^= BIT5; //Toggle interrupt rising edge
    P5IFG &= ~BIT5;  // Clears interrupt flag for button


    if(!(P5IES & BIT5)  = BIT5){
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
    P5IE |= BIT5;   //Enable Button Interrupt
    TA1CTL = TASSEL_2 + MC_0 +ID_3 + TACLR;
    P5IFG &= BIT5; //enables interrupt flag
}
