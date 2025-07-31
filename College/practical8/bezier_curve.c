#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_POINTS 10

typedef struct {
    float x, y;
} Point;

// nCr function
int nCr(int n, int r) {
    int res = 1;
    for (int i = 0; i < r; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

// Bernstein polynomial
float bernstein(int n, int i, float t) {
    return nCr(n, i) * pow(t, i) * pow(1 - t, n - i);
}

// Calculate Bezier point
Point bezier(Point ctrl[], int n, float t) {
    Point p = {0, 0};
    for (int i = 0; i <= n; ++i) {
        float b = bernstein(n, i, t);
        p.x += ctrl[i].x * b;
        p.y += ctrl[i].y * b;
    }
    return p;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Bezier Curve", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // Set control points (you can change them)
    Point ctrl[] = {
        {100, 500},
        {200, 100},
        {600, 100},
        {700, 500}
    };
    int n = 3; // Degree = number of control points - 1

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    // Draw control polygon (dotted line)
    SDL_SetRenderDrawColor(ren, 100, 100, 100, 255);
    for (int i = 0; i < n; i++) {
        SDL_RenderDrawLine(ren, ctrl[i].x, ctrl[i].y, ctrl[i+1].x, ctrl[i+1].y);
    }

    // Draw Bezier curve (smooth red)
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    for (float t = 0; t <= 1.0; t += 0.001) {
        Point p = bezier(ctrl, n, t);
        SDL_RenderDrawPoint(ren, p.x, p.y);
    }

    // Draw control points (blue dots)
    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
    for (int i = 0; i <= n; ++i) {
        SDL_Rect dot = {ctrl[i].x - 2, ctrl[i].y - 2, 4, 4};
        SDL_RenderFillRect(ren, &dot);
    }

    SDL_RenderPresent(ren);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = 1;
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
