#include "included/customnight.hpp"

namespace customnight{

    float reticlePosition = 0;
    float actualReticlePosition;
    std::string editing = "freddy";

    float crashDelay = 300;
    bool mustCrash = false;

    void reset(){
        reticlePosition = 0;
        actualReticlePosition = 60;
        editing = "freddy";
    }

    namespace render{
        void renderHeads(){
            if (mustCrash == false){
                drawSpriteAlpha(0, 0, 60, 60, sprite::UI::customnight::icons[0], 60, 80, 0);
                drawSpriteAlpha(0, 0, 60, 60, sprite::UI::customnight::icons[1], 160, 80, 0);
                drawSpriteAlpha(0, 0, 60, 60, sprite::UI::customnight::icons[2], 260, 80, 0);
                drawSpriteAlpha(0, 0, 60, 60, sprite::UI::customnight::icons[3], 360, 80, 0);
            }
        }
        void renderReticle(){
            if (mustCrash == false){
                drawSpriteAlpha(0, 0, 60, 60, sprite::UI::customnight::reticle, actualReticlePosition, 80, 0);
            }
        }
        void renderInstructions(){
            if (mustCrash == false){
                drawSpriteAlpha(0, 0, 13, 20, sprite::UI::customnight::instructions[0], 10, 10, 0);
                drawSpriteAlpha(0, 0, 13, 20, sprite::UI::customnight::instructions[1], 457, 10, 0);
            }
        }
        void renderTitle(){
            if (mustCrash == false){
                drawSpriteAlpha(0, 0, 175, 24, sprite::UI::customnight::title, 153, 25, 0);
            }
        }
        void renderNames(){
            if (mustCrash == false){
                drawSpriteAlpha(0, 0, 60, 17, sprite::UI::customnight::names[0], 60, 64, 0);
                drawSpriteAlpha(0, 0, 60, 17, sprite::UI::customnight::names[1], 160, 63, 0);
                drawSpriteAlpha(0, 0, 60, 17, sprite::UI::customnight::names[2], 260, 63, 0);
                drawSpriteAlpha(0, 0, 60, 17, sprite::UI::customnight::names[3], 360, 64, 0);
            }
        }
        void renderArrows(){
            if (mustCrash == false){
                //freddy
                drawSpriteAlpha(0, 0, 13, 20, sprite::UI::customnight::arrows[0], 60, 160, 0);
                drawSpriteAlpha(0, 0, 13, 20, sprite::UI::customnight::arrows[1], 108, 160, 0);

                //bonnie
                drawSpriteAlpha(0, 0, 13, 20, sprite::UI::customnight::arrows[0], 160, 160, 0);
                drawSpriteAlpha(0, 0, 13, 20, sprite::UI::customnight::arrows[1], 208, 160, 0);

                //chika
                drawSpriteAlpha(0, 0, 13, 20, sprite::UI::customnight::arrows[0], 260, 160, 0);
                drawSpriteAlpha(0, 0, 13, 20, sprite::UI::customnight::arrows[1], 308, 160, 0);

                //foxy
                drawSpriteAlpha(0, 0, 13, 20, sprite::UI::customnight::arrows[0], 360, 160, 0);
                drawSpriteAlpha(0, 0, 13, 20, sprite::UI::customnight::arrows[1], 408, 160, 0);
            }
        }
        void renderText(){
            if (mustCrash == false){
                drawSpriteAlpha(0, 0, 60, 10, sprite::UI::customnight::levelDesc, 60, 145, 0);
                drawSpriteAlpha(0, 0, 60, 10, sprite::UI::customnight::levelDesc, 160, 145, 0);
                drawSpriteAlpha(0, 0, 60, 10, sprite::UI::customnight::levelDesc, 260, 145, 0);
                drawSpriteAlpha(0, 0, 60, 10, sprite::UI::customnight::levelDesc, 360, 145, 0);

                drawSpriteAlpha(0, 0, 300, 11, sprite::UI::customnight::difficulty, 60, 212, 0);
            }
        }
        void renderLevels(){
            if (mustCrash == false){
                //2 numbers per ani

                //freddy
                drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersNormal[animatronic::freddy::levelOnes], 88, 160, 0);
                if (animatronic::freddy::totalLevel > 9){
                    drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersNormal[animatronic::freddy::levelTenths], 73, 160, 0);
                }

