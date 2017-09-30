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

#include "Slider.h"
#include "engine/System.h"
#include "engine/utils/Log.h"
#include <algorithm>

Slider::Slider(){}

Slider::~Slider(){
    free_textures();
}


/**
 * Libera texturas da memória
 */
void Slider::free_textures(){
    for (auto logo : logos)
        delete logo.second;
}

/**
 * Reccarega as logos dos jogos
 */
void Slider::reload(std::vector<std::string> games){
    free_textures();
    names.clear();
    positions.clear();
    render_order.clear();
    dests.clear();

    for (std::string game : games){
        names.push_back(game);
        render_order.push_back(game);
        positions[game] = Point(0,0,1);
        dests[game] = SDL_Rect{0,0,300,300};
        logos[game] = new Texture();
        logos[game]->load(System::get_renderer(), System::GAME_FOLDER() + game + "/media/logo.png");
    }
    current_game = names[0];
    // ajusta novos posicionamentos iniciais na tela
    ajust_game();
    sort_in_z();
    set_perspective();
}

/**
 * Método de comparação para definir qual ponto está mais atrśa em z
 */
bool Slider::compare_in_z(std::string a, std::string b){
    return positions[a].z <= positions[b].z;
}

/**
 * Ordena a fila de renderização baseado no valor de z
 */
void Slider::sort_in_z(){
    using namespace std::placeholders;
    auto comp = std::bind(&Slider::compare_in_z, this, _1, _2);
    std::sort(render_order.begin(), render_order.end(), comp);
}

/**
 * Atribui posicionamentos aos retângulos de destino para renderização
 * baseado no cálculo de projeção em perspectiva
 */
void Slider::set_perspective(){
    for (std::string game : names){
        Point center = positions[game];
        Point topleft = Point(-0.5,-0.5,0) + center;
        Point bottomright = Point(0.5,0.5,0) + center;

        topleft = (topleft * DISTANCE) / (topleft.z + DISTANCE - 1);
        bottomright = (bottomright * DISTANCE) / (bottomright.z + DISTANCE - 1);
        dests[game] = SDL_Rect{
            (int)(topleft.x * DEFAULT_SIZE.x + CENTER_VIEWPORT.x),
            (int)(topleft.y * DEFAULT_SIZE.y + CENTER_VIEWPORT.y),
            (int)((bottomright.x - topleft.x) * DEFAULT_SIZE.x),
            (int)((bottomright.y - topleft.y) * DEFAULT_SIZE.y)
        };
    }
}

/**
 * Comando para vançar na lista de jogos
 */
void Slider::goto_next(int direction){
    if (!rotating || rot_direction/abs(rot_direction) == direction){
        rotating = true;
        rot_direction += direction;
    }
}

/**
 * Posiciona com exatidão as logos no espaço de mundo tomando por base
 * o jogo que está a frente (current_game)
 */
void Slider::ajust_game(){
    int n_games = logos.size();
    double ang = 360.0 / n_games;
    int idx = (int)(std::find(names.begin(), names.end(), current_game) - names.begin());
    for (int i=0; i<n_games; i++){
        double j = i - idx;
        if (j > 0)  j += n_games;
        std::string name = names[i];
        positions[name] = BASE_VEC.rotate_3d(Point::X_AXIS, deg2rad(ang * j)) * SCALE;
    }
}

/**
 * Rotaciona todos os logos em um ângulo theta
 */
void Slider::rotate(double theta){
    for (std::string game : names){
        Point vec = positions[game];
        vec.y /= SCALE.y;
        positions[game] = vec.rotate_3d(Point::X_AXIS, deg2rad(theta)) * SCALE;
    }
}

/** 
 * Método de update.
 * Se em animação de rotação, calcula o angulo necessário para o frame
 * e rotaciona. Se terminar a rotação, ajusta a tela com o novo jogo
 * na frente. Por fim, usa a callback para notificar a GameList que um 
 * novo jogo foi selecionado.
 */
void Slider::update(double delta){
    if(rotating){
        double ang = 360.0 / names.size() * abs(rot_direction);
        double step = ang * delta * rot_direction;
        rotate(step);
        rot_accum += step;
        if (abs(rot_accum) >= abs(ang)){
            rot_accum = 0;
            rotating = false;
            current_game = get_next_game(rot_direction);
            ajust_game();
            rot_direction = 0;
            game_selected(current_game);
        }
        sort_in_z();
        set_perspective();        
    }
}

/**
 * encapsulamento da callback
 */
void Slider::set_callback(std::function<void(std::string)> game_selected){
    this->game_selected = game_selected;
}

/**
 * Retorna o jogo selcionado baseado na posição do jogo atual + deslocamento
 */
std::string Slider::get_next_game(int offset){
    // rotação no sentido contrário da direção da lista
    offset = -offset;
    auto game_it = std::find(names.begin(), names.end(), current_game);
    int idx = game_it - names.begin();
    int n_idx = (idx + offset) % names.size();
    if (n_idx >= 0)
        return names[n_idx];
    else
        return names[names.size() + n_idx];
}

/**
 * Renderiza as logos na tela
 */
void Slider::render(){
    for(std::string game : render_order)
        System::blit(logos[game]->get(), logos[game]->get_src_rect(), dests[game]);
}