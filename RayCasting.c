#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

#define HEIGHT 600
#define WIDTH 900
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_GRAY 0XEFEFEFEF
#define RAYS_NUMBER 10000

struct Circle {
  double x;
  double y;
  double radius;
};

struct Ray {
  double x_start, y_start;
  double angle;
  double x_end, y_end;
};

void FillCircle(SDL_Surface *surface, struct Circle circle, Uint32 color) {
  double radius_squared = pow(circle.radius, 2);
  for (double x=circle.x - circle.radius; x<= circle.x + circle.radius; x++){
    for (double y=circle.y - circle.radius; y<= circle.y + circle.radius; y++){
      double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
      if (distance_squared < radius_squared) {
        SDL_Rect pixel = (SDL_Rect) {x,y,1,1};
        SDL_FillRect(surface, &pixel, color);
      }
    }
  }
}

void generate_rays(struct Circle circle, struct Ray rays[RAYS_NUMBER]) {
  for (int i = 0; i<RAYS_NUMBER; i++) {
    double angle = ((double)i / RAYS_NUMBER) * 2 * M_PI;
    struct Ray ray = {circle.x, circle.y, angle};
    rays[i] = ray;
  }
}

void FillRays(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 color) {
  for (int i=0; i<RAYS_NUMBER; i++) {
    struct Ray ray = rays[i];
    
    int end_of_screen = 0;
    int object_hit = 0;

    double step = 1;
    double x_draw = ray.x_start;
    double y_draw = ray.y_start;
    
    while(!end_of_screen && !object_hit) {
      x_draw += step*cos(ray.angle);
      y_draw += step*sin(ray.angle);

      SDL_Rect pixel = (SDL_Rect) {x_draw,y_draw,1,1};
      SDL_FillRect(surface, &pixel, color);
      
      if (x_draw < 0 || x_draw > WIDTH)
        end_of_screen = 1;
      if (y_draw < 0 || y_draw > HEIGHT)
        end_of_screen = 1;
    }
  }
}

int main()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *pwindow = SDL_CreateWindow("RayCasting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
  
  struct Circle circle = {200, 200, 80};
  struct Circle shadow_circle = {650,300,140};
  SDL_Rect erase_rect = (SDL_Rect){0,0, WIDTH, HEIGHT};

  int simulation_running = 1;
  SDL_Event event;

  struct Ray rays[RAYS_NUMBER];
  generate_rays(circle, rays);

  while (simulation_running) {
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        simulation_running = 0;
      }
      if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
        circle.x = event.motion.x;
        circle.y = event.motion.y;
        generate_rays(circle,rays);
      }
    }
    SDL_FillRect(psurface, &erase_rect, COLOR_BLACK);
    FillCircle(psurface, circle,COLOR_WHITE);
    FillCircle(psurface, shadow_circle, COLOR_WHITE);
    FillRays(psurface, rays, COLOR_GRAY);

    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(10);
  }

  return EXIT_SUCCESS;
}
