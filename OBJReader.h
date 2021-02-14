#pragma once

#include <vector>
#include "Vector3D.h"
#include "Triangle3D.h"

// v X Y Z
//f l1 l2 l3 l4
class OBJReader {
private:
	static string getValue(string data, char separator, int index) {
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

	static int countChar(string data, char search) {
		int count = 0;

		for (unsigned int i = 0; i < data.length(); i++) {
			if (data.at(i) == search) {
				count++;
			}
		}

		return count;
	}

public:
	static void GetTriangles(Vector3D* vertexArray, Vector3D* triangleVecArray, Triangle3D* triangleArray, int* vertexLength, int* triangleLength, const string* value, bool flipX, bool flipY, const int maxVertices, const int maxTriangles) {
		string line;
    
		//read obj data and parse
		for (int i = 0; i < countChar(*value, '\n') + 1; i++) {
			line = getValue(*value, '\n', i);

			if (countChar(line, ' ') > 2) {
				if (getValue(line, ' ', 0).compare("v")==0) {
					Vector3D vertex;

					vertex.X = stof(getValue(line, ' ', 1));
					vertex.Y = stof(getValue(line, ' ', 2));
					vertex.Z = stof(getValue(line, ' ', 3));

          if (flipX) vertex.X = -vertex.X;
          if (flipY) vertex.Y = -vertex.Y;

					vertexArray[*vertexLength].X = vertex.X;
          vertexArray[*vertexLength].Y = vertex.Y;
          vertexArray[*vertexLength].Z = vertex.Z;
          (*vertexLength)++;
          
          if (*vertexLength > maxVertices) break;
				}
				else if (getValue(line, ' ', 0).compare("f")==0) {
					int x, y, z;

					x = stoi(getValue(line, ' ', 1)) - 1;
					y = stoi(getValue(line, ' ', 2)) - 1;
					z = stoi(getValue(line, ' ', 3)) - 1;
					
          triangleVecArray[*triangleLength].X = x;
          triangleVecArray[*triangleLength].Y = y;
          triangleVecArray[*triangleLength].Z = z;
          (*triangleLength)++;
          
          if (*triangleLength > maxTriangles) break;
				}
			}
		}

    for (int i = 0; i < *triangleLength; i++) {
      triangleArray[i].p1 = &vertexArray[(int)triangleVecArray[i].X];
      triangleArray[i].p2 = &vertexArray[(int)triangleVecArray[i].Y];
      triangleArray[i].p3 = &vertexArray[(int)triangleVecArray[i].Z];
    }
	}
};
