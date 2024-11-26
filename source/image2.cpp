#include "included/image2.hpp"

namespace image{
    namespace menu{
        Image *menuBackground[4];
        Image *selectionText[4];
        Image *selectionCursor;

        Image *logo;
        Image *copyright;

        void loadMenuBackground(){
            menuBackground[0] = loadPng("romfs/gfx/menu/frame_1.png");
            menuBackground[1] = loadPng("romfs/gfx/menu/frame_2.png");
            menuBackground[2] = loadPng("romfs/gfx/menu/frame_3.png");
            menuBackground[3] = loadPng("romfs/gfx/menu/frame_4.png");
        }
        void unloadMenuBackground(){
            freeImage(menuBackground[0]);
            freeImage(menuBackground[1]);
            freeImage(menuBackground[2]);
            freeImage(menuBackground[3]);
        }

        void loadLogo(){
            logo = loadPng("romfs/gfx/menu/logo.png");
        }
        void unloadLogo(){
            freeImage(logo);
        }

        void loadCopyright(){
            copyright = loadPng("romfs/gfx/menu/copyright.png");
        }
        void unloadCopyright(){
            freeImage(copyright);
        }

        void loadTextAndCursor(){
            selectionText[0] = loadPng("romfs/gfx/menu/selection/continue.png");
            selectionText[1] = loadPng("romfs/gfx/menu/selection/newGame.png");
            selectionText[2] = loadPng("romfs/gfx/menu/selection/6thNight.png");
            selectionText[3] = loadPng("romfs/gfx/menu/selection/customNight.png");

            selectionCursor = loadPng("romfs/gfx/menu/selection/arrow.png");
        }
        void unloadTextAndCursor(){
            freeImage(selectionText[0]);
            freeImage(selectionText[1]);
            freeImage(selectionText[2]);
            freeImage(selectionText[3]);

            freeImage(selectionCursor);
            
        }
    }

    namespace global{
        namespace n_static{
            Image *staticFrames[4];
        
            void loadStatic(){
                staticFrames[0] = loadPng("romfs/gfx/menu/static/image1_480x272.png");
                staticFrames[1] = loadPng("romfs/gfx/menu/static/image2_480x272.png");
                staticFrames[2] = loadPng("romfs/gfx/menu/static/image3_480x272.png");
                staticFrames[3] = loadPng("romfs/gfx/menu/static/image4_480x272.png");
            }
            void unloadStatic(){
                freeImage(staticFrames[0]);
                freeImage(staticFrames[1]);
                freeImage(staticFrames[2]);
                freeImage(staticFrames[3]);
            }
        }
    }

    namespace n_newspaper{
        Image *newspaper;
        bool loaded = false;

        void loadNewsPaper(){
            newspaper = loadPng("romfs/gfx/newspaper/paper.png");
            loaded = true;
        }
        void unloadNewsPaper(){
            freeImage(newspaper);
            loaded = false;
        }
    }

    namespace n_ending{
        Image *ending;

        void loadEnding(){
            if (save::whichNight == 5){
                ending = loadPng("romfs/gfx/ending/good.png");
            }
            if (save::whichNight == 7){
                ending = loadPng("romfs/gfx/ending/bad.png");
            }
        }
        void unloadEnding(){
            freeImage(ending);
        }
    }

    namespace n_noPower{
        Image *noPower[2];

        void loadNoPower(){
            noPower[0] = loadPng("romfs/gfx/powerout/freddy1.png");
            noPower[1] = loadPng("romfs/gfx/powerout/freddy2.png");
        }
        void unloadNoPower(){
            freeImage(noPower[0]);
            freeImage(noPower[1]);
        }
    }
}

namespace sprite{

    namespace menu{
        Image *star;

        void loadStar(){
            star = loadPng("romfs/gfx/menu/star.png");
        }
        void unloadStar(){
            freeImage(star);
        }
    }
    namespace nightinfo{
        Image *info;
        Image *clock;

        void loadNightInfoSprite(){
            info = loadPng("romfs/gfx/nightinfo/info.png");
            clock = loadPng("romfs/gfx/nightinfo/clock.png");
        }
        void unloadNightInfoSprite(){
            freeImage(info);
            freeImage(clock);
        }
    }


    namespace office{
        Image *buttonsLeft[4];
        Image *buttonsRight[4];

