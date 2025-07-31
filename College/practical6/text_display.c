// display_text_sdl.c
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

void renderText(SDL_Renderer *renderer, const char *text, const char *fontPath, int fontSize, int x, int y, SDL_Color color) {
    TTF_Font *font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        printf("Font Load Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
        printf("Init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Font Display",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Color white = {255, 255, 255, 255};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
    SDL_RenderClear(renderer);

    renderText(renderer, "Hello, to EveryOne!", 
        "/usr/share/fonts/TTF/FiraCode-Retina.ttf", 36, 50, 100, white);


    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
