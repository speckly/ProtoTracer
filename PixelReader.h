#pragma once

#include "Vector3D.h"
#include "Pixel.h"

class PixelReader {
private:
	string getValue(string data, char separator, int index) {
		int found = 0;
		int strIndex[] = { 0, -1 };
		int maxIndex = data.length() - 1;

		for (int i = 0; i <= maxIndex && found <= index; i++) {
			if (data.at(i) == separator || i == maxIndex) {
				found++;
				strIndex[0] = strIndex[1] + 1;
				strIndex[1] = (i == maxIndex) ? i + 1 : i;
			}
		}

		return found > index ? data.substr(strIndex[0], strIndex[1]) : "";
	}

	unsigned int countChar(string data, char search) {
		int count = 0;

		for (unsigned int i = 0; i < data.length(); i++) {
			if (data.at(i) == search) {
				count++;
			}
		}

		return count;
	}

public:
	PixelReader() {}

	void GetPixels(Pixel* pixels, unsigned int count, const string* value, bool flipX, bool flipY) {
		string line;

		for (unsigned int i = 0; i < countChar(*value, '\n') + 1; i++) {
			line = getValue(*value, '\n', i);
     
      if(i > count) break;//maxed out pixels available to memory, cancel reading

			if (countChar(line, ',') > 2) {
				double x, y;

				x = stof(getValue(line, ',', 1));
				y = stof(getValue(line, ',', 2));

        if (flipX){
          x = -x;
        }
        if (flipY){
          y = -y;
        }

				pixels[i] = Pixel(x, y);

			}
		}
	}

	void GetPixels(Pixel* pixels, int width, int height){
    int currentPixel = 0;
		for (int i = 0; i < width; i++) {
			for (int k = 0; k < height; k++) {
				pixels[currentPixel] = Pixel(i, k);
        currentPixel++;
			}
		}
	}
};
