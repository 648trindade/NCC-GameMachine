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

#include "engine/System.h"
#include "engine/managers/Events.h"
#include "Background.h"
#include "GameList.h"
#include "Infos.h"
#include "Slider.h"
#include <SDL2/SDL.h>

Background* background;
GameList* game_list;
Infos* infos;
Slider* slider;

void run(){
    double delta;
    while (!(Events::quit)){
        delta = System::get_delta_time();

        // update
        System::update();
        game_list->update();
        background->update(delta);
        infos->update(delta);
        slider->update(delta);

        // render
        background->render();
        infos->render();
        slider->render();
        System::render();
    }
}

void instantiate_obj(){
    background = new Background();
    infos = new Infos();
    slider = new Slider();
    game_list = new GameList(infos, slider);
}

void free_obj(){
    delete background;
    delete infos;
    delete slider;
    delete game_list;
}

int main(){
    if (System::init()){
        instantiate_obj();
        run();
        free_obj();
    }
    System::quit();
    return 0;
}