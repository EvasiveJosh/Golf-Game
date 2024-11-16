#include "TextureClass.h"

TextureClass::~TextureClass()
{
    clearLoadedTextures();
    clearLoadedImages();
}

void TextureClass::loadImage(std::string folder, ImageFinder img)
{
    std::string filepath = "./" + folder + "/" + std::to_string(img) + ".png";
    loadedImages.push_back(std::make_unique<Image>(LoadImage(filepath.c_str())));
}

void TextureClass::clearLoadedImages()
{
    while(!loadedImages.empty())
    {
        UnloadImage(*loadedImages.back());
        loadedImages.pop_back();
    }
}

void TextureClass::clearLoadedTextures()
{
    while(!loadedTextures.empty())
    {
        UnloadTexture(loadedTextures.back());
        loadedTextures.pop_back();
    }
}

void TextureClass::loadTexture()
{
    Image &img = *loadedImages[loadedImages.size() - 1];
    loadedTextures.push_back(LoadTextureFromImage(img));
}

void TextureClass::loadAllTextures()
{
    for(int i = 0; i < loadedImages.size(); i++)
    {
        Image &img = *loadedImages[i];
        loadedTextures.push_back(LoadTextureFromImage(img));
    }
}

void TextureClass::rescale(int width, int height)
{
    Image &resize = *loadedImages[loadedImages.size() - 1];
    ImageResize(&resize, width, height);
}

void TextureClass::rescaleAll(int width, int height)
{
    for (int i = 0; i < loadedImages.size(); i++)
    {
        Image &resize = *loadedImages[i];
        ImageResize(&resize, width, height); 
    }
}

const Texture2D& TextureClass::getTexture(int index)
{
    if (index >= loadedTextures.size())
        throw std::runtime_error("Index is out of Bounds");
    return loadedTextures[index];
}
