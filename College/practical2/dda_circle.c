// DDA Circle Drawing Algorithm using SDL2 on Linux
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// "The shortest distance between two points is a circle." – Mark Twain (sort of)

#define PI 3.14159265

void drawCircleDDA(SDL_Renderer *renderer, int xc, int yc, int r) {
    float angle_step = 1.0; // degrees
    for (float angle = 0; angle <= 360; angle += angle_step) {
        float rad = angle * PI / 180.0;
        int x = xc + r * cos(rad);
        int y = yc + r * sin(rad);
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("DDA Circle Drawing",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Clear background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int x, y, r;
    printf("Enter center x y: ");
    scanf("%d%d", &x, &y);
    printf("Enter radius r: ");
    scanf("%d", &r);

    // Set draw color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    drawCircleDDA(renderer, x, y, r);

    SDL_RenderPresent(renderer);

    // Wait for window close
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = 1;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
