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

#ifndef GAME_CODES_H
#define GAME_CODES_H

#include <SDL2/SDL_keycode.h>

typedef enum {
    KEY_a = SDLK_a,
    KEY_b = SDLK_b,
    KEY_c = SDLK_c,
    KEY_d = SDLK_d,
    KEY_e = SDLK_e,
    KEY_f = SDLK_f,
    KEY_g = SDLK_g,
    KEY_h = SDLK_h,
    KEY_i = SDLK_i,
    KEY_j = SDLK_j,
    KEY_k = SDLK_k,
    KEY_l = SDLK_l,
    KEY_m = SDLK_m,
    KEY_n = SDLK_n,
    KEY_o = SDLK_o,
    KEY_p = SDLK_p,
    KEY_q = SDLK_q,
    KEY_r = SDLK_r,
    KEY_s = SDLK_s,
    KEY_t = SDLK_t,
    KEY_u = SDLK_u,
    KEY_v = SDLK_v,
    KEY_w = SDLK_w,
    KEY_x = SDLK_x,
    KEY_y = SDLK_y,
    KEY_z = SDLK_z,
    KEY_0 = SDLK_0,
    KEY_1 = SDLK_1,
    KEY_2 = SDLK_2,
    KEY_3 = SDLK_3,
    KEY_4 = SDLK_4,
    KEY_5 = SDLK_5,
    KEY_6 = SDLK_6,
    KEY_7 = SDLK_7,
    KEY_8 = SDLK_8,
    KEY_9 = SDLK_9,
    KEY_ENTER   = SDLK_RETURN,
    KEY_SHIFT_L = SDLK_LSHIFT,
    KEY_SHIFT_R = SDLK_RSHIFT,
    KEY_CTRL_L  = SDLK_LCTRL,
    KEY_CTRL_R  = SDLK_RCTRL,
    KEY_ALT_L   = SDLK_LALT,
    KEY_ALT_R   = SDLK_RALT,
    KEY_TAB     = SDLK_TAB,
    KEY_COMMA   = SDLK_COMMA,
    KEY_DOT     = SDLK_PERIOD,
    KEY_SEMICOLON = SDLK_SEMICOLON,
    KEY_SPACE   = SDLK_SPACE,
    KEY_UP    = SDLK_UP,
    KEY_DOWN  = SDLK_DOWN,
    KEY_LEFT  = SDLK_LEFT,
    KEY_RIGHT = SDLK_RIGHT,
    KEY_ESC   = SDLK_ESCAPE,
    KEY_SUPER = SDLK_LGUI
} Key;

#endif //GAME_CODES_H
