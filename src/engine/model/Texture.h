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

//==============================================================================
/*
	Texture class for wrapping SDL Textures

	3/13/2014
    SDLTutorials.com
    Tim Jones
*/
//==============================================================================

#ifndef __TEXTURE_H__
	#define __TEXTURE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

class Texture {
	private:
		SDL_Rect src;
		SDL_Texture* sdl_texture = nullptr;

	public:
		Texture();
		~Texture();

		bool load(SDL_Renderer*, std::string);
		bool from_surface(SDL_Renderer*, SDL_Surface*);

		int get_width();
		int get_height();
		const SDL_Rect& get_src_rect();

		SDL_Texture* get(){ return sdl_texture; };
};

#endif