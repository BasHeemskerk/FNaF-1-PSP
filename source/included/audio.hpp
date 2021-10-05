#include "global.hpp"
#include "save.hpp"

namespace music{
    namespace menu{
        void loadMenuMusic();
        void playMenuMusic();
        void unloadMenuMusic();
    }

    namespace n_ending{

        extern bool stopped;

        extern OSL_SOUND* endingSong;

        void loadEndingSong();
        void playEndingSong();
        void stopEndingSong();
        void unloadEndingSong();
    }
}

namespace ambience{
    namespace office{
        extern OSL_SOUND* ambience;

        void loadAmbience();
        void playAmbience();
        void unloadAmbience();


        extern OSL_SOUND* fan;

        void loadFanSound();
        void playFanSound();
        void unloadFanSound();
    }
}

namespace call{
    extern OSL_SOUND* phoneCalls[5];
    extern bool stopped;

    void loadPhoneCalls();
    void playPhoneCalls();
    void unloadPhoneCalls();
}

namespace sfx{
    namespace office{
        extern OSL_SOUND* buzz;
        extern OSL_SOUND* door;
        extern OSL_SOUND* scare;
        extern OSL_SOUND* switchCam;
        extern OSL_SOUND* laugh;
        extern OSL_SOUND* move;
        extern OSL_SOUND* walk;
        extern OSL_SOUND* kitchen;
        extern OSL_SOUND* run;
        extern OSL_SOUND* knock;
        extern OSL_SOUND* camera[2];

        void loadSfx();
        void stopSfx();
        void unloadSfx();

        void playLightOn();
        void playLightOff();

        void playDoor();

        void playCamOpen();
        void playCamClose();
        void playSwitch();
        void playMove();

        void playLaugh();
        void playWalk();
        void playKitchen();
        void playScare();

        void playRun();
        void playKnock();
    }
    namespace sixam{

        extern OSL_SOUND* ding;

        void loadSixAm();
        void unloadSixAm();
        
        void playSixAm();
    }
    namespace jumpscare{
        extern OSL_SOUND *jumpscare;
        extern OSL_SOUND *jumpscare2;
        extern OSL_SOUND *dead;

        void loadJumpscareSound();
        void playJumpscareSound();
        void unloadJumpscareSound();

        void loadJumpscare2Sound();
        void playJumpscare2Sound();
        void unloadJumpscare2Sound();

        void loadDeadSound();
        void playDeadSound();
        void unloadDeadSound();
    }
}