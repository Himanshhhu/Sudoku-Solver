cpp-sudoku
-solver


A simple sudoku solver in C++. It uses a backtracking algorithm, that:
- counts the possible values for each empty cell
- if a cell has no possible value, the grid is not solvable; backtrack
- fills each cell where only one value is possible with this value
- tries each value for the remaining cell with the lowest count of possible values, recursively
- if it could not solve the grid, backtrack.

Note: for a given empty cell, the algorithm computes possible values only by checking the row, the column and the 3x3 subsquare.