        void loadButtons(){
            buttonsLeft[0] = loadPng("romfs/gfx/office/buttons/left/left_0.png");
            buttonsLeft[1] = loadPng("romfs/gfx/office/buttons/left/left_1.png");
            buttonsLeft[2] = loadPng("romfs/gfx/office/buttons/left/left_2.png");
            buttonsLeft[3] = loadPng("romfs/gfx/office/buttons/left/left_3.png");

            buttonsRight[0] = loadPng("romfs/gfx/office/buttons/right/right_0.png");
            buttonsRight[1] = loadPng("romfs/gfx/office/buttons/right/right_1.png");
            buttonsRight[2] = loadPng("romfs/gfx/office/buttons/right/right_2.png");
            buttonsRight[3] = loadPng("romfs/gfx/office/buttons/right/right_3.png");
        }
        void unloadButtons(){
            freeImage(buttonsLeft[0]);
            freeImage(buttonsLeft[1]);
            freeImage(buttonsLeft[2]);
            freeImage(buttonsLeft[3]);

            freeImage(buttonsRight[0]);
            freeImage(buttonsRight[1]);
            freeImage(buttonsRight[2]);
            freeImage(buttonsRight[3]);
        }


        Image *doorLeft[7];
        Image *doorRight[7];

        void loadDoors(){
            doorLeft[0] = loadPng("romfs/gfx/office/doors/left/door_1.png");
            doorLeft[1] = loadPng("romfs/gfx/office/doors/left/door_2.png");
            doorLeft[2] = loadPng("romfs/gfx/office/doors/left/door_3.png");
            doorLeft[3] = loadPng("romfs/gfx/office/doors/left/door_4.png");
            doorLeft[4] = loadPng("romfs/gfx/office/doors/left/door_5.png");
            doorLeft[5] = loadPng("romfs/gfx/office/doors/left/door_6.png");
            doorLeft[6] = loadPng("romfs/gfx/office/doors/left/door_7.png");

            doorRight[0] = loadPng("romfs/gfx/office/doors/right/door_1.png");
            doorRight[1] = loadPng("romfs/gfx/office/doors/right/door_2.png");
            doorRight[2] = loadPng("romfs/gfx/office/doors/right/door_3.png");
            doorRight[3] = loadPng("romfs/gfx/office/doors/right/door_4.png");
            doorRight[4] = loadPng("romfs/gfx/office/doors/right/door_5.png");
            doorRight[5] = loadPng("romfs/gfx/office/doors/right/door_6.png");
            doorRight[6] = loadPng("romfs/gfx/office/doors/right/door_7.png");
            //doorRight[7] = loadPng("romfs/gfx/office/doors/right/door_8.png");
        }
        void unloadDoors(){
            freeImage(doorLeft[0]);
            freeImage(doorLeft[1]);
            freeImage(doorLeft[2]);
            freeImage(doorLeft[3]);
            freeImage(doorLeft[4]);
            freeImage(doorLeft[5]);
            freeImage(doorLeft[6]);

            freeImage(doorRight[0]);
            freeImage(doorRight[1]);
            freeImage(doorRight[2]);
            freeImage(doorRight[3]);
            freeImage(doorRight[4]);
            freeImage(doorRight[5]);
            freeImage(doorRight[6]);
            //freeImage(doorRight[7]);
        }
    }


    namespace UI{
        namespace office{
            Image *powerBar[5];
            Image *usageFrame;
            Image *powerLeft;

            void loadPowerInfo(){
                powerBar[0] = loadPng("romfs/gfx/office/ui/bar_1.png");
                powerBar[1] = loadPng("romfs/gfx/office/ui/bar_2.png");
                powerBar[2] = loadPng("romfs/gfx/office/ui/bar_3.png");
                powerBar[3] = loadPng("romfs/gfx/office/ui/bar_4.png");
                powerBar[4] = loadPng("romfs/gfx/office/ui/bar_5.png");

                usageFrame = loadPng("romfs/gfx/office/ui/usage.png");

                powerLeft = loadPng("romfs/gfx/office/ui/powerLeft.png");
            }
            void unloadPowerInfo(){
                freeImage(powerBar[0]);
                freeImage(powerBar[1]);
                freeImage(powerBar[2]);
                freeImage(powerBar[3]);
                freeImage(powerBar[4]);

                freeImage(usageFrame);

                freeImage(powerLeft);
            }


