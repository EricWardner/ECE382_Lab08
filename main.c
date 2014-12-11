#include <msp430.h>
#include "motor.h"
#include "sensors.h"

int main(void) {

	unsigned int c, c1, c2, c3;
	unsigned int l, l1, l2, l3;
	initMotor();

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	P1DIR = BIT0|BIT6;												// Set the red LED as output
	P1OUT &= ~(BIT0|BIT6);

	forward();


	while(1){


		c = centerSensor();
		l = leftSensor();
		c1 = centerSensor();
		l1 = leftSensor();
		c2 = centerSensor();
		l2 = leftSensor();
		c3 = centerSensor();
		l3 = leftSensor();

		c = (c+c1+c2+c3)/4;
		l = (l+l1+l2+l3)/4;

		while(l < 650){
			c = centerSensor();
			l = leftSensor();
			c1 = centerSensor();
			l1 = leftSensor();
			c2 = centerSensor();
			l2 = leftSensor();
			c3 = centerSensor();
			l3 = leftSensor();

			c = (c+c1+c2+c3)/4;
			l = (l+l1+l2+l3)/4;
			leftTurn();
			P1OUT |= (BIT6);

		}
		while(c > 600){
			c = centerSensor();
			l = leftSensor();
			c1 = centerSensor();
			l1 = leftSensor();
			c2 = centerSensor();
			l2 = leftSensor();
			c3 = centerSensor();
			l3 = leftSensor();

			c = (c+c1+c2+c3)/4;
			l = (l+l1+l2+l3)/4;
			rightTurn();
			P1OUT |= (BIT0|BIT6);


		}
		P1OUT &= ~(BIT0|BIT6);
		forward();


	}
} // end main
