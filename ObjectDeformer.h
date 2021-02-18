#pragma once

#include "Object3D.h"

class ObjectDeformer{
  public:
    enum Axis {
        XAxis,
        YAxis,
        ZAxis
    };
    
  private:
    Object3D** objects;
    int objectCount = 0;

    bool CheckClipAxis(Vector3D base, bool positive, Axis valueCheckAxis){
      if (valueCheckAxis == XAxis && positive && base.X > 0){
        return true;
      }
      else if (valueCheckAxis == XAxis && !positive && base.X < 0){
        return true;
      }
      else if (valueCheckAxis == YAxis && positive && base.Y > 0){
        return true;
      }
      else if (valueCheckAxis == YAxis && !positive && base.Y < 0){
        return true;
      }
      else if (valueCheckAxis == ZAxis && positive && base.Z > 0){
        return true;
      }
      else if (valueCheckAxis == ZAxis && !positive && base.Z < 0){
        return true;
      }
      else{
        return false;
      }
    }
    
  public:
    ObjectDeformer(Object3D* object){
      objects = new Object3D*[1];
      
      objects[0] = object;
      
      objectCount = 1;
    }

    ObjectDeformer(Object3D** objects, int objectCount){
      this->objects = objects;
      this->objectCount = objectCount;
    }

    void SinusoidalDeform(double magnitude, double timeRatio, double periodModifier, double frequencyModifier, Axis axis){
      for(int i = 0; i < objectCount; i++){
        for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
          Vector3D base = objects[i]->GetVertices()[j];
          
          switch(axis){
            case XAxis:
              objects[i]->GetVertices()[j].X = (sin((base.Y) + timeRatio * frequencyModifier) * periodModifier + cos((base.Z) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            case YAxis:
              objects[i]->GetVertices()[j].Y = (sin((base.X) + timeRatio * frequencyModifier) * periodModifier + cos((base.Z) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            case ZAxis:
              objects[i]->GetVertices()[j].Z = (sin((base.X) + timeRatio * frequencyModifier) * periodModifier + cos((base.Y) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            default:
              break;
          }
        }
      }
    }
    
    void DropwaveDeform(double magnitude, double timeRatio, double periodModifier, double frequencyModifier, Axis axis){
      for(int i = 0; i < objectCount; i++){
        for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
          Vector3D base = objects[i]->GetVertices()[j];
          
          switch(axis){
            case XAxis:
              objects[i]->GetVertices()[j].X = -(1.0 + cos(12.0*sqrt(base.Y * base.Y + base.Z + base.Z) + timeRatio * frequencyModifier) * periodModifier) / (0.5 * (base.Y * base.Y + base.Z + base.Z) + 2.0) * magnitude;
              break;
            case YAxis:
              objects[i]->GetVertices()[j].Y = -(1.0 + cos(12.0*sqrt(base.X * base.X + base.Z + base.Z) + timeRatio * frequencyModifier) * periodModifier) / (0.5 * (base.X * base.X + base.Z + base.Z) + 2.0) * magnitude;
              break;
            case ZAxis:
              objects[i]->GetVertices()[j].Z = -(1.0 + cos(12.0*sqrt(base.X * base.X + base.Y * base.Y) + timeRatio * frequencyModifier) * periodModifier) / (0.5 * (base.X * base.X + base.Y * base.Y) + 2.0) * magnitude;
              break;
            default:
              break;
          }
        }
      }
    }

    void SineWaveSurfaceDeform(Vector3D offset, double magnitude, double timeRatio, double periodModifier, double frequencyModifier, Axis axis){
      for(int i = 0; i < objectCount; i++){
        for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
          Vector3D base = objects[i]->GetVertices()[j] - offset;
        
          switch(axis){
            case XAxis:
              objects[i]->GetVertices()[j].X = objects[i]->GetVertices()[j].X + sin((sqrt(base.Y * base.Y + base.Z * base.Z) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            case YAxis:
              objects[i]->GetVertices()[j].Y = objects[i]->GetVertices()[j].Y + sin((sqrt(base.X * base.X + base.Z * base.Z) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            case ZAxis:
              objects[i]->GetVertices()[j].Z = objects[i]->GetVertices()[j].Z + sin((sqrt(base.X * base.X + base.Y * base.Y) + timeRatio * frequencyModifier) * periodModifier) * magnitude;
              break;
            default:
              break;
          }
        }
      }
    }

    void CosineInterpolationDeformer(double* pointMultiplier, int points, double scale, double minAxis, double maxAxis, Axis selectionAxis, Axis deformAxis){
      //map axis offsets based on value range for multiplying vertex coordinates at set intervals spaced evenly across minimum and maximum range of selected axis
      for(int i = 0; i < objectCount; i++){
        for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
          double value;
          
          switch(selectionAxis){
            case XAxis:
              value = objects[i]->GetVertices()[j].X;
              break;
            case YAxis:
              value = objects[i]->GetVertices()[j].Y;
              break;
            case ZAxis:
              value = objects[i]->GetVertices()[j].Z;
              break;
            default:
              value = 0.0;
              break;
          }

          double stepWindow = (maxAxis - minAxis) / points;//window size for the step interval

          double roundUpWindow = Mathematics::RoundUpWindow(value, stepWindow);
          double roundDownWindow = roundUpWindow - stepWindow;
          int roundUpIndex = (roundUpWindow - minAxis) / stepWindow;
          
          double intervalMultiplier, windowRatio;
          
          if (roundUpIndex < 1){//below range
            intervalMultiplier = 1.0;// Mathematics::CosineInterpolation(1.0, pointMultiplier[0], windowRatio)
          }
          else if (roundUpIndex > points){//above range
            intervalMultiplier = 1.0;// Mathematics::CosineInterpolation(pointMultiplier[points - 1], 1.0, windowRatio)
          }
          else{
            windowRatio = (value - roundDownWindow) / stepWindow;
            intervalMultiplier = Mathematics::CosineInterpolation(pointMultiplier[roundUpIndex], pointMultiplier[roundUpIndex - 1], 1.0 - windowRatio);
          }
          
          
          //calculate where the axis fits on the range
          
          switch(deformAxis){
            case XAxis:
              objects[i]->GetVertices()[j].X = objects[i]->GetVertices()[j].X + scale * intervalMultiplier;
              break;
            case YAxis:
              objects[i]->GetVertices()[j].Y = objects[i]->GetVertices()[j].Y + scale * intervalMultiplier;
              break;
            case ZAxis:
              objects[i]->GetVertices()[j].Z = objects[i]->GetVertices()[j].Z + scale * intervalMultiplier;
              break;
            default:
              break;
          }
        }
      }
    }

    void AxisZeroClipping(bool positive, Axis clipAxis, Axis valueCheckAxis){
      for(int i = 0; i < objectCount; i++){
        for(int j = 0; j < objects[i]->GetVertexAmount(); j++){
          Vector3D base = objects[i]->GetVertices()[j];
        
          switch(clipAxis){
            case XAxis:
              if(CheckClipAxis(base, positive, valueCheckAxis)) base.X = 0;
              break;
            case YAxis:
              if(CheckClipAxis(base, positive, valueCheckAxis)) base.Y = 0;
              break;
            case ZAxis:
              if(CheckClipAxis(base, positive, valueCheckAxis)) base.Z = 0;
              break;
            default:
              break;

            objects[i]->GetVertices()[j] = base;
          }
        }
      }
    }
};