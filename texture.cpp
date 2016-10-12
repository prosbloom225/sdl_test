#include "texture.h"
#include <SDL2/SDL_image.h>

#include "main.h"

// Init
LTexture::LTexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
};

LTexture::~LTexture() {
    // Deallocate
    free();
}


bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer){
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
       defaultLogger->error("Unable to load image %v! SDL_image error: %v\n", path.c_str(), IMG_GetError());
    } else {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            defaultLogger->error("Unable to create texture from %v! SDL Error: %v\n", path.c_str(), IMG_GetError());
        } else {
            // Get image dims
            mWidth = loadedSurface->w;
            mHeight= loadedSurface->h;
        }
        // Free old surface
        SDL_FreeSurface(loadedSurface);
    }
     // return success
     mTexture = newTexture;
     return mTexture != NULL;
};

// Dealloc texture
void LTexture::free(){
    // Free texture if it exists
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
};

void LTexture::render(int x, int y, SDL_Renderer* renderer){
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
};
