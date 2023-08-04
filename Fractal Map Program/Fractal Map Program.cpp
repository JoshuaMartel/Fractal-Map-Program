// Fractal Map Program.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>

#include "FractalCreator.h"
#include "RGB.h"
#include "Zoom.h"
#include "Window.h"
#include "Image.h"
#include "UI.h"

using namespace std;
using namespace fractalprogram;

int main()
{
   
    int const WIDTH = 800;
    int const HEIGHT = 600;
    const string imageName1 = "Mandelbrot1.bmp";
    const string imageName2 = "Mandelbrot2.bmp";

    Window window{WIDTH,HEIGHT};

    FractalCreator fractalCreator(WIDTH, HEIGHT);

    fractalCreator.addRange(0.0, RGB(0, 0, 0));
    fractalCreator.addRange(0.3, RGB(255,0,0));
    fractalCreator.addRange(0.6, RGB(0, 255, 0));
    fractalCreator.addRange(1.0, RGB(0, 0, 255));


    //fractalCreator.addZoom(Zoom(295, 202, 0.1));
    fractalCreator.run(imageName1);

    UI ui(fractalCreator, window, imageName1, imageName2);
    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Quit();
                return 0;
            }
            if (ui.handleEvent(&event)){
                continue;
            }
        }

        window.renderFrame();
    }

    //fractalCreator.addZoom(Zoom(295, HEIGHT - 202, 0.1));
    
    ui.~UI();
    cout << "Finished" << endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
