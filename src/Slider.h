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

#ifndef SLIDER_H
#define SLIDER_H

#include <map>
#include <vector>
#include <string>
#include <functional>
#include "engine/model/Texture.h"
#include "engine/Defines.h"

class Slider{
private:
    std::vector<std::string> names;
    std::map<std::string, Texture*> logos;
    std::map<std::string, Point> positions;
    std::map<std::string, SDL_Rect> dests;
    std::vector<std::string> render_order;

    std::function<void(std::string)> game_selected;
    bool rotating = false;
    int rot_direction = 0;
    double rot_accum = 0;
    std::string current_game;

    const Point BASE_VEC = Point(0, 0, 1);
    const Point SCALE = Point(0, 1.25, 1);
    const Point CENTER_VIEWPORT = Point(200,512);
    const Point DEFAULT_SIZE = Point(300,300);
    const double DISTANCE = -7;

    void ajust_game();
    void free_textures();
    void sort_in_z();
    void set_perspective();
    void rotate(double);
    std::string get_next_game(int);

    bool compare_in_z(std::string, std::string);

public:
    Slider();
    ~Slider();

    void set_callback(std::function<void(std::string)>);
    void reload(std::vector<std::string>);
    void update(double);
    void render();
    void goto_next(int);
};

#endif