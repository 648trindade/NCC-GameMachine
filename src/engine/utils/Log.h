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

#ifndef GAME_LOG_H
#define GAME_LOG_H

#include <string>
#include <SDL2/SDL.h>

#define DEBUG 1

#ifdef DEBUG
#define Log(...) SDL_Log(__VA_ARGS__);
#define Error(...) SDL_LogError(SDL_LOG_CATEGORY_ERROR, __VA_ARGS__);
#define Warning(...) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__);
#else
#define Log(...) ;
#endif

void MessageBox(std::string, std::string);

#endif //GAME_LOG_H
