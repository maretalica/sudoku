#include <iostream>
#include "Board.h"

int main() {
    Sudoku sudoku;
    sudoku.generate();
    sudoku.draw();
    sudoku.solve();
    sudoku.draw();
}
