#include <iostream>
#include <SDL2/SDL.h>

SDL_Texture* loadtexture(SDL_Renderer* r, const char *str) {
    SDL_Surface* s = SDL_LoadBMP(str);
    SDL_Texture* t = SDL_CreateTextureFromSurface(r, s);
    SDL_FreeSurface(s);
    return t;
}

void drawframe(SDL_Renderer* r, SDL_Texture* t, int scale) {
    SDL_RenderClear(r);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = scale;
    rect.h = scale;
    SDL_RenderCopy(r, t, NULL, &rect);
    return;
}

int main(int, char **) {
    int scale = 0;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *w = SDL_CreateWindow("dog", 100, 100, 500, 500, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
    SDL_Texture* t = loadtexture(r, "dog.bmp");
    while (true) {
        drawframe(r, t, scale);
        scale += 1;
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