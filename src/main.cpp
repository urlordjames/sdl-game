#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include "SDL.h"

SDL_Texture* loadtexture(SDL_Renderer* r, const char *str) {
    SDL_Surface* s = SDL_LoadBMP(str);
    SDL_Texture* t = SDL_CreateTextureFromSurface(r, s);
    SDL_FreeSurface(s);
    return t;
}

class DrawComponent {
protected:
	SDL_Texture *tex;
public:
	double rot;
	SDL_Rect rect;
	DrawComponent(double rotation, SDL_Rect rectangle, SDL_Texture* texture) {
		rot = rotation;
		rect = rectangle;
		tex = texture;
	}

	SDL_Texture* getTexture() {
		return tex;
	}
};

class Entity {
public:
	std::vector<DrawComponent *> textures;
};

void drawEntity(SDL_Renderer* r, Entity* entity) {
	for (const auto drawcomp : entity->textures) {
		SDL_RenderCopyEx(r, drawcomp->getTexture(), NULL, &drawcomp->rect, drawcomp->rot, NULL, SDL_FLIP_NONE);
	}
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
    DrawComponent *dogcomp = new DrawComponent(0, rect, t);

    Entity *dogent = new Entity;
    dogent->textures.push_back(dogcomp);

    int deltatime = 0;
    while (true) {
	int starttime = SDL_GetTicks();
	std::cout << deltatime << std::endl;
	SDL_RenderClear(r);
	drawEntity(r, dogent);
	dogcomp->rect.w = dogcomp->rect.w + 1;
	dogcomp->rect.h = dogcomp->rect.h + 1;
	dogcomp->rot = std::fmod(dogcomp->rot + 1, 360);
        SDL_RenderPresent(r);
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
	SDL_Delay(std::min(30 - deltatime, 0));
	deltatime = SDL_GetTicks() - starttime;
    }
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}
