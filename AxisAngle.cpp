#include "AxisAngle.h"

AxisAngle::AxisAngle(float rotation, float x, float y, float z) {
	Rotation = rotation;
	Axis = Vector3D(x, y, z);
}

AxisAngle::AxisAngle(float rotation, Vector3D axis) {
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
