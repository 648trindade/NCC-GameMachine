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

#include "Infos.h"
#include "engine/System.h"
#include "engine/utils/json.hpp"
#include "engine/utils/Log.h"
#include "engine/utils/Stringify.h"
#include <fstream>
#include <SDL2/SDL.h>

using json = nlohmann::json;

Infos::Infos(){
    // carrega fontes ttf
    open_sans = TTF_OpenFont((System::FONT_FOLDER() + "OpenSans-Regular.ttf").c_str(), 16);
    open_sans_bold = TTF_OpenFont((System::FONT_FOLDER() + "OpenSans-Bold.ttf").c_str(), 16);
    open_sans_bold_big = TTF_OpenFont((System::FONT_FOLDER() + "OpenSans-Bold.ttf").c_str(), 32);
    
    // renderiza fonte para labels
    labels["Autor:"] = gen_text(open_sans_bold, "Autor:");
    labels["Versão:"] = gen_text(open_sans_bold, "Versão:");
}

Infos::~Infos(){
    free_textures();
    for (const auto &label : labels)
        delete label.second;
    TTF_CloseFont(open_sans);
    TTF_CloseFont(open_sans_bold);
    TTF_CloseFont(open_sans_bold_big);
    Log("- [ Cleaned ] Infos");
}

/*
 * Recarrega a lista de informações. Libera texturas
 * antigas primeiro.
 */
void Infos::reload(std::vector<std::string> list){
    free_textures();
    for (std::string game : list)
        load_infos(game);
}

/*
 * Gera textura apartir de fonte e texto
 */
Texture* Infos::gen_text(TTF_Font* font, std::string text){
    SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(), font_color);
    Texture* tex = new Texture();
    tex->from_surface(System::get_renderer(), surf);
    SDL_FreeSurface(surf);
    return tex;
}

/*
 * Carrega informações de um jogo. Carrega Imagens também.
 */
void Infos::load_infos(std::string game){
    // carregando screenshots
    ss[game] = std::array<Texture*,3>();
    for (int i=0; i<3; i++){
        ss[game][i] = new Texture();
        ss[game][i]->load(System::get_renderer(), System::GAME_FOLDER() + game + "/media/ss" + Stringify::Int(i) + ".png");
    }

    // lendo json de informações
    std::ifstream file(System::GAME_FOLDER() + game + "/info.json");
    json j;
    file >> j;

    // carregando texto e renderizando fontes
    texts[game] = std::map<std::string, Texture*>();
    texts[game]["name"] = gen_text(open_sans_bold_big, j["name"]);
    std::array<std::string, 3> labels_txt = {"author", "version", "description"};
    for (std::string label : labels_txt)
        texts[game][label] = gen_text(open_sans, j[label]);
}

void Infos::update(double delta){
    // troca de imagem depois de um tempo
    // TODO: shade off
    timer += delta;
    if (timer >= flip){
        timer -= flip;
        current_frame = (current_frame + 1)%3;
    }
}

void Infos::render(){
    Texture* frame = ss[current_game][current_frame];
    Texture* prev_frame = ss[current_game][(current_frame)?(current_frame-1):2];
    SDL_Renderer* renderer = System::get_renderer();
    
    // desenha imagem
    if (timer <= 1){
        // shade in e shade out
        SDL_SetTextureAlphaMod(frame->get(), timer * 255);
        SDL_SetTextureAlphaMod(prev_frame->get(), (1.0-timer) * 255);
        System::blit(prev_frame->get(), prev_frame->get_src_rect(), image_area);
    }
    System::blit(frame->get(), frame->get_src_rect(), image_area);

    // desenha retangulo cinza
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderFillRect(renderer, &gray_area);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // escreve labels
    System::blit(labels["Autor:"]->get(), labels["Autor:"]->get_src_rect(), labels["Autor:"]->get_src_rect() + descr_origin);
    System::blit(labels["Versão:"]->get(), labels["Versão:"]->get_src_rect(), labels["Versão:"]->get_src_rect() + (descr_origin + Point(0,25)));

    // escreve textos de informação
    for (auto text : texts[current_game]){
        SDL_Rect src = (text.second)->get_src_rect();
        SDL_Rect dest = src;
        if (text.first == "name")
            dest += (name_center - Point(src.w/2, src.h/2));
        else if (text.first == "author")
            dest += (descr_origin + Point(70,0));
        else if (text.first == "version")
            dest += (descr_origin + Point(70,25));
        else{
            // quebra texto da descrição em várias linhas (750 px por linha)
            int pxpl = 750;
            dest += (descr_origin + Point(0,50));
            dest.w = pxpl;
            SDL_Rect _src = {0, 0, pxpl, src.h};
            while (_src.x < src.w){
                if (src.w < _src.x + pxpl)
                    dest.w = _src.w = src.w - _src.x;
                System::blit((text.second)->get(), _src, dest);
                dest += Point(0,25);
                _src.x += pxpl;
            }
            continue;
        }
        System::blit((text.second)->get(), src, dest);
    }
}

/*
 * Libera memória de texturas
 */
void Infos::free_textures(){
    for (const auto &array : ss)
        for(int i=0; i<3; i++)
            delete (array.second)[i];
    ss.clear();
    for (const auto &game : texts)
        for (const auto &label : game.second)
            delete label.second;
    texts.clear();
}

/*
 * Define o jogo corrente
 */
void Infos::set_game(std::string game){
    current_game = game;
    current_frame = 0;
    timer = 0;
}