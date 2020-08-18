#include <iostream>
#include "SDL.h"

SDL_Texture* loadtexture(SDL_Renderer* r, const char *str) {
    SDL_Surface* s = SDL_LoadBMP(str);
    SDL_Texture* t = SDL_CreateTextureFromSurface(r, s);
    SDL_FreeSurface(s);
    return t;
}

class Entity {
public:
	SDL_Rect rect;
	SDL_Texture *texture;
};

void drawEntity(SDL_Renderer* r, Entity* ent) {
	SDL_RenderCopy(r, ent->texture, NULL, &ent->rect);
}

int main(int, char **) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *w = SDL_CreateWindow("dog", 100, 100, 500, 500, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(r, 0, 0, 255, 255);

    SDL_Texture *t = loadtexture(r, "assets/dog.bmp");
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 1;
    rect.h = 1;
    Entity *dogent = new Entity;
    dogent->rect = rect;
    dogent->texture = t;

    while (true) {
	SDL_RenderClear(r);
	drawEntity(r, dogent);
	dogent->rect.w = dogent->rect.w + 1;
	dogent->rect.h = dogent->rect.h + 1;
        SDL_RenderPresent(r);
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
    }
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}
