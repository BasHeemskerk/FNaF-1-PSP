#include "included/powerout.hpp"

namespace powerout{

    int whichFrame = 0;
    float frameWaitTime = 15;
    float totalWaitTime = 1020;
    bool belowMain = false;

    void reset(){
        whichFrame = 0;
        frameWaitTime = 15;
        totalWaitTime = 1020;
        belowMain = false;
    }

    namespace render{
        void renderPowerout(){
            drawSpriteAlpha(0, 0, 480, 272, image::n_noPower::noPower[whichFrame], 0, 0, 0);
        }
    }
    namespace animate{
        void animatePowerOut(){
            totalWaitTime -= 1;

            if (totalWaitTime == 310){
                belowMain = true;
            }

            if (belowMain == false){
                if (frameWaitTime <= 0){
                    if (whichFrame != 1){
                        whichFrame = 1;
                    }
                    else{
                        whichFrame = 0;
                    }

                    frameWaitTime = 15;
                }
                else{
                    frameWaitTime -= 1;
                }
            }
            else if (belowMain == true){
                whichFrame = 0;

                if (music::n_ending::stopped == false){
                    music::n_ending::unloadEndingSong();
                    music::n_ending::stopped = true;
                }
                if (totalWaitTime <= 0){
                    initJumpscare();
                    totalWaitTime = 1020;
                }
                
            }
        }

        void initJumpscare(){
            state::isPowerOut = false;

            image::n_noPower::unloadNoPower();
            sfx::jumpscare::loadJumpscareSound();

            sprite::n_jumpscare::whichJumpscare = 1;
            //sprite::n_jumpscare::loadJumpscare();

            state::isJumpscare = true;
        }
    }
}