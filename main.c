#include <msp430.h>
#include "motor.h"
#include "sensors.h"

int main(void) {

	unsigned int c, c1, c2, c3;
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

		c = centerSensor();
		c1 = centerSensor();
		c2 = centerSensor();
		c3 = centerSensor();

		c = (c+c1+c2+c3)/4;


		while (c > 600){
			c = centerSensor();
			c1 = centerSensor();
			c2 = centerSensor();
			c3 = centerSensor();

			c = (c+c1+c2+c3)/4;
			P1OUT |= (BIT0|BIT6);
			//stop();
			//__delay_cycles(LEFT45);
			leftTurn();
			//__delay_cycles(LEFT45);
			//forward();
		}
		P1OUT &= ~(BIT0|BIT6);

		forward();

		c = centerSensor();
		c1 = centerSensor();
		c2 = centerSensor();
		c3 = centerSensor();

		c = (c+c1+c2+c3)/4;

		while (c > 600){
			c = centerSensor();
			c1 = centerSensor();
			c2 = centerSensor();
			c3 = centerSensor();

			c = (c+c1+c2+c3)/4;
			P1OUT |= (BIT0|BIT6);
			//stop();
			//__delay_cycles(LEFT45);
			rightTurn();
			//__delay_cycles(LEFT45);
			//forward();
		}

	}

//	forward();
//	__delay_cycles(FORWARD);
//	stop();
//	__delay_cycles(PAUSE);
//
//	back();
//	__delay_cycles(BACK);
//	stop();
//	__delay_cycles(PAUSE);
//
//	rightTurn();
//	__delay_cycles(RIGHT45);
//	stop();
//	__delay_cycles(PAUSE);
//
//	leftTurn();
//	__delay_cycles(LEFT45);
//	stop();
//	__delay_cycles(PAUSE);
//
//	rightTurn();
//	__delay_cycles(RIGHT90);
//	stop();
//	__delay_cycles(PAUSE);
//
//	leftTurn();
//	__delay_cycles(LEFT90);
//	stop();

} // end main
