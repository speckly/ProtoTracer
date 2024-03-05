//Inherit from protogen animation, adding additional function for splitting the face render
//Implement ws35/hub75#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Objects\Background.h"
#include "..\Objects\LEDStripBackground.h"
#include "..\Morph\NukudeFlat.h"
#include "..\Render\Scene.h"
#include "..\Signals\FunctionGenerator.h"
#include "..\Menu\SingleButtonMenu.h"
//#include "..\Menu\NeoTrellisMenu.h"
#include "..\Sensors\APDS9960.h"
// #include "..\Sensors\SpeckPotentiometer.h"

#include "..\Materials\Animated\RainbowNoise.h"
#include "..\Materials\Animated\RainbowSpiral.h"
#include "..\Materials\Animated\SpectrumAnalyzer.h"
#include "..\Materials\Animated\AudioReactiveGradient.h"
#include "..\Materials\Animated\Oscilloscope.h"

#include "..\Materials\MaterialAnimator.h"

#include "AnimationTracks\BlinkTrack.h"

#include "..\Signals\FFTVoiceDetection.h"

#include "..\Sensors\MicrophoneFourier_MAX9814.h"

#include "..\Render\ObjectAlign.h"
#include "Flash\ImageSequences\BadAppleTrim.h"

#include "..\Screenspace\GlitchX.h"
#include "..\Screenspace\Fisheye.h"
#include "..\Screenspace\HorizontalBlur.h"
#include "..\Screenspace\PhaseOffsetX.h"
#include "..\Screenspace\PhaseOffsetY.h"
#include "..\Screenspace\PhaseOffsetR.h"
#include "..\Screenspace\Magnet.h"
#include "..\Screenspace\Overflow.h"
#include "..\Screenspace\RadialBlur.h"
#include "..\Screenspace\ShiftR.h"
#include "..\Screenspace\VerticalBlur.h"

class WS35AnimationSplit : public Animation<3> {
private:
    static const uint8_t faceCount = 9;
    NukudeFace pM;
    Background background;
    LEDStripBackground ledStripBackground;
    EasyEaseAnimator<25> eEA = EasyEaseAnimator<25>(EasyEaseInterpolation::Overshoot, 1.0f, 0.35f);
    
    //Materials
    RainbowNoise rainbowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial orangeMaterial = SimpleMaterial(RGBColor(255, 165, 0));
    SimpleMaterial whiteMaterial = SimpleMaterial(RGBColor(255, 255, 255));
    SimpleMaterial greenMaterial = SimpleMaterial(RGBColor(0, 255, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0));
    SimpleMaterial purpleMaterial = SimpleMaterial(RGBColor(255, 0, 255));
    
    RGBColor gradientSpectrum[2] = {RGBColor(58, 254, 80), RGBColor(29, 128, 20)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
    MaterialAnimator<10> materialAnimator;
    MaterialAnimator<5> backgroundMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 100), Vector2D(0, 0));
    BadAppleSequence gif = BadAppleSequence(Vector2D(200, 145), Vector2D(0,0), 18);

    //Animation controllers
    BlinkTrack<1> blink;

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 6.7f);
    FunctionGenerator fGenMatHue = FunctionGenerator(FunctionGenerator::Triangle, 0.0f, 360.0f, 17.3f);

    FunctionGenerator fGenMatXMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 1.1f);
    FunctionGenerator fGenMatYMenu = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 2.7f);
    FunctionGenerator fGenMatRMenu = FunctionGenerator(FunctionGenerator::Sine, -5.0f, 5.0f, 1.7f);

    FunctionGenerator fGenBlur = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 1.0f, 1.5f);

    APDS9960 boop;
    // SpeckPotentiometer potentiometer = SpeckPotentiometer(15,9);

    FFTVoiceDetection<128> voiceDetection;

    ObjectAlign objA = ObjectAlign(Vector2D(0.0f, 0.0f), Vector2D(189.0f, 93.0f), Quaternion());
    
    Fisheye fisheye = Fisheye();
    GlitchX glitchX = GlitchX(30);
    HorizontalBlur blurH = HorizontalBlur(8);
    VerticalBlur blurV = VerticalBlur(8);
    Magnet magnet = Magnet();
    RadialBlur blurR = RadialBlur(8);
    PhaseOffsetX phaseX = PhaseOffsetX(8);
    PhaseOffsetY phaseY = PhaseOffsetY(8);
    PhaseOffsetR phaseR = PhaseOffsetR(8);
    ShiftR shiftR = ShiftR(8);
    Overflow overflow = Overflow(8);

    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    float offsetFaceBad = 1.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;
