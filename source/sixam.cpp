#include "included/sixam.hpp"

namespace sixam{

    int whichNumber = 5;
    float delayChange = 150;
    float delayReload = 500;

    void reset(){
        whichNumber = 5;
        delayChange = 150;
        delayReload = 500;
    }

    namespace saveIt{
        void saveTheData(){
            save::saveData();
            save::file();
        }
    }
    namespace render{
        void renderSixAm(){
            drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersPixel[whichNumber], 215, 123, 0);
            drawSpriteAlpha(0, 0, 27, 20, sprite::UI::office::AM, 240, 126, 0);
        }
    }
    namespace animate{
        void wait(){
            if (delayChange <= 0){
                whichNumber = 6;
            }
            else{
                delayChange -= 1;
            }
        }
    }
    namespace next{
        void wait(){
            if (delayReload <= 0){
                switch (save::whichNight){
                    case 5: case 7:
                        clearRest();
                        initEnding();
                        break;
                    case 6:
                        clearRest();
                        initMenu();
                        break;
                    default:
                        clearRest();
                        initNightinfo();
                        break;
                }
            }
            else{
                delayReload -= 1;
            }
        }
        void clearRest(){
            officeImage::unloadOffice2Sprites();

            sprite::UI::office::unloadPowerInfo();
            sprite::UI::office::unloadTimeInfo();
            sprite::office::unloadDoors();
            sprite::office::unloadButtons();
        }
        void initNightinfo(){
            state::isSixAm = false;

            save::readData();

            sprite::nightinfo::loadNightInfoSprite();
            sfx::sixam::unloadSixAm();
            state::isNightinfo = true;
        }
        void initEnding(){
            state::isSixAm = false;
            image::n_ending::loadEnding();
            music::n_ending::loadEndingSong();
            music::n_ending::playEndingSong();
            state::isEnding = true;
        }
        void initMenu(){
            state::isSixAm = false;
            
            save::readData();

            image::menu::loadMenuBackground();
            image::menu::loadLogo();
            sprite::menu::loadStar();
            image::menu::loadCopyright();
            text::global::loadNightText();

            menu::menuCursor::moveCursor();

            music::menu::loadMenuMusic();
            music::menu::playMenuMusic();

            state::isMenu = true;
        }
    }
}