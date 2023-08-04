

#include <complex>
#include "Mandelbrot.h"

using namespace std;

namespace fractalprogram {

	/*int Mandalbrot::getInterations(double x0, double y0) {
		double x = 0.0, y = 0.0;
		int iteration = 0;

		while (x * x + y * y <= 4 && iteration < MAX_ITERATIONS) {
			double xtemp = x * x - y * y + x0;
			y = 2 * x * y + y0;
			x = xtemp;
			iteration++;
		}

		return iteration;
	}*/

	int Mandelbrot::getInterations(double x, double y) {

		complex<double> z = 0;
		complex<double> c(x, y);

		int iterations = 0;

		while (iterations < MAX_ITERATIONS) {
			z = z * z + c;

			if (abs(z) > 2) {
				break;
			}

			iterations++;
		}

		return iterations;
	}

	int* Mandelbrot::getPallet(int totalColours) {
		int pallet[3]{};

		if (totalColours < 256) {
			pallet[0] = totalColours;
		}
		else if (totalColours < 512) {
			pallet[0] = 255;
			pallet[1] = totalColours - 255;
		}
		else {
			pallet[0] = 255;
			pallet[1] = 255;
			pallet[2] = totalColours - 255;
		}

		return pallet;
	}
}
