#include "EulerAngles.h"

EulerAngles::EulerAngles() {
	Angles = Vector3D(0, 0, 0);
	Order = EulerConstants::EulerOrderXYZS;
}

EulerAngles::EulerAngles(Vector3D angles, EulerOrder order) {
	Angles = angles;
	Order = order;
}

string EulerAngles::ToString() {
	string angles = Angles.ToString();
	string order = Order.ToString();

	return "[ " + angles + ", " + order + " ]";
}
