#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H

#include <vector>
#include <memory>
#include "raylib.h"
#include <string>
#include <stdexcept>

enum ImageFinder
{
    Background_M,
    PixelFlag
};

class TextureClass
{
    private:
        //Stores the loaded Images
        std::vector<std::unique_ptr<Image>> loadedImages;
        //Stores the loaded textures
        std::vector<Texture2D> loadedTextures;
    public:
        //Destructor that unloads all loaded images and textures
        ~TextureClass();
        void loadImage(std::string folder, ImageFinder img);
        void loadTexture();
        void loadAllTextures();
        void clearLoadedImages();
        void clearLoadedTextures();
        //Rescales the last loaded image using a given width and height
        void rescale(int width, int height);
        //Rescales all loaded images using a given width and height
        void rescaleAll(int width, int height);

        //Returns the specified loaded texture
        const Texture2D& getTexture(int index);
};

#endif