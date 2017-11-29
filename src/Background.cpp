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

#include "Background.h"
#include "engine/System.h"
#include "engine/utils/Log.h"

Background::Background(){
    pos = Point(rect_topleft(origin));
    for (int i=0; i<3; i++){
        textures[i] = new Texture();
        textures[i]->load(System::get_renderer(), System::MEDIA_FOLDER() + images[i]);
    }
}

Background::~Background(){
    for (int i=0; i<3; i++)
        delete textures[i];
    Log("- [ Cleaned ] Background");
}

void Background::update(double delta){
    timer += delta;
    if (timer >= frame_time){
        timer -= frame_time;
        current_frame = (current_frame+1)%3;
    }
    pos += (movement * delta);
    if (pos.x <= -300)
        pos = Point(rect_topleft(origin));
}

void Background::render(){
    Point t_pos = Point((int)pos.x, (int)pos.y);
    for (int x = 0; x < 6; x++)
        for (int y = 0; y < 5; y++){
            Point idx(x, -y);
            SDL_Rect block_pos = {0,0,300,300};
            block_pos += (t_pos + (idx * origin.w));
            System::blit(textures[current_frame]->get(), textures[current_frame]->get_src_rect(), block_pos);
        }
}