            Image *AM;
            Image *Night;

            void loadTimeInfo(){
                AM = loadPng("romfs/gfx/office/ui/AM.png");
                Night = loadPng("romfs/gfx/office/ui/Night.png");
            }
            void unloadTimeInfo(){
                freeImage(AM);
                freeImage(Night);
            }


            Image *camFlip[4];

            void loadCamFlip(){
                camFlip[0] = loadPng("romfs/gfx/office/camera/animation/flip_0.png");
                camFlip[1] = loadPng("romfs/gfx/office/camera/animation/flip_1.png");
                camFlip[2] = loadPng("romfs/gfx/office/camera/animation/flip_2.png");
                camFlip[3] = loadPng("romfs/gfx/office/camera/animation/flip_3.png");
                //camFlip[4] = loadPng("romfs/gfx/office/camera/animation/flip_4.png");
                //camFlip[5] = loadPng("romfs/gfx/office/camera/animation/flip_5.png");
                //camFlip[6] = loadPng("romfs/gfx/office/camera/animation/flip_6.png");
                //camFlip[7] = loadPng("romfs/gfx/office/camera/animation/flip_7.png");
                //camFlip[8] = loadPng("romfs/gfx/office/camera/animation/flip_8.png");
                //camFlip[9] = loadPng("romfs/gfx/office/camera/animation/flip_9.png");
                //camFlip[10] = loadPng("romfs/gfx/office/camera/animation/flip_10.png");
            }
            void unloadCamFlip(){
                freeImage(camFlip[0]);
                freeImage(camFlip[1]);
                freeImage(camFlip[2]);
                freeImage(camFlip[3]);
                //freeImage(camFlip[4]);
                //freeImage(camFlip[5]);
                //freeImage(camFlip[6]);
                //freeImage(camFlip[7]);
                //freeImage(camFlip[8]);
                //freeImage(camFlip[9]);
                //freeImage(camFlip[10]);
            }


            Image *cams[11];

            float freddyPosition = 0;
            float bonniePosition = 0;
            float chicaPosition = 0;
            float foxyPosition = 0;

            bool loaded = false;

            //bool freddyPrior = false;
            //bool bonniePrior = false;
            //bool chicaPrior = false;
            //bool foxyPrior = false;

            /*
            bool cam1aloaded = true;
            bool cam1bloaded = false;
            bool cam1cloaded = false;

            bool cam2aloaded = false;
            bool cam2bloaded = false;

            bool cam3loaded = false;

            bool cam4aloaded = false;
            bool cam4bloaded = false;
            */

            //int whichCamera;

