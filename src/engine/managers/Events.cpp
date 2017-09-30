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

#include "Events.h"
#include "../System.h"
#include "../utils/Log.h"

bool Events::mouse_pressed = false;
bool Events::quit = false;
SDL_Point Events::mouse_rel = {0, 0};
bool Events::mouse_focused = false;
bool Events::mouse_button_down = false;
bool Events::mouse_button_up = false;
bool Events::mouse_motion = false;
bool Events::key_down = false;
bool Events::key_up = false;
int Events::key = 0;
std::map<int, bool> Events::keys;
SDL_Point Events::mouse_pos;
char Events::mouse_button = 0;

void Events::update(){
    reset();
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_MOUSEBUTTONDOWN:
                mouse_button_down = true;
                break;
            case SDL_MOUSEBUTTONUP:
                mouse_button_up = true;
                break;
            case SDL_MOUSEMOTION:
                mouse_motion = true;
                mouse_rel = System::to_view_coord({ event.motion.xrel, event.motion.yrel });
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_ENTER:
                        mouse_focused = true;
                        break;
                    case SDL_WINDOWEVENT_LEAVE:
                        mouse_focused = false;
                        break;
                    case SDL_WINDOWEVENT_RESIZED:
                        System::resize_window(event.window.data1, event.window.data2);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYDOWN:
                key_down = true;
                key = event.key.keysym.sym;
                keys[key] = true;
                if(key == SDLK_F11)
                    System::set_fullscreen(!System::is_fullscreen());
                break;
            case SDL_KEYUP:
                key_up = true;
                key = event.key.keysym.sym;
                keys[key] = false;
                break;
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
        }
    }
    mouse_button = SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    mouse_pos = System::to_view_coord(mouse_pos);
    mouse_pressed = mouse_button > 0;
}

void Events::reset() {
    mouse_rel = {0, 0};
    mouse_button_down = false;
    mouse_button_up = false;
    mouse_motion = false;
    key_down = false;
    key_up = false;
}

bool Events::isPressed(int key) {
    bool state;
    try {
        state = keys.at(key);
    }
    catch (std::out_of_range e){
        state = false;
        keys[key] = state;
    }
    return state;
}