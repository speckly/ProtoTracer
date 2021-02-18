#pragma once
#include <math.h> 
#include <string>

using namespace std;

class Mathematics {
public:
	static double MPI;

	static double Constrain(double value, double minimum, double maximum);
	static double DegreesToRadians(double degrees);
	static double RadiansToDegrees(double radians);
	static string DoubleToCleanString(double value);
	static bool IsNaN(double);
	static bool IsInfinite(double);
	static bool IsFinite(double);
	static int Sign(double);
	static int RoundUpWindow(int value, int multiple);

	static double CosineInterpolation(double, double, double);
};
