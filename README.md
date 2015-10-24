# glCube

This a C + OpenGL implementation of a puzzle game [1] created by Paul Scott 
called Cube.

[2] You have a grid of 16 squares, six of which are blue; on one square rests a 
cube. Your move is to use the arrow keys to roll the cube through 90 degrees so 
that it moves to an adjacent square. If you roll the cube on to a blue square, 
the blue square is picked up on one face of the cube; if you roll a blue face 
of the cube on to a non-blue square, the blueness is put down again. In 
general, whenever you roll the cube, the two faces that come into contact swap 
colours. Your job is to get all six blue squares on to the six faces of the 
cube at the same time. Count your moves and try to do it in as few as possible.

**Controls:**

The arrow keys are used to roll the cube on its square grid in the four 
cardinal directions.

**Compilation:**

To compile this code, use:
`gcc glCube.c -lGL -lGLU -lglut -o glCube`

And execute with:
`./glCube`

[1] (http://www3.sympatico.ca/paulscott/cube/cube.htm)
[2] (http://www.chiark.greenend.org.uk/~sgtatham/puzzles/doc/cube.html)
