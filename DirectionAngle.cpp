#include "DirectionAngle.h"

DirectionAngle::DirectionAngle(float rotation, float x, float y, float z) {
	Rotation = rotation;
	Direction = Vector3D(x, y, z);
}

DirectionAngle::DirectionAngle(float rotation, Vector3D direction) {
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
