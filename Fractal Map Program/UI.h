#pragma once

#include <SDL.h>
#include <string>
#include <memory>

#include "FractalCreator.h"
#include "Image.h"
#include "Window.h"
using namespace fractalprogram;

class UI
{
private:
	FractalCreator* m_fractalCreator{ nullptr };
	Window* mp_window{nullptr};
	Image mp_displayImage;
	Image mp_menuImage;
	string m_imageName1{ "" };
	string m_imageName2{ "" };
	int m_currentImage{ 0 }; // must be 0 or 1
public:
	UI(FractalCreator &fractal, Window &window, string imageName1, string ImageName2);
	~UI();
	bool handleMouse(const SDL_Event *event);
	bool handleKeyboard(const SDL_Event* event);
	bool handleEvent(const SDL_Event* event);
};

