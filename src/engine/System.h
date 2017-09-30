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

#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include <SDL2/SDL.h>
#include "model/Timer.h"
#include "Defines.h"
#include <ctime>
#include <string>

const int SCREEN_FPS = 60;
const int TICKS_PER_SEC = 1000;
const int SCREEN_TICKS_PER_FRAME = TICKS_PER_SEC/SCREEN_FPS;

class System {
  public:

    static bool init();
    static void quit();
    //static void run();

    static void update();
    static void fill(SDL_Color);
    static void blit(SDL_Texture*, const SDL_Rect&, const SDL_Rect&);
    static void render();
    static void resize_window(int, int);

    static SDL_Point to_view_coord(SDL_Point);

    static float  get_FPS();
    static double get_scale();
    static SDL_Point  get_screen_offset();
    static double get_delta_time();
    static SDL_Window* get_window();
    static SDL_Renderer* get_renderer();
    static void   set_fullscreen(bool);
    static bool   is_fullscreen();

    static std::string MEDIA_FOLDER() { return "etc/"; };
    static std::string GAME_FOLDER() { return "games/"; };
    static std::string FONT_FOLDER() { return "open-sans/"; };

  private:

    static System instance;
    int    w_width;
    int    w_height;
    float  fps;
    double scaleX;
    double scaleY;
    Timer  cap_timer;
    Point  screen_offset;
    long long delta_time;
   
    SDL_Window*     window;
    SDL_Renderer*   renderer;
    
    static void calc_FPS();
    static bool create_renderer();
};

#endif //GAME_SYSTEM_H