<<<<<<< Updated upstream:lib/ProtoTracer/Examples/Protogen/ProtogenSplitWS35Project.h
    bool mirror = false;
=======
    uint8_t offsetFaceIndBad = 54;
    unsigned long previousMillis = 0;
    unsigned long currentMillis = 0;
    uint8_t mode = 0;
>>>>>>> Stashed changes:src/Animation/HUB75Animation.h

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Anger), NukudeFace::Anger, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Sadness), NukudeFace::Sadness, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Surprised), NukudeFace::Surprised, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Doubt), NukudeFace::Doubt, 25, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Frown), NukudeFace::Frown, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookUp), NukudeFace::LookUp, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookDown), NukudeFace::LookDown, 30, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ee), NukudeFace::vrc_v_ee, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ih), NukudeFace::vrc_v_ih, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_dd), NukudeFace::vrc_v_dd, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_rr), NukudeFace::vrc_v_rr, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ch), NukudeFace::vrc_v_ch, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_aa), NukudeFace::vrc_v_aa, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_oh), NukudeFace::vrc_v_oh, 2, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ss), NukudeFace::vrc_v_ss, 2, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::HideBlush), NukudeFace::HideBlush, 30, 1.0f, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::HideBlush), NukudeFace::HideBlush, 30, 1.0f, 0.0f);

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndBad, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(NukudeFace::Blink));
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(NukudeFace::HideBlush, EasyEaseInterpolation::Cosine);
        eEA.SetInterpolationMethod(NukudeFace::Sadness, EasyEaseInterpolation::Cosine);
        
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ee, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ih, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_dd, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_rr, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ch, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_aa, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_oh, EasyEaseInterpolation::Linear);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ss, EasyEaseInterpolation::Linear);
    }

    void SetMaterialLayers(){
<<<<<<< Updated upstream:lib/ProtoTracer/Examples/Protogen/ProtogenSplitWS35Project.h
        materialAnimator.SetBaseMaterial(Material::Add, &gradientMat);
        materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 4
        materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8
        materialAnimator.AddMaterial(Material::Replace, &rainbowNoise, 40, 0.15f, 1.0f);//layer 9
=======
        materialAnimator.SetBaseMaterial(Material::Add, &rainbowSpiral);
        // materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 1
        // materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 3
        // materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 4
        // materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        // materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        // materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        // materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8
        // materialAnimator.AddMaterial(Material::Replace, &rainbowNoise, 40, 0.15f, 1.0f);//layer 9
>>>>>>> Stashed changes:src/Animation/HUB75Animation.h

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &gif, 20, 0.0f, 1.0f);
    }

