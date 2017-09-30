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

#ifndef INFOS_H
#define INFOS_H

#include "engine/model/Texture.h"
#include "engine/Defines.h"
#include <map>
#include <vector>
#include <array>
#include <string>
#include <SDL2/SDL_ttf.h>

class Infos{
private:
    std::map<std::string, std::array<Texture*,3>> ss;
    std::map<std::string, Texture*> labels;
    std::map<std::string, std::map<std::string, Texture*>> texts;

    const SDL_Rect gray_area = SDL_Rect{450,730,770,260};
    const SDL_Rect image_area = SDL_Rect{457,100,750,600};

    void free_textures();
    void load_infos(std::string);
    Texture* gen_text(TTF_Font*, std::string);

    double timer = 0;
    const double flip = 10;
    int current_frame = 0;
    std::string current_game;

    TTF_Font* open_sans;
    TTF_Font* open_sans_bold;
    TTF_Font* open_sans_bold_big;
    const SDL_Color font_color = SDL_Color{255,255,255,255};

    const Point name_center = Point(835,765);
    const Point descr_origin = Point(460, 800);

public:
    Infos();
    ~Infos();
    
    void set_game(std::string);
    void reload(std::vector<std::string>);
    void update(double);
    void render();
};

#endif