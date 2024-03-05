#pragma once

#include "AnimatedMaterial.h"
#include "..\..\Signals\FunctionGenerator.h"
#include "..\..\Materials\SpiralMaterial.h"

class RainbowSpiral : public AnimatedMaterial
{
private:
    FunctionGenerator fGenMatBend = FunctionGenerator(FunctionGenerator::Sine, 0.8f, 0.9f, 6.7f);
    RGBColor rainbowSpectrum[20] = {
        RGBColor(255, 0, 0),     // Red
        RGBColor(255, 63, 0),    // Orange-red
        RGBColor(255, 127, 0),   // Orange
        RGBColor(255, 191, 0),   // Gold
        RGBColor(255, 255, 0),   // Yellow
        RGBColor(191, 255, 0),   // Lime
        RGBColor(127, 255, 0),   // Lime-green
        RGBColor(0, 255, 0),     // Green
        RGBColor(0, 255, 63),    // Green-cyan
        RGBColor(0, 255, 127),   // Cyan
        RGBColor(0, 191, 255),   // Light-blue
        RGBColor(0, 127, 255),   // Blue
        RGBColor(0, 0, 255),     // Blue-magenta
        RGBColor(127, 0, 255),   // Magenta
        RGBColor(191, 0, 255),   // Violet
        RGBColor(255, 0, 255),   // Purple
        RGBColor(255, 0, 191),   // Pink
        RGBColor(255, 0, 127),   // Pink-red
        RGBColor(255, 0, 63),    // Red-pink
        RGBColor(255, 0, 23)    // Red-pink
    };
    SpiralMaterial spiralMaterial = SpiralMaterial(20, rainbowSpectrum, 1.0f, 10.0f);

public:
    RainbowSpiral() {}

    void Update(float ratio)
    {
        spiralMaterial.SetBend(fGenMatBend.Update());
        spiralMaterial.SetRotationAngle((1.0f - ratio) * 360.0f);
        spiralMaterial.SetPositionOffset(Vector2D(0.0f, 75.0f));
    }

    Material *GetMaterial()
    {
        return &spiralMaterial;
    }

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override
    {
        return spiralMaterial.GetRGB(position, normal, uvw);
    }
};
