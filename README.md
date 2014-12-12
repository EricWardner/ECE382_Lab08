ECE382_Lab08
============
## Table of Contents ##
- [Introduction](#introduction)
- [Pre-lab](#pre-lab)
    - [Useful Information](#useful-information)
    - [Sensor Test](#sensor-test)
    - [Setup of ADC10](#setup-of-adc10)
    - [Hardware Setup](#hardwaressetup)
    - [Code Ideas](#code-ideas)
- [Lab](#lab)
Path finding MSP430 IR sensor robot

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
####Objectives/Overview
The goal of this lab was to use the sensor and motor libraries created in [Lab 6](https://github.com/EricWardner/ECE382_Lab06) and [Lab 7](https://github.com/EricWardner/ECE382_Lab07) to navigate the IR sensing robot through the following maze.

The full description of the lab can be found [here](http://ece382.com/labs/lab8/index.html)


![Alt text](http://ece382.com/labs/lab8/maze_diagram.png)


####Set-up
I began initialy by cleaning up my motor and sensor library to simplify the code and make it easier to use in this lab.
In the motor library I took out unnessicary functions and register sets, each individual turn function was changed to only modify the registers it had to modify. An initilaize function was created so it would only have to be run once. 

The sensor library was already fairly effective and simple. The next step was to bring all the libraries into one project and hope that they played nicely. 






