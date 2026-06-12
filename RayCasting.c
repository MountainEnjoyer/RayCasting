#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define HEIGHT 600
#define WIDTH 900
#define COLOR_WHITE 0xffffffff

int main()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *pwindow = SDL_CreateWindow("RayCasting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
  SDL_Rect rect = (SDL_Rect) {200,200,200,200};
  SDL_FillRect(psurface, &rect, COLOR_WHITE);

  SDL_UpdateWindowSurface(pwindow);
  SDL_Delay(3000);
  return EXIT_SUCCESS;
}
