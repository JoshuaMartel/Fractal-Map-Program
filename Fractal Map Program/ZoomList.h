#pragma once

#include <vector>
#include <utility>
#include "Zoom.h"

using namespace std;

namespace fractalprogram {
	class ZoomList {
	private:
		double m_xCentre{0};
		double m_yCentre{0};
		double m_scale{1.0};

		int m_width{ 0 };
		int m_height{ 0 };
		vector<Zoom> zooms;

	public:
		ZoomList(int width, int height);
		void add(const Zoom& zoom);
		pair<double, double> doZoom(int x, int y);
	};
}

