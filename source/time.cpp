#include "included/time.hpp"

namespace timegame{

    int gtime = 0;
    float framesPerUpdate = 5100; //5100 frames = 85 seconds

    void reset(){
        gtime = 0;
        framesPerUpdate = 5100;
    }

    namespace render{
        void renderTime(){
            if (gtime == 0){
                drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersPixel[gtime + 1], 395, 19, 0);
                drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersPixel[gtime + 2], 405, 19, 0);
            }
            else{
                drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersPixel[gtime], 405, 19, 0);
            }
            drawSpriteAlpha(0, 0, 27, 20, sprite::UI::office::AM, 430, 20, 0);

            drawSpriteAlpha(0, 0, 62, 20, sprite::UI::office::Night, 377, 45, 0);
            drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersPixel[save::whichNight], 437, 44, 0);
        }
    }
    namespace update{
        void updateTime(){
            if (framesPerUpdate <= 0){
                gtime += 1;
                framesPerUpdate = 5100;

                if (gtime == 2){
                    animatronic::bonnie::incrementDifficulty();
                }
                else if (gtime == 3){
                    animatronic::bonnie::incrementDifficulty();
                    animatronic::chika::incrementDifficulty();
                }
                else if (gtime == 4){
                    animatronic::bonnie::incrementDifficulty();
                    animatronic::chika::incrementDifficulty();
                }
                else if (gtime == 5){
                    animatronic::bonnie::incrementDifficulty();
                    animatronic::chika::incrementDifficulty();
                }
                
                if (gtime >= 6){
                    initSixAm();
                    gtime = 0;
                }
            }
            else{
                framesPerUpdate -= 1;
            }
        }

        void initSixAm(){
            state::isOffice = false;

            sfx::office::unloadSfx();
            ambience::office::unloadAmbience();
            ambience::office::unloadFanSound();

            sprite::UI::office::unloadCams();
            sprite::UI::office::unloadCamFlip();

            officeImage::unloadOffice1Sprites();

            sixam::saveIt::saveTheData();

            sfx::sixam::loadSixAm();
            sfx::sixam::playSixAm();

            state::isSixAm = true;
        }
    }

}