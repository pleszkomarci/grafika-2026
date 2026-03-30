#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_CIRCLE_COUNT 50
#define PALETTE_SIZE 5

typedef struct Color {
    Uint8 r, g, b;
} Color;

typedef struct Circle {
    double x, y;
    double radius;
    Color color;
} Circle;

void set_circle_data(Circle* circle, double x, double y, double radius, Color color) {
    circle->x = x;
    circle->y = y;
    circle->color = color;
    circle->radius = (radius > 0.0) ? radius : 0.0;
}

void draw_approximated_circle(SDL_Renderer* renderer, const Circle* circle) {
    int segments = (int)(circle->radius * 0.5) + 20; 
    double step = 2.0 * M_PI / segments;

    SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, 255);

    for (int i = 0; i < segments; i++) {
        double a1 = i * step;
        double a2 = (i + 1) * step;

        int x1 = circle->x + cos(a1) * circle->radius;
        int y1 = circle->y + sin(a1) * circle->radius;
        int x2 = circle->x + cos(a2) * circle->radius;
        int y2 = circle->y + sin(a2) * circle->radius;

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Circles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 768);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Circle circles[MAX_CIRCLE_COUNT];
    int circle_count = 0;
    Color palette[PALETTE_SIZE] = {{255,0,0}, {0,255,0}, {0,100,255}, {255,255,0}, {255,255,255}};
    Color currentColor = palette[4];

    Circle* dragged_circle = NULL;
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        int mx, my;
        Uint32 mouse_state = SDL_GetMouseState(&mx, &my);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (my < 50 && mx < PALETTE_SIZE * 60) {
                    currentColor = palette[mx / 60];
                } else {
                    //The circle exists
                    bool found = false;
                    for (int i = 0; i < circle_count; i++) {
                        double dist = sqrt(pow(mx - circles[i].x, 2) + pow(my - circles[i].y, 2));
                        if (dist < circles[i].radius) {
                            dragged_circle = &circles[i];
                            found = true;
                            break;
                        }
                    }
                    // Create new circle
                    if (!found && circle_count < MAX_CIRCLE_COUNT) {
                        set_circle_data(&circles[circle_count++], mx, my, 40.0, currentColor);
                    }
                }
            }
            if (e.type == SDL_MOUSEBUTTONUP) dragged_circle = NULL;
        }

        // Moving circle
        if (dragged_circle) {
            dragged_circle->x = mx;
            dragged_circle->y = my;
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 25, 255);
        SDL_RenderClear(renderer);

        // Körök és "+" jelek rajzolása
        for (int i = 0; i < circle_count; i++) {
            draw_approximated_circle(renderer, &circles[i]);

            // Circle hovered
            double dist = sqrt(pow(mx - circles[i].x, 2) + pow(my - circles[i].y, 2));
            if (dist < circles[i].radius) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawLine(renderer, circles[i].x - 10, circles[i].y, circles[i].x + 10, circles[i].y);
                SDL_RenderDrawLine(renderer, circles[i].x, circles[i].y - 10, circles[i].x, circles[i].y + 10);
            }
        }

        for (int i = 0; i < PALETTE_SIZE; i++) {
            SDL_Rect r = {i * 60 + 5, 5, 50, 40};
            SDL_SetRenderDrawColor(renderer, palette[i].r, palette[i].g, palette[i].b, 255);
            SDL_RenderFillRect(renderer, &r);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}