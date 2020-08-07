CPP Sudoku-Solver

A simple sudoku solver in C++. It uses a backtracking algorithm, that:
- counts the possible values for each empty cell
- if a cell has no possible value, the grid is not solvable; backtrack
- fills each cell where only one value is possible with this value
- tries each value for the remaining cell with the lowest count of possible values, recursively
- if it could not solve the grid, backtrack.

