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

#include "Texture.h"
#include "../utils/Log.h"
#include <cstring>

//==============================================================================
Texture::Texture() {
}

//------------------------------------------------------------------------------
Texture::~Texture() {
	if(sdl_texture)
		SDL_DestroyTexture(sdl_texture);
}

//==============================================================================
bool Texture::load(SDL_Renderer* renderer, std::string filename) {
	if(renderer == NULL) {
		Log("Bad SDL renderer passed");
		return false;
	}

	SDL_Surface* temp_surface = IMG_Load(filename.c_str());
	if(temp_surface == NULL) {
		Log("Unable to load image : %s : %s", filename.c_str(), IMG_GetError());
		return false;
	}

	if(!from_surface(renderer, temp_surface)){
		Log("Unable to create SDL Texture : %s : %s", filename.c_str(), IMG_GetError());
		return false;
	}

	SDL_FreeSurface(temp_surface);
	return true;
}

bool Texture::from_surface(SDL_Renderer* renderer, SDL_Surface* surface){
	sdl_texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(sdl_texture == NULL)
		return false;

	// Grab dimensions
	src.x = src.y = 0;
	src.w = surface->w;
	src.h = surface->h;
	return true;
}

//------------------------------------------------------------------------------
int Texture::get_width()  { return src.w;  }
int Texture::get_height() { return src.h; }
const SDL_Rect& Texture::get_src_rect() { return src; }
//==============================================================================
