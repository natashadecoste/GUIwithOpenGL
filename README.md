
=======
# Simple GUI using openGL

THIS IS THE README FILE FOR ASSIGNMENT 1 (GRAPHICS USING OPENGL)

The purpose of this was to learn and use openGL and the GLUT library. 



********************************

From Assignment outline:

Write a simple robot program in C++ using OpenGL/GLUT.
The program will draw a user selectable grid with minimum size 10x10 and max size 50x50.



A Random square will be filled in with Green. Right next to it will be a red square. The red square is the head of the robot. As the robot turns the red square will rotate around the green square in the grid. The robot will be able to look in 4 directions, up, down, left, right. The green square will be its position. The purpose of this program is to control the robot from a gui. You will need to keep track of both the current position and orientation of the robot.





You must implement your own drawing function (i.e., see our discussion of raster algorithms). In other words, you cannot use the built-in primitive types such as GL_LINES, GL_POLYGON, etc, except for points. In all cases, only the point primitive type may be used, i.e., you must write your own functions to draw lines, rectangles, etc. using points. Left click will open a menu with the commands move and turn. It will then have a 2nd level of menu for right left up down, turn right, turn left.You should include the following functionality (e.g., as GLUT menu items, or keys – include a reference with your code): 

a)   Drawing the primitive types above with your own drawing routines  
b)   Quit the program 
c)   Random robot position 
d)   Reset Robot Position and orientation 


**********************************

Files

There is an interface.cpp and interface.h file that simply get input from the user (how big the grid must be).

There is also a main.cpp file that runs openGL and GLUT.

There is a makefile that compiles the cpp files together to make the executable and then runs it automatically.


**********************************

To Run

via Terminal (ON LINUX):


$ make



***********************************

Final Notes:
The code will be released after the due date of the project.


***********************************

Natasha DeCoste
