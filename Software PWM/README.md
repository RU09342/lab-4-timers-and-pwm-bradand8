# Software PWM
Further use of timers for interrupts can have unique effects when blinking LEDs.

## PWM Concept
PWM or Pulse Width modulation allows for changing the duty cycle of a signal. For this lab, the signal is used to blink the LED. So far the LED has had a 50% duty cycle. The duty cycle refers to how long the signal is high divided by the time the signal lasts in a given period. A 50% duty cycle means that the LED is spending as much time on as it is off when it toggles. If the LED has a higher than 50% duty cycle, it will get brighter as it is being powered on for more time than it is powered off, and our eyes will perceive it as brighter. Likewise, if the duty cycle is less than 50%, it will appear dimmer.

## Parameters
* 1kHz PwM signal
* LED1 starts 50% duty cycle and powered off
* LED2 lights up when button is pressed to test for interrupts
* Upon pressing a button, the duty cycle for LED 1 should increase by 10%.

## Broken Down
To make things simpler, four methods were created to initialize the different parameters needed which are called by the main method. The methods are as follows:

```
void ledSetup();
void buttonSetup();
void timerA0Setup();
void timerA1Setup();

```
## How the code works
After initializing the clocks speeds to the given parameters, two capture compare registers are used to determine the duty cycle. TA0CCR0 is set to 1kHZ as required and TA0CCR1 is set to 500. (Being half of 1000, the duty cycle starts at 50%). In the Button ISR, whenever the button is pressed, LED2 toggles, while the capture compare value for LED 1 is incremented by 100. This raises the duty cycle to 60% for LED 1. Whenever the button is pressed, The duty cycle raises to 10%, until it is at 100%. If the button is pushed after 100%, the duty cycle becomes 0% and the light is off. 

## Differences Among Processors
Because of the parameter definitions at the start of the code, the only changes necessary are the pins that correspond to the buttons and LEDs in the definitions. Ofcourse, the FR family processors need the LOCK5 code segment and the FR2311 uses Timer B not A.

### Fun Reminder

			 Time LED ON
DUTY CYCLE =          -------------------   X 100 = %
			Time of Period
