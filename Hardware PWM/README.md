# Hardware PWM
Reproduces the effect of the previous lab but utilizing hardware for PWM.

## Implementation
This lab required the use of a button interrupt service routine and a timer interrupt service routine. The timer module has different modes that it can switch between. Having the timer count up to the given CCR0 value while toggling at the CCR1 value allows for the duty cycle to be changed by simply changing the CCR1 value on the button press ISR. Using the Port select registers allows a certain pin to be set for the given port. 

## Important Resources 
The MSP430 Data sheets were a big help for figuring out this lab. (Not Surprising there)

## Differences Between Processors 
Depending on the Board, the LED port and pins needed to be changed. For the FR2311 micro processor, timer B must be used in Timer A's place. The buttons used also had seperate pins from each other, and needed that bit needed to be changed in the code.
