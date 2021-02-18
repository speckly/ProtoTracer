#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

typedef struct AxisAngle {
public:
	double Rotation;
	Vector3D Axis;

	AxisAngle(double rotation, double x, double y, double z);
	AxisAngle(double rotation, Vector3D axis);

	string ToString();
} AxisAngle;
