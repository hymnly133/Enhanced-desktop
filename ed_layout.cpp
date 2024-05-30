#include "ed_layout.h"

ED_Layout::ED_Layout(int row, int col, QWidget *father) {
    this->row = row;
    this->col = col;
    W_Father = father->width();
    H_Father = father->height();
    W_Block = W_Father/row;
    H_Block = H_Father/col;
}


