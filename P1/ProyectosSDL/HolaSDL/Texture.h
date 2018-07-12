#pragma once

#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using uint = unsigned int;

class Texture
{
public:
	Texture();
	~Texture();

	bool loadTexture(SDL_Renderer* renderer, std::string const& path, uint rows, uint cols);
	void render(SDL_Renderer* renderer, const SDL_Rect& desRect);
	void renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect, uint row, uint col);

	uint getFrameWidth() { return frameWidth; };
	uint getFrameHeight() { return frameHeight; };
private:
	SDL_Texture *texture;
	uint frameWidth;
	uint frameHeight;
};

