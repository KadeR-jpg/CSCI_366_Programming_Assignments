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
#include "Client.hpp"

Client::~Client() {

}


void Client::initialize(unsigned int player, unsigned int board_size) {
    this->player = player;
    if(player < 1 || player > 2){
        throw ClientWrongPlayerNumberException();
    }//I could probably simplify this
    if (board_size != 10) {
        board_size = 10;
        throw exception(ClientException("Incorrect Board Size, corrected.\n"));
        throw ClientException("Wrong board Size");
    }else {

        this->board_size = board_size;
        string fileName = "player_" + to_string(player) + ".action_board.json";
        remove(fileName.c_str());
        vector<vector<int> > vec(board_size, vector<int>(board_size));
        ofstream array_ofp(fileName);
        cereal::JSONOutputArchive write_archive(array_ofp);
        write_archive(cereal::make_nvp("board", vec));
//        write_archive.finishNode();//Note to self, Cooper and mike said these are wack. Leave Commented out.
    }

}

void Client::fire(unsigned int x, unsigned int y) {
    string shotFile = "player_" + to_string(player) + ".shot.json";
    remove(shotFile.c_str());
    ofstream array_ofp(shotFile);
    cereal::JSONOutputArchive write_archive(array_ofp);
    write_archive(cereal::make_nvp("x", x), cereal::make_nvp("y", y));
}


bool Client::result_available() {
    ifstream shotFile("player_" + to_string(player) + ".result.json");
    return !shotFile.fail();
}


int Client::get_result() {
    string resultsIn  = ("player_" + to_string(player) + ".result.json");
    ifstream resultFile(resultsIn);
    cereal::JSONInputArchive coords(resultFile);
    int returnValue;
    coords(returnValue);
    if (returnValue == 1) {
        remove(resultsIn.c_str());
        return HIT;
    }
    if (returnValue == -1) {
        remove(resultsIn.c_str());
        return MISS;
    }
    if (returnValue == 0) {
        remove(resultsIn.c_str());
        return OUT_OF_BOUNDS;
    } else{
        throw("Bad result");
    }

}


void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    vector<vector<int> > board(board_size, vector<int>(board_size));
    ifstream local("player_" + to_string(player) + ".action_board.json");
    cereal::JSONInputArchive getAction(local);
    getAction(board);
    board[x][y] = result;
    local.close();
    ofstream outFile("player_" + to_string(player) + ".action_board.json");
    cereal::JSONOutputArchive updateAction(outFile);
    updateAction(CEREAL_NVP(board));
}

string Client::render_action_board() {
    vector<vector<int> > board(board_size, vector<int>(board_size));
    ifstream local("player_" + to_string(player) + ".action_board.json");
    cereal::JSONOutputArchive getAction(std::cout);
    getAction(CEREAL_NVP(board));
    //I have no Idea if this works. Copied the format from Cereal docs.
//
//    string Client::render_action_board() {
//    }
}
