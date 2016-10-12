#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

class LTexture {
    public:
        // Init
        LTexture();

        // Dealloc mem
        ~LTexture();

        bool loadFromFile(std::string path, SDL_Renderer* renderer);

        // Dealloc texture
        void free();

        void render(int x, int y, SDL_Renderer* renderer);

        int getWidth(){return mWidth;};
        int getHeight(){return mHeight;};

    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};
#endif
