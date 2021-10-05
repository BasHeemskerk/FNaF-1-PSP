#include "included/menu.hpp"

namespace menu{

    int whichFrame = 0;
    float waitFrames = 10;

    namespace render{
        void renderBackground(){
            drawSpriteAlpha(0, 0, 300, 272, image::menu::menuBackground[whichFrame], 180, 0, 0);
        }
        void animateBackground(){
            if (waitFrames <= 0){
                    whichFrame = rand() % 4;

                if (whichFrame > 3){
                    whichFrame = 0;
                }
                
                waitFrames = 10;
            }
            else{
                waitFrames -= 1;
            }
        }

        void renderLogo(){
            drawSpriteAlpha(0, 0, 165, 165, image::menu::logo, 5, 5, 0);
        }
        void renderCopyright(){
            drawSpriteAlpha(0, 0, 287, 17, image::menu::copyright, 193, 255, 0);
        }

        void renderStars(){
            if (save::starAmount == 1){
                drawSpriteAlpha(0, 0, 28, 27, sprite::menu::star, 140, 5, 0);
            }
            if (save::starAmount == 2){
                drawSpriteAlpha(0, 0, 28, 27, sprite::menu::star, 140, 5, 0);
                drawSpriteAlpha(0, 0, 28, 27, sprite::menu::star, 170, 5, 0);
            }
            if (save::starAmount == 3){
                drawSpriteAlpha(0, 0, 28, 27, sprite::menu::star, 140, 5, 0);
                drawSpriteAlpha(0, 0, 28, 27, sprite::menu::star, 170, 5, 0);
                drawSpriteAlpha(0, 0, 28, 27, sprite::menu::star, 200, 5, 0);
            }
        }
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

    namespace menuCursor{
        float cursorPos = 0;
        float cursorLimit = 1;
        float posY;

        void renderCursor(){
            drawSpriteAlpha(0, 0, 205, 20, image::menu::selectionText[0], 40, 180, 0);
            drawSpriteAlpha(0, 0, 205, 20, image::menu::selectionText[1], 40, 203, 0);

            if (save::mode1Unlocked == 1){
                drawSpriteAlpha(0, 0, 205, 20, image::menu::selectionText[2], 40, 226, 0);
            }
            if (save::mode2Unlocked == 1){
                drawSpriteAlpha(0, 0, 205, 20, image::menu::selectionText[3], 40, 249, 0);
            }

            if (cursorPos == 0){
                drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersNormal[save::whichNight], 140, 177, 0);
            }

            drawSpriteAlpha(0, 0, 205, 20, image::menu::selectionCursor, 13, posY, 0);
        }
        void moveCursor(){
            if (cursorPos == 0){
                posY = 182;
            }
            if (cursorPos == 1){
                posY = 205;
            }
            if (cursorPos == 2){
                posY = 228;
            }
            if (cursorPos == 3){
                posY = 251;
            }

            if (cursorPos > cursorLimit){
                cursorPos = cursorLimit;
                moveCursor();
            }
            if (cursorPos <= 0){
                cursorPos = 0;
            }

            if (save::mode1Unlocked == 1){
                cursorLimit = 2;
            }
            if (save::mode2Unlocked == 1){
                cursorLimit = 3;
            }
        }

        void select(){
            if (cursorPos == 0){
                if (save::whichNight == 1){
                    initNewspaper();
                }
                else{
                    initNightinfo();
                }
            }
            else if (cursorPos == 1){
                initNewspaper();

                save::whichNight = 1;
                save::mode1Unlocked = 0;
                save::mode2Unlocked = 0;
                save::starAmount = 0;

                save::clearData();

                //save::saveData();
            }
            else if (cursorPos == 2){
                initNightinfo();

                save::whichNight = 6;

                //save::saveData();
            }
            else if (cursorPos == 3){
                initCustomNight();
            }
        }

        void initNewspaper(){
            state::isMenu = false;
            image::menu::unloadMenuBackground();
            //image::unloadStatic();
            image::menu::unloadLogo();
            image::menu::unloadCopyright();
            image::menu::unloadTextAndCursor();
            music::menu::unloadMenuMusic();
            sprite::menu::unloadStar();

            image::n_newspaper::loadNewsPaper();
            state::isNewspaper = true;
        }

        void initNightinfo(){
            state::isMenu = false;
            image::menu::unloadMenuBackground();
            //image::unloadStatic();
            image::menu::unloadLogo();
            image::menu::unloadCopyright();
            image::menu::unloadTextAndCursor();
            music::menu::unloadMenuMusic();
            sprite::menu::unloadStar();

            sprite::nightinfo::loadNightInfoSprite();
            state::isNightinfo = true;
        }

        void initCustomNight(){
            state::isMenu = false;
            image::menu::unloadMenuBackground();
            //image::unloadStatic();
            image::menu::unloadLogo();
            image::menu::unloadCopyright();
            image::menu::unloadTextAndCursor();
            music::menu::unloadMenuMusic();
            sprite::menu::unloadStar();

            sprite::UI::customnight::loadIcons();
            sprite::UI::customnight::loadReticle();
            sprite::UI::customnight::loadInstructions();
            sprite::UI::customnight::loadTitle();
            sprite::UI::customnight::loadArrows();
            sprite::UI::customnight::loadText();
            sprite::UI::customnight::loadNames();
            sprite::UI::customnight::loadActions();
            sprite::UI::customnight::loadGoldenFreddy();

            state::isCustomNight = true;
        }
    }
}

