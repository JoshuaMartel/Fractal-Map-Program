
#include <iostream>
#include <cassert>
#include "UI.h"

// This is pass-by-reference
UI::UI(FractalCreator& fractal, Window& window, string imageName1, string imageName2) {
	m_imageName1 = imageName1;
	m_imageName2 = imageName2;
	m_fractalCreator = &fractal;
	mp_window = &window;
	mp_displayImage = Image(imageName1, SDL_GetWindowSurface(mp_window->getWindow()));

	assert(mp_window->getSurface() != NULL);
	assert(SDL_GetWindowSurface(mp_window->getWindow()) != NULL);
	//mp_menuImage = &newImage;
	//this will need to be change later, but this suffices for now
	
}

UI::~UI() {
	mp_window->~Window();
	mp_displayImage.~Image();
}

bool UI::handleMouse(const SDL_Event* event) {
	//We assume event.type is of SDL_MOUSE

	if (event->type == SDL_MOUSEBUTTONDOWN) {
		if (event->button.button == SDL_BUTTON_LEFT) {
			cout << "Left Mouse Button clicked" << endl;
			int x = event->motion.x, y = event->motion.y;
			
			cout << "Swapping image..." << endl;

			m_fractalCreator->addZoom(Zoom(x, y, 0.1));
			// current image is image1, so rewrite image 2 and diplay it
			if (m_currentImage == 0) {

				m_fractalCreator->run(m_imageName2);
				mp_displayImage = Image{ m_imageName2, SDL_GetWindowSurface(mp_window->getWindow())};
				mp_window->updateSurface(*mp_displayImage.getSurface());
				mp_window->renderFrame();
				m_currentImage = 1;
			}
			// current image is image2, so rewrite image1 and display it
			else {

				m_fractalCreator->run(m_imageName1);
				mp_displayImage = Image{ m_imageName1, SDL_GetWindowSurface(mp_window->getWindow()) };
				mp_window->updateSurface(*mp_displayImage.getSurface());
				mp_window->renderFrame();
				m_currentImage = 0;
			}

			cout << "Swapping complete." << endl;
			
			
			
			
			return true;
		}
	}

	return false;
}

bool UI::handleKeyboard(const SDL_Event* event) {
	return false;
}

bool UI::handleEvent(const SDL_Event* event) {
	if (handleMouse(event)) {
		return true;
	}
	return false;
}
