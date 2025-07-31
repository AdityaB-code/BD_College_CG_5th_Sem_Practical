#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

// Get pixel color at (x, y)
Uint32 get_pixel(SDL_Surface *surface, int x, int y) {
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
    Uint32 pixel = 0;
    memcpy(&pixel, p, surface->format->BytesPerPixel);
    return pixel;
}

// Set pixel color at (x, y)
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
    memcpy(p, &color, surface->format->BytesPerPixel);
}

// Boundary Fill (4-connected)
void boundaryFill(SDL_Surface *surface, int x, int y, Uint32 fillColor, Uint32 boundaryColor) {
    if (x < 0 || y < 0 || x >= surface->w || y >= surface->h)
        return;

    Uint32 currentColor = get_pixel(surface, x, y);
    if (currentColor != boundaryColor && currentColor != fillColor) {
        set_pixel(surface, x, y, fillColor);
        boundaryFill(surface, x + 1, y, fillColor, boundaryColor);
        boundaryFill(surface, x - 1, y, fillColor, boundaryColor);
        boundaryFill(surface, x, y + 1, fillColor, boundaryColor);
        boundaryFill(surface, x, y - 1, fillColor, boundaryColor);
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Boundary Fill", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255)); // Background white

    // Draw boundary rectangle in red
    SDL_Rect rect = {100, 100, 300, 200};
    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 0, 0)); // Fill red (boundary)

    SDL_LockSurface(surface);

    // Start boundary fill from inside rectangle
    boundaryFill(surface, 150, 150,
                 SDL_MapRGB(surface->format, 0, 0, 255),  // Fill color: Blue
                 SDL_MapRGB(surface->format, 255, 0, 0)); // Boundary color: Red

    SDL_UnlockSurface(surface);

    // Create texture from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Show result
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
