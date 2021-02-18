#pragma once

#include "Rotation.h"
#include "Pixel.h"
#include "PixelReader.h"
#include "Scene.h"
#include "Triangle2D.h"
#include <iostream>

class Camera {
private:
	Quaternion q;
	Vector3D p;
  unsigned int pixelCount;
  Pixel* pixelStorage;
  PixelReader pixelReader;
  bool antiAliasing = false;
  unsigned int antiAliasingSubdivisions = 2;
  double pixelPixelDistance = 1.0;

  Vector3D CheckRasterPixel(Scene* scene, Triangle2D* triangles, int numTriangles, Vector2D pixelRay){
      Vector3D color;
      double zBuffer = 3.402823466e+38;

      for (int t = 0; t < numTriangles; t++) {
        Vector3D barycentric;
		//Vector2D tCenter = triangles[t].GetCenter();

        //printf("PixelRay: %f, %f; ", pixelRay.X, pixelRay.Y);
        //printf("TriangleCen: %f, %f\n", tCenter.X, tCenter.Y);




        if (triangles[t].DidIntersect(pixelRay, &barycentric)) {
          Vector3D tempInt = *triangles[t].t3p1 + (*triangles[t].t3e2 * barycentric.X) + (*triangles[t].t3e1 * barycentric.Y);
          double rayDistanceToTriangle = Vector3D(pixelRay.X + p.X, pixelRay.Y + p.Y, p.Z).CalculateEuclideanDistance(tempInt);



          if(rayDistanceToTriangle < zBuffer){//closest triangle to ray so far
            zBuffer = rayDistanceToTriangle;
            color = Vector3D();

            for (int l = 0; l < scene->numLights; l++) {
              Vector3D lVector = scene->lights[l].p - tempInt;

              double angle = triangles[t].normal.DotProduct(lVector.UnitSphere());

              if (angle > 0) {
                double lDistance = scene->lights[l].p.CalculateEuclideanDistance(tempInt) / scene->lights[l].falloff;
                double intensity = 1.0 / (1.0 + lDistance * scene->lights[l].a + powf(lDistance / scene->lights[l].falloff, 2.0) * scene->lights[l].b);

                color = color + (scene->lights[l].intensity * angle * intensity);//add intensity drop with distance?
              }
            }
          }
        }
				else{

				}
      }

      return color;
  }

  Vector3D CheckRasterPixelAntiAlias(int subdivisions, double pixelDistance, Scene* scene, Triangle2D* triangles, int numTriangles, Vector2D pixelRay){
      Vector3D color;
      double pixelHDistance = pixelDistance / 2.0;
      double scanDistance = pixelDistance / (double)subdivisions;
      Vector2D startPoint = Vector2D(-pixelHDistance + (scanDistance / 2.0), pixelHDistance - (scanDistance / 2.0));

      for (int i = 0; i < subdivisions; i++){
        for (int j = 0; j < subdivisions; j++){
          color = color + CheckRasterPixel(scene, triangles, numTriangles, pixelRay + startPoint + Vector2D(scanDistance * subdivisions, scanDistance * subdivisions));
        }
      }

      return color / subdivisions;
  }

public:
  Camera(Vector3D q, Vector3D p, unsigned int pixelCount, const string* pixelData, bool flipX, bool flipY) {
    pixelStorage = new Pixel[pixelCount];
    pixelReader.GetPixels(pixelStorage, pixelCount, pixelData, flipX, flipY);

    pixelPixelDistance = fabs(pixelStorage[0].X - pixelStorage[1].X);

    this->pixelCount = pixelCount;

    this->q = Rotation(EulerAngles(q, EulerConstants::EulerOrderXYZR)).GetQuaternion();
    this->p = p;

    this->p.X = -p.X;
    this->p.Y = -p.Y;
  }

	Camera(Quaternion q, Vector3D p, unsigned int pixelCount, const string* pixelData, bool flipX, bool flipY) {
    pixelStorage = new Pixel[pixelCount];
    pixelReader.GetPixels(pixelStorage, pixelCount, pixelData, flipX, flipY);

    pixelPixelDistance = fabs(pixelStorage[0].X - pixelStorage[1].X);

    this->pixelCount = pixelCount;

		this->q = q;
		this->p = p;

		this->p.X = -p.X;
		this->p.Y = -p.Y;
	}

  Camera(Quaternion q, Vector3D p, unsigned int horizontal, unsigned int vertical) {
    pixelStorage = new Pixel[horizontal * vertical];
    pixelReader.GetPixels(pixelStorage, false, false);

    pixelPixelDistance = fabs(pixelStorage[0].X - pixelStorage[1].X);

    this->q = q;
    this->p = p;

    this->p.X = -p.X;
    this->p.Y = -p.Y;
  }

  unsigned int GetPixelCount(){
    return pixelCount;
  }

  Pixel* GetPixels(){
    return pixelStorage;
  }

	void Translate(Quaternion q, Vector3D p) {
		this->q = (this->q + q).UnitQuaternion();
		this->p = this->p + p.Multiply(-1.0);
	}

	void MoveTo(Quaternion q, Vector3D p) {
		this->q = q;
		this->p = p;

		this->p.X = -p.X;
		this->p.Y = -p.Y;
	}

	void MoveTo(Vector3D qv, Vector3D p) {
		qv.Z = -qv.Z;
		this->q = Rotation(EulerAngles(qv, EulerConstants::EulerOrderXYZS)).GetQuaternion();
		this->p = p;

		this->p.X = -p.X;
		this->p.Y = -p.Y;
	}

  void EnableAntiAliasing(){
    antiAliasing = true;
  }

  void DisableAntiAliasing(){
    antiAliasing = false;
  }

  void SetAntiAliasingLevel(unsigned int level){
    antiAliasingSubdivisions = level;
  }

	void Rasterize(Scene* scene, double scale, double maxBrightness) {
    int numTriangles = 0;

    //printf("Num objects: %i\n", scene->numObjects);

    //for each object in the scene, get the triangles
    for(int i = 0; i < scene->numObjects; i++){
      if(scene->objects[i]->IsEnabled()){
        for (int j = 0; j < scene->objects[i]->GetTriangleAmount(); j++) {
          numTriangles++;
        }
      }
    }

		Triangle2D* triangles = new Triangle2D[numTriangles];
    int triangleCounter = 0;

    //for each object in the scene, get the triangles
    for(int i = 0; i < scene->numObjects; i++){
      if(scene->objects[i]->IsEnabled()){
        //for each triangle in object, project onto 2d surface
        for (int j = 0; j < scene->objects[i]->GetTriangleAmount(); j++) {
          scene->objects[i]->GetTriangles()[i].Normal();
          triangles[triangleCounter] = Triangle2D(q, p, scene->objects[i]->GetTriangles()[j]);
          triangleCounter++;
        }
      }
	  }

		//printf("Rasterized triangles: %i\n", triangleCounter);

		for (unsigned int i = 0; i < pixelCount; i++) {
      Vector2D pixelRay = Vector2D(pixelStorage[i].X * scale, pixelStorage[i].Y * scale);
      Vector3D color;

      if (antiAliasing){
        color = CheckRasterPixelAntiAlias(2, pixelPixelDistance * scale, scene, triangles, numTriangles, pixelRay);
      }
      else{
        color = color + CheckRasterPixel(scene, triangles, numTriangles, pixelRay);
      }

      pixelStorage[i].RGB = color.Divide(255.0 / maxBrightness).Constrain(0.0, maxBrightness);
		}

		delete[] triangles;
	}

};
