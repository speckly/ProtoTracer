#pragma once
#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

typedef struct Vector2D {
public:
	double X = 0.0;
	double Y = 0.0;

	Vector2D();
	Vector2D(const Vector2D& vector);
	Vector2D(double x, double y);
	Vector2D(Vector3D xy);
	Vector2D(const Vector3D& vector);
	Vector2D Absolute();
	Vector2D Normal();
	Vector2D Add(Vector2D vector);
	Vector2D Subtract(Vector2D vector);
	Vector2D Multiply(Vector2D vector);
	Vector2D Divide(Vector2D vector);
	Vector2D Multiply(double scalar);
	Vector2D Divide(double scalar);
	Vector3D CrossProduct(Vector2D vector);
	Vector2D UnitCircle();//unit sphere
	Vector2D Constrain(double minimum, double maximum);
	Vector2D Constrain(Vector2D minimum, Vector2D maximum);
	Vector2D Minimum(Vector2D v1, Vector2D v2);
	Vector2D Maximum(Vector2D v1, Vector2D v2);

	double Magnitude();
	double DotProduct(Vector2D vector);
	double CalculateEuclideanDistance(Vector2D vector);
	bool IsEqual(Vector2D vector);
	string ToString();
  
  static Vector2D LERP(Vector2D start, Vector2D finish, double ratio) {
    return finish * ratio + start * (1.0 - ratio);
  }
  
	static Vector2D DegreesToRadians(Vector2D degrees) {
		return degrees / (180.0 / Mathematics::MPI);
	}

	static Vector2D RadiansToDegrees(Vector2D radians) {
		return radians * (180.0 / Mathematics::MPI);
	}

	//Static function declaractions
	static Vector2D Normal(Vector2D vector) {
		return vector.Normal();
	}

	static Vector2D Add(Vector2D v1, Vector2D v2) {
		return v1.Add(v2);
	}

	static Vector2D Subtract(Vector2D v1, Vector2D v2) {
		return v1.Subtract(v2);
	}

	static Vector2D Multiply(Vector2D v1, Vector2D v2) {
		return v1.Multiply(v2);
	}

	static Vector2D Divide(Vector2D v1, Vector2D v2) {
		return v1.Divide(v2);
	}

	static Vector2D Multiply(Vector2D vector, double scalar) {
		return vector.Multiply(scalar);
	}

	static Vector2D Multiply(double scalar, Vector2D vector) {
		return vector.Multiply(scalar);
	}

	static Vector2D Divide(Vector2D vector, double scalar) {
		return vector.Divide(scalar);
	}

	static Vector3D CrossProduct(Vector2D v1, Vector2D v2) {
		return v1.CrossProduct(v2);
	}

	static double DotProduct(Vector2D v1, Vector2D v2) {
		return v1.DotProduct(v2);
	}

	static double CalculateEuclideanDistance(Vector2D v1, Vector2D v2) {
		return v1.CalculateEuclideanDistance(v2);
	}

	static bool IsEqual(Vector2D v1, Vector2D v2) {
		return v1.IsEqual(v2);
	}

	//Operator overloads
	bool operator ==(Vector2D vector) {
		return this->IsEqual(vector);
	}

	bool operator !=(Vector2D vector) {
		return !(this->IsEqual(vector));
	}

	Vector2D operator  =(Vector2D vector) {
		this->X = vector.X;
		this->Y = vector.Y;

		return *this;
	}

	Vector2D operator  =(Vector3D vector) {
		this->X = vector.X;
		this->Y = vector.Y;

		return *this;
	}

	Vector2D operator  +(Vector2D vector) {
		Vector2D v = Vector2D(*this);

		return v.Add(vector);
	}

	Vector2D operator  -(Vector2D vector) {
		Vector2D v = Vector2D(*this);

		return v.Subtract(vector);
	}

	Vector2D operator  *(Vector2D vector) {
		Vector2D v = Vector2D(*this);

		return v.Multiply(vector);
	}

	Vector2D operator  /(Vector2D vector) {
		Vector2D v = Vector2D(*this);

		return v.Divide(vector);
	}

	Vector2D operator  *(double value) {
		Vector2D v = Vector2D(*this);

		return v.Multiply(value);
	}

	Vector2D operator  /(double value) {
		Vector2D v = Vector2D(*this);

		return v.Divide(value);
	}
} Vector2D;
