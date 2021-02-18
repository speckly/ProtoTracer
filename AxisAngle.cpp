#include "AxisAngle.h"

AxisAngle::AxisAngle(double rotation, double x, double y, double z) {
	Rotation = rotation;
	Axis = Vector3D(x, y, z);
}

AxisAngle::AxisAngle(double rotation, Vector3D axis) {
	Rotation = rotation;
	Axis = axis;
}

string AxisAngle::ToString() {
	string r = Mathematics::DoubleToCleanString(Rotation);
	string x = Mathematics::DoubleToCleanString(Axis.X);
	string y = Mathematics::DoubleToCleanString(Axis.Y);
	string z = Mathematics::DoubleToCleanString(Axis.Z);

	return r + ": [" + x + " " + y + " " + z + "]";
}
