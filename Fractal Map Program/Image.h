#pragma once

#include <string>
#include <SDL.h>

class Image
{
private:
	SDL_Surface* m_pSDLSurface{nullptr};

public:
	Image();
	Image(std::string filename, SDL_Surface* windowSurface);
	~Image();

	SDL_Surface* getSurface();

	void swapImage(std::string filename);
};