void UpdateKeyFrameTracks(){
        blink.Update();
    }

    void Default(){
        scene.DisableEffect();
    }

    void Angry(){
        eEA.AddParameterFrame(NukudeFace::Anger, 1.0f);
        materialAnimator.AddMaterialFrame(redMaterial, 0.8f);
    } 

    void Sad(){
        eEA.AddParameterFrame(NukudeFace::Sadness, 1.0f);
        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
        materialAnimator.AddMaterialFrame(blueMaterial, 0.8f);
    }

    void Surprised(){
        scene.SetEffect(&glitchX);
        scene.DisableEffect();

        eEA.AddParameterFrame(NukudeFace::Surprised, 1.0f);
        eEA.AddParameterFrame(NukudeFace::HideBlush, 0.0f);
        materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f);
    }
    
    void Doubt(){
        eEA.AddParameterFrame(NukudeFace::Doubt, 1.0f);
    }
    
    void Frown(){
        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
    }

    void LookUp(){
        eEA.AddParameterFrame(NukudeFace::LookUp, 1.0f);
    }

    void LookDown(){
        eEA.AddParameterFrame(NukudeFace::LookDown, 1.0f);
    }

    void SpectrumAnalyzerFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndSA, 1.0f);

        backgroundMaterial.AddMaterialFrame(sA, offsetFaceSA);
    }

    void AudioReactiveGradientFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndARG, 1.0f);

        backgroundMaterial.AddMaterialFrame(aRG, offsetFaceARG);
    }

    void OscilloscopeFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndOSC, 1.0f);

        backgroundMaterial.AddMaterialFrame(oSC, offsetFaceOSC);
    }

    void BadAppleFace(){
        eEA.AddParameterFrame(offsetFaceInd, 1.0f);
        eEA.AddParameterFrame(offsetFaceIndBad, 1.0f);

        backgroundMaterial.AddMaterialFrame(gif, offsetFaceBad);
    }

    void UpdateFFTVisemes(){
        if(Menu::UseMicrophone()){
            eEA.AddParameterFrame(NukudeFace::vrc_v_ss, MicrophoneFourierIT::GetCurrentMagnitude() / 2.0f);

            if(MicrophoneFourierIT::GetCurrentMagnitude() > 0.05f){
                voiceDetection.Update(MicrophoneFourierIT::GetFourierFiltered(), MicrophoneFourierIT::GetSampleRate());
        
                eEA.AddParameterFrame(NukudeFace::vrc_v_ee, voiceDetection.GetViseme(voiceDetection.EE));
                eEA.AddParameterFrame(NukudeFace::vrc_v_ih, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(NukudeFace::vrc_v_dd, voiceDetection.GetViseme(voiceDetection.UH));
                eEA.AddParameterFrame(NukudeFace::vrc_v_rr, voiceDetection.GetViseme(voiceDetection.AR));
                eEA.AddParameterFrame(NukudeFace::vrc_v_ch, voiceDetection.GetViseme(voiceDetection.ER));
                eEA.AddParameterFrame(NukudeFace::vrc_v_aa, voiceDetection.GetViseme(voiceDetection.AH));
                eEA.AddParameterFrame(NukudeFace::vrc_v_oh, voiceDetection.GetViseme(voiceDetection.OO));
            }
        }
    }

    void SetMaterialColor(){
        switch(Menu::GetFaceColor()){
            case 1: materialAnimator.AddMaterialFrame(redMaterial, 0.8f); break;
            case 2: materialAnimator.AddMaterialFrame(orangeMaterial, 0.8f); break;
            case 3: materialAnimator.AddMaterialFrame(whiteMaterial, 0.8f); break;
            case 4: materialAnimator.AddMaterialFrame(greenMaterial, 0.8f); break;
            case 5: materialAnimator.AddMaterialFrame(blueMaterial, 0.8f); break;
            case 6: materialAnimator.AddMaterialFrame(yellowMaterial, 0.8f); break;
            case 7: materialAnimator.AddMaterialFrame(purpleMaterial, 0.8f); break;
            case 8: materialAnimator.AddMaterialFrame(rainbowSpiral, 0.8f); break;
            case 9: materialAnimator.AddMaterialFrame(rainbowNoise, 0.8f); break;
            default: break;
        }
    }

public:
    WS35AnimationSplit() {
        scene.AddObject(pM.GetObject());
        scene.AddObject(background.GetObject());
        scene.AddObject(ledStripBackground.GetObject());

        LinkEasyEase();
        LinkParameters();

        ChangeInterpolationMethods();

        SetMaterialLayers();

        pM.GetObject()->SetMaterial(&materialAnimator);
        background.GetObject()->SetMaterial(&backgroundMaterial);
        ledStripBackground.GetObject()->SetMaterial(&materialAnimator);

        objA.SetJustification(ObjectAlign::Stretch);
        objA.SetMirrorX(true);
    }

    void Initialize() override {
        boop.Initialize(5);

<<<<<<< Updated upstream:lib/ProtoTracer/Examples/Protogen/ProtogenSplitWS35Project.h
        MicrophoneFourierIT::Initialize(22, 8000, 50.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
=======
        MicrophoneFourierIT::Initialize(A2, 8000, 90.0f, 120.0f);//8KHz sample rate, 50dB min, 120dB max
>>>>>>> Stashed changes:src/Animation/HUB75Animation.h
        //Menu::Initialize(9);//NeoTrellis
        Menu::Initialize(9, 0, 500);//7 is number of faces
    }


    uint8_t GetAccentBrightness(){
        return Menu::GetAccentBrightness();
    };

    uint8_t GetBrightness(){
        return Menu::GetBrightness();
    };

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }
    
    void SetCameraMirror(bool mirror){
        this->mirror = mirror;
    }

    void Update(float ratio) override {
        if(!mirror){
            gradientSpectrum[0] = RGBColor(255, 0, 0).HueShift(Menu::GetHueF() * 36);
            gradientSpectrum[1] = RGBColor(255, 0, 0).HueShift(Menu::GetHueB() * 36);

            gradientMat.UpdateGradient(gradientSpectrum);
            gradientMat.UpdateRGB();

            pM.Reset();

            float xOffset = fGenMatXMove.Update();
            float yOffset = fGenMatYMove.Update();
            
            Menu::Update(ratio);

<<<<<<< Updated upstream:lib/ProtoTracer/Examples/Protogen/ProtogenSplitWS35Project.h
            //Menu::SetSize(Vector2D(280, 60));
            //Menu::SetPositionOffset(Vector2D(0.0f, -30.0f * yOffset));
            
            //glitchX.SetRatio(fGenBlur.Update());
            magnet.SetRatio(ratio);
            fisheye.SetRatio(fGenBlur.Update());
            blurH.SetRatio(fGenBlur.Update());
            blurV.SetRatio(fGenBlur.Update());
            blurR.SetRatio(fGenBlur.Update());
            phaseX.SetRatio(fGenBlur.Update());
            phaseY.SetRatio(fGenBlur.Update());
            phaseR.SetRatio(fGenBlur.Update());
            shiftR.SetRatio(fGenBlur.Update());

            SetMaterialColor();

            bool isBooped = Menu::UseBoopSensor() ? boop.isBooped() : 0;
            uint8_t mode = Menu::GetFaceState();//change by button press

            MicrophoneFourierIT::Update();
            sA.SetHueAngle(ratio * 360.0f * 4.0f);
            sA.SetMirrorYState(Menu::MirrorSpectrumAnalyzer());
            sA.SetFlipYState(!Menu::MirrorSpectrumAnalyzer());
            
            aRG.SetRadius((xOffset + 2.0f) * 2.0f + 25.0f);
            aRG.SetSize(Vector2D((xOffset + 2.0f) * 10.0f + 50.0f, (xOffset + 2.0f) * 10.0f + 50.0f));
            aRG.SetHueAngle(ratio * 360.0f * 8.0f);
            aRG.SetRotation(ratio * 360.0f * 2.0f);
            aRG.SetPosition(Vector2D(80.0f + xOffset * 4.0f, 48.0f + yOffset * 4.0f));
=======
        bool isBooped = false;
        
        if (this->boopExists && Menu::UseBoopSensor()) {
           isBooped = boop.isBooped();
        }
        
        // uint8_t mode = Menu::GetFaceState();//change by button press
        // uint8_t mode = potentiometer.read(); 
        // currentMillis = millis();
        // if ((currentMillis - previousMillis) >= 15000) {
        //     mode = (mode + 1) % 10;
        //     previousMillis = currentMillis;
        // }

        // mode = 9;
        MicrophoneFourierIT::Update();
        sA.SetHueAngle(ratio * 360.0f * 4.0f);
        sA.SetMirrorYState(Menu::MirrorSpectrumAnalyzer());
        sA.SetFlipYState(!Menu::MirrorSpectrumAnalyzer());
        
        aRG.SetRadius((xOffset + 2.0f) * 2.0f + 25.0f);
        aRG.SetSize(Vector2D((xOffset + 2.0f) * 10.0f + 50.0f, (xOffset + 2.0f) * 10.0f + 50.0f));
        aRG.SetHueAngle(ratio * 360.0f * 8.0f);
        aRG.SetRotation(ratio * 360.0f * 2.0f);
        aRG.SetPosition(Vector2D(80.0f + xOffset * 4.0f, 48.0f + yOffset * 4.0f));

        oSC.SetSize(Vector2D(200.0f, 100.0f));
        oSC.SetHueAngle(ratio * 360.0f * 8.0f);
        oSC.SetPosition(Vector2D(100.0f, 50.0f));

        
        
        voiceDetection.SetThreshold(map(Menu::GetMicLevel(), 0, 10, 1000, 50));
>>>>>>> Stashed changes:src/Animation/HUB75Animation.h

            oSC.SetSize(Vector2D(200.0f, 100.0f));
            oSC.SetHueAngle(ratio * 360.0f * 8.0f);
            oSC.SetPosition(Vector2D(100.0f, 50.0f));
            
            voiceDetection.SetThreshold(map(Menu::GetMicLevel(), 0, 10, 1000, 50));

            UpdateFFTVisemes();

<<<<<<< Updated upstream:lib/ProtoTracer/Examples/Protogen/ProtogenSplitWS35Project.h
            if (isBooped && mode != 6){
                Surprised();
            }
            else{
                if (mode == 0) Default();
                else if (mode == 1) Angry();
                else if (mode == 2) Doubt();
                else if (mode == 3) Frown();
                else if (mode == 4) LookUp();
                else if (mode == 5) Sad();
                else if (mode == 6) {
                    aRG.Update(MicrophoneFourierIT::GetFourierFiltered());
                    AudioReactiveGradientFace();
                }
                else if (mode == 7){
                    oSC.Update(MicrophoneFourierIT::GetSamples());
                    OscilloscopeFace();
                }
                else {
                    sA.Update(MicrophoneFourierIT::GetFourierFiltered());
                    SpectrumAnalyzerFace();
                }
            }

            UpdateKeyFrameTracks();
            
            pM.SetMorphWeight(NukudeFace::BiggerNose, 1.0f);
            pM.SetMorphWeight(NukudeFace::MoveEye, 1.0f);

            eEA.Update();
            pM.Update();
            
            //phaseR.SetRatio(eEA.GetValue(NukudeFace::Surprised));
            glitchX.SetRatio(eEA.GetValue(NukudeFace::Surprised));

            rainbowNoise.Update(ratio);
            rainbowSpiral.Update(ratio);
            materialAnimator.Update();
            backgroundMaterial.Update();

            uint8_t faceSize = Menu::GetFaceSize();
            float scale = Menu::ShowMenu() * 0.6f + 0.4f;
            float faceSizeOffset = faceSize * 8.0f;

            objA.SetPlaneOffsetAngle(0.0f);
            objA.SetEdgeMargin(4.0f);
            objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 115.0f - 115.0f * offsetFace).Multiply(scale));

            objA.AlignObjects(scene.GetObjects(), 1);
            
            pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset, 0.0f));
            pM.GetObject()->UpdateTransform();
        }
        else{
            gradientSpectrum[0] = RGBColor(255, 0, 0).HueShift(Menu::GetHueF() * 36);
            gradientSpectrum[1] = RGBColor(255, 0, 0).HueShift(Menu::GetHueB() * 36);

            gradientMat.UpdateGradient(gradientSpectrum);
            gradientMat.UpdateRGB();
        }