            void loadCams() {
                // Helper function to determine camera path
                auto getPath = [](const std::string& basePath, const std::string& suffix) -> std::string {
                    return "romfs/gfx/office/camera/" + basePath + suffix + ".png";
                };

                // Cam 1A
                if (freddyPosition > 0) freddyPosition = 0;
                if (freddyPosition == 0 && bonniePosition == 0 && chicaPosition == 0) {
                    cams[0] = loadPng(getPath("main/", "cam1a").c_str());
                } else if (freddyPosition == 0 && bonniePosition > 0 && chicaPosition == 0) {
                    cams[0] = loadPng(getPath("animatronic/cam1a/", "cam1a-freddy&chica").c_str());
                } else if (freddyPosition == 0 && bonniePosition == 0 && chicaPosition > 0) {
                    cams[0] = loadPng(getPath("animatronic/cam1a/", "cam1a-freddy&bonnie").c_str());
                } else if (freddyPosition == 0 && bonniePosition > 0 && chicaPosition > 0) {
                    cams[0] = loadPng((save::whichNight < 4)
                                        ? getPath("animatronic/cam1a/", "cam1a-freddy").c_str()
                                        : getPath("animatronic/cam1a/", "cam1a-freddystare").c_str());
                } else {
                    cams[0] = loadPng(getPath("animatronic/cam1a/", "cam1a-empty").c_str());
                }

                // Cam 1B
                if (bonniePosition == 1 && chicaPosition != 1 && freddyPosition != 1) {
                    cams[1] = loadPng(getPath("animatronic/cam1b/", "cam1b-bonnie").c_str());
                } else if (bonniePosition != 1 && chicaPosition == 1 && freddyPosition != 1) {
                    cams[1] = loadPng(getPath("animatronic/cam1b/", "cam1b-chica").c_str());
                } else if (freddyPosition == 1) {
                    cams[1] = loadPng(getPath("animatronic/cam1b/", "cam1b-freddy").c_str());
                } else {
                    cams[1] = loadPng(getPath("main/", "cam1b").c_str());
                }

                // Cam 1C
                int foxyPosInt = static_cast<int>(foxyPosition); // Cast to integer
                std::string cam1C;

                switch (foxyPosInt) {
                    case 0:
                        cam1C = "cam1c";
                        cams[2] = loadPng(getPath("main/", cam1C).c_str());
                        break;
                    case 1:
                        cam1C = "cam1c-foxy1";
                        cams[2] = loadPng(getPath("animatronic/cam1c/", cam1C).c_str());
                        break;
                    case 2:
                        cam1C = "cam1c-foxy2";
                        cams[2] = loadPng(getPath("animatronic/cam1c/", cam1C).c_str());
                        break;
                    default:
                        cam1C = "cam1c-foxy3";
                        cams[2] = loadPng(getPath("animatronic/cam1c/", cam1C).c_str());
                        break;
                }

                // Cam 2A
                cams[3] = (bonniePosition == 3)
                            ? loadPng(getPath("animatronic/cam2a/", "cam2a-bonnie").c_str())
                            : loadPng(getPath("main/", "cam2a").c_str());

                // Cam 2B
                cams[4] = (bonniePosition == 5)
                            ? loadPng(getPath("animatronic/cam2b/", "cam2b-bonnie").c_str())
                            : loadPng(getPath("main/", "cam2b").c_str());

                // Cam 3
                cams[5] = (bonniePosition == 4)
                            ? loadPng(getPath("animatronic/cam3/", "cam3-bonnie").c_str())
                            : loadPng(getPath("main/", "cam3").c_str());

                // Cam 4A
                if (chicaPosition == 3 && freddyPosition != 3) {
                    cams[6] = loadPng(getPath("animatronic/cam4a/", "cam4a-chica").c_str());
                } else if (chicaPosition == 4 && freddyPosition != 3) {
                    cams[6] = loadPng(getPath("animatronic/cam4a/", "cam4a-chicaclose").c_str());
                } else if (freddyPosition == 3) {
                    cams[6] = loadPng(getPath("animatronic/cam4a/", "cam4a-freddy").c_str());
                } else {
                    cams[6] = loadPng(getPath("main/", "cam4a").c_str());
                }

                // Cam 4B
                if (chicaPosition == 5 && freddyPosition != 4) {
                    cams[7] = loadPng(getPath("animatronic/cam4b/", "cam4b-chica").c_str());
                } else if (freddyPosition == 4) {
                    cams[7] = loadPng(getPath("animatronic/cam4b/", "cam4b-freddy").c_str());
                } else {
                    cams[7] = loadPng(getPath("main/", "cam4b").c_str());
                }

                // Cam 5
                cams[8] = (bonniePosition == 7)
                            ? loadPng((save::whichNight > 4)
                                            ? getPath("animatronic/cam5/", "cam5-bonnieclose").c_str()
                                            : getPath("animatronic/cam5/", "cam5-bonnie").c_str())
                            : loadPng(getPath("main/", "cam5").c_str());

                // Cam 6
                cams[9] = loadPng(getPath("main/", "cam6").c_str());

                // Cam 7
                if (chicaPosition == 7 && freddyPosition != 2) {
                    cams[10] = loadPng(getPath("animatronic/cam7/", "cam7-chica").c_str());
                } else if (chicaPosition == 8 && freddyPosition != 2) {
                    cams[10] = loadPng(getPath("animatronic/cam7/", "cam7-chicaclose").c_str());
                } else if (freddyPosition == 2) {
                    cams[10] = loadPng(getPath("animatronic/cam7/", "cam7-freddy").c_str());
                } else {
                    cams[10] = loadPng(getPath("main/", "cam7").c_str());
                }

                loaded = true;
            }



            void unloadCams(){
                freeImage(cams[0]);
                freeImage(cams[1]);
                freeImage(cams[2]);
                freeImage(cams[3]);
                freeImage(cams[4]);
                freeImage(cams[5]);
                freeImage(cams[6]);
                freeImage(cams[7]);
                freeImage(cams[8]);
                freeImage(cams[9]);
                freeImage(cams[10]);

                loaded = false;
            }


