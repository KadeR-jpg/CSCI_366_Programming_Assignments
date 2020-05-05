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
int get_file_length(ifstream *file) {
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board) {
    this->board_size = board_size;
    if (board_size != 10) {
        board_size = 10;
        throw exception(ServerException("Board Size was not correct...Corrected"));
    }

    if (p1_setup_board.empty() || p2_setup_board.empty()) {
        p1_setup_board = p1_setup_board;
        p2_setup_board = p2_setup_board;
        throw exception(ServerException("Empty Board File name..Set to default"));
    }

}


Server::~Server() {
    free(p1_setup_board);
    free(p2_setup_board);
}


BitArray2D *Server::scan_setup_board(string setup_board_name) {
    BitArray2D *playerBoard = new BitArray2D(board_size, board_size);

}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    if (x > board_size || y > board_size) { return OUT_OF_BOUNDS; }
    if (x < 0 || y < 0) { return OUT_OF_BOUNDS; }
    if (player < 1 || player > MAX_PLAYERS) {
        throw exception(ServerException("Player Number can only be 1 or 2"));
    }
    if (player == 1) {
        player = 2;
    } else {
        player = 1;
    }
    ifstream localShot("player_" + to_string(player) + ".setup_board.txt");
    string hitOrMiss;
    std::string line;
    for (int i = 0; i <= y; ++i) {
        std::getline(localShot, line);
    }
    hitOrMiss = line.at(x);
    localShot.close();
    if (hitOrMiss != "_") {
        return HIT;
    } else {
        return MISS;
    }

}

//    ifstream localShot("player_" + to_string(player) + ".setup_board.txt");
//    string hitOrMiss;
//    std:string everyLine;
//    std::string line;
//    int i;
//    //While loop works but i think its giving me a segmentation fault, tests won't run with this
//    //while loop only debugger and stepping through the program. Otherwise i get
//    //a exit code 139.
//    while(std::getline(localShot, everyLine)) {
//        boardLines[i] = everyLine;
//        ++i;
//    }
//    line = boardLines.at(y);
//    hitOrMiss = line.at(x);
//    localShot.close();
//
//    if (hitOrMiss != "_") {
//        return 1;
//    } else {
//        return MISS;
//    }
//
//}


int Server::process_shot(unsigned int player) {
    if (player != 1) {
        if (player != 2) {
            throw exception(ServerException("Bad player number"));
        }
    }
    string shotFile = ("player_" + to_string(player) + ".shot.json");
    std::ifstream shotCoord(shotFile);
    int x, y;
    cereal::JSONInputArchive getCoord(shotCoord);
    getCoord(x, y);

    int bang = evaluate_shot(player, x, y);
    remove(shotFile.c_str());

    string resultFile = ("player_" + to_string(player) + ".result.json");

    ofstream shotResult(resultFile);
    cereal::JSONOutputArchive writeResult(shotResult);
    writeResult(cereal::make_nvp("result", bang));
    shotResult.close();
//    remove(shotFile.c_str());
//    remove(resultFile.c_str());
    return SHOT_FILE_PROCESSED;

}