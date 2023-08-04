#pragma once

namespace fractalprogram {

class Mandelbrot
{
private:

public:
	static const int MAX_ITERATIONS = 1000;

public:
	static int getInterations(double x, double y);
	static int* getPallet(int totalColours);
};

}