            Image *camNames[11];
            Image *camButtons[11];
            Image *reticle;
            Image *camBorder;
            Image *recording;
            Image *camMap;

            void loadCamUi(){
                camBorder = loadPng("romfs/gfx/office/ui/camera_border.png"); 
                camMap = loadPng("romfs/gfx/office/ui/camera-map.png");
                recording = loadPng("romfs/gfx/office/ui/recording.png");

                camNames[0] = loadPng("romfs/gfx/office/ui/cam-names/ShowStage.png");
                camNames[1] = loadPng("romfs/gfx/office/ui/cam-names/DiningArea.png");
                camNames[2] = loadPng("romfs/gfx/office/ui/cam-names/PirateCove.png");
                camNames[3] = loadPng("romfs/gfx/office/ui/cam-names/W-Hall.png");
                camNames[4] = loadPng("romfs/gfx/office/ui/cam-names/W-Hall-corner.png");
                camNames[5] = loadPng("romfs/gfx/office/ui/cam-names/Closet.png");
                camNames[6] = loadPng("romfs/gfx/office/ui/cam-names/E-Hall.png");
                camNames[7] = loadPng("romfs/gfx/office/ui/cam-names/E-Hall-corner.png");
                camNames[8] = loadPng("romfs/gfx/office/ui/cam-names/BackStage.png");
                camNames[9] = loadPng("romfs/gfx/office/ui/cam-names/Kitchen.png");
                camNames[10] = loadPng("romfs/gfx/office/ui/cam-names/Restrooms.png");

                camButtons[0] = loadPng("romfs/gfx/office/camera/main/buttons/cam1a.png");
                camButtons[1] = loadPng("romfs/gfx/office/camera/main/buttons/cam1b.png");
                camButtons[2] = loadPng("romfs/gfx/office/camera/main/buttons/cam1c.png");
                camButtons[3] = loadPng("romfs/gfx/office/camera/main/buttons/cam2a.png");
                camButtons[4] = loadPng("romfs/gfx/office/camera/main/buttons/cam2b.png");
                camButtons[5] = loadPng("romfs/gfx/office/camera/main/buttons/cam3.png");
                camButtons[6] = loadPng("romfs/gfx/office/camera/main/buttons/cam4a.png");
                camButtons[7] = loadPng("romfs/gfx/office/camera/main/buttons/cam4b.png");
                camButtons[8] = loadPng("romfs/gfx/office/camera/main/buttons/cam5.png");
                camButtons[9] = loadPng("romfs/gfx/office/camera/main/buttons/cam6.png");
                camButtons[10] = loadPng("romfs/gfx/office/camera/main/buttons/cam7.png");

                reticle = loadPng("romfs/gfx/office/camera/main/buttons/reticle.png");
            }
            void unloadCamUi(){
                freeImage(camBorder);
                freeImage(camMap);
                freeImage(recording);

                freeImage(camNames[0]);
                freeImage(camNames[1]);
                freeImage(camNames[2]);
                freeImage(camNames[3]);
                freeImage(camNames[4]);
                freeImage(camNames[5]);
                freeImage(camNames[6]);
                freeImage(camNames[7]);
                freeImage(camNames[8]);
                freeImage(camNames[9]);
                freeImage(camNames[10]);

                freeImage(camButtons[0]);
                freeImage(camButtons[1]);
                freeImage(camButtons[2]);
                freeImage(camButtons[3]);
                freeImage(camButtons[4]);
                freeImage(camButtons[5]);
                freeImage(camButtons[6]);
                freeImage(camButtons[7]);
                freeImage(camButtons[8]);
                freeImage(camButtons[9]);
                freeImage(camButtons[10]);

                freeImage(reticle);
            }
        }

        namespace customnight{
            Image *icons[4];
            Image *reticle;
            Image *instructions[2];
            Image *title;
            Image *arrows[2];
            Image *levelDesc;
            Image *difficulty;
            Image *names[4];
            Image *create;
            Image *exit;
            Image *goldFreddy;

