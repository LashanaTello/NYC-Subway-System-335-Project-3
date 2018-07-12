/*******************************************************************************
  Title          : README.txt
  Author         : Lashana Tello
  Created on     : May 3, 2018
  Description    : Text file documenting my roadblocks working on Project 3
  Purpose        : To document my struggles
  Usage          : To learn from my previous mistakes when writing code in the
									 future
  Build with     : No building 
  Modifications  : 
 
*******************************************************************************/


4/20: Began writing pseudocode to figure out what needed to be done

4/21: Began writing actual code. Created and tested Entrance class

Created and tested SubwayStation class

Created and tested SubwayLine class

Created and tested SubwayStationHash class

Created and tested SubwayStationLine class

Created and tested SubwaySystem class

For some reason the total amount of stations I have is 491. So I put cout 
statements in the unionize method to see if the entrances are being unioned 
correctly. It seems as though there are entrances that don't connect to the
root when it actually is connected to the root, but the add method doesn't say
that they are connected because the root is too far away from the entrance. So
instead of the entrance being connected to the root, the entrance connects to 
one of the root's children. So when a union is performed, the second value of 
the child that the entrance connected to is modified. So that child no longer
points to its actual parent. I modified the union function to make the 
entrance's second value equal to the child's second value. Now find will
perform path compression and update the root's second value to correctly reflect
the number of children it has

For some reason, I'm only coming up with 449 stations instead of 451 and I don't 
know why. But everything else works just fine


