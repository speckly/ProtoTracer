#include "DirectionAngle.h"

DirectionAngle::DirectionAngle(double rotation, double x, double y, double z) {
	Rotation = rotation;
	Direction = Vector3D(x, y, z);
}

DirectionAngle::DirectionAngle(double rotation, Vector3D direction) {
	Rotation = rotation;
	Direction = direction;
}

string DirectionAngle::ToString() {
	string r = Mathematics::DoubleToCleanString(Rotation);
	string x = Mathematics::DoubleToCleanString(Direction.X);
	string y = Mathematics::DoubleToCleanString(Direction.Y);
	string z = Mathematics::DoubleToCleanString(Direction.Z);

	return r + ": [" + x + " " + y + " " + z + "]";
}
