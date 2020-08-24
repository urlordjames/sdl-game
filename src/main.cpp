// Copyright 2020 urlordjames
#include <iostream>
#include <cmath>
#include <algorithm>
#include "SDL.h"
#include "entity.hpp"

SDL_Texture* loadtexture(SDL_Renderer* r, const char *str) {
  SDL_Surface* s = SDL_LoadBMP(str);
  SDL_Texture* t = SDL_CreateTextureFromSurface(r, s);
  SDL_FreeSurface(s);
  return t;
}

void drawEntity(SDL_Renderer* r, Entity* entity) {
  for (const auto drawcomp : entity->textures) {
    SDL_RenderCopyEx(r,
                    drawcomp->getTexture(),
                    NULL,
                    &drawcomp->rect,
                    drawcomp->rot,
                    NULL,
                    SDL_FLIP_NONE);
  }
}

Entity* getDog(SDL_Renderer* r) {
  SDL_Texture *t = loadtexture(r, "assets/dog.bmp");
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = 64;
  rect.h = 64;
  DrawComponent *dogcomp = new DrawComponent(0, rect, t);
  Entity *dogent = new Entity;
  dogent->textures.push_back(dogcomp);
  return dogent;
}

int main(int, char **) {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *w = SDL_CreateWindow("dog",
                                  100,
                                  100,
                                  500,
                                  500,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  SDL_Renderer *r = SDL_CreateRenderer(w,
                                      -1,
                                      SDL_RENDERER_ACCELERATED |
                                      SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
  Entity *dogent = getDog(r);
  DrawComponent *dogcomp = dogent->textures.at(0);
  int deltatime = 0;
  bool quit = false;
  while (!quit) {
  int starttime = SDL_GetTicks();
  SDL_RenderClear(r);
  drawEntity(r, dogent);
  SDL_RenderPresent(r);
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        break;
      }
    }
    SDL_Delay(std::max(30 - deltatime, 0));
    deltatime = SDL_GetTicks() - starttime;
  }
  SDL_DestroyRenderer(r);
  SDL_DestroyWindow(w);
  SDL_Quit();
  return 0;
}
