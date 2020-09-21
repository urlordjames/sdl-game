// Copyright 2020 urlordjames
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_map>
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
    SDL_Rect newrect;
    newrect.x = drawcomp->rect.x + entity->x;
    newrect.y = drawcomp->rect.y + entity->y;
    newrect.w = drawcomp->rect.w;
    newrect.h = drawcomp->rect.h;
    SDL_RenderCopyEx(r,
                    drawcomp->getTexture(),
                    NULL,
                    &newrect,
                    drawcomp->rot,
                    NULL,
                    SDL_FLIP_NONE);
  }
}

void drawEnts(SDL_Renderer* r, std::vector<Entity*>* ents) {
  for (auto i : *ents) {
    drawEntity(r, i);
  }
}

Entity* basicEnt(SDL_Renderer* r, SDL_Texture* t) {
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

#define movespeed 1
#define friction 0.95

int deltatime = 0;
bool quit = false;
std::unordered_map<int, bool> keys;
double acx = 0;
double acy = 0;
std::vector<Entity*> ents;

void handleInput() {
  if (keys[79] || keys[7]) {
    acx += movespeed;
  }
  if (keys[80] || keys[4]) {
    acx -= movespeed;
  }
  if (keys[81] || keys[22]) {
    acy += movespeed;
  }
  if (keys[82] || keys[26]) {
    acy -= movespeed;
  }
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
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
  Entity *dogent = basicEnt(r, loadtexture(r, "assets/dog.bmp"));
  SDL_Texture *cheesetex = loadtexture(r, "assets/cheese.bmp");
  Entity *cheeseent = basicEnt(r, cheesetex);
  Entity *cheeseent2 = basicEnt(r, cheesetex);
  cheeseent2->x = 30;
  ents.push_back(cheeseent);
  ents.push_back(cheeseent2);
  while (!quit) {
    int starttime = SDL_GetTicks();
    handleInput();
    if (keys[8]) {
      if (ents.size() > 0) {
        auto it = ents.begin();
        ents.erase(it);
      }
    }
    dogent->x += acx;
    dogent->y += acy;
    dogent->x *= friction;
    dogent->y *= friction;
    SDL_RenderClear(r);
    drawEnts(r, &ents);
    drawEntity(r, dogent);
    SDL_RenderPresent(r);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYDOWN:
          keys[event.key.keysym.scancode] = true;
          break;
        case SDL_KEYUP:
          keys[event.key.keysym.scancode] = false;
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
