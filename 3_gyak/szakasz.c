#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LINE_COUNT 100
#define PALETTE_SIZE 5
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct Color {
    Uint8 r, g, b;
} Color;

typedef struct Line {
    int x1, y1, x2, y2;
    Color color;
} Line;

Color palette[PALETTE_SIZE] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {255, 255, 0},
    {255, 255, 255}
};

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    SDL_Window* window = SDL_CreateWindow("Szakaszok", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Line lines[MAX_LINE_COUNT];
    int line_count = 0;
    
    Color currentColor = palette[4]; // default white color
    bool is_drawing = false;
    int startX, startY;
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;

            // mouse movement
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mx = e.button.x;
                int my = e.button.y;

                printf("Mouse click: x=%d, y=%d\n", mx, my);

                // Color selection
                if (my < 50 && mx < PALETTE_SIZE * 60) {
                    int index = mx / 60;
                    currentColor = palette[index];
                    printf("Chosen color: R:%d G:%d B:%d\n", currentColor.r, currentColor.g, currentColor.b);
                }
                else {
                    if (!is_drawing) {
                        startX = mx;
                        startY = my;
                        is_drawing = true;
                    } else {
                        if (line_count < MAX_LINE_COUNT) {
                            lines[line_count] = (Line){startX, startY, mx, my, currentColor};
                            line_count++;
                        }
                        is_drawing = false;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Drawing
        for (int i = 0; i < PALETTE_SIZE; i++) {
            SDL_Rect pRect = {i * 60 + 5, 5, 50, 40};
            SDL_SetRenderDrawColor(renderer, palette[i].r, palette[i].g, palette[i].b, 255);
            SDL_RenderFillRect(renderer, &pRect);

            if (currentColor.r == palette[i].r && currentColor.g == palette[i].g) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
                SDL_RenderDrawRect(renderer, &pRect);
            }
        }

        for (int i = 0; i < line_count; i++) {
            SDL_SetRenderDrawColor(renderer, lines[i].color.r, lines[i].color.g, lines[i].color.b, 255);
            SDL_RenderDrawLine(renderer, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
        }

        if (is_drawing) {
            int curX, curY;
            SDL_GetMouseState(&curX, &curY);
            SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, 100);
            SDL_RenderDrawLine(renderer, startX, startY, curX, curY);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}