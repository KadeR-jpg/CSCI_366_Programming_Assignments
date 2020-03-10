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


#include "common.hpp"
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){
    if(board_size != 10){
        board_size = 10;
        throw exception(ServerException("Board Size was not correct...Corrected"));
    }


    if(p1_setup_board.empty() && p2_setup_board.empty()){
        p1_setup_board = p1_setup_board;
        p2_setup_board = p2_setup_board;
        throw exception(ServerException("Empty Board File name..Set to default"));
    }

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y){
    if(x <= 10 && y <= 10){
        exception(ServerException("X or Y out of bounds"));
    }
    if(player < 1 || player > MAX_PLAYERS){
        throw exception(ServerException("Player Number can only be 1 or 2"));
    }



}


int Server::process_shot(unsigned int player) {
    if (player != 1 || player != 2){
        throw exception(ServerException("Bad player number"));




    }
   return NO_SHOT_FILE;
}