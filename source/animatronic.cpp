#include "included/animatronic.hpp"

namespace animatronic{

    bool isMoving = false;
    bool reloaded = true;
    bool usingCams = false;
    bool leftClosed = false;
    bool rightClosed = false;

    bool jumpscaring = false;

    bool locked = false;

    int ThreadIdR;
    int PspThreadStatus = 1;

    //int whichJumpscare = 0;

    bool unloaded = false;

    float waitBeforeForceReset = 450;

    //float wait = 0;
    //float maxWait = 1000;

    void reset(){

        freddy::levelOnes = 0;
        freddy::levelTenths = 0;
        freddy::totalLevel = 0;
        freddy::atDoor = false;

        bonnie::levelOnes = 0;
        bonnie::levelTenths = 0;
        bonnie::totalLevel = 0;
        bonnie::atDoor = false;

        chika::levelOnes = 0;
        chika::levelTenths = 0;
        chika::totalLevel = 0;
        chika::atDoor = false;

        foxy::levelOnes = 0;
        foxy::levelTenths = 0;
        foxy::totalLevel = 0;
        foxy::atDoor = false;

        freddy::position = 0;
        bonnie::position = 0;
        chika::position = 0;
        foxy::position = 0;

        //setDefault();

        isMoving = false;
        reloaded = true;
        usingCams = false;
        leftClosed = false;
        rightClosed = false;

        jumpscaring = false;

        unloaded = false;

        locked = false;

        waitBeforeForceReset = 450;

        sprite::n_jumpscare::whichJumpscare = 0;

        //wait = 0;
    }

    void forceAnimatronicAiReset(){
        if (waitBeforeForceReset <= 0 && jumpscaring == false){

            if (reloaded == true && isMoving == true){
                isMoving = false;
            }
            if (isMoving == true && reloaded == true && freddy::delay > 0 && bonnie::delay > 0 && chika::delay > 0 && foxy::delay > 0){
                isMoving = false;
            }

            if (freddy::position > 6){
                freddy::position = 6;
            }
            if (bonnie::position > 6 && bonnie::position != 7){
                bonnie::position = 6;
            }
            if (chika::position > 6 && chika::position != 7 && chika::position != 8 && chika::position != 9){
                chika::position = 6;
            }
            if (foxy::position > 4){
                foxy::position = 4;
            }

            if (foxy::position == 0){
                foxy::position = 0;
            }

            if (bonnie::inOtherRoom == true && bonnie::position != 7){
                bonnie::inOtherRoom = false;
            }
            if (chika::inOtherRoom == true && chika::position != 7 && chika::position != 8 && chika::position != 9){
                chika::inOtherRoom = false;
            }

            if (freddy::atDoor == true && freddy::position < 6){
                freddy::atDoor = false;
            }
            if (bonnie::atDoor == true && bonnie::position < 6){
                bonnie::atDoor = false;
            }
            if (chika::atDoor == true && chika::position < 6){
                chika::atDoor = false;
            }
            if (foxy::atDoor == true && foxy::position < 4){
                foxy::atDoor = false;
            }

            std::cout << "forcefully reseted AI" << std::endl;

            waitBeforeForceReset = 450;
        }
        else{
            waitBeforeForceReset -= 1;
        }
    }

    int reloadCams(SceSize args, void* argp){

        if (jumpscaring == false){

            std::cout << "moving = true" << std::endl;
            reloaded = false;
            isMoving = true;

            sprite::UI::office::unloadCams();
            sprite::UI::office::loadCams();

            if (usingCams == true){
                sfx::office::playMove();
            }

            reloaded = true;
            isMoving = false;

            std::cout << "moving = false" << std::endl;
        }
        
        ThreadIdR = sceKernelExitThread(PspThreadStatus);

        return 0;
    }

    void setReload(){
        if (jumpscaring == false){
            ThreadIdR = sceKernelCreateThread("load_thread", reloadCams, 0x11, 0xFA0, 0, NULL);
            sceKernelStartThread(ThreadIdR, 0, NULL);
        }
    }
    
    void runAiLoop(){
        freddy::wait();
        if (save::whichNight == 2){
            freddy::incrementDifficulty();
        }

        bonnie::wait();
        chika::wait();
        if (save::whichNight > 1){
            foxy::wait();
        }
    }

    void unloadMain(){

        //locked = true;

        state::isOffice = false;

        sfx::office::unloadSfx();
        ambience::office::unloadAmbience();
        ambience::office::unloadFanSound();

        sprite::UI::office::unloadCams();
        sprite::UI::office::unloadCamFlip();

        officeImage::unloadOffice1Sprites();
        //officeImage::unloadOffice2Sprites();

        sfx::jumpscare::loadJumpscareSound();

        initJumpscare();
    }

