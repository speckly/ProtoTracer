#pragma once

#include "Vector3D.h"

class Light {
public:
	Vector3D p;
	Vector3D intensity;//R, G, B
  double falloff = 1000.0;
  double a = 0.0;
  double b = 1.0;
  
	Light(){}

	Light(Vector3D p, Vector3D intensity, double falloff, double a, double b) : p(p), intensity(intensity), falloff(falloff), a(a), b(b) {}

	void Set(Vector3D p, Vector3D intensity, double falloff, double a, double b) {
		this->p = p;
		this->intensity = intensity;
    this->falloff = falloff;
    this->a = a;
    this->b = b;
	}

  void SetIntensity(Vector3D intensity) {
    this->intensity = intensity;
  }

  void SetFalloff(double falloff, double a, double b) {
    this->falloff = falloff;
    this->a = a;
    this->b = b;
  }

	void MoveTo(Vector3D p) {
		this->p = p;
	}

	void Translate(Vector3D p) {
		this->p = this->p + p;
	}

  void SetFalloff(double falloff){
    this->falloff = fabs(falloff);
  }

  void SetCurve(double a, double b){
    this->a = a;
    this->b = b;
  }
};
