#include <msp430.h>
#include "motor.h"
#include "sensors.h"

int main(void) {

	initMotor();

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	P1DIR = BIT0|BIT6;												// Set the red LED as output
	P1OUT &= ~(BIT0|BIT6);

	forward();
	while(1){
		// Configure P1.1 to be the ADC input (Left)

//		if (leftSensor() > 0x0200)	P1OUT |= BIT0;
//		else				P1OUT &= ~BIT0;
//
//
//		if (rightSensor() > 0x0200)	P1OUT |= BIT6;
//		else					P1OUT &= ~BIT6;


		if (centerSensor() > 0x0200){
			P1OUT |= (BIT0|BIT6);
			stop();
			leftTurn();
			__delay_cycles(LEFT45);
			forward();
		}
		else{
			P1OUT &= ~(BIT0|BIT6);
		}
		}

	forward();
	__delay_cycles(FORWARD);
	stop();
	__delay_cycles(PAUSE);

	back();
	__delay_cycles(BACK);
	stop();
	__delay_cycles(PAUSE);

	rightTurn();
	__delay_cycles(RIGHT45);
	stop();
	__delay_cycles(PAUSE);

	leftTurn();
	__delay_cycles(LEFT45);
	stop();
	__delay_cycles(PAUSE);

	rightTurn();
	__delay_cycles(RIGHT90);
	stop();
	__delay_cycles(PAUSE);

	leftTurn();
	__delay_cycles(LEFT90);
	stop();

} // end main
