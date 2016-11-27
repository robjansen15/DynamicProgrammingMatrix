//
// Created by terrabyte on 11/27/16.
//

#include "Combo.h"

Combo::Combo(int x, int y) {
    this->x_ = x;
    this->y_ = y;
    this->priority_ = y -x;
    this->value_ = -1;
}