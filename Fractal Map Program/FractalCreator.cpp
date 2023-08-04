
#include <iostream>
#include <math.h>
#include "FractalCreator.h"
#include <cassert>
#include <fstream>

using namespace std;

namespace fractalprogram {
	FractalCreator::FractalCreator(int width, int height) :
		m_width(width), m_height(height),
		m_histogram{ new int[Mandelbrot::MAX_ITERATIONS]{0} },
		m_fractal(new int[m_width * m_height]{ 0 }),
		m_bitmap(m_width, m_height),
		m_zoomList(m_width, m_height),
		m_total{ 0 }
	{
		m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
	}

	FractalCreator::FractalCreator(const FractalCreator& fractal): 
		m_width(fractal.m_width), m_height(fractal.m_height),
		m_histogram{ new int[Mandelbrot::MAX_ITERATIONS]{0} },
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
		m_ranges.push_back(rangeEnd*Mandelbrot::MAX_ITERATIONS);
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
		cout << "Running FractalCreator..." << endl;
		calaculateIterations();
		calculateTotalIterations();
		//caluclateRangeTotals();
		drawFractal();
		writeBitmap(name);
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

				if (iterations != Mandelbrot::MAX_ITERATIONS) {
					m_histogram[iterations]++;
				}
			}
		}

		
	}

	void FractalCreator::caluclateRangeTotals() {
		int rangeIndex = 0;

		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
			//m_histogram[i] is the number of pixels that required i iterations
			int pixels = m_histogram[i];

			if (i >= m_ranges[rangeIndex + 1]) {
				rangeIndex++;
			}

			m_rangeTotals[rangeIndex] += pixels;
		}

		for (int value : m_rangeTotals) {
			cout << "Range total: " << value << endl;
		}
		cout << "Range size: " << m_rangeTotals.size() << endl;
	}

	/*
	Calculates total iterations, excluding entries with value MAX_ITERATIONS
	*/
	void FractalCreator::calculateTotalIterations() {
		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
			m_total += m_histogram[i];
			//cout << m_histogram[i] << " ";
		}

		//cout << endl;

		//cout << "total: " << m_total << endl;
	}

	void FractalCreator::drawFractal() {
		//cout << "draw fractal" << endl;
		//cout << "total: " << m_total << endl;

		//RGB startColour(5,  20, 55);
		//RGB endColour(150, 200, 75);
		//RGB colourDiff = endColour - startColour;

		ofstream myfile;
		myfile.open("bitmap_results.txt");
		
		for (int y = 0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {

				int iterations = m_fractal[y * m_width + x];

				/*int range = getRange(iterations);
				int rangeTotal = m_rangeTotals[range];
				int rangeStart = m_ranges[range];

				RGB& startColour = m_colours[range];
				RGB& endColour = m_colours[range+1];
				RGB colourDiff = endColour - startColour;*/

				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;

				if (iterations != Mandelbrot::MAX_ITERATIONS) {

					int pixels = 0;

					/*for (int i = rangeStart; i <= iterations; i++) {
						pixels += m_histogram[i];
					}*/
					double hue = 0.0;
					for (int i = 0; i < iterations; i++) {
						hue += (double)m_histogram[i] / m_total;
					}
					
					//cout << hue << " ";
					//green = pow(255, hue);

					red = 0;
					green = pow(255, hue);
					blue = 0;

					/*red = startColour.r + colourDiff.r * 
						(double)pixels / rangeTotal;
					green = startColour.g + colourDiff.g * 
						(double)pixels / rangeTotal;
					blue = startColour.b + colourDiff.b * 
						(double)pixels / rangeTotal;*/
				}
				/*if (iterations % 1000 == 0) {
					cout << " Range: " << range
						<< "; iterations: " << iterations
						<< "; red: " << (int)red
						<< ", green: " << (int)green
						<< ", blue: " << (int)blue;
				}*/
				myfile << (int)green << endl;
				m_bitmap.setPixel(x, y, 0, green, 0);
			}
		}
		myfile.close();
		//cout << endl;
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