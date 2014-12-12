ECE382_Lab08
============
## Table of Contents ##
- [Introduction](#introduction/objectives)
- [Pre-lab](#pre-lab)
- [Lab](#lab)
    - [Set-up](#setup)
    	- [Code](#code-setup)
        - [Robot](#robot-setup)
    - [Design Process](#design-process)
        - [Required Functionality](#required-functionality)
        - [A Functionality](#a-functionality)
    - [Testing/Debugging](#testing/debugging)


Path finding MSP430 IR sensor robot
##Introduction/Objectives
The goal of this lab was to use the sensor and motor libraries created in [Lab 6](https://github.com/EricWardner/ECE382_Lab06) and [Lab 7](https://github.com/EricWardner/ECE382_Lab07) to navigate the IR sensing robot through the following maze.

The full description of the lab can be found [here](http://ece382.com/labs/lab8/index.html)




![Alt text](http://ece382.com/labs/lab8/maze_diagram.png)




##Pre-Lab
Plan: Follow the left wall!!

```
forward();
while(1){
  if(centerIsClose() && rightIsClose()){
    left45();
  }
  if(centerIsClose() && leftIsClose()){
    right45();
  }
  if(leftIsClose()){
    forward();
  }
}
```

##Lab

####Setup
######Code setup
I began initialy by cleaning up my motor and sensor library to simplify the code and make it easier to use in this lab.
In the motor library I took out unnessicary functions and register sets, each individual turn function was changed to only modify the registers it had to modify. An initilaize function was created so it would only have to be run once. 

The sensor library was already fairly effective and simple. The next step was to bring all the libraries into one project and hope that they played nicely. 
######Robot Setup
Luckily, the robot was already wired from Lab 6 and Lab 7 so all of the ports were connected correctly. The finial wiring setup can be seen below

![alt tag](http://i.imgur.com/mbM4Imk.png)

####Design Process
######Required Functionality
The first part of the design process was required functionality, which required the robot to get through Door #1 in the diagram. For this I planned to only use the center sensor and when the center sensor detected something, it would turn left. This seemed simple enough, but the robot would just not work. When I finally got the code working with eachother (I used the main from lab 07 with some calls to lab 06 functions) The sensor would not work! After a lot of debugging I put some capacitors in thinking it might have been noise, that helped a little. I thought it was still having some noise becasue my code was ver simple and it was picking up center sensor readings when it shouldn't have been so I made an average of 4 sensor readings to try and get outliers out and it worked! This is what the moving average looked like

```C
c = centerSensor();
c1 = centerSensor();
c2 = centerSensor();
c3 = centerSensor();

c = (c+c1+c2+c3)/4;
```

######A Functionality
Since my efforts for required functionality did most of the debugging and figuring out how to actually get the robot to move properly A functionality was fairly straight-forward. I had an idea to keep the robot following the left wall and the way I though to implement that was a bit different than what I thought of in the Pre-Lab it was something like

```
goForward()
while(true){
    while(tooFarFromLeftWall()){
        turnLeft()
    }
    while(tooCloseToCenterSensor()){
        turnRight()
    }
    goForward()
}
```

To accomplish this I had to do multiple debugging tests where I put my hands close to the sensor to see what a good value was for the tooCloseToCenterSensor() and tooFarFromLeftWall(). I also had to ensure I was constantly grabbing new sensor readings in the while loops. This is what my algorithm came out to. I replaced the moving average code with a function call.

```C
forward();
	while(1){
		c = movingAverage(centerSensor());
		l = movingAverage(leftSensor());

		while(l < 670){
		    c = movingAverage(centerSensor());
		    l = movingAverage(leftSensor());
			leftTurn();
			P1OUT |= (BIT6);
		}
		while(c > 600){
		    c = movingAverage(centerSensor());
		    l = movingAverage(leftSensor());
			rightTurn();
			P1OUT |= (BIT0|BIT6);
		}
		P1OUT &= ~(BIT0|BIT6);
		forward();
	}
```

This algorithm also worked for bonus functionality. 

####Testing/Debugging
######How to
A big thing I learned here was how to test and debug with the sensors and motor powered on. Apparently you can not have the reset pin hooked up to anything and your MSP430 needs to be hooken up to your robot's ground and the breaker for Vcc had to be taken off when plugged into the usb. I also learned how important it is to use th logic analyzer and a voltage probe to check what readings your board is seeing.
######My long process
Testing and debugging was by far the hardest part of the lab. Even after having a working Lab 7 and Lab 6 it was hard to get the motors to work with the sensors. The first difficulty I ran into was I had hooked up one of the sensors to P1.2 which apparently does not work well with the sensors so that had to be changed. Then I was still getting random noise from the motors so I put in some capacitors to help with that which did but not entirely so I finally added a moving average into the code. I also had to slow down my robot greatly. Then it all worked. The last part of my testing was trying to optimize which involved changing my motor's PWM signals.


####Conclusion
In the end after optimization I had my robot going through the maze in about 16 seconds! Here is a nice video of it working!

[![Lab 08 Functionality](http://img.youtube.com/vi/UxiMcg6cxUs/0.jpg)](http://www.youtube.com/watch?v=UxiMcg6cxUs)

If I were to change anythin about my design I would probably edit my motor library to have a turn function that actualy turned the robot in a curve rather than just rotated it in place. I think this would have sped up my time and helped with the sharp turn in bonus functionality. 


Documentation: Dr. Coulston helped me debugg my code and suggested the moving average. Kevin Cooper and Bll Parks gave me ideas on how to optimize my libraries