            void loadIcons(){
                icons[0] = loadPng("romfs/gfx/customnight/icons/freddy.png");
                icons[1] = loadPng("romfs/gfx/customnight/icons/bonnie.png");
                icons[2] = loadPng("romfs/gfx/customnight/icons/chika.png");
                icons[3] = loadPng("romfs/gfx/customnight/icons/foxy.png");
            }
            void unloadIcons(){
                freeImage(icons[0]);
                freeImage(icons[1]);
                freeImage(icons[2]);
                freeImage(icons[3]);
            }

            void loadReticle(){
                reticle = loadPng("romfs/gfx/customnight/icons/reticle.png");
            }
            void unloadReticle(){
                freeImage(reticle);
            }

            void loadInstructions(){
                instructions[0] = loadPng("romfs/gfx/customnight/ui/L.png");
                instructions[1] = loadPng("romfs/gfx/customnight/ui/R.png");
            }
            void unloadInstructions(){
                freeImage(instructions[0]);
                freeImage(instructions[1]);
            }

            void loadTitle(){
                title = loadPng("romfs/gfx/customnight/ui/title.png");
            }
            void unloadTitle(){
                freeImage(title);
            }

            void loadArrows(){
                arrows[0] = loadPng("romfs/gfx/customnight/ui/left.png");
                arrows[1] = loadPng("romfs/gfx/customnight/ui/right.png");
            }
            void unloadArrows(){
                freeImage(arrows[0]);
                freeImage(arrows[1]);
            }

            void loadText(){
                levelDesc = loadPng("romfs/gfx/customnight/ui/AI.png");
                difficulty = loadPng("romfs/gfx/customnight/ui/difficulty.png");
            }
            void unloadText(){
                freeImage(levelDesc);
                freeImage(difficulty);
            }

            void loadNames(){
                names[0] = loadPng("romfs/gfx/customnight/ui/freddy.png");
                names[1] = loadPng("romfs/gfx/customnight/ui/bonnie.png");
                names[2] = loadPng("romfs/gfx/customnight/ui/chika.png");
                names[3] = loadPng("romfs/gfx/customnight/ui/foxy.png");
            }
            void unloadNames(){
                freeImage(names[0]);
                freeImage(names[1]);
                freeImage(names[2]);
                freeImage(names[3]);
            }

            void loadActions(){
                create = loadPng("romfs/gfx/customnight/ui/create.png");
                exit = loadPng("romfs/gfx/customnight/ui/exit.png");
            }
            void unloadActions(){
                freeImage(create);
                freeImage(exit);
            }

            void loadGoldenFreddy(){
                goldFreddy = loadPng("romfs/gfx/customnight/ui/gold.png");
            }
            void unloadGoldenFreddy(){
                //i purposfully unload while rendering so boom, crash
                freeImage(goldFreddy);
            }
        }
    }

    namespace n_jumpscare{
        Image *jumpscareAnim[9];
        float whichJumpscare;

        //int ThreadIdJ;
        //int PspThreadStatus = 1;

        bool loaded = false;
        //bool wasFreddy = false;

        void loadFreddy(){
            jumpscareAnim[0] = loadPng("romfs/gfx/jumpscare/freddy/0.png");
            jumpscareAnim[1] = loadPng("romfs/gfx/jumpscare/freddy/1.png");
            jumpscareAnim[2] = loadPng("romfs/gfx/jumpscare/freddy/2.png");
            jumpscareAnim[3] = loadPng("romfs/gfx/jumpscare/freddy/3.png");
            jumpscareAnim[4] = loadPng("romfs/gfx/jumpscare/freddy/4.png");
            jumpscareAnim[5] = loadPng("romfs/gfx/jumpscare/freddy/5.png");
            jumpscareAnim[6] = loadPng("romfs/gfx/jumpscare/freddy/6.png");
            jumpscareAnim[7] = loadPng("romfs/gfx/jumpscare/freddy/7.png");
            jumpscareAnim[8] = loadPng("romfs/gfx/jumpscare/freddy/8.png");

            loaded = true;
        }

