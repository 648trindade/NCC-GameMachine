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

#ifndef GAME_EVENTS_H
#define GAME_EVENTS_H

#include <SDL2/SDL.h>
#include <list>
#include <map>

#define MOUSE_BT(x) SDL_BUTTON(x)

class Events{
private:
    static std::list<SDL_Event> eventList;
    static void reset();
    static std::map<int, bool> keys;
public:
    static void update();
    static bool isPressed(int);

    static bool quit;

    static SDL_Point mouse_pos;
    static SDL_Point mouse_rel;
    static char mouse_button;
    static bool mouse_button_down;
    static bool mouse_button_up;
    static bool mouse_motion;
    static bool mouse_focused;
    static bool mouse_pressed;

    static bool key_down;
    static bool key_up;
    static int  key;

};

#endif //GAME_EVENTS_H
