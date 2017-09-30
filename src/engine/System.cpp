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

#include "System.h"
#include "utils/Log.h"
#include "managers/Events.h"
#include "utils/Stringify.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>

#define self instance

System System::instance;

/*
 * Inicializa o sistema. Carrega todas as coisas necessárias e define as
 * variáveis com seus valores iniciais.
 */
bool System::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        MessageBox("Unable to Init SDL", "Error: " +
                std::string(SDL_GetError()));
        return false;
    }
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode)){
        MessageBox("Unable to get informations about display", "Error: " + std::string(SDL_GetError()));
        return false;
    }
    self.screen_offset = {0, 0};
    self.w_width = 1440;
    self.w_height = 900;
    self.scaleX = (double)self.w_width/(double)WINDOW_WIDTH;
    self.scaleY = (double)self.w_height/(double)WINDOW_HEIGHT;
    if ((self.window = SDL_CreateWindow(
            "Game Application",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            self.w_width, self.w_height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN)
        ) == NULL) {
            MessageBox("Unable to create SDL Window", "Error: " + std::string(SDL_GetError()));
            return false;
    }
    else
        Log("+ [ Created ] %dx%d SDL Window", self.w_width, self.w_height);
    if (!create_renderer()){
        MessageBox("Unable to create renderer", "Error: " + std::string(SDL_GetError()));
        return false;
    }
#if DEBUG
    else{
        int logicalHeight = (int)(self.w_width*4.0f/5.0f);
        float scale = (float)std::min(self.scaleX, self.scaleY);
        SDL_RenderSetLogicalSize(self.renderer, self.w_width, logicalHeight);
        SDL_RenderSetScale(self.renderer, scale, scale);
    }
#endif

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear")) {
        MessageBox("Unable to Init hinting", "Error: " + std::string(SDL_GetError()));
        return false;
    }

    // Initialize image loading for PNGs
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        MessageBox("Unable to init SDL_image", "Error: " + std::string(IMG_GetError()));
        return false;
    }

    if (TTF_Init()){
        MessageBox("Unable to init SDL_ttf", "Error: " + std::string(TTF_GetError()));
        return false;
    }
    Log("+ [ Created ] System");

    return true;
}

/*
 * Fecha o sistema. Descarrega todas as coisas da memória e fecha os módulos do
 * SDL.
 */
