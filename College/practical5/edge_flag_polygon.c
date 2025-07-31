// Edge Flag (Scanline) Polygon Fill Algorithm using SDL2
#include <SDL2/SDL.h>
#include <stdio.h>

#define MAX_VERTICES 100
#define WIDTH 800
#define HEIGHT 600

// "Fill what's inside. Leave what's outside." — Polygon Philosophy 😄

void drawPolygon(SDL_Renderer *r, int x[], int y[], int n) {
    for (int i = 0; i < n; i++) {
        SDL_RenderDrawLine(r, x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
    }
}

void edgeFlagFill(SDL_Renderer *r, int x[], int y[], int n) {
    int flag[WIDTH] = {0};

    for (int scan_y = 0; scan_y < HEIGHT; scan_y++) {
        // Reset flag array
        for (int i = 0; i < WIDTH; i++) flag[i] = 0;

        // For each edge
        for (int i = 0; i < n; i++) {
            int x1 = x[i], y1 = y[i];
            int x2 = x[(i + 1) % n], y2 = y[(i + 1) % n];

            // Skip horizontal edges
            if (y1 == y2) continue;

            // Ensure y1 < y2
            if (y1 > y2) {
                int temp = x1; x1 = x2; x2 = temp;
                temp = y1; y1 = y2; y2 = temp;
            }

            // Check if scan_y is between y1 and y2
            if (scan_y >= y1 && scan_y < y2) {
                float slopeInv = (float)(x2 - x1) / (y2 - y1);
                int x_intersect = x1 + (scan_y - y1) * slopeInv;
                if (x_intersect >= 0 && x_intersect < WIDTH)
                    flag[x_intersect] = !flag[x_intersect]; // Toggle
            }
        }

        // Fill pixels between toggles
        int inside = 0;
        for (int x_pos = 0; x_pos < WIDTH; x_pos++) {
            if (flag[x_pos]) inside = !inside;
            if (inside) SDL_RenderDrawPoint(r, x_pos, scan_y);
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Edge Flag Polygon Fill",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *r = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(r, 0, 0, 0, 255); SDL_RenderClear(r);
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

    int n;
    printf("Enter number of polygon vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &n);

    int x[MAX_VERTICES], y[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        printf("Enter x y for vertex %d: ", i + 1);
        scanf("%d%d", &x[i], &y[i]);
    }

    drawPolygon(r, x, y, n);                // Outline
    edgeFlagFill(r, x, y, n);               // Fill
    SDL_RenderPresent(r);

    // Wait for quit
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
        }
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
