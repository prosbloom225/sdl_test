#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

#include "texture.h"
#include "main.h"
INITIALIZE_EASYLOGGINGPP

el::Logger* defaultLogger = el::Loggers::getLogger("main");


// STUBS
SDL_Texture* loadTexture(std::string path);

// CONST DECLARE
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// GLOBALS 
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gOptimizedSurface = NULL;
LTexture *texture = NULL;




bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        defaultLogger->error( "SDL could not initialize! SDL_Error: %v\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
        defaultLogger->error ("Window could not be created!  SDL_Error: %v\n", SDL_GetError());
        success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                defaultLogger->error("Renderer could not be created! SDL Error: %v\n", SDL_GetError());
                success = false;
            } else {

                // Init PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    defaultLogger->error("SDL_image could not initialize! SDL_image error: %v\n", IMG_GetError());
                    success = false;
                }

                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    // Load texture
    texture = new LTexture();
    if (!texture->loadFromFile("assets/background.png", gRenderer)) {
        defaultLogger->error("Failed to load background texture image\n");
        success = false;
    } else {
        texture->render(0,0, gRenderer);
    }

    return success;
}

void close() {
    SDL_FreeSurface(gOptimizedSurface);

    texture->free();

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(std::string path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        defaultLogger->error("Unable to load image %v! SDL_Image error: %v\n", path.c_str(), IMG_GetError());
    } else {
        // Create new texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface (gRenderer, loadedSurface);
        if (newTexture == NULL) {
            defaultLogger->error("Unable to create texture from %v! SDL_Error %v\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

int main(){
    if (!init()) {
        defaultLogger->error("Failed to init!\n");
    } else {
        if (!loadMedia()) {
            defaultLogger->error("Failed to load media!\n");
        } else {

            // Main loop
            bool quit = false;
            while (!quit) {
                SDL_Event e;
                // Game loop
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        // Keybinds
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                defaultLogger->info("Up pressed!");
                                break;
                            case SDLK_DOWN:
                                defaultLogger->info("Down pressed!");
                                break;
                            case SDLK_LEFT:
                                defaultLogger->info("Left pressed!");
                                break;
                            case SDLK_RIGHT:
                                defaultLogger->info("Right pressed!");
                                break;
                        }
                    }

                    // Clear screen
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    loadMedia();

                    /* // Left Viewport */
                    /* SDL_Rect topLeftViewport; */
                    /* topLeftViewport.x = 0; */
                    /* topLeftViewport.y = 0; */
                    /* topLeftViewport.w = SCREEN_WIDTH/2; */
                    /* topLeftViewport.h = SCREEN_HEIGHT/2; */
                    /* SDL_RenderSetViewport(gRenderer, &topLeftViewport); */
                    /* // Right Viewport */
                    /* SDL_Rect topRightViewport; */
                    /* topRightViewport.x = SCREEN_WIDTH/2; */
                    /* topRightViewport.y = 0; */
                    /* topRightViewport.w = SCREEN_WIDTH/2; */
                    /* topRightViewport.h = SCREEN_HEIGHT/2; */
                    /* SDL_RenderSetViewport(gRenderer, &topRightViewport); */
                    /* // Bottom Viewport */
                    /* SDL_Rect bottomViewport; */
                    /* bottomViewport.x = 0; */
                    /* bottomViewport.y = SCREEN_HEIGHT/2; */
                    /* bottomViewport.w = SCREEN_WIDTH; */
                    /* bottomViewport.h = SCREEN_HEIGHT/2; */
                    /* SDL_RenderSetViewport(gRenderer, &bottomViewport); */

                    // Rect
                    SDL_Rect fillRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                    SDL_RenderFillRect(gRenderer, &fillRect);

                    /* // Outline Rect */
                    /* SDL_Rect outlineRect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH *3/3, SCREEN_HEIGHT*2/3}; */
                    /* SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF); */
                    /* SDL_RenderDrawRect(gRenderer, &outlineRect); */
                    
                    /* // Line */
                    /* SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF); */
                    /* SDL_RenderDrawLine(gRenderer, 9, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2); */

                    /* // Dotted line */
                    /* SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF); */
                    /* for (int i=0; i < SCREEN_HEIGHT; i += 4) { */
                    /*     SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH/2, i); */
                    /* } */

                    // Update
                    SDL_RenderPresent(gRenderer);
                }
            }
            close();
            return 0;
        }
    }
     
}
