#include "Window.h"

Window::Window(int width, int height) {
	SDL_Init(SDL_INIT_VIDEO);

	m_pSDLWindow = SDL_CreateWindow("Fractal Program",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_RESIZABLE);

	m_pSDLWindowSurface = SDL_GetWindowSurface(m_pSDLWindow);

	update();
}

void Window::update() {
	SDL_FillRect(
		m_pSDLWindowSurface,
		nullptr,
		SDL_MapRGB(m_pSDLWindowSurface->format, red, green, blue)
	);
}

Window::~Window() {
	SDL_DestroyWindow(m_pSDLWindow);
}

void Window::renderFrame() {
	SDL_UpdateWindowSurface(m_pSDLWindow);
}

void Window::moveRelative(int x, int y) {
	int currentX = 0;
	int currentY = 0;
	SDL_GetWindowPosition(
		m_pSDLWindow, &currentX, &currentX
	);

	SDL_SetWindowPosition(
		m_pSDLWindow, currentX + x, currentY + y
	);
}

void Window::updateSurface(SDL_Surface surface) {
	SDL_FreeSurface(m_pSDLWindowSurface);
	m_pSDLWindowSurface = &surface;
}

[[nodiscard]]
int Window::getWindowWidth() const {
	return m_windowWidth;
}

[[nodiscard]]
int Window::getWindowHeight() const {
	return m_windowHeight;
}

[[nodiscard]]
SDL_Surface* Window::getSurface() {
	return m_pSDLWindowSurface;
}

[[nodiscard]]
SDL_Window* Window::getWindow() {
	return m_pSDLWindow;
}