#include "included/dead.hpp"

namespace dead{

    float waitFrames = 600;

    void reset(){
        waitFrames = 600;
    }

    namespace n_static{
        int whichFrameStatic = 0;
        float waitFrames2 = 5;

        void renderStatic(){
            drawSpriteAlpha(0, 0, 480, 272, image::global::n_static::staticFrames[whichFrameStatic], 0, 0, 0);
        }
        void animateStatic(){
            if (waitFrames2 <= 0){
                whichFrameStatic += 1;

                if (whichFrameStatic > 3){
                    whichFrameStatic = 0;
                }

                waitFrames2 = 5;
            }
            else{
                waitFrames2 -= 1;
            }
        }
    }

    namespace wait{
        void waitForFrames(){
            if (waitFrames <= 0){
                initMenu();
                waitFrames = 600;
            }
            else{
                waitFrames -= 1;
            }
        }

        void initMenu(){
            state::isDead = false;

            sfx::jumpscare::unloadDeadSound();
            
            sprite::UI::office::unloadCamUi();
            sprite::UI::office::unloadPowerInfo();
            sprite::office::unloadDoors();
            sprite::office::unloadButtons();

            //sfx::jumpscare::unloadJumpscareSound();

            save::readData();

            image::menu::loadMenuBackground();
            image::menu::loadLogo();
            image::menu::loadCopyright();
            image::menu::loadTextAndCursor();
            sprite::menu::loadStar();

            music::menu::loadMenuMusic();
            music::menu::playMenuMusic();

            state::isMenu = true;
        }
    }
}