void System::quit() {
    if (self.renderer)
        SDL_DestroyRenderer(self.renderer);
    if (self.window)
        SDL_DestroyWindow(self.window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    Log("- [ Cleaned ] System");
}

/*
 * Atualiza o sistema.
 * Limpa a tela, reseta o timer do frame e lê os eventos
 */
void System::update() {
    SDL_RenderClear(self.renderer);
    self.cap_timer.start();
    Events::update();
}

/*
 * Preenche a tela com uma cor
 */
void System::fill(SDL_Color color) {
    SDL_SetRenderDrawColor(self.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(self.renderer);
}

/*
 * Desenha uma textura na tela.
 * texID: ID da textura
 * src: Retângulo de origem da textura, fração da textura original que será
 *      renderizada
 * dst: Retângulo de destino da textura, fração da tela onde será renderizada a
 *      textura.
 * _static: Define se a posição da textura na tela é referente à janela (true)
 *          ou ao mundo (false). O padrão é mundo.
 */
void System::blit(SDL_Texture* tex, const SDL_Rect& src, const SDL_Rect& dst) {
    SDL_RenderCopy(self.renderer, tex, &src, &dst);
}

/*
 * Renderiza a tela gerada e calcula a taxa de quadros do frame.
 */
void System::render() {
    SDL_RenderPresent(self.renderer);
    calc_FPS();
}

/*
 * Redimensiona a janela para o tamanho especificado
 */
void System::resize_window(int w, int h) {
    self.w_width = w;
    self.w_height = h;
    SDL_SetWindowSize(self.window, self.w_width, self.w_height);

    self.scaleY = (double) self.w_height / (double) WINDOW_HEIGHT;
    self.scaleX = (double) self.w_width / (double) WINDOW_WIDTH;
#if DEBUG
    int logicalHeight = (int)(self.w_width*4.0f/5.0f);
    float scale = (float) std::min(self.scaleX, self.scaleY);

    SDL_RenderSetLogicalSize(self.renderer, self.w_width, logicalHeight);
    SDL_RenderSetScale(self.renderer, scale, scale);
#endif
}

/*
 * Traduz uma coordenada de janela para a coordenada de tela
 */
SDL_Point System::to_view_coord(SDL_Point p) {
    double scale = std::min(self.scaleX, self.scaleY);
    Point screen_real_size = Point{WINDOW_WIDTH, WINDOW_HEIGHT} * scale;
    Point offset = (Point{self.w_width, self.w_height} - screen_real_size)/2;

    return (SDL_Point)(Point(p - offset) / scale);
}

/*
 * Retorna a taxa de quadros por segundo (frames per second)
 */
float System::get_FPS() {
    return self.fps;
}

/*
 * Retorna a taxa de redimensionamento da tela em relação a da janela
 */
double System::get_scale(){
    return std::min(self.scaleX, self.scaleY);
}

/*
 * Retorna o tempo em milisegundos gasto no último quadro
 */
double System::get_delta_time() {
    return self.delta_time/1000.0;
}

/*
 * Retorna a janela
 */
SDL_Window *System::get_window() {
    return self.window;
}

/*
 * Retorna o renderer
 */
SDL_Renderer *System::get_renderer() {
    return self.renderer;
}

/*
 * Define a janela para a tela inteira
 */
void System::set_fullscreen(bool active) {
    if (active)
        SDL_SetWindowFullscreen(self.window,
                SDL_GetWindowFlags(self.window) | SDL_WINDOW_FULLSCREEN);
    else
        SDL_SetWindowFullscreen(self.window,
                SDL_GetWindowFlags(self.window) & (~SDL_WINDOW_FULLSCREEN));
}

/* private methods */

bool System::is_fullscreen() {
    return (bool)(SDL_GetWindowFlags(self.window) & SDL_WINDOW_FULLSCREEN);
}

/*
 * Calcula as taxas de quadros
 */
void System::calc_FPS() {
    self.delta_time = self.cap_timer.getTicks();
    if( self.delta_time < SCREEN_TICKS_PER_FRAME ) {
        //Wait remaining time
        SDL_Delay(SCREEN_TICKS_PER_FRAME - self.delta_time);
        self.delta_time = SCREEN_TICKS_PER_FRAME;
    }
    self.fps = 1.f/(self.delta_time / 1000.f);
#if 1
    if (self.delta_time > SCREEN_TICKS_PER_FRAME)
        Log("FPS: %f DELTA: %lf\n", self.fps, self.delta_time/1000.0);
#endif
}

/*
 * Cria o renderizador.
 */
bool System::create_renderer() {

    std::vector<std::string> drivers;
    std::string prior[] = {"opengl", "opengles2", "opengles",
                           "software"};

    int num_drivers = SDL_GetNumRenderDrivers();
    for (int i=0; i<num_drivers; i++){
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        std::string name(info.name);
        drivers.push_back(name);
    }

    int driver = -1;
    for (int i=0; i<4; i++){
        auto it = find(drivers.begin(), drivers.end(), prior[i]);
        if (it != drivers.end()){
            driver = it - drivers.begin();
            break;
        }
    }

    if ((self.renderer = SDL_CreateRenderer(self.window, driver,
            SDL_RENDERER_ACCELERATED)) == NULL)
        return false;
    else
        Log("+ [ Created ] SDL Renderer");

    SDL_RendererInfo info;
    SDL_GetRendererInfo(self.renderer, &info);
    Log("! [ Render  ] Name: %s", info.name);
    Log("! [ Render  ] Maximum Texture Size: %d x %d", info.max_texture_width,
            info.max_texture_height);

    SDL_SetRenderDrawColor(self.renderer, 0x0, 0x0, 0x0, 255);
    SDL_SetRenderDrawBlendMode(self.renderer, SDL_BLENDMODE_BLEND);
    return true;
}