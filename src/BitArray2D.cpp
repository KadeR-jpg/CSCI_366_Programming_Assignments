//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <math.h>
#include "BitArray2D.hpp"

BitArray2D::BitArray2D(unsigned int rows, unsigned int columns){
    //allocating a memory block for array
//    array = (char *) calloc(rows * columns, sizeof(char));
    this->rows = rows;
    this->columns = columns;
    if (columns < 1 || rows < 1){
        throw BitArray2DException("Wrong board size; Too Small");
    } else if (columns > 10 || rows > 10){
        throw BitArray2DException("Wrong board size; Too Large");
    }

}


BitArray2D::~BitArray2D() {
    //deallocate the memory block of array
    free(array);
}


bool BitArray2D::get(unsigned int row, unsigned int column) {
    if (column >= 10 || row >= 10) {
        throw BitArray2DException("Wrong board size; Too big");
    } else if (column < 1 || row < 1) {
        throw BitArray2DException("Wrong board size; Too small");
    }
    return get_bit_elem(array, columns, row, column);

}


void BitArray2D::set(unsigned int row, unsigned int column) {
    if (column >= 10 || row >= 10) {
        throw BitArray2DException("Wrong board size; Too big");
    } else if (column < 1 || row < 1) {
        throw BitArray2DException("Wrong board size; Too small");
    }
    return set_bit_elem(array, columns, row, column);
}
