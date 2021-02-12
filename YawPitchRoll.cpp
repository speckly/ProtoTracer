#include "YawPitchRoll.h"

YawPitchRoll::YawPitchRoll() {
	this->Yaw = 0.0;
	this->Pitch = 0.0;
	this->Roll = 0.0;
}

YawPitchRoll::YawPitchRoll(Vector3D vector) {
	this->Yaw = vector.X;
	this->Pitch = vector.Y;
	this->Roll = vector.Z;
}

YawPitchRoll::YawPitchRoll(const YawPitchRoll& ypr) {
	this->Yaw = ypr.Yaw;
	this->Pitch = ypr.Pitch;
	this->Roll = ypr.Roll;
}

YawPitchRoll::YawPitchRoll(float yaw, float pitch, float roll) {
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->Roll = roll;
}

string YawPitchRoll::ToString() {
	string y = Mathematics::DoubleToCleanString(this->Yaw);
	string p = Mathematics::DoubleToCleanString(this->Pitch);
	string r = Mathematics::DoubleToCleanString(this->Roll);

	return "[" + y + ", " + p + ", " + r + "]";
}
