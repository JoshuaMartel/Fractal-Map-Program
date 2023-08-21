#pragma once
struct Pixel
{
	int x{ 0 };
	int y{ 0 };
	double hue{ 0.0 };

	Pixel() {}
	Pixel(int x, int y, double hue) : x(x), y(y), hue(hue) {};
};

