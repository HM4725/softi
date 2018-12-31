# Soduku Solve Prog.
### This program solves a sudoku game.
### Author: HM.Lee

## How to build
1. cd [sudoku_root_dir]
2. make

## How to execute
1. cd bin
2. ./sudokuSolve [input_file]

### Input file
A sudoku consists of 9x9 numbers.

If a box has zero, a gamer has to guess the number of the box.

If a box has a number which is not zero, it has a given number. Not guess.

```
[input file format example]

0 0 0 7 9 6 0 0 0
0 3 7 0 0 0 4 8 0
0 2 0 0 0 0 6 9 7
2 0 0 3 7 4 0 0 6
0 4 0 0 8 0 3 2 0
8 0 3 6 0 2 0 0 5
0 6 0 0 0 0 0 5 0
0 5 1 0 0 0 9 7 0
0 0 0 4 0 8 0 0 0
```
In ~/bin/ex, there are example input files.

Difficulty: easy < normal < hard < elite < crazy

### Output file: result
If a sudoku is solvable, sudokuSolve prints the solution of the sudoku.

Type ```cat result``` in "bin" directory.


## Design
* Read input file and set boxes. 

First, sudokuSolve saves the input numbers in int[9][9]. Then in Box[9][9]. 
Box[9][9] is called boxes.

sudokuSolve takes a snapshot of the boxes and the context. The snapshot is the data structure
that saves the boxes, heap, row, column, and block. The heap is used to calculate the minimum 
number of candidates. The row, column and block are used to check the already writen numbers on 
the row, column and block of the position. sudokuSolve expresses them with bit flags. If there are 
given numbers 1, 2, 7, 9 on the row, the row variable of the box has 101000011. The data type of
them is integer. To have 9 bits, they has more than 9bits. So sudokuSolve chose the 4bytes data type.

* Find a box that has the smallest number of candidates.
To find min, sodokuSolve uses a heap data structure.

* If the number is 1, continue in the current snapshot.
Put the candidate on the box. Then pick the minimun ncandi box again.

* Else if the number is more than 1, continue in a new snapshot.
Take a new snapshot. Then put a candidate on the box and continue recursively.
If the candidate is wrong, put another candidate.

* Else if the number is 0, stop.
It is wrong. Move back to the previous snapshot. Then choice another number.

## Analysis
TODO: analysis the time complexity of sudokuSolve.