    void initJumpscare(){
        state::isJumpscare = true;
    }


    namespace freddy{
        int levelOnes = 0;
        int levelTenths = 0;
        float totalLevel = 0;
        int randomNumber;

        float position;

        float delay = 650;

        bool atDoor = false;

        void wait(){
            if (delay <= 0){
                genRandom();
                delay = 650;
            }
            else{
                delay -= 1;
            }
        }

        void incrementDifficulty(){
            if (save::whichNight == 3){
                totalLevel = rand() % 3;
            }
        }

        void genRandom(){
            randomNumber = rand() % 20;
            //randomNumber += 1;

            compare();
        }

        void compare(){
            if (randomNumber < totalLevel || position == 6){
                if (atDoor == false){
                    oppurtunity();
                }
            }
        }

        void oppurtunity(){
            if (position >= 6){
                atDoor = true;
                
                if (atDoor == true && jumpscaring == false && rightClosed == false && usingCams == true){
                    jumpscaring = true;
                    sprite::n_jumpscare::whichJumpscare = 1;
                    unloadMain();

                    //position = 0;
                }
                else if (atDoor == true && jumpscaring == false && rightClosed == true){
                    atDoor = false;
                    position = 6;
                    reload();
                }
            }
            else{
                if (usingCams == false && isMoving == false){
                    position += 1;
                    sfx::office::playLaugh();
                    reload();
                }
            }
        }

        void reload(){
            sprite::UI::office::freddyPosition = position;
            setReload();
        }
    }
    namespace bonnie{
        int levelOnes = 0;
        int levelTenths = 0;
        float totalLevel = 0;
        int randomNumber;

        bool inOtherRoom = false;

        float position;

        float delay = 389;

        bool atDoor = false;

        void wait(){
            if (delay <= 0){
                genRandom();
                delay = 389;
            }
            else{
                delay -= 1;
            }
        }
        
        void incrementDifficulty(){
            totalLevel += 1;
        }

        void genRandom(){
            randomNumber = rand() % 20;
            //randomNumber += 1;

            compare();
        }
        
        void compare(){
            if (randomNumber < totalLevel || position == 6){
                if (position != 7){
                    if (inOtherRoom == false && atDoor == false){
                        oppurtunity();
                    }
                }
                else if (position == 7){
                    if (inOtherRoom == true && atDoor == false){
                        position = 2;
                        reload();
                        inOtherRoom = false;
                    }
                }
            }
        }

        void oppurtunity(){
            if (randomNumber == 2){
                if (position == 2 || position == 3){
                    position = 7;
                    inOtherRoom = true;
                    isMoving = true;
                    reload();
                }
            }

            if (position == 5){
                sfx::office::playWalk();
            }
            if (position >= 6 && position != 7){
                atDoor = true;
                
                if (atDoor == true && jumpscaring == false && leftClosed == false){
                    jumpscaring = true;
                    sprite::n_jumpscare::whichJumpscare = 2;
                    unloadMain();

                    //position = 0;
                }
                else if (atDoor == true && jumpscaring == false && leftClosed == true){
                    atDoor = false;
                    position = 1;
                    reload();
                }
            }
            else{
                if (isMoving == false){
                    position += 1;
                    reload();
                }
            }
        }

        void reload(){
            sprite::UI::office::bonniePosition = position;
            setReload();
        }
    }
    namespace chika{
        int levelOnes = 0;
        int levelTenths = 0;
        float totalLevel = 0;
        int randomNumber;

        bool inOtherRoom = false;

        float position;

        float delay = 432;

        bool atDoor = false;

        void wait(){
            if (delay <= 0){
                inOtherRoom = false;
                genRandom();
                delay = 432;
            }
            else{
                delay -= 1;
            }
        }

        void incrementDifficulty(){
            totalLevel += 1;
        }

        void genRandom(){
            randomNumber = rand() % 20;
            //randomNumber += 1;

            compare();
        }

        void compare(){
            if (randomNumber < totalLevel || position == 6){
                if (position != 8 && position != 9){
                    if (inOtherRoom == false && atDoor == false){
                        oppurtunity();
                    }
                }
                
                if (position == 8 && position != 9){
                    if (inOtherRoom == true && atDoor == false){
                        position = 1;
                        inOtherRoom = false;
                        reload();
                    }
                }
                else if (position == 9 && position != 8){
                    if (inOtherRoom == true && atDoor == false){
                        position = 1;
                        inOtherRoom = false;
                        reload();
                    }
                }
            }
        }

