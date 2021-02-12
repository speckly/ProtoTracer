#include "Camera.h"
#include "Rotation.h"

//MATRIX SPECIFIC FOR CUSTOM PANELS
#include "TemporaryObjCamera.h"
//END MATRIX SPECIFIC FOR CUSTOM PANELS

//PI SPECIFIC FOR WRITING TO LEDS
#include <sense/fb.hpp>


//END TEENSY SPECIFIC FOR WRITING TO LEDS

Light lights[6];
Object3D *objects[1];
Object3D dvdObj = Object3D(dvd, 100, 100);
Scene *scene;
Camera camFrontTop = Camera(Vector3D(-45, 0, 180), Vector3D(90, -220, -500), 64, &pixelString, false, false);

int main(){
    printf("Starting...\n");
	printf("%s, %s\n", pixelString.c_str(), dvd.c_str());
	sense::bitmap mem(true);
    sense::bitmap fb;
	
    lights[0].Set(Vector3D(1000, 0, 0), Vector3D(255, 0, 0), 1000.0f, 0.5f,
                  0.5f);//Set lights position, color intensity, falloff distance, and falloff curvature
    lights[1].Set(Vector3D(0, 100, 0), Vector3D(0, 255, 0), 1000.0f, 0.5f, 0.5f);
    lights[2].Set(Vector3D(0, 0, 100), Vector3D(0, 0, 255), 1000.0f, 0.5f, 0.5f);
    lights[3].Set(Vector3D(-100, 0, 0), Vector3D(120, 0, 120), 1000.0f, 0.5f, 0.5f);
    lights[4].Set(Vector3D(0, -100, 0), Vector3D(120, 120, 0), 1000.0f, 0.5f, 0.5f);
    lights[5].Set(Vector3D(0, 0, -100), Vector3D(0, 120, 120), 1000.0f, 0.5f, 0.5f);

    printf("Linking objects...\n");
    objects[0] = &dvdObj;

    scene = new Scene(objects, lights, 1, 6);
    printf("Objects linked, scene created...\n");
    for (int i = 0; i < 720; i++) {
        printf("Rendering frame %i\n", i);
        //Example of DVD 3D object scaling, moving, and rotating
        //Objects visibility can be enabled and disabled at any point before rasterizing to change its visibility
        objects[0]->Enable();
		
		objects[0]->ResetVertices();

        //Scales to 20mm x 10mm
		objects[0]->Scale(Vector3D(0.2f + sin(i * 3.14159f / 180.0f * 3.0f) * 0.05f, 0.2f + sin(i * 3.14159f / 180.0f * 3.0f) * 0.05f, 1.0f), Vector3D(0, 0, 0));

		//Moves in a figure 8 up around position 4, 4 with a 4mm amplitude
		objects[0]->Move(Vector3D(4 + sin(i * 3.14159f / 180.0f * 3.0f) * 4.0f, 4 + cos(i * 3.14159f / 180.0f * 1.5f) * 4.0f, 0.0f));

        lights[0].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0, -cosf(i * 3.14159f / 180.0f * 2.0f) *1000.0f));//Lights can be moved to any vector coordinate
        lights[1].MoveTo(Vector3D(sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f,0));
        lights[2].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f,cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));
        lights[3].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f, 0,cosf(i * 3.14159f / 180.0f * 2.0f) * 1000.0f));
        lights[4].MoveTo(Vector3D(-sinf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, cosf(i * 3.14159f / 180.0f * 4.0f) * 1000.0f, 0));
        lights[5].MoveTo(Vector3D(0, sinf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f, -cosf(i * 3.14159f / 180.0f * 6.0f) * 1000.0f));


        camFrontTop.Rasterize(scene, 1.0f, 255);
		
        //TEENSY SPECIFIC FOR WRITING TO LEDS/COPYING TO MEMORY
        for (int ii = 0; ii < 8; ii++) {
            for (int jj = 0; jj < 8; jj++) {
				int currentLED = (ii * 8) + jj;
				
				
				uint8_t red = (uint8_t)(camFrontTop.GetPixels()[currentLED].RGB.X);
				uint8_t green = (uint8_t)(camFrontTop.GetPixels()[currentLED].RGB.Y);
				uint8_t blue = (uint8_t)(camFrontTop.GetPixels()[currentLED].RGB.Z);
				
				printf("Frame %i, Pixel %i: %s\n", i, currentLED, camFrontTop.GetPixels()[currentLED].RGB.ToString().c_str());
				
				mem.setPixel(jj,ii,sense::color(red,green,blue));
            }

        }
		fb = mem;

    }
	return 0;
}
