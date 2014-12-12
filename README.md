ECE382_Lab08
============
## Table of Contents ##
- [Introduction](#introduction/objectives)
- [Pre-lab](#pre-lab)
- [Lab](#lab)
    - [Set-up](#set-up)
        -[Code](#code-set-up)
        -[Robot](#robot-set-up)
    - [Design Process](#design-process)


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

####Set-up
######Code set-up
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




