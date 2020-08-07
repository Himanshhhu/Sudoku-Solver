#include <bits/stdc++.h>
#include "SudokuSolver.h"
using namespace std;
SudokuSolver::SudokuSolver(string & input) {
    int i = 0;
    int j = 0;
    for (char c: input) {
        if (c == '.') {
            grid[i][j] = 0;
        } else {
            grid[i][j] = ((int) c - 48);
        }
        i++;
        if (i >= 9) {
            i = 0;
            j++;
        }
    }
}

void SudokuSolver::print() const {
    cout << "-----------------------------" << endl;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (grid[i][j])
                cout << setw(3) << grid[i][j];
            else
                cout << "  .";
        }
        cout<<endl;
    }
}

int SudokuSolver::eligible(int i, int j, bitset<10> & nums) const {
    nums.set();
    nums[0] = false;

    for (int k = 0; k < 9; ++k) {
        if (grid[i][k] != 0) {
            nums[grid[i][k]] = false;
        }
        if (grid[k][j] != 0) {
            nums[grid[k][j]] = false;
        }
    }

    int si = 3 * (i / 3);
    int sj = 3 * (j / 3);
    for (int k = 0; k < 3; ++k) {
        for (int m = 0; m < 3; ++m) {
            if (grid[si + k][sj + m] != 0) {
                nums[grid[si + k][sj + m]] = false;
            }
        }
    }
    return nums.count();
}



bool SudokuSolver::solve() {

    // coordinate of the smallest non-trivial move
    int mini = 0;
    int minj = 0;
    bitset<10> min_eligibles;
    int mincount = 10;

    // number of pushes to backtrack
    // for which we did not recurse
    // i.e. there was only one possible nb
    int immediate_pushs = 0;


    // Process every move with
    // only one possibility while we can
    bool solved = true;
    bool found;
    do {
        found = false;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (grid[i][j] == 0) {
                    bitset<10> eligibles;
                    int count = eligible(i, j, eligibles);
                    // no possible move! -> backtrack
                    if (count == 0) {
                        backtrack(immediate_pushs);
                        return false;
                    }
                    // 1 possible move; set it right now
                    if (count == 1) {
                        for (int k = 1; k < 10; ++k) {
                            if (eligibles[k]) {
                                immediate_pushs++;
                                pushMove(i, j, k);
                                found = true;
                            }
                        }
                    } else {
                        if (count < mincount) {
                            solved = false;
                            mincount = count;
                            mini = i;
                            minj = j;
                            min_eligibles = eligibles;
                        }
                    }
                }
            }
        }
    } while (found);

    if (solved)
        return true;

    for (int k = 1; k < 10; ++k) {
        if (min_eligibles[k]) {
            pushMove(mini, minj, k);
            solved = solve();
            if (solved)
                return true;
            popMove();
        }
    }
    // we couldn't find a solution
    backtrack(immediate_pushs);
    return false;
}



void SudokuSolver::pushMove(int i, int j, int val) {
    Move m;
    m.i = i;
    m.j = j;
    grid[i][j] = val;
    moves.push(m);
}

void SudokuSolver::popMove() {
    Move & m = moves.top();
    grid[m.i][m.j] = 0;
    moves.pop();
}

void SudokuSolver::backtrack(int moves) {
    for (int k = 0; k < moves; ++k) {
        popMove();
    }
}

void SudokuSolver::solve(string &input) {
    SudokuSolver ss(input);
    if(ss.solve()) {
        ss.print();
    } else {
        cout << "No solution found" <<endl;
    }
}
