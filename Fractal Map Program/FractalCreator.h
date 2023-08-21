#pragma once

#include <string>
#include <memory>
#include <cstdint>
#include <vector>
#include "Zoom.h"
#include "ZoomList.h"
#include "Mandelbrot.h"
#include "Bitmap.h"
#include "RGB.h"

using namespace std;

namespace fractalprogram {
	class FractalCreator {
	private:
		static const int MAX_ITERATIONS = Mandelbrot::MAX_ITERATIONS;
		int m_total{ 0 };
		int m_width{ 0 };
		int m_height{ 0 };
		ZoomList m_zoomList;
		unique_ptr<int[]> m_histogram{nullptr};
		unique_ptr<int[]> m_fractal{nullptr};
		Bitmap m_bitmap;
		string m_bitmapName{"Mandelbrot.bmp"};

		vector<int> m_ranges;
		vector<RGB> m_colours;
		vector<int> m_rangeTotals;

		bool m_bGotFirstRange{ false };

		void calculateTotalIterations();
		void calaculateIterations();
		void caluclateRangeTotals();
		void drawFractal();
		void writeBitmap(string name);
		int getRange(int iterations) const;
		int findGreatest();

	public:
		FractalCreator(int width, int height);
		FractalCreator(const FractalCreator& fractal);
		virtual ~FractalCreator();

		void addRange(double rangeEnd, const RGB& rgb);
		void addZoom(const Zoom& zoom);
		void run(string name);
		void run();

		string getBitmapName();

	};
}

