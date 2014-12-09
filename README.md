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
