#include "included/jumpscare.hpp"

namespace jumpscare{

    //float whichJumpscare;
    //bool loaded = false;
    //bool loading = false;

    int whichFrame = 0;
    float timePerFrame = 1.3f;
    //float replayAmount = 1;

    //int ThreadIDJ;
    //int PspThreadStatus = 1;

    void reset(){
        whichFrame = 0;
        timePerFrame = 1.3f;
    }

    namespace render{
        void renderJumpscare(){
            if (sprite::n_jumpscare::loaded == true){
                drawSpriteAlpha(0, 0, 480, 272, sprite::n_jumpscare::jumpscareAnim[whichFrame], 0, 0, 0);
            }
        }
    }

    namespace animate{
        void animateJumpscare(){

            std::cout << "scaring the crap outta u (well maybe idk)" << std::endl;

            if (timePerFrame <= 0){
                if (whichFrame == 1){
                    sfx::jumpscare::playJumpscareSound();
                }

                if (whichFrame < 8){
                    whichFrame += 1;
                }
                else if (whichFrame >= 8){
                    initDeathScreen();
                    whichFrame = 0;
                }

                timePerFrame = 1.3f;
            }
            else{
                timePerFrame -= 1;
            }
        }

        void initDeathScreen(){
            state::isJumpscare = false;

            sprite::n_jumpscare::unloadJumpscare();
            sfx::jumpscare::unloadJumpscareSound();

            sfx::jumpscare::loadDeadSound();
            sfx::jumpscare::playDeadSound();

            state::isDead = true;
        }
    }

    namespace load{
        float waitBeforeLoading = 2; //in frames

        void loadWithDelay(){
            if (waitBeforeLoading <= 0 && sprite::n_jumpscare::loaded == false){
                sprite::n_jumpscare::loadJumpscare();
                waitBeforeLoading = 2;
            }
            else if (waitBeforeLoading > 0 && sprite::n_jumpscare::loaded == false){
                waitBeforeLoading -= 1;
            }
        }
    }

    
}