        void loadBonnie(){
            jumpscareAnim[0] = loadPng("romfs/gfx/jumpscare/bonnie/0.png");
            jumpscareAnim[1] = loadPng("romfs/gfx/jumpscare/bonnie/1.png");
            jumpscareAnim[2] = loadPng("romfs/gfx/jumpscare/bonnie/2.png");
            jumpscareAnim[3] = loadPng("romfs/gfx/jumpscare/bonnie/3.png");
            jumpscareAnim[4] = loadPng("romfs/gfx/jumpscare/bonnie/4.png");
            jumpscareAnim[5] = loadPng("romfs/gfx/jumpscare/bonnie/5.png");
            jumpscareAnim[6] = loadPng("romfs/gfx/jumpscare/bonnie/6.png");
            jumpscareAnim[7] = loadPng("romfs/gfx/jumpscare/bonnie/7.png");
            jumpscareAnim[8] = loadPng("romfs/gfx/jumpscare/bonnie/8.png");

            loaded = true;
        }

        void loadChica(){
            jumpscareAnim[0] = loadPng("romfs/gfx/jumpscare/chica/0.png");
            jumpscareAnim[1] = loadPng("romfs/gfx/jumpscare/chica/1.png");
            jumpscareAnim[2] = loadPng("romfs/gfx/jumpscare/chica/2.png");
            jumpscareAnim[3] = loadPng("romfs/gfx/jumpscare/chica/3.png");
            jumpscareAnim[4] = loadPng("romfs/gfx/jumpscare/chica/4.png");
            jumpscareAnim[5] = loadPng("romfs/gfx/jumpscare/chica/5.png");
            jumpscareAnim[6] = loadPng("romfs/gfx/jumpscare/chica/6.png");
            jumpscareAnim[7] = loadPng("romfs/gfx/jumpscare/chica/7.png");
            jumpscareAnim[8] = loadPng("romfs/gfx/jumpscare/chica/8.png");

            loaded = true;
        }

        void loadFoxy(){
            jumpscareAnim[0] = loadPng("romfs/gfx/jumpscare/foxy/0.png");
            jumpscareAnim[1] = loadPng("romfs/gfx/jumpscare/foxy/1.png");
            jumpscareAnim[2] = loadPng("romfs/gfx/jumpscare/foxy/2.png");
            jumpscareAnim[3] = loadPng("romfs/gfx/jumpscare/foxy/3.png");
            jumpscareAnim[4] = loadPng("romfs/gfx/jumpscare/foxy/4.png");
            jumpscareAnim[5] = loadPng("romfs/gfx/jumpscare/foxy/5.png");
            jumpscareAnim[6] = loadPng("romfs/gfx/jumpscare/foxy/6.png");
            jumpscareAnim[7] = loadPng("romfs/gfx/jumpscare/foxy/7.png");
            jumpscareAnim[8] = loadPng("romfs/gfx/jumpscare/foxy/8.png");

            loaded = true;
        }

        void loadJumpscare(){

            //unloadJumpscare();

            if (whichJumpscare == 1){
                loadFreddy();
            }
            else if (whichJumpscare == 2){
                loadBonnie();
            }
            else if (whichJumpscare == 3){
                loadChica();
            }
            else if (whichJumpscare == 4){
                loadFoxy();
            }

            
        }
        void unloadJumpscare(){
            if (loaded == true){
                freeImage(jumpscareAnim[0]);
                freeImage(jumpscareAnim[1]);
                freeImage(jumpscareAnim[2]);
                freeImage(jumpscareAnim[3]);
                freeImage(jumpscareAnim[4]);
                freeImage(jumpscareAnim[5]);
                freeImage(jumpscareAnim[6]);
                freeImage(jumpscareAnim[7]);
                freeImage(jumpscareAnim[8]);

                loaded = false;
            }
        }
    }
}

namespace officeImage{
    Image *office1Sprites[5];
    Image *office2Sprites[5];

    void loadOffice1Sprites(){
        office1Sprites[0] = loadPng("romfs/gfx/office/chuncks/nothing/office_1.png");
        office1Sprites[1] = loadPng("romfs/gfx/office/chuncks/left-empty/office_1.png");
        office1Sprites[2] = loadPng("romfs/gfx/office/chuncks/right-empty/office_1.png");
        office1Sprites[3] = loadPng("romfs/gfx/office/chuncks/left-bonnie/office_1.png");
        office1Sprites[4] = loadPng("romfs/gfx/office/chuncks/right-chika/office_1.png");
    }
    void unloadOffice1Sprites(){
        freeImage(office1Sprites[0]);
        freeImage(office1Sprites[1]);
        freeImage(office1Sprites[2]);
        freeImage(office1Sprites[3]);
        freeImage(office1Sprites[4]);
    }


