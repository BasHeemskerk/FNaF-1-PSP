#include "included/nightinfo.hpp"

namespace nightinfo{

    float countdown = 400;
    bool officeObjectsLoaded = false;
    bool isLoading = false;
    bool deactivated = false;
    bool loadedMain = false;

    void reset(){
        countdown = 400;
        officeObjectsLoaded = false;
        isLoading = false;
        deactivated = false;
        loadedMain = false;
    }

    namespace render{
        void renderNightinfo(){
            drawSpriteAlpha(0, 0, 75, 48, sprite::nightinfo::info, 200, 100, 0);
            drawSpriteAlpha(0, 0, 40, 40, sprite::nightinfo::clock, 435, 227, 0);
            drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersPixel[save::whichNight], 265, 128, 0);
        }
    }
    namespace next{
        void preloadOffice(){
            if (officeObjectsLoaded == false && isLoading == false){
                isLoading = true;

                if (image::n_newspaper::loaded == true){
                    image::n_newspaper::unloadNewsPaper();
                }

                officeImage::loadOffice1Sprites();
                officeImage::loadOffice2Sprites();

                sprite::office::loadButtons();
                sprite::office::loadDoors();

                sprite::UI::office::loadCamFlip();
                sprite::UI::office::loadPowerInfo();
                sprite::UI::office::loadTimeInfo();

                sprite::UI::office::loadCams();
                sprite::UI::office::loadCamUi();

                power::update::setDrainTime();

                office::main::setX();
                
                animatronic::setDefault();

                ambience::office::loadAmbience();
                ambience::office::loadFanSound();
                sfx::office::loadSfx();
                call::loadPhoneCalls();

                animatronic::setDefault();

                officeObjectsLoaded = true;
            }
        }

        void initOffice(){
            if (countdown <= 0 && officeObjectsLoaded == true && deactivated == false){
                state::isNightinfo = false;
                
                sprite::nightinfo::unloadNightInfoSprite();

                ambience::office::playAmbience();
                ambience::office::playFanSound();
                call::playPhoneCalls();

                state::isOffice = true;
            }
            else{
                countdown -= 1;
            }
        }
    }
}