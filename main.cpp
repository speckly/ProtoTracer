#include "Camera.h"
#include "Rotation.h"
//MATRIX SPECIFIC FOR CUSTOM PANELS
#include "TemporaryObjCamera.h"
//END MATRIX SPECIFIC FOR CUSTOM PANELS

//PI SPECIFIC FOR WRITING TO LEDS
#include <sense/fb.hpp>
//END PI SPECIFIC FOR WRITING TO LEDS

Light lights[6];
Object3D *objects[1];
Object3D triangleObj = Object3D(dvd, 100, 100);
Scene *scene;
Camera camFrontTop = Camera(Vector3D(0, 0, 0), Vector3D(0, 0, -500), 64, &pixelString, false, false);


int main(){
    printf("Starting...\n");
	//printf("%s\n%s\n", pixelString.c_str(), triangle.c_str());
	sense::bitmap mem(true);
    sense::bitmap fb;
	
    lights[0].Set(Vector3D(1000, 0, 0), Vector3D(255, 0, 0), 1000.0f, 0.5f, 0.5f);
	lights[1].Set(Vector3D(0, 1000, 0), Vector3D(0, 255, 0), 1000.0f, 0.5f, 0.5f);
	lights[2].Set(Vector3D(0, 0, 1000), Vector3D(0, 0, 255), 1000.0f, 0.5f, 0.5f);
	lights[3].Set(Vector3D(-1000, 0, 0), Vector3D(120, 0, 120), 1000.0f, 0.5f, 0.5f);
	lights[4].Set(Vector3D(0, -1000, 0), Vector3D(120, 120, 0), 1000.0f, 0.5f, 0.5f);
	lights[5].Set(Vector3D(0, 0, -1000), Vector3D(0, 120, 120), 1000.0f, 0.5f, 0.5f);

    printf("Linking objects...\n");
    objects[0] = &triangleObj;

    scene = new Scene(objects, lights, 1, 6);
    printf("Objects linked, scene created...\n");
	clock_t start = clock();
	while(true){
		for (int i = 0; i < 720; i++) {
			
			printf("Rendering frame %i\n", i);

			objects[0]->Enable();

			//Resets the object back to the original state before any translates/modifications, must be ran once per loop in most cases
			objects[0]->ResetVertices();

			//Objects can be scaled by origin, center, and at a point
			objects[0]->ScaleCenter(Vector3D((sin(i * 3.14159f / 180.0f * 3.0f) + 1) / 2.0f, (sin(i * 3.14159f / 180.0f * 3.0f) + 1) / 2.0f, 1.0f));
			
			objects[0]->Move(Vector3D(-33, -33, 0));
			
			//Objects can be moved to a coordinate or translated by a vector
			objects[0]->Move(Vector3D(sin(i * 3.14159f / 180.0f * 3.0f) * 10.0f,cos(i * 3.14159f / 180.0f * 3.0f) * 10.0f, 0.0f));
			
			//Objects can be rotated with by any rotation object (quaternion is preferred) and about any coordinate or center
			objects[0]->Rotate(Vector3D(7 + sinf(i * 3.14159f / 180.0f * 4.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f, sinf(i * 3.14159f / 180.0f * 2.0f) * 1.0f), Vector3D(0, 100, 0));

			lights[0].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, -cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));//Lights can be moved to any vector coordinate
			lights[1].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
			lights[2].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));
			lights[3].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));
			lights[4].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
			lights[5].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));
			

			//Vector3D objCenter = objects[0]->GetVertexCenter();
			//printf("Object Center: %f, %f, %f", objCenter.X, objCenter.Y);
			
			camFrontTop.Rasterize(scene, 1.0f, 255);

			//SENSE HAT SPECIFIC FOR WRITING TO LEDS/COPYING TO MEMORY
			for (int ii = 0; ii < 8; ii++) {
				for (int jj = 0; jj < 8; jj++) {
					int currentLED = (ii * 8) + jj;
					
					uint8_t red = (uint8_t)(camFrontTop.GetPixels()[currentLED].RGB.X);
					uint8_t green = (uint8_t)(camFrontTop.GetPixels()[currentLED].RGB.Y);
					uint8_t blue = (uint8_t)(camFrontTop.GetPixels()[currentLED].RGB.Z);
					
					//printf("Frame %i, Pixel %i: %s\n", i, currentLED, camFrontTop.GetPixels()[currentLED].RGB.ToString().c_str());
					
					mem.setPixel(jj,ii,sense::color(red,green,blue));
				}
			
			}
			fb = mem;
			usleep(8333);//The pi is much faster than a teensy, so we must sleep in order to keep the framerate reasonable.
			//END SENSE HAT SPECIFIC CODE
		}
	}
	return 0;
}
