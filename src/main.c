#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#define sdl_handle_error(error)                    \
    do {                                           \
        SDL_Log("%s : %s",error,SDL_GetError());   \
        SDL_Quit();                                \
        return 1;                                  \
    } while (0)

int main(int argc, char *argv[]) {

  SDL_SetHint(SDL_HINT_VIDEODRIVER,"wayland");

  if(0 != SDL_Init(SDL_INIT_VIDEO))
    sdl_handle_error("Unable to initialize");


  SDL_Window *window = SDL_CreateWindow("Ragnarok",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         1280,720,
                                         SDL_WINDOW_RESIZABLE);
  if(window == NULL)
    sdl_handle_error("Unable to create Window");

  SDL_Renderer *render  = SDL_CreateRenderer(window,
                                             -1,
                                             SDL_RENDERER_ACCELERATED);
  
  if(render == NULL)
    sdl_handle_error("Unable to create Renderer");

  SDL_Event event;
  int pos_x,pos_y = 100;
  int speed = 1;

  while(true){
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
      break;

    const uint8_t *key_state = SDL_GetKeyboardState(NULL);
    if(key_state[SDL_SCANCODE_W]){
      pos_y -= speed;
    } else if(key_state[SDL_SCANCODE_S]){
      pos_y += speed;
    } else if(key_state[SDL_SCANCODE_A]){
      pos_x -= speed;
    } else if(key_state[SDL_SCANCODE_D]){
      pos_x += speed;
    }

    SDL_SetRenderDrawColor(render,0,0,0,0);
    SDL_RenderClear(render);

    SDL_Rect rectangle = {
      .x = pos_x,
      .y = pos_y,
      .w = 10,
      .h = 10,
    };

    SDL_SetRenderDrawColor(render,0,255,0,0);

    SDL_RenderDrawRect(render, &rectangle);

    SDL_RenderFillRect(render, &rectangle);

    SDL_RenderPresent(render);

    // SDL_RenderClear(render);
  }

  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
