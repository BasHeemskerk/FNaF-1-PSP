#include "included/ending.hpp"

namespace ending{

    float waitTime = 3660;

    void reset(){
        waitTime = 3660;
    }

    namespace render{
        void renderEnding(){
            drawSpriteAlpha(0, 0, 480, 272, image::n_ending::ending, 0, 0, 0);
        }
    }

    namespace wait{
        void waitForFrames(){
            if (waitTime <= 0){
                initMenu();
                waitTime = 3660;
            }
            else{
                waitTime -= 1;
            }
        }

        void initMenu(){
            state::isEnding = false;

            image::n_ending::unloadEnding();
            music::n_ending::unloadEndingSong();

            image::menu::loadMenuBackground();
            image::menu::loadLogo();
            image::menu::loadCopyright();
            image::menu::loadTextAndCursor();
            sprite::menu::loadStar();

            menu::menuCursor::moveCursor();
            save::readData();

            music::menu::loadMenuMusic();
            music::menu::playMenuMusic();

            state::isMenu = true;
        }
    }
}