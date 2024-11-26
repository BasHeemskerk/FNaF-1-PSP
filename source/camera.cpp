#include "included/camera.hpp"

namespace camera{

    int whichCamera;
    //int whichCameraUsing;
    bool isUsing = false;

    bool opening = false;
    bool closing = false;

    int whichFrame;
    float waitFrames = 1;
    float delay = 3;

    float reticleX = 353;
    float reticleY = 115;
    
    std::string buttonState = "up";

    void reset(){
        whichCamera = 0;
        
        isUsing = false;
        animatronic::usingCams = false;
        opening = false;
        closing = false;

        whichFrame = 0;
        waitFrames = 1;
        delay = 3;

        reticleX = 353;
        reticleY = 115;

        buttonState = "up";
    }

    namespace render {
        void renderCamFlip() {
            if (closing || opening) {
                if (sprite::UI::office::camFlip[whichFrame]) {
                    drawSpriteAlpha(0, 0, 480, 272, sprite::UI::office::camFlip[whichFrame], 0, 0, 0);
                } else {
                    std::cerr << "Error: camFlip frame is null at index " << whichFrame << std::endl;
                }
            }
        }

        void renderCamera() {
            if (isUsing && !closing) {
                if (sprite::UI::office::cams[whichCamera]) {
                    drawSpriteAlpha(0, 0, 480, 272, sprite::UI::office::cams[whichCamera], 0, 0, 0);
                } else {
                    std::cerr << "Error: Camera frame is null for camera " << whichCamera << std::endl;
                }
            }
        }

