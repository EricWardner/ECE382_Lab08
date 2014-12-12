ECE382_Lab08
============

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

![Alt text](http://ece382.com/labs/lab8/maze_diagram.png)