                //bonnie
                drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersNormal[animatronic::bonnie::levelOnes], 188, 160, 0);
                if (animatronic::bonnie::totalLevel > 9){
                    drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersNormal[animatronic::bonnie::levelTenths], 173, 160, 0);
                }

                //chika
                drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersNormal[animatronic::chika::levelOnes], 288, 160, 0);
                if (animatronic::chika::totalLevel > 9){
                    drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersNormal[animatronic::chika::levelTenths], 273, 160, 0);
                }

                //foxy
                drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersNormal[animatronic::foxy::levelOnes], 388, 160, 0);
                if (animatronic::foxy::totalLevel > 9){
                    drawSpriteAlpha(0, 0, 20, 20, text::global::nightNumbersNormal[animatronic::foxy::levelTenths], 373, 160, 0);
                }
            }
        }
        void renderActions(){
            if (mustCrash == false){
                drawSpriteAlpha(0, 0, 78, 18, sprite::UI::customnight::create, 380, 242, 0);
                drawSpriteAlpha(0, 0, 69, 18, sprite::UI::customnight::exit, 10, 242, 0);
            }
        }
        void renderGoldenFreddy(){
            if (mustCrash == true){

                std::cout << "CRASHHHH (well its not an actual crash, just exits the game)" << std::endl;

                drawSpriteAlpha(0, 0, 480, 272, sprite::UI::customnight::goldFreddy, 0, 0, 0);

                if (crashDelay <= 0){
                    sceKernelExitGame();
                }
                else{
                    crashDelay -= 1;
                }
            }
        }
    }

    namespace edit{
        void plus(){
            if (mustCrash == false){
                if (editing == "freddy"){
                    if (animatronic::freddy::totalLevel < 20){
                        animatronic::freddy::totalLevel += 1;
                        animatronic::freddy::levelOnes += 1;
                    }
                }
                else if (editing == "bonnie"){
                    if (animatronic::bonnie::totalLevel < 20){
                        animatronic::bonnie::totalLevel += 1;
                        animatronic::bonnie::levelOnes += 1;
                    }
                }
                else if (editing == "chika"){
                    if (animatronic::chika::totalLevel < 20){
                        animatronic::chika::totalLevel += 1;
                        animatronic::chika::levelOnes += 1;
                    }
                }
                else if (editing == "foxy"){
                    if (animatronic::foxy::totalLevel < 20){
                        animatronic::foxy::totalLevel += 1;
                        animatronic::foxy::levelOnes += 1;
                    }
                }

                editValue();
            }
        }
        void minus(){
            if (mustCrash == false){
                if (editing == "freddy"){
                    if (animatronic::freddy::totalLevel > 0){
                        animatronic::freddy::totalLevel -= 1;
                        animatronic::freddy::levelOnes -= 1;
                    }
                }
                else if (editing == "bonnie"){
                    if (animatronic::bonnie::totalLevel > 0){
                        animatronic::bonnie::totalLevel -= 1;
                        animatronic::bonnie::levelOnes -= 1;
                    }
                }
                else if (editing == "chika"){
                    if (animatronic::chika::totalLevel > 0){
                        animatronic::chika::totalLevel -= 1;
                        animatronic::chika::levelOnes -= 1;
                    }
                }
                else if (editing == "foxy"){
                    if (animatronic::foxy::totalLevel > 0){
                        animatronic::foxy::totalLevel -= 1;
                        animatronic::foxy::levelOnes -= 1;
                    }
                }

                editValue();
            }
        }
        
        void editValue(){
            if (editing == "freddy"){
                if (animatronic::freddy::levelOnes == 10){
                    animatronic::freddy::levelOnes = 0;
                    animatronic::freddy::levelTenths += 1;
                }
                else if (animatronic::freddy::levelOnes < 0 && animatronic::freddy::levelTenths > 0){
                    animatronic::freddy::levelOnes = 9;
                    animatronic::freddy::levelTenths -= 1;
                }
            }
            else if (editing == "bonnie"){
                if (animatronic::bonnie::levelOnes == 10){
                    animatronic::bonnie::levelOnes = 0;
                    animatronic::bonnie::levelTenths += 1;
                }
                else if (animatronic::bonnie::levelOnes < 0 && animatronic::bonnie::levelTenths > 0){
                    animatronic::bonnie::levelOnes = 9;
                    animatronic::bonnie::levelTenths -= 1;
                }
            }
            else if (editing == "chika"){
                if (animatronic::chika::levelOnes == 10){
                    animatronic::chika::levelOnes = 0;
                    animatronic::chika::levelTenths += 1;
                }
                else if (animatronic::chika::levelOnes < 0 && animatronic::chika::levelTenths > 0){
                    animatronic::chika::levelOnes = 9;
                    animatronic::chika::levelTenths -= 1;
                }
            }
            else if (editing == "foxy"){
                if (animatronic::foxy::levelOnes == 10){
                    animatronic::foxy::levelOnes = 0;
                    animatronic::foxy::levelTenths += 1;
                }
                else if (animatronic::foxy::levelOnes < 0 && animatronic::foxy::levelTenths > 0){
                    animatronic::foxy::levelOnes = 9;
                    animatronic::foxy::levelTenths -= 1;
                }
            }
        }
    }

    namespace reticle{
        std::string dir = "none";

        void moveReticleLeft(){
            if (mustCrash == false){
                if (reticlePosition > 0){
                    reticlePosition -= 1;
                }
            }
        }
        void moveReticleRight(){
            if (mustCrash == false){
                if (reticlePosition < 3){
                    reticlePosition += 1;
                }
            }
        }
        void updatePosition(){
            if (mustCrash == false){
                if (reticlePosition == 0){
                    actualReticlePosition = 60;
                    editing = "freddy";
                }
                else if (reticlePosition == 1){
                    actualReticlePosition = 160;
                    editing = "bonnie";
                }
                else if (reticlePosition == 2){
                    actualReticlePosition = 260;
                    editing = "chika";
                }
                else if (reticlePosition == 3){
                    actualReticlePosition = 360;
                    editing = "foxy";
                }
            }
        }
    }

    namespace actions{

        void create(){
            if (animatronic::freddy::totalLevel == 1 && animatronic::bonnie::totalLevel == 9 && animatronic::chika::totalLevel == 8 && animatronic::foxy::totalLevel == 7){
                if (mustCrash == false){
                    state::isCustomNight = false;

                    sfx::jumpscare::loadJumpscare2Sound();

                    sprite::UI::customnight::unloadIcons();
                    sprite::UI::customnight::unloadReticle();
                    sprite::UI::customnight::unloadInstructions();
                    sprite::UI::customnight::unloadTitle();
                    sprite::UI::customnight::unloadArrows();
                    sprite::UI::customnight::unloadText();
                    sprite::UI::customnight::unloadNames();
                    sprite::UI::customnight::unloadActions();

                    sfx::jumpscare::playJumpscare2Sound();

                    state::isCustomNight = true;

                    mustCrash = true;
                }
            }
            else{
                save::whichNight = 7;
                state::isCustomNight = false;
                
                sprite::UI::customnight::unloadIcons();
                sprite::UI::customnight::unloadReticle();
                sprite::UI::customnight::unloadInstructions();
                sprite::UI::customnight::unloadTitle();
                sprite::UI::customnight::unloadArrows();
                sprite::UI::customnight::unloadText();
                sprite::UI::customnight::unloadNames();
                sprite::UI::customnight::unloadActions();
                sprite::UI::customnight::unloadGoldenFreddy();

                sprite::nightinfo::loadNightInfoSprite();
                state::isNightinfo = true;
            }
        }
        void exit(){
            if (mustCrash == false){
                if (save::whichNight > 5){
                    save::readData();
                }
                state::isCustomNight = false;

                sprite::UI::customnight::unloadIcons();
                sprite::UI::customnight::unloadReticle();
                sprite::UI::customnight::unloadInstructions();
                sprite::UI::customnight::unloadTitle();
                sprite::UI::customnight::unloadArrows();
                sprite::UI::customnight::unloadText();
                sprite::UI::customnight::unloadNames();
                sprite::UI::customnight::unloadActions();
                sprite::UI::customnight::unloadGoldenFreddy();

                image::menu::loadMenuBackground();
                image::menu::loadLogo();
                image::menu::loadCopyright();
                image::menu::loadTextAndCursor();
                sprite::menu::loadStar();

                menu::menuCursor::moveCursor();

                music::menu::loadMenuMusic();
                music::menu::playMenuMusic();

                state::isMenu = true;
            }
        }
    }
}