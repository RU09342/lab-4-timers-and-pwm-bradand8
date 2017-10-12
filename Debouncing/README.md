# Software Debouncing
So far, Buttons have been used to trigger interrupts in order to toggle an LED. While they do allow
for the LED to toggle, there are some concerns that exist due to the physical capabilities of the buttons.

## Understanding Bouncing
When a button is originally pressed, it bounces up and down for a short time (milli seconds) before the value stabilizes.
This processor reads this as being both pressed and not pressed at the same time before the signal settles on being pressed.
While the time for this to occur varies from button to button, there are ways to deal with this concern. The fix is known as debouncing.

## Understanding Debouncing
While hardware debouncing does occur, it is not always practical to add hardware. This lab relies on software debouncing instead. 
All software debouncing does is delays the reading on the button pin until a later time when the button has stabilized. This can be implemented with timers.

## How the Code Work
Like the previous button interrupt codes, a Port Interupt Service Routine occurs whenever a particular button is pressed that in turn toggles the LED. However, A Timer Interrupt service routine is also used to pause the timer whenever that same button is pressed.  The Port ISR then restarts the timer  when the port interrupt occurs. Using the Port interrupt Edge select (PXIES) decides whether the intterupt will occur when the button is pressed or released.


## Difference Among the Processors

* MSP430G2553
* MSP430FR6989
* MSP430FR2311  -- Much like the timer code, the FR2311 uses the B Timer instead of the A timer
* MSP430FR5994  
* MSP430F5529

General differences, the Ports for the Buttons as well as the BIT corresponding to the Pin of the button has to be change in accordance with the micro processor used. This information can be obtained from the datasheets or the included codes for each processor. And ofcourse, the three FR family registers need to include the code line:  ```  PM5CTL0 &= ~LOCKLPM5; ``` to stop the processor from clearing all bits.

## Is It Debouncing?
Understanding the concept is a big part of debouncing, but how can a person be sure that debouncing occurs? One way to test is to repeatedly press the button at different speeds looking for any quirks in how the LED toggles. An even better way to test the LED involves using equipment such as an oscilliscope to visualize the signal of the button being pressed. If the signal is debounced it should have a smooth transition from low to high, where as if it bounces there will be a staggered signal before settling on the input being high.

## Double Debouncing (Extra Work)
For the extra work of this lab, a second button was used to toggle another LED at the same time. After including the necessary enables for the second button and second Led, an additional Port Interrupt Service routine was needed to toggle LED2. However, the same timer was used as the Port ISR calls the timer ISR when it is used. With the same capture compare register, both LEDS toggle at the same rate when the buttons are being pressed.

