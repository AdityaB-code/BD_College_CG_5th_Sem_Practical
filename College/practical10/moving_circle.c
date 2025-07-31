#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265

// Draw filled circle
void draw_circle(SDL_Renderer *renderer, int cx, int cy, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if (dx*dx + dy*dy <= radius * radius)
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Moving Circle with Transformations", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    float x = 100;
    float y = HEIGHT / 2;
    float radius = 50;
    float scale = 1.0f;
    float angle = 0.0f;
    float dx = 2.0f;  // Speed

    SDL_Event e;
    bool quit = false;
    bool moveRight = true;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT)
                    moveRight = false;
                else if (e.key.keysym.sym == SDLK_RIGHT)
                    moveRight = true;
            }
        }

        // Update transformations
        if (moveRight) x += dx;
        else x -= dx;

        scale = 1.0 + 0.2 * sin(SDL_GetTicks() / 300.0);  // pulsating scale
        angle += 1.0f;  // rotate (not visually applied here since it’s a circle)

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw transformed circle
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        draw_circle(renderer, (int)x, (int)y, (int)(radius * scale));

        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
