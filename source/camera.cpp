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

    namespace render{
        void renderCamFlip(){
            if (closing == true || opening == true){
                drawSpriteAlpha(0, 0, 480, 272, sprite::UI::office::camFlip[whichFrame], 0, 0, 0);
            }
        }
        void renderCamera(){
            if (isUsing == true && closing == false /*&& sprite::UI::office::loaded == true*/){
                drawSpriteAlpha(0, 0, 480, 272, sprite::UI::office::cams[whichCamera], 0, 0, 0);
            }
        }
        void renderUi(){
            if (isUsing == true && closing == false){
                drawSpriteAlpha(0, 0, 480, 272, sprite::UI::office::camBorder, 0, 0, 0);
                drawSpriteAlpha(0, 0, 160, 160, sprite::UI::office::camMap, 310, 108, 0);
                drawSpriteAlpha(0, 0, 20, 20, sprite::UI::office::recording, 20, 20, 0);
                drawSpriteAlpha(0, 0, 121, 13, sprite::UI::office::camNames[whichCamera], 310, 95, 0);

                //the "buttons" on the map
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[0], 353, 115, 0);
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[1], 348, 140, 0);
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[2], 333, 172, 0);
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[3], 352, 215, 0);
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[4], 352, 232, 0);
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[5], 323, 210, 0);
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[6], 395, 215, 0);
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[7], 395, 232, 0);
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[8], 307, 150, 0);
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[9], 435, 202, 0);
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::camButtons[10], 440, 150, 0);

                //the reticle (shows the cam ur on)
                drawSpriteAlpha(0, 0, 20, 15, sprite::UI::office::reticle, reticleX, reticleY, 0);
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

        void left(){
            if (isUsing == true){
                if (whichCamera == 1 || whichCamera == 2){
                    whichCamera = 8;
                }
                else if (whichCamera == 3 || whichCamera == 4){
                    whichCamera = 5;
                }
                else if (whichCamera == 6 || whichCamera == 7){
                    whichCamera = 3;
                }
                else if (whichCamera == 9){
                    whichCamera = 6;
                }
                else if (whichCamera == 10){
                    whichCamera = 1;
                }

                sfx::office::playSwitch();
                setReticle();
            }
        }
        void right(){
            if (isUsing == true){
                if (whichCamera == 1 || whichCamera == 2){
                    whichCamera = 10;
                }
                else if (whichCamera == 3 || whichCamera == 4){
                    whichCamera = 6;
                }
                else if (whichCamera == 6 || whichCamera == 7){
                    whichCamera = 9;
                }
                else if (whichCamera == 5){
                    whichCamera = 3;
                }
                else if (whichCamera == 8){
                    whichCamera = 1;
                }

                sfx::office::playSwitch();
                setReticle();
            }
        }
        void up(){
            if (isUsing == true){

                if (whichCamera == 1){
                    whichCamera = 0;
                }
                else if (whichCamera == 2){
                    whichCamera = 1;
                }
                else if (whichCamera == 3){
                    whichCamera = 2;
                }
                else if (whichCamera == 4){
                    whichCamera = 3;
                }
                else if (whichCamera == 7){
                    whichCamera = 6;
                }
                else if (whichCamera == 9){
                    whichCamera = 10;
                }
                sfx::office::playSwitch();
                setReticle();
            }
        }
        void down(){
            if (isUsing == true){
                if (whichCamera == 0){
                    whichCamera = 1;
                }
                else if (whichCamera == 1){
                    whichCamera = 2;
                }
                else if (whichCamera == 2){
                    whichCamera = 3;
                }
                else if (whichCamera == 3){
                    whichCamera = 4;
                }
                else if (whichCamera == 6){
                    whichCamera = 7;
                }
                else if (whichCamera == 10){
                    whichCamera = 9;
                }

                sfx::office::playSwitch();
                setReticle();
            }
        }

        /*
        void plus(){
            if (isUsing == true){
                if (whichCamera < 10){
                    whichCamera += 1;
                    sfx::office::playSwitch();
                    setReticle();
                }
                else if (whichCamera == 10){
                    whichCamera = 0;
                    sfx::office::playSwitch();
                    setReticle();
                }
            }
        }
        void minus(){
            if (isUsing == true){
                if (whichCamera > 0){
                    whichCamera -= 1;
                    sfx::office::playSwitch();
                    setReticle();
                }
                else if (whichCamera == 0){
                    whichCamera = 10;
                    sfx::office::playSwitch();
                    setReticle();
                }
            }
        }
        */

        void setReticle(){
            if (whichCamera == 0){
                reticleX = 353;
                reticleY = 115;
            }
            else if (whichCamera == 1){
                reticleX = 348;
                reticleY = 140;
            }
            else if (whichCamera == 2){
                reticleX = 333;
                reticleY = 172;
            }
            else if (whichCamera == 3){
                reticleX = 352;
                reticleY = 215;
            }
            else if (whichCamera == 4){
                reticleX = 352;
                reticleY = 232;
            }
            else if (whichCamera == 5){
                reticleX = 323;
                reticleY = 210;
            }
            else if (whichCamera == 6){
                reticleX = 395;
                reticleY = 215;
            }
            else if (whichCamera == 7){
                reticleX = 395;
                reticleY = 232;
            }
            else if (whichCamera == 8){
                reticleX = 307;
                reticleY = 150;
            }
            else if (whichCamera == 9){
                reticleX = 435;
                reticleY = 202;
            }
            else if (whichCamera == 10){
                reticleX = 440;
                reticleY = 150;
            }
        }
    }
}