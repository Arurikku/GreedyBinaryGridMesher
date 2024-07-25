# Greedy Binary Grid Mesher (Naive)
This code is an implementation of a naive algorithm for a rather simple but highly optimisable problem:

Given an $N \times N$ grid of $0\text{s}$ and $1\text{s}$, how can we efficiently pack the $1\text{s}$ into rectangles?

The algorithms chosen can depend on the type of meshing needed, and the type of architecture (fast rendering, slow memory access, ...)

## How it works
The following algorithm is written for $32 \times 32$ grids for simplicity of memory manipulation in C (using the type `uint32_t`)

The algorithm follows a greedy paradigm, trying to fill rectangles vertically as much as possible and then widening if possible. This is a naive algorithm, so it can (and will) be optimised a lot.

The expected input is an array of length 32, containing 32 bit unsigned integers, essentially forming a $32 \times 32$ grid using the bits, and the output is an array of rectangles stored as `xPos, yPos, width, height`.

/!\ The input array gets modified by the algorithm, but the resulting array of rectangles contains all the necessary information without loss

## Example
Here is the output for a random grid illustrated using python (blue is 1 and red is 0):
![image](https://github.com/user-attachments/assets/e527fca8-9026-4934-9d07-2dd7b65487f6)

## Is it useful..?
The goal of such an algorithm is to facilitate storing the grid and rendering it.

Note that storing the coordinates for the rectangle can be worst than just storing each bit inside of the rectangle, and the computation of the mesh might make the rendering less efficient. However, in games such as Minecraft, the (3D) grids following a certain structure, meaning that a lot of bits can be compressed like this. 

## Warning
The algorithm uses a `GCC` builtin function (`__builtin_ctzl`) to count the amount trailing zeroes in a `uint32_t`, meaning that this needs to be compiled with `GCC`. For other compilers, you'll need to change the builtin function to match the compiler.
