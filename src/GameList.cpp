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

#include "GameList.h"
#include "engine/System.h"
#include "engine/Enums.h"
#include "engine/utils/Files.h"
#include "engine/utils/Log.h"
#include "engine/managers/Events.h"
#include <cstdlib>
#include <functional>
#include <algorithm>

GameList::GameList(Infos* _infos, Slider* _slider) : infos(_infos), slider(_slider){
    
    using namespace std::placeholders; // for `_1`
    auto _callback = std::bind(&GameList::game_selected, this, _1);
    slider->set_callback(_callback);
    reload();
}

/*
 * Recarrega lista de jogos. Testa se o jogo é valido
 * antes de adicionar  
 */
void GameList::reload(){
    list.clear();
    auto tmp_list = Files::getFilesInFolder(System::GAME_FOLDER());
    for (std::string dir : tmp_list){
        dir = Files::getFilenameWithoutExt(dir);
        if (validate_game(dir))
            list.push_back(dir);
    }

    // ordena em ordem alfabética
    std::sort(list.begin(), list.end());

    infos->reload(list);
    slider->reload(list);

    // pega nome do diretorio sem caminho completo
    current_game = Files::getFilenameWithoutExt(tmp_list[0]);
    infos->set_game(current_game);
}

/*
 * Valida o jogo -> testa se contém run.sh
 */
bool GameList::validate_game(std::string game){
    Log("Game Válido: %s\n",game.c_str());
    return Files::fileExists(System::GAME_FOLDER() + game + "/run.sh");
}

/*
 * Se apertada a tecla do reload, recarrega a lista de jogos.
 */
void GameList::update(){
    if (Events::key_down){
        if (Events::isPressed(KEY_r))
            reload();
        else if (Events::isPressed(KEY_DOWN))
            slider->goto_next(1);
        else if (Events::isPressed(KEY_UP))
            slider->goto_next(-1);
        else if (Events::isPressed(KEY_SPACE)){
            Log("%s", (System::GAME_FOLDER() + current_game + "/run.sh").c_str());
            system((System::GAME_FOLDER() + current_game + "/run.sh").c_str());
            SDL_RaiseWindow(System::get_window());
            SDL_SetWindowInputFocus(System::get_window());
        }
    }
}

void GameList::game_selected(std::string game){
    current_game = game;
    infos->set_game(game);
}