        void oppurtunity(){
            if (randomNumber == 3 && position == 1){
                position = 7;
                inOtherRoom = true;
                isMoving = true;
                reload();
            }
            else if (randomNumber == 6 && position == 2){
                position = 9;
                //sfx::office::playKitchen();
                inOtherRoom = true;
                isMoving = true;
                reload();
            }

            if (position == 5){
                sfx::office::playWalk();
            }

            if (position >= 6 && position != 7 && position != 8 && position != 9){
                atDoor = true;
                
                if (atDoor == true && jumpscaring == false && rightClosed == false){
                    jumpscaring = true;
                    sprite::n_jumpscare::whichJumpscare = 3;
                    unloadMain();

                    //position = 0;
                }
                else if (atDoor == true && jumpscaring == false && rightClosed == true){
                    atDoor = false;
                    position = 1;
                    reload();
                }
            }
            else{
                if (isMoving == false){
                    position += 1;
                    reload();
                }
            }
        }

        void reload(){
            sprite::UI::office::chicaPosition = position;
            setReload();
        }
    }
    namespace foxy{
        int levelOnes = 0;
        int levelTenths = 0;
        float totalLevel = 0;
        int randomNumber;

        float position;

        float delay = 460;
        //float attackDelay = 200;

        bool atDoor = false;
        bool wasAttacking = false;

        void wait(){
            if (delay <= 0){
                genRandom();
                delay = 460;
            }
            else{
                delay -= 1;
            }
        }

        void incrementDifficulty(){
            //nothing?
        }

        void genRandom(){
            randomNumber = rand() % 20;
            //randomNumber += 1;

            compare();
        }

        void compare(){
            if (randomNumber <= totalLevel){
                if (isMoving == false && atDoor == false){
                    oppurtunity();
                    isMoving = true;
                }
            }
            else if (randomNumber > totalLevel){
                if (position == 3 || position == 4){
                    if (isMoving == false && atDoor == false){
                        oppurtunity();
                        isMoving = true;
                    }
                }
            }
        }

        void oppurtunity(){
            if (position == 3){
                sfx::office::playRun();
            }
            
            if (position >= 4){
                if (atDoor == false){
                    atDoor = true;
                }
                if (wasAttacking == false){
                    wasAttacking = true;
                }
                    
                if (atDoor == true && jumpscaring == false && leftClosed == false){
                    jumpscaring = true;
                    sprite::n_jumpscare::whichJumpscare = 4;
                    unloadMain();

                    //position = 0;
                }
                else if (atDoor == true && jumpscaring == false && leftClosed == true){
                    sfx::office::playKnock();
                    atDoor = false;
                    position = 0;
                    reload();
                }
            }
            else{
                if ((position < 4 && usingCams == false && isMoving == false) || (position == 3 && usingCams == true && isMoving == false) || (position == 4 && usingCams == true && isMoving == false)){
                    position += 1;
                    reload();
                }
            }
        }

        void reload(){
            sprite::UI::office::foxyPosition = position;
            setReload();
        }
    }

    void setDefault(){
        if (save::whichNight == 1){
            freddy::totalLevel = 0;
            bonnie::totalLevel = 0;
            chika::totalLevel = 0;
            foxy::totalLevel = 0;
        }
        else if (save::whichNight == 2){
            freddy::totalLevel = 0;
            bonnie::totalLevel = 3;
            chika::totalLevel = 1;
            foxy::totalLevel = 1;
        }
        else if (save::whichNight == 3){
            freddy::totalLevel = 1;
            bonnie::totalLevel = 0;
            chika::totalLevel = 5;
            foxy::totalLevel = 2;
        }
        else if (save::whichNight == 4){
            freddy::totalLevel = 1;
            bonnie::totalLevel = 2;
            chika::totalLevel = 4;
            foxy::totalLevel = 6;
        }
        else if (save::whichNight == 5){
            freddy::totalLevel = 3;
            bonnie::totalLevel = 5;
            chika::totalLevel = 7;
            foxy::totalLevel = 5;
        }
        else if (save::whichNight == 6){
            freddy::totalLevel = 4;
            bonnie::totalLevel = 10;
            chika::totalLevel = 12;
            foxy::totalLevel = 6;
        }
        else if (save::whichNight == 7){
            std::cout << "night 7 nothing to set" << std::endl;
        }
    }
}