// Draw simple shapes (Hut, Star, Car) using SDL2
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

void drawHut(SDL_Renderer *r) {
    // Walls (rectangle)
    SDL_RenderDrawLine(r, 200, 300, 200, 500);
    SDL_RenderDrawLine(r, 400, 300, 400, 500);
    SDL_RenderDrawLine(r, 200, 500, 400, 500);
    SDL_RenderDrawLine(r, 200, 300, 400, 300);

    // Roof (triangle)
    SDL_RenderDrawLine(r, 200, 300, 300, 200);
    SDL_RenderDrawLine(r, 300, 200, 400, 300);
}

void drawStar(SDL_Renderer *r, int cx, int cy, int radius) {
    float angle = 2 * PI / 5;
    SDL_Point points[6];
    for (int i = 0; i < 5; ++i) {
        points[i].x = cx + radius * cos(i * 2 * angle);
        points[i].y = cy + radius * sin(i * 2 * angle);
    }
    points[5] = points[0]; // close the star

    for (int i = 0; i < 5; ++i) {
        SDL_RenderDrawLine(r, points[i].x, points[i].y, points[(i + 2) % 5].x, points[(i + 2) % 5].y);
    }
}

void drawCar(SDL_Renderer *r) {
    // Body
    SDL_Rect body = {100, 400, 300, 100};
    SDL_RenderDrawRect(r, &body);

    // Top part
    SDL_RenderDrawLine(r, 150, 400, 200, 350);
    SDL_RenderDrawLine(r, 200, 350, 300, 350);
    SDL_RenderDrawLine(r, 300, 350, 350, 400);

    // Wheels
    for (int i = 0; i < 360; i++) {
        int x1 = 160 + 30 * cos(i * PI / 180);
        int y1 = 510 + 30 * sin(i * PI / 180);
        SDL_RenderDrawPoint(r, x1, y1);

        int x2 = 340 + 30 * cos(i * PI / 180);
        int y2 = 510 + 30 * sin(i * PI / 180);
        SDL_RenderDrawPoint(r, x2, y2);
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Simple Shapes: Hut, Star, Car",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    drawHut(renderer);
    drawStar(renderer, 600, 150, 50);
    drawCar(renderer);

    SDL_RenderPresent(renderer);

    // Wait for quit
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

