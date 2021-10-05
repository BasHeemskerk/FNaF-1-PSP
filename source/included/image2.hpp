#include "global.hpp"
#include "save.hpp"
#include "state.hpp"

namespace image{
    namespace menu{
        extern Image *menuBackground[4];
        extern Image *selectionText[4];
        extern Image *selectionCursor;
        
        extern Image *logo;
        extern Image *copyright;

        void loadMenuBackground();
        void unloadMenuBackground();

        void loadLogo();
        void unloadLogo();

        void loadCopyright();
        void unloadCopyright();

        void loadTextAndCursor();
        void unloadTextAndCursor();
    }

    namespace global{
        namespace n_static{
            extern Image *staticFrames[4];
    
            void loadStatic();
            void unloadStatic();
        }
    }


    namespace n_newspaper{
        extern Image *newspaper;
        extern bool loaded;

        void loadNewsPaper();
        void unloadNewsPaper();
    }

    namespace n_ending{
        extern Image *ending;

        void loadEnding();
        void unloadEnding();
    }

    namespace n_noPower{
        extern Image *noPower[2];

        void loadNoPower();
        void unloadNoPower();
    }
}

namespace sprite{

    namespace menu{
        extern Image *star;

        void loadStar();
        void unloadStar();
    }

    namespace nightinfo{
        extern Image *info;
        extern Image *clock;

        void loadNightInfoSprite();
        void unloadNightInfoSprite();
    }


    namespace office{
        extern Image *buttonsLeft[4];
        extern Image *buttonsRight[4];

        void loadButtons();
        void unloadButtons();


        extern Image *doorLeft[7];
        extern Image *doorRight[7];

        void loadDoors();
        void unloadDoors();
    }


    namespace UI{

        
        namespace office{
            extern Image *powerBar[5];
            extern Image *usageFrame;
            extern Image *powerLeft;

            void loadPowerInfo();
            void unloadPowerInfo();


            extern Image *AM;
            extern Image *Night;

            void loadTimeInfo();
            void unloadTimeInfo();


            extern Image *camFlip[4];

            void loadCamFlip();
            void unloadCamFlip();


            extern Image *cams[11];
            extern int whichCamera;
            extern Image *camNames[11];
            extern Image *camButtons[11];
            extern Image *reticle;
            extern Image *camBorder;
            extern Image *recording;
            extern Image *camMap;

            extern float freddyPosition;
            extern float bonniePosition;
            extern float chicaPosition;
            extern float foxyPosition;

            extern bool loaded;

            void loadCams();
            void unloadCams();

            /*
            extern Image *cam1a_a[5];
            extern Image *cam1b_a[5];
            extern Image *cam1c_a[3];
            extern Image *cam2a_a;
            extern Image *cam2b_a;
            extern Image *cam3_a;
            extern Image *cam4a_a[3];
            extern Image *cam4b_a[2];
            extern Image *cam5_a[2];
            extern Image *cam7_a[2];

            void loadCamsAnimatronic();
            void unloadCamsAnimatronic();
            void clearAllCamsAnimatronic();
            */

            void loadCamUi();
            void unloadCamUi();
        }

        namespace customnight{
            extern Image *icons[4];
            extern Image *reticle;
            extern Image *instructions[2];
            extern Image *title;
            extern Image *arrows[2];
            extern Image *levelDesc;
            extern Image *difficulty;
            extern Image *names[4];
            extern Image *create;
            extern Image *exit;
            extern Image *goldFreddy;

            void loadIcons();
            void unloadIcons();

            void loadReticle();
            void unloadReticle();

            void loadInstructions();
            void unloadInstructions();

            void loadTitle();
            void unloadTitle();

            void loadArrows();
            void unloadArrows();

            void loadText();
            void unloadText();

            void loadNames();
            void unloadNames();

            void loadActions();
            void unloadActions();

            void loadGoldenFreddy();
            void unloadGoldenFreddy();
        }
    }

    namespace n_jumpscare{
        extern Image *jumpscareAnim[9];
        extern float whichJumpscare;

        extern bool loaded;

        void loadJumpscare();
        void unloadJumpscare();
    }
}

namespace officeImage{
    extern Image *office1Sprites[5];
    extern Image *office2Sprites[5];

    void loadOffice1Sprites();
    void unloadOffice1Sprites();

    void loadOffice2Sprites();
    void unloadOffice2Sprites();
}

namespace text{
    namespace global{
        extern Image *nightNumbersNormal[10];
        extern Image *nightNumbersPixel[10];
        extern Image *symbols;

        void loadNightText();
        void unloadNightText();
    }
}