        void renderUi() {
            if (isUsing && !closing) {
                // Render camera border
                if (sprite::UI::office::camBorder) {
                    drawSpriteAlpha(0, 0, 480, 272, sprite::UI::office::camBorder, 0, 0, 0);
                } else {
                    std::cerr << "Error: camBorder is null." << std::endl;
                }

                // Render map
                if (sprite::UI::office::camMap) {
                    drawSpriteAlpha(0, 0, 160, 160, sprite::UI::office::camMap, 310, 108, 0);
                } else {
                    std::cerr << "Error: camMap is null." << std::endl;
                }

                // Render recording icon
                if (sprite::UI::office::recording) {
                    drawSpriteAlpha(0, 0, 20, 20, sprite::UI::office::recording, 20, 20, 0);
                } else {
                    std::cerr << "Error: recording icon is null." << std::endl;
                }

                // Render camera name
                if (sprite::UI::office::camNames[whichCamera]) {
                    drawSpriteAlpha(0, 0, 121, 13, sprite::UI::office::camNames[whichCamera], 310, 95, 0);
                } else {
                    std::cerr << "Error: camNames is null for camera " << whichCamera << std::endl;
                }

                // Render camera buttons
                for (size_t i = 0; i < 11; ++i) {
                    if (sprite::UI::office::camButtons[i]) {
                        int buttonX, buttonY;

                        // Map button positions
                        switch (i) {
                            case 0: buttonX = 353; buttonY = 115; break;
                            case 1: buttonX = 348; buttonY = 140; break;
                            case 2: buttonX = 333; buttonY = 172; break;
                            case 3: buttonX = 352; buttonY = 215; break;
                            case 4: buttonX = 352; buttonY = 232; break;
                            case 5: buttonX = 323; buttonY = 210; break;
                            case 6: buttonX = 395; buttonY = 215; break;
                            case 7: buttonX = 395; buttonY = 232; break;
                            case 8: buttonX = 307; buttonY = 150; break;
                            case 9: buttonX = 435; buttonY = 202; break;
                            case 10: buttonX = 440; buttonY = 150; break;
                            default: continue;
                        }

                        drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[i], buttonX, buttonY, 0);
                    } else {
                        std::cerr << "Error: camButton at index " << i << " is null." << std::endl;
                    }
                }

                // Render reticle
                if (sprite::UI::office::reticle) {
                    drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::reticle, reticleX, reticleY, 0);
                } else {
                    std::cerr << "Error: reticle is null." << std::endl;
                }
            }
        }
    }

    namespace n_static{
        int whichFrameStatic = 0;
        float waitFrames2 = 5;

        void renderStatic(){
            if (isUsing == true && closing == false){
                drawSpriteAlpha(0, 0, 480, 272, image::global::n_static::staticFrames[whichFrameStatic], 0, 0, 0);
            }
        }
        void animateStatic(){
            if (waitFrames2 <= 0){
                whichFrameStatic += 1;

                if (whichFrameStatic > 3){
                    whichFrameStatic = 0;
                }

                waitFrames2 = 3;
            }
            else{
                waitFrames2 -= 1;
            }
        }
    }

    namespace animation{

        void camera(){
            if (opening == false && isUsing == false){
                opening = true;
                sfx::office::playCamOpen();
            }
            else if (closing == false && isUsing == true){
                closing = true;
                sfx::office::playCamClose();
            }
        }

        void openCams(){
            if (waitFrames <= 0){
                if (whichFrame < 3){
                    whichFrame += 1;

                    waitFrames = 1;
                }
                else{
                    opening = false;
                    isUsing = true;
                    animatronic::usingCams = true;
                }
            }
            else{
                waitFrames -= 1;
            }
        }
        void closeCams(){
            if (delay <= 0){
                if (waitFrames <= 0){
                    if (whichFrame > 0){
                        whichFrame -= 1;

                        waitFrames = 1;
                    }
                    else{
                        closing = false;
                        isUsing = false;
                        animatronic::usingCams = false;
                        delay = 2;
                    }
                }
                else{
                    waitFrames -= 1;
                }
            }
            else{
                delay -= 1;
            }
        }

        
    }

    namespace system{

        void left() {
            if (isUsing) {
                switch (whichCamera) {
                    case 1:
                    case 2:
                        whichCamera = 8;
                        break;
                    case 3:
                    case 4:
                        whichCamera = 5;
                        break;
                    case 6:
                    case 7:
                        whichCamera = 3;
                        break;
                    case 9:
                        whichCamera = 6;
                        break;
                    case 10:
                        whichCamera = 1;
                        break;
                }

                sfx::office::playSwitch();
                setReticle();
            }
        }
        void right() {
            if (isUsing) {
                switch (whichCamera) {
                    case 1:
                    case 2:
                        whichCamera = 10;
                        break;
                    case 3:
                    case 4:
                        whichCamera = 6;
                        break;
                    case 6:
                    case 7:
                        whichCamera = 9;
                        break;
                    case 5:
                        whichCamera = 3;
                        break;
                    case 8:
                        whichCamera = 1;
                        break;
                }

                sfx::office::playSwitch();
                setReticle();
            }
        }
        void up() {
            if (isUsing) {
                switch (whichCamera) {
                    case 1:
                        whichCamera = 0;
                        break;
                    case 2:
                        whichCamera = 1;
                        break;
                    case 3:
                        whichCamera = 2;
                        break;
                    case 4:
                        whichCamera = 3;
                        break;
                    case 7:
                        whichCamera = 6;
                        break;
                    case 9:
                        whichCamera = 10;
                        break;
                }

                sfx::office::playSwitch();
                setReticle();
            }
        }
        void down() {
            if (isUsing) {
                switch (whichCamera) {
                    case 0:
                        whichCamera = 1;
                        break;
                    case 1:
                        whichCamera = 2;
                        break;
                    case 2:
                        whichCamera = 3;
                        break;
                    case 3:
                        whichCamera = 4;
                        break;
                    case 6:
                        whichCamera = 7;
                        break;
                    case 10:
                        whichCamera = 9;
                        break;
                }

                sfx::office::playSwitch();
                setReticle();
            }
        }


        void setReticle(){
            switch (whichCamera){
                case 0:
                    reticleX = 353;
                    reticleY = 115;
                    break;
                case 1:
                    reticleX = 348;
                    reticleY = 140;
                    break;
                case 2:
                    reticleX = 333;
                    reticleY = 172;
                    break;
                case 3:
                    reticleX = 352;
                    reticleY = 215;
                    break;
                case 4:
                    reticleX = 352;
                    reticleY = 232;
                    break;
                case 5:
                    reticleX = 323;
                    reticleY = 210;
                    break;
                case 6:
                    reticleX = 395;
                    reticleY = 215;
                    break;
                case 7:
                    reticleX = 395;
                    reticleY = 232;
                    break;
                case 8:
                    reticleX = 307;
                    reticleY = 150;
                    break;
                case 9:
                    reticleX = 435;
                    reticleY = 202;
                    break;
                case 10:
                    reticleX = 440;
                    reticleY = 150;
                    break;
                default:
                    break;
            }
        }
    }
}