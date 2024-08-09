#include <stdio.h>

#include <SDL2/SDL.h>

const char *TITLE = "Brick Breaker";
const int SCREEN_SIZE[2] = {640, 480};
const int SCREEN_POS[2] = {100, 100};

const int FPS = 20;

typedef struct {
    int r;
    int g;
    int b;
} Color;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int vx;
    int vy;
    Color color;
} GameObject;

// Color constants
const Color BLACK = {255, 255, 255};
const Color WHITE = {255, 255, 255};

GameObject create_GameObject(int x, int y, int width, int height, int vx, int vy, Color color) {
    GameObject go;

    go.x = x;
    go.y = y;
    go.width = width;
    go.height = height;
    go.vx = vx;
    go.vy = vy;
    go.color = color;

    return go;
}

// draw all game objects
void draw_rectangle(SDL_Renderer *renderer, GameObject *go) {
    // Set the draw color to the game object's color
    SDL_SetRenderDrawColor(renderer, go->color.r, go->color.g, go->color.b, 255);

    // Define the rectangle to be drawn
    SDL_Rect rect = {go->x, go->y, go->width, go->height};

    // Draw the rectangle (filled)
    if (SDL_RenderFillRect(renderer, &rect) != 0) {
        fprintf(stderr, "Error drawing rectangle: %s\n", SDL_GetError());
    }
}

void move_player(GameObject *player, int dir) {
    player->x += player->vx * dir;
}

void animate_ball(GameObject *ball) {
    ball->x += ball->vx;
    ball->y += ball->vy;

    if (ball->x >= SCREEN_SIZE[0] - (ball->width / 2) || ball->x <= 0) {
        ball->vx *= -1;
    }
    
    if (ball->y >= SCREEN_SIZE[1] - (ball->height / 2) || ball->y <= 0) {
        ball->vy *= -1;
    }
}

int main() {
    const int PLAYER_WIDTH = 50;
    const int PLAYER_HEIGHT = 10;
    const int BALL_SIZE = 10;

    GameObject player = create_GameObject(
        (SCREEN_SIZE[0] / 2) - (PLAYER_WIDTH / 2), SCREEN_SIZE[1] - 50,
        PLAYER_WIDTH, PLAYER_HEIGHT,
        10, 0, WHITE);
    
    GameObject ball = create_GameObject(
        (SCREEN_SIZE[0] / 2) - (BALL_SIZE / 2), (SCREEN_SIZE[1] / 2) - (BALL_SIZE / 2),
        BALL_SIZE, BALL_SIZE,
        12, 12, WHITE);
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow(TITLE,
                                          SCREEN_POS[0], SCREEN_POS[1],
                                          SCREEN_SIZE[0], SCREEN_SIZE[1],
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop placeholder
    int running = 1;
    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        move_player(&player, -1);
                        break;
                    case SDLK_RIGHT:
                        move_player(&player, 1);
                        break;
                }
            }
        }

        // Clear the screen with a black color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the game object
        draw_rectangle(renderer, &player);
        draw_rectangle(renderer, &ball);
        animate_ball(&ball);

        // Present the renderer
        SDL_RenderPresent(renderer);

        // Frame rate control
        SDL_Delay(1000 / FPS);
    }

    // Clean up and quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}