#pragma once

#include <SDL.h>

class Window
{
private:
	SDL_Window* m_pSDLWindow{ nullptr };
	SDL_Surface* m_pSDLWindowSurface{ nullptr };
	int m_windowWidth{ 800 };
	int m_windowHeight{ 600 };

	int red{ 40 };
	int green{ 40 };
	int blue{ 40 };
	
public:
	Window(int width, int height);

	~Window();

	void update();

	void updateSurface(SDL_Surface surface);

	void renderFrame();

	void moveRelative(int x, int y);

	int getWindowWidth() const;

	int getWindowHeight() const;

	SDL_Surface* getSurface();

	SDL_Window* getWindow();
};

