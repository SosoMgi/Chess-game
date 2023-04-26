#include <SDL.h>
#include <iostream>
#include "include/lab.h"
#include "include/screen.h"


int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up

enum Direction {UP, DOWN, LEFT, RIGHT};


// screen class for the game from include/screen.h Screen::Screen(SDL_Window* pWindow = nullptr, SDL_Surface* win_surf = nullptr, SDL_Surface* plancheSprites = nullptr, SDL_Rect src_bg = { 200,3, 168,216 }, SDL_Rect bg = { 4,4, 672,864 }) : eventManager(eventManager), pWindow(pWindow), win_surf(win_surf), plancheSprites(plancheSprites), src_bg(src_bg), bg(bg)

Screen screen(nullptr, nullptr, nullptr, { 200,3, 168,216 }, { 4,4, 672,864 });
SDL_Rect ghost_r = { 3,123, 16,16 }; 
SDL_Rect ghost_l = { 37,123, 16,16 }; 
SDL_Rect ghost_d = { 105,123, 16,16 }; 
SDL_Rect ghost_u = { 71,123, 16,16 }; 
SDL_Rect ghost = { 38,38, 32,32 };     // ici scale x2

// initialisation position ghost en haut à gauche de l'arene
int count;

/*
* @brief: fonction which test if the position is a wall
*/

bool isWall(int x, int y)
{
    if (x < 0 || x >= ARENA_WIDTH || y < 0 || y >= ARENA_HEIGHT) {
        return true; // out of bounds
    }
    return arena[y][x] == 'w'; // check if the position is a wall
}


int xp =0;
int yp =0;
int counter = 0; // counter variable that increments every time the draw() function is called
int last_direction = direction;


int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        std::cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError() << std::endl;
        return 1;
    }

    screen.init();

    // BOUCLE PRINCIPALE
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (!quit && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            quit = true;
                            break;
                        case SDL_SCANCODE_UP: // id=f no wall in the direction of the key pressed so we change else we continue in the same direction
                            if (!isWall(ghost.x / 32, (ghost.y - 32) / 32)) {
                                last_direction = direction;
                                direction = 3;
                            } else {
                            }
                            break;
                        case SDL_SCANCODE_DOWN:
                            if (!isWall(ghost.x / 32, (ghost.y + 32) / 32)) {
                                last_direction = direction;
                                direction = 1;
                            } else {
                            }
                            break;
                        case SDL_SCANCODE_LEFT:
                            if (!isWall((ghost.x - 32) / 32, ghost.y / 32)) {
                                last_direction = direction;
                                direction = 2;
                            } else {
                            }
                            break;
                        case SDL_SCANCODE_RIGHT:
                            if (!isWall((ghost.x + 32) / 32, ghost.y / 32)) {
                                last_direction = direction;
                                direction = 0;
                            } else {
                            }
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    
        // update ghost position
        switch (direction) {
            case 0:
                // on teste si la prochaine position est un mur dans la direction actuelle
                if (!isWall((ghost.x + 32) / 32, ghost.y / 32)) {
                    for (int i = 0; i < 32; i++) {
                        ghost.x += 1;
                        // void draw(SDL_Rect ghost_r, SDL_Rect ghost_d, SDL_Rect ghost_l, SDL_Rect ghost_u, SDL_Rect ghost, int direction);
                        screen.draw(ghost_r, ghost_d, ghost_l, ghost_u, ghost, direction);
                        SDL_UpdateWindowSurface(screen.getWindow());
                        SDL_Delay(16);
                    }
                }
                break;
            case 1:
                if (!isWall(ghost.x / 32, (ghost.y + 32) / 32)) {
                    for (int i = 0; i < 32; i++) {
                        ghost.y += 1;
                        screen.draw(ghost_r, ghost_d, ghost_l, ghost_u, ghost, direction);
                        SDL_UpdateWindowSurface(screen.getWindow());
                        SDL_Delay(16);
                    }
                }
                break;
            case 2:
                if (!isWall((ghost.x - 32) / 32, ghost.y / 32)) {
                    for (int i = 0; i < 32; i++) {
                        ghost.x -= 1;
                        screen.draw(ghost_r, ghost_d, ghost_l, ghost_u, ghost, direction);
                        SDL_UpdateWindowSurface(screen.getWindow());
                        SDL_Delay(16);
                    }
                }
                break;
            case 3:
                if (!isWall(ghost.x / 32, (ghost.y - 32) / 32)) {
                    for (int i = 0; i < 32; i++) {
                        ghost.y -= 1;
                        screen.draw(ghost_r, ghost_d, ghost_l, ghost_u, ghost, direction);
                        SDL_UpdateWindowSurface(screen.getWindow());
                        SDL_Delay(16);
                    }
                }
                break;
            default:
                break;
        }

        // AFFICHAGE
        screen.draw(ghost_r, ghost_d, ghost_l, ghost_u, ghost, direction);
        SDL_UpdateWindowSurface(screen.getWindow());
        // LIMITE A 60 FPS
        SDL_Delay(16); // utiliser SDL_GetTicks64() pour plus de precisions
    }
        // on sort
        SDL_Quit();
        return 0;
}