=======
        gradientMat.UpdateGradient(gradientSpectrum);
        if (isBooped && mode != 6){
            Surprised();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Angry();
            else if (mode == 2) Doubt();
            else if (mode == 3) Frown();
            else if (mode == 4) LookUp();
            else if (mode == 5) Sad();
            else if (mode == 6) {
                aRG.Update(MicrophoneFourierIT::GetFourierFiltered());
                AudioReactiveGradientFace();
            }
            else if (mode == 7){
                oSC.Update(MicrophoneFourierIT::GetSamples());
                OscilloscopeFace();
            }
            else if (mode == 8){
                sA.Update(MicrophoneFourierIT::GetFourierFiltered());
                SpectrumAnalyzerFace();
            } else if (mode == 9) {
                BadAppleFace();
                gif.SetPosition(Vector2D(96.0f, 48.0f));
                gif.SetSize(Vector2D(191.0f, 95.0f));
                //gif.SetRotation(15.0f);
                gif.Update();
            }
        }

        UpdateKeyFrameTracks();
        
        pM.SetMorphWeight(NukudeFace::BiggerNose, 1.0f);
        pM.SetMorphWeight(NukudeFace::MoveEye, 1.0f);

        eEA.Update();
        pM.Update();

        // rainbowNoise.Update(ratio);
        rainbowSpiral.Update(ratio);
        materialAnimator.Update();
        backgroundMaterial.Update();

        uint8_t faceSize = Menu::GetFaceSize();
        float scale = Menu::ShowMenu() * 0.6f + 0.4f;
        float faceSizeOffset = faceSize * 8.0f;

        objA.SetPlaneOffsetAngle(-7.5f);
        objA.SetEdgeMargin(2.0f);
        objA.SetCameraMax(Vector2D(110.0f + faceSizeOffset, 93.0f - 93.0f * offsetFace).Multiply(scale));

        objA.AlignObjects(scene.GetObjects(), 1);
        
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(xOffset, yOffset, 0.0f));
        pM.GetObject()->UpdateTransform();
>>>>>>> Stashed changes:src/Animation/HUB75Animation.h
    }
};
