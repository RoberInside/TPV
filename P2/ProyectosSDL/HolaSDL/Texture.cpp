#include "Texture.h"



Texture::Texture():
	texture(nullptr), frameWidth(0), frameHeight(0)
{
}


Texture::~Texture()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

bool Texture::loadTexture(SDL_Renderer * renderer, std::string const & path, uint rows, uint cols)
{
	SDL_Surface* tempSurface = nullptr;

	tempSurface = IMG_Load(path.c_str());
	if (!tempSurface)
	{
		std::cout << "Unable to load image " << path << "!\nSDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	frameHeight = tempSurface->h / rows;
	frameWidth = tempSurface->w / cols;

	return (bool)texture;
}

void Texture::render(SDL_Renderer * renderer, const SDL_Rect & desRect)
{
	SDL_RenderCopy(renderer, texture, nullptr, &desRect);
}

void Texture::renderFrame(SDL_Renderer * renderer, const SDL_Rect & destRect, uint row, uint col)
{
	SDL_Rect srcRect{frameWidth*col, frameHeight*row, frameWidth, frameHeight};
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