    void loadOffice2Sprites(){
        office2Sprites[0] = loadPng("romfs/gfx/office/chuncks/nothing/office_2.png");
        office2Sprites[1] = loadPng("romfs/gfx/office/chuncks/left-empty/office_2.png");
        office2Sprites[2] = loadPng("romfs/gfx/office/chuncks/right-empty/office_2.png");
        office2Sprites[3] = loadPng("romfs/gfx/office/chuncks/left-bonnie/office_2.png");
        office2Sprites[4] = loadPng("romfs/gfx/office/chuncks/right-chika/office_2.png");
    }
    void unloadOffice2Sprites(){
        freeImage(office2Sprites[0]);
        freeImage(office2Sprites[1]);
        freeImage(office2Sprites[2]);
        freeImage(office2Sprites[3]);
        freeImage(office2Sprites[4]);
    }
}

namespace text{
    namespace global{
        Image *nightNumbersNormal[10];
        Image *nightNumbersPixel[10];
        Image *symbols;

        void loadNightText(){
            nightNumbersNormal[0] = loadPng("romfs/gfx/global/numbers/normal/0-2.png");
            nightNumbersNormal[1] = loadPng("romfs/gfx/global/numbers/normal/1.png");
            nightNumbersNormal[2] = loadPng("romfs/gfx/global/numbers/normal/2.png");
            nightNumbersNormal[3] = loadPng("romfs/gfx/global/numbers/normal/3.png");
            nightNumbersNormal[4] = loadPng("romfs/gfx/global/numbers/normal/4.png");
            nightNumbersNormal[5] = loadPng("romfs/gfx/global/numbers/normal/5.png");
            nightNumbersNormal[6] = loadPng("romfs/gfx/global/numbers/normal/6.png");
            nightNumbersNormal[7] = loadPng("romfs/gfx/global/numbers/normal/7.png");
            nightNumbersNormal[8] = loadPng("romfs/gfx/global/numbers/normal/8.png");
            nightNumbersNormal[9] = loadPng("romfs/gfx/global/numbers/normal/9.png");

            nightNumbersPixel[0] = loadPng("romfs/gfx/global/numbers/pixel/0.png");
            nightNumbersPixel[1] = loadPng("romfs/gfx/global/numbers/pixel/1.png");
            nightNumbersPixel[2] = loadPng("romfs/gfx/global/numbers/pixel/2.png");
            nightNumbersPixel[3] = loadPng("romfs/gfx/global/numbers/pixel/3.png");
            nightNumbersPixel[4] = loadPng("romfs/gfx/global/numbers/pixel/4.png");
            nightNumbersPixel[5] = loadPng("romfs/gfx/global/numbers/pixel/5.png");
            nightNumbersPixel[6] = loadPng("romfs/gfx/global/numbers/pixel/6.png");
            nightNumbersPixel[7] = loadPng("romfs/gfx/global/numbers/pixel/7.png");
            nightNumbersPixel[8] = loadPng("romfs/gfx/global/numbers/pixel/8.png");
            nightNumbersPixel[9] = loadPng("romfs/gfx/global/numbers/pixel/9.png");

            symbols = loadPng("romfs/gfx/global/numbers/symbols/%.png");
        }
        void unloadNightText(){
            freeImage(nightNumbersNormal[0]);
            freeImage(nightNumbersNormal[1]);
            freeImage(nightNumbersNormal[2]);
            freeImage(nightNumbersNormal[3]);
            freeImage(nightNumbersNormal[4]);
            freeImage(nightNumbersNormal[5]);
            freeImage(nightNumbersNormal[6]);
            freeImage(nightNumbersNormal[7]);
            freeImage(nightNumbersNormal[8]);
            freeImage(nightNumbersNormal[9]);


            freeImage(nightNumbersPixel[0]);
            freeImage(nightNumbersPixel[1]);
            freeImage(nightNumbersPixel[2]);
            freeImage(nightNumbersPixel[3]);
            freeImage(nightNumbersPixel[4]);
            freeImage(nightNumbersPixel[5]);
            freeImage(nightNumbersPixel[6]);
            freeImage(nightNumbersPixel[7]);
            freeImage(nightNumbersPixel[8]);
            freeImage(nightNumbersPixel[9]);

            freeImage(symbols);
        }
    }
}