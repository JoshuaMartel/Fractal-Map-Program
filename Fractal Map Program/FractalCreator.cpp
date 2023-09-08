
#include <iostream>
#include <math.h>
#include <cassert>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

#include "FractalCreator.h"
#include "Pixel.h"
#include "Timer.h"

using std::cout;

namespace fractalprogram {
	FractalCreator::FractalCreator(int width, int height) :
		m_width(width), m_height(height),
		m_histogram{ new int[MAX_ITERATIONS]{0} },
		m_fractal(new int[m_width * m_height]{ 0 }),
		m_bitmap(m_width, m_height),
		m_zoomList(m_width, m_height),
		m_total{ 0 }
	{
		m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
	}

	FractalCreator::FractalCreator(const FractalCreator& fractal): 
		m_width(fractal.m_width), m_height(fractal.m_height),
		m_histogram{ new int[MAX_ITERATIONS]{0} },
		m_fractal(new int[fractal.m_width * fractal.m_height]{ 0 }), 
		m_bitmap(fractal.m_width, fractal.m_height),
		m_zoomList(fractal.m_width, fractal.m_height),
		m_total{ 0 }
	{
		m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
	}

	FractalCreator::~FractalCreator() {
		
	}

	void FractalCreator::addRange(double rangeEnd, const RGB& rgb) {
		m_ranges.push_back(rangeEnd * MAX_ITERATIONS);
		m_colours.push_back(rgb);

		if (m_bGotFirstRange) {
			m_rangeTotals.push_back(0);
		}

		m_bGotFirstRange = true;
	}

	void FractalCreator::addZoom(const Zoom& zoom) {
		m_zoomList.add(zoom);
	}

	void FractalCreator::run(string name) {
		unsigned long const hardware_threads = std::thread::hardware_concurrency();
		cout << "hardware threads available: " << hardware_threads << endl;
		cout << "Running FractalCreator..." << endl;
		timer::function_timer([this]() {calaculateIterations();},"Timing calaculateIterations...");
		timer::function_timer([this]() {calculateTotalIterations();}, "Timing calculateTotalIterations...");
		timer::function_timer([this]() {drawFractal(); }, "Timing drawFractal...");
		timer::function_timer([this, name]() {writeBitmap(name); }, "Timing writeBitmap...");
		
		//caluclateRangeTotals();

		cout << "FractalCreator finished." << endl;
	}

	void FractalCreator::run() {
		run(m_bitmapName);
	}

	void FractalCreator::calaculateIterations() {

		for (int y = 0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {

				pair<double, double> coords = m_zoomList.doZoom(x, y);

				int iterations = Mandelbrot::getInterations(coords.first, coords.second);

				m_fractal[y * m_width + x] = iterations;

				if (iterations != MAX_ITERATIONS) {
					m_histogram[iterations]++;
				}
			}
		}
	}

	void FractalCreator::caluclateRangeTotals() {
		int rangeIndex = 0;

		for (int i = 0; i < MAX_ITERATIONS; i++) {
			// m_histogram[i] is the number of pixels that required i iterations
			int pixels = m_histogram[i];

			if (i >= m_ranges[rangeIndex + 1]) {
				rangeIndex++;
			}

			m_rangeTotals[rangeIndex] += pixels;
		}

		/*for (int value : m_rangeTotals) {
			cout << "Range total: " << value << endl;
		}
		cout << "Range size: " << m_rangeTotals.size() << endl;*/
	}

	int FractalCreator::findGreatest() {
		// m_histogram should always be of size MAX_ITERATIONS and is initialised to all 0s so 'max' will always return at least 0
		int max = 0;
		for (int i = 0; i < MAX_ITERATIONS; i++) {
			if (max < m_histogram[i]) {
				max = m_histogram[i];
			}
		}
		assert(max != 0);
		return max;
	}

	/*
	Calculates total iterations, excluding entries with value MAX_ITERATIONS
	*/
	void FractalCreator::calculateTotalIterations() {
		for (int i = 0; i < MAX_ITERATIONS; i++) {
			m_total += m_histogram[i];
			//cout << m_histogram[i] << " ";
		}

		//cout << endl;

		//cout << "total: " << m_total << endl;
	}

	void FractalCreator::drawFractal() {

		//RGB startColour(5,  20, 55);
		//RGB endColour(150, 200, 75);
		//RGB colourDiff = endColour - startColour;

		ofstream myfile;
		myfile.open("bitmap_results.txt");

		const int AREA = m_width * m_height;
		
		const int MAX_INTENSITY = 100; // in this case out of 100
		
		const int INTENSITY_THRESHOLD = MAX_INTENSITY - 25;
		vector<Pixel> pixels(AREA, Pixel());
		int maxHueIntensity = 0;

		for (int y = 0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {
				int index = y * m_width + x;
				int iterations = m_fractal[y * m_width + x];

				pixels[index].y = y;
				pixels[index].x = x;
				/*int range = getRange(iterations);
				int rangeTotal = m_rangeTotals[range];
				int rangeStart = m_ranges[range];

				RGB& startColour = m_colours[range];
				RGB& endColour = m_colours[range+1];
				RGB colourDiff = endColour - startColour;*/

				/*uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;*/

				if (iterations != MAX_ITERATIONS) {

					for (int i = 0; i < iterations; i++) {
						pixels[y * m_width + x].hue += (double)m_histogram[i] / m_total;
						if ((int)(pixels[y * m_width + x].hue * 100) > maxHueIntensity) {
							maxHueIntensity = (int)(pixels[y * m_width + x].hue * 100);
						}
					}
					
					/*red = startColour.r + colourDiff.r * 
						(double)pixels / rangeTotal;
					green = startColour.g + colourDiff.g * 
						(double)pixels / rangeTotal;
					blue = startColour.b + colourDiff.b * 
						(double)pixels / rangeTotal;*/
				}
			}
		}

		// Increase the brightness of each pixel if the max pixel hue is less than threshold
		if (maxHueIntensity < INTENSITY_THRESHOLD) {
			double diff = (double)(MAX_INTENSITY - maxHueIntensity) / MAX_INTENSITY;
			//cout << "diff = " << diff << endl;
			std::transform(pixels.begin(), pixels.end(), pixels.begin(),
				[diff](Pixel p) {return Pixel(p.x, p.y, p.hue + diff); });
		}

		for (vector<Pixel>::iterator iter = pixels.begin(); iter < pixels.end(); iter++) {

			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;

			if (m_fractal[iter->y * m_width + iter->x] != MAX_ITERATIONS) {
				red = 0;
				green = pow(255, iter->hue);
				blue = 0;
			}
			myfile << "x, y: " << iter->x << " " << iter->y << " hue: " << iter->hue << endl;
			m_bitmap.setPixel(iter->x, iter->y, red, green, blue);
		}
		myfile.close();
		//cout << endl;
		//cout << "max hue: " << maxHueIntensity << endl;
	}

	int FractalCreator::getRange(int iterations) const {
		int range = 0;

		for (int i = 1; i < m_ranges.size(); i++) {
			range = i;

			if (m_ranges[i] > iterations) {
				break;
			}
		}

		range--;
		assert(range > -1);
		assert(range < m_ranges.size());

		return range;
	}
	

	void FractalCreator::writeBitmap(string name) {
		m_bitmap.write(name);
	}

	string FractalCreator::getBitmapName() {
		return m_bitmapName;
	}
}