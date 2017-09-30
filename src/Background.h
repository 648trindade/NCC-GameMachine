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

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>
#include "engine/model/Texture.h"
#include "engine/Defines.h"

class Background {
private:
    const std::string images[3] = {
        std::string("backscreen1.png"), 
        std::string("backscreen2.png"), 
        std::string("backscreen3.png")
    };
    Texture* textures[3] = {nullptr, nullptr, nullptr};
    
    const SDL_Rect origin = SDL_Rect{0, 724, 300, 300};
    const Point movement = Point(-60, 60);
    const double frame_time = 1.0/3;
    
    Point pos;
    int current_frame = 0;
    double timer = 0;
public:
    Background();
    ~Background();
    void update(double);
    void render();
};

#endif