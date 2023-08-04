#include "Image.h"


Image::Image() {

}

Image::Image(std::string filename, SDL_Surface* windowSurface) {
	m_pSDLSurface = SDL_LoadBMP(filename.c_str());
	SDL_BlitSurface(m_pSDLSurface, nullptr, windowSurface, nullptr);
}

Image::~Image() {
	SDL_FreeSurface(m_pSDLSurface);
}

SDL_Surface* Image::getSurface() {
	return m_pSDLSurface;
}

void Image::swapImage(std::string filename) {
	
	SDL_BlitSurface(m_pSDLSurface, nullptr, SDL_LoadBMP(filename.c_str()), nullptr);
}