#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    float x, y;
} Point;

// Apply transformation matrix to a point
Point transform(Point p, float matrix[2][2], Point translation) {
    Point result;
    result.x = matrix[0][0] * p.x + matrix[0][1] * p.y + translation.x;
    result.y = matrix[1][0] * p.x + matrix[1][1] * p.y + translation.y;
    return result;
}

// Draw triangle
void drawTriangle(SDL_Renderer *renderer, Point p1, Point p2, Point p3) {
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLine(renderer, p2.x, p2.y, p3.x, p3.y);
    SDL_RenderDrawLine(renderer, p3.x, p3.y, p1.x, p1.y);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("2D Transformations", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // Original triangle
    Point A = {200, 200}, B = {250, 100}, C = {300, 200};

    // Choose a transformation below:
    
    // 1. Translation
    float matrix[2][2] = {{1, 0}, {0, 1}};
    Point translation = {200, 150};

    // 2. Scaling
    // float matrix[2][2] = {{1.5, 0}, {0, 1.5}};
    // Point translation = {0, 0};

    // 3. Rotation (45 degrees)
    // float angle = M_PI / 4;
    // float matrix[2][2] = {{cos(angle), -sin(angle)}, {sin(angle), cos(angle)}};
    // Point translation = {0, 0};

    // 4. Shearing (x shear)
    // float matrix[2][2] = {{1, 0.5}, {0, 1}};
    // Point translation = {0, 0};

    // 5. Reflection over X-axis
    // float matrix[2][2] = {{1, 0}, {0, -1}};
    // Point translation = {0, 400}; // Adjust to make it visible

    // Transform triangle
    Point A2 = transform(A, matrix, translation);
    Point B2 = transform(B, matrix, translation);
    Point C2 = transform(C, matrix, translation);

    // Draw
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    // Original (white)
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    drawTriangle(ren, A, B, C);

    // Transformed (red)
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    drawTriangle(ren, A2, B2, C2);

    SDL_RenderPresent(ren);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
