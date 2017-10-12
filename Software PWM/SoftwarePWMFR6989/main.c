/**
 * Software PWM FR6989
 * Created by Bradley Anderson
 * Last Edit 10/11/2017
 */


#include <msp430g2253.h>

#define LED1        BIT0
#define LED2        BIT7
#define LED_DIR1    P1DIR
#define LED_DIR2    P9DIR
#define LED_OUT1    P1OUT
#define LED_OUT2    P9OUT
#define BUTTON      BIT1
#define BUTTON_IN   P1DIR


void ledSetup();
void buttonSetup();
void timerA0Setup();
void timerA1Setup();

int main(void){

    // Stop watchdog timer
    WDTCTL = WDTPW + WDTHOLD;

    ledSetup();  //Initialize LEDS
    buttonSetup(); //Initialize our button
    timerA0Setup();   //Initialize Timer0
    timerA1Setup();  //initialize TimerA1

    __enable_interrupt();
    __bis_SR_register(LPM0_bits + GIE);  //Low powermode 0 plus global interrupt enable
}

//button interrupt
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {

    if (P1IN & BUTTON){   //if button is pressed
        LED_OUT1 ^= LED1; //toggles LED 1
        LED_OUT2 = ~LED2; //LED 2 turns off
        TA0CCR1 = TA0CCR1 + 100;  //Duty cycle increases by 10%
    }
    else {
        LED_OUT2 |= LED2


        }


    P1IFG &= ~BUTTON; //clears intterupt flag

}


void ledSetup(){

    LED_DIR1 |= (LED1);   //Sets P1.0 as output
    LED_DIR2 |= (LED2);  //Sets LED 2 as output
    LED_OUT2 |= (LED2);  //Sets LED2 on at start
    LED_OUT1 &= ~(LED1); //Sets LED1 Off at start


void buttonSetup(){

   BUTTON_IN &= ~BUTTON;  //BUTTON becomes an input
    P1REN |= BUTTON; // enables resistor for button
    P1OUT |= BUTTON; //makes pullup resistor
    P1IE |= BUTTON;  //enables interrupt on button press
    P1IES |= BUTTON; //sets interrupt on falling edge


    P1IE |=BUTTON; //enable interrupt on port 1.3
    P1IES |=BUTTON; //sets as falling edge
    P1IFG &=~BUTTON;//clear interrupt flag
}

void timerA1Setup(){

    TA0CCR1 |= 500; //PWM start 50% Duty cycle     .50 X10000K Hz freq = 500ticks led on  Duty cycle = TACCR1/ TACCR0 +1

    TA0CCTL1 |= OUTMOD_7; //counts up and then resets when hit TA0CCR0
    // SMCLK, Up Mode (Counts to TA0CCR0)
    TA0CTL |= TASSEL_2 + MC_1 + ID_3; //1M hz clock upcount mode divided by 8

    _BIS_SR(LPM0_bits + GIE);       // enable interrupts in lowpowermode 0
}

void timerA0Setup(){

    TA0CCTL0 = CCIE;  //Enable capture compare interrupt
    TA0CTL = TASSEL_2 + MC_1 + ID_3;  //Uses 1000000Hz clock, divided by 8 in Up count mode
    TA0CCR0 = 1000;





