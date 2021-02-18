#include "Mathematics.h"

double Mathematics::MPI = atan(1) * 4;

double Mathematics::Constrain(double value, double minimum, double maximum) {
	if (value > maximum)
	{
		value = maximum;
	}
	else if (value < minimum)
	{
		value = minimum;
	}

	return value;
}

double Mathematics::DegreesToRadians(double degrees) {
	return degrees / (180.0 / MPI);
}

double Mathematics::RadiansToDegrees(double radians) {
	return radians * (180.0 / MPI);
}

string Mathematics::DoubleToCleanString(double value) {
	return  to_string(value);
}

bool Mathematics::IsNaN(double value) {
	return value != value;
}

bool Mathematics::IsInfinite(double value) {
	return value == 3.402823466e+38;
}

bool Mathematics::IsFinite(double value) {
	return value != 3.402823466e+38;
}

int Mathematics::Sign(double value) {
		return (0 < value) - (value < 0);
}

double Mathematics::CosineInterpolation(double beg, double fin, double ratio){
   double mu2 = (1.0 - cosf(ratio * MPI)) / 2.0;
   
   return(beg * (1.0 - mu2) + fin * mu2);
}

int Mathematics::RoundUpWindow(int value, int multiple){
    if (multiple == 0)
        return value;

    int remainder = abs(value) % multiple;
    if (remainder == 0)
        return value;

    if (value < 0)
        return -(abs(value) - remainder);
    else
        return value + multiple - remainder;
}