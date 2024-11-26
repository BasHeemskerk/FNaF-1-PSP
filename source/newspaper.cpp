#include "included/newspaper.hpp"

namespace newspaper{

    float countdown = 400;
    bool deactivated = false;

    void reset(){
        countdown = 400;
        deactivated = false;
    }

    namespace render{
        void renderNewspaper(){
            if (deactivated == false){
                drawSpriteAlpha(0, 0, 480, 272, image::n_newspaper::newspaper, 0, 0, 0);
            }
        }
    }

    namespace next{
        void initNightinfo(){
            if (countdown <= 0 && deactivated == false){
                deactivated = true;
                state::isNewspaper = false;
                sprite::nightinfo::loadNightInfoSprite();
                state::isNightinfo = true;
            }
            else{
                countdown -= 1;
            }
        }
    }
}