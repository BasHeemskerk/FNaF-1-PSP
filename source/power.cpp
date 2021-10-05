#include "included/power.hpp"

namespace power{
    int usage = 0;
    float total = 99;
    float drainTime = 600;

    int lightUsage = 0;
    int doorUsage = 0;
    int camUsage = 0;

    int tenths = 9;
    int ones = 9;

    //std::string keyState = "up";

    void reset(){
        usage = 0;
        total = 99;
        lightUsage = 0;
        doorUsage = 0;
        camUsage = 0;
        tenths = 9;
        ones = 9;
    }

    namespace render{
        void renderPowerLeft(){
            drawSpriteAlpha(0, 0, 72, 17, sprite::UI::office::usageFrame, 10, 215, 0);
            drawSpriteAlpha(0, 0, 55, 20, sprite::UI::office::powerBar[usage], 92, 215, 0);
            drawSpriteAlpha(0, 0, 127, 17, sprite::UI::office::powerLeft, 10, 245, 0);
            if (total > 9){
                drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersPixel[tenths], 140, 243, 0);
            }
            if (total > 0){
                drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersPixel[ones], 155, 243, 0);
            }
            drawSpriteAlpha(0, 0, 20, 20, text::global::symbols, 170, 243, 0);
        }
    }

    namespace update{
        void checkDrain(){
            if (office::leftOn == false && office::rightOn == false){
                lightUsage = 0;
            }
            if (office::leftOn == true || office::rightOn == true){
                lightUsage = 1;
            }
            if (office::leftOn == true && office::rightOn == true){
                lightUsage = 2;
            }

            if (office::leftClosed == false && office::rightClosed == false){
                doorUsage = 0;
            }
            if (office::leftClosed == true || office::rightClosed == true){
                doorUsage = 1;
            }
            if (office::leftClosed == true && office::rightClosed == true){
                doorUsage = 2;
            }

            if (camera::isUsing == false){
                camUsage = 0;
            }
            if (camera::isUsing == true){
                camUsage = 1;
            }

            usage = lightUsage + doorUsage + camUsage;
            if (usage > 4){
                usage = 4;
            }
            

            if (total == 0){
                initPowerOut();
                total = 0;
            }
            
        }

        void drainConstant(){
            if (usage == 1){
                if (drainTime == 600 || drainTime == 540 || drainTime == 480 || drainTime == 420){
                    drainTime /= 2;
                }
            }
            else if (usage == 2){
                if (drainTime == 600 || drainTime == 540 || drainTime == 480 || drainTime == 420){
                    drainTime /= 4;
                }
            }
            else if (usage == 3){
                if (drainTime == 600 || drainTime == 540 || drainTime == 480 || drainTime == 420){
                    drainTime /= 6;
                }
            }
            else if (usage == 4){
                if (drainTime == 600 || drainTime == 540 || drainTime == 480 || drainTime == 420){
                    drainTime /= 8;
                }
            }

            if (drainTime <= 0){
                total -= 1;
                ones -= 1;

                if (ones < 0 && tenths > 0){
                    ones = 9;
                    tenths -= 1;
                }

                setDrainTime();
            }
            else{
                drainTime -= 1;
            }
        }

        void setDrainTime(){
            if (save::whichNight == 1){
                drainTime = 600;
            }
            else if (save::whichNight == 2){
                drainTime = 540;
            }
            else if (save::whichNight == 3){
                drainTime = 540;
            }
            else if (save::whichNight == 4){
                drainTime = 480;
            }
            else if (save::whichNight == 5){
                drainTime = 420;
            }
            else if (save::whichNight == 6){
                drainTime = 420;
            }
            else if (save::whichNight == 7){
                drainTime = 420;
            }
        }

        void initPowerOut(){
            state::isOffice = false;

            //sprite::UI::office::unloadPowerInfo();
            //sprite::office::unloadDoors();
            //sprite::office::unloadButtons();
            sprite::UI::office::unloadCamFlip();
            //sprite::UI::office::unloadCamUi();
            sprite::UI::office::unloadCams();

            sfx::office::unloadSfx();
            ambience::office::unloadAmbience();
            ambience::office::unloadFanSound();

            image::n_noPower::loadNoPower();

            music::n_ending::loadEndingSong();
            music::n_ending::playEndingSong();

            state::isPowerOut = true;
        }
    }
}