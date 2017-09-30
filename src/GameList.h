/**
 * This file is part of NCC-GameMachine.
 * 
 * NCC-GameMachine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NCC-GameMachine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NCC-GameMachine.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef GAMELIST_H
#define GAMELIST_H

#include<vector>
#include<string>
#include "Infos.h"
#include "Slider.h"

class GameList{
private:
    std::vector<std::string> list;
    void reload();
    bool validate_game(std::string);
    std::string current_game;
    Infos* infos;
    Slider* slider;
    void game_selected(std::string);

public:
    GameList(Infos*, Slider*);

    void update();
};

#endif