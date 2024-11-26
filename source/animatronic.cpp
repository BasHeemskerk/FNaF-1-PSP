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

        switch (jumpscaring){
            case false:
                reloaded = false;
                isMoving = true;

                sprite::UI::office::unloadCams();
                sprite::UI::office::loadCams();

                if (usingCams == true){
                    sfx::office::playMove();
                }

                reloaded = true;
                isMoving = false;
                break;
            default:
                break;
        }
        
        ThreadIdR = sceKernelExitThread(PspThreadStatus);

        return 0;
    }

    void setReload(){
        switch (jumpscaring){
            case false:
                ThreadIdR = sceKernelCreateThread("load_thread", reloadCams, 0x11, 0xFA0, 0, NULL);
                sceKernelStartThread(ThreadIdR, 0, NULL);
                break;
            default:
                break;
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


    namespace freddy {
        int levelOnes = 0;
        int levelTenths = 0;
        float totalLevel = 0;
        int randomNumber = 0;

        float position = 0;
        float delay = 650;

        bool atDoor = false;

        void wait() {
            if (delay > 0) {
                delay -= 1;
            } else {
                generateRandom();
                delay = 650;
            }
        }

        void incrementDifficulty() {
            if (save::whichNight == 3) {
                totalLevel = rand() % 3; // Set totalLevel randomly for Night 3
            }
        }

        void generateRandom() {
            randomNumber = rand() % 20; // Generate random number in [0, 19]
            evaluateMovement();
        }

        void evaluateMovement() {
            if (shouldMoveOrAttack()) {
                if (!atDoor) {
                    decideNextMove();
                }
            }
        }

        bool shouldMoveOrAttack() {
            return (randomNumber < totalLevel || position == 6);
        }

        void decideNextMove() {
            if (position >= 6) {
                handleAtDoor();
            } else if (!usingCams && !isMoving) {
                moveForward();
            }
        }

        void handleAtDoor() {
            atDoor = true;

            if (!jumpscaring && !rightClosed && usingCams) {
                triggerJumpscare();
            } else if (!jumpscaring && rightClosed) {
                blockAttack();
            }
        }

        void triggerJumpscare() {
            jumpscaring = true;
            sprite::n_jumpscare::whichJumpscare = 1; // Set Freddy's jumpscare
            unloadMain(); // Transition to jumpscare sequence
        }

        void blockAttack() {
            atDoor = false;
            position = 6; // Reset position to 6 after attack is blocked
            reloadPosition();
        }

        void moveForward() {
            position += 1;
            sfx::office::playLaugh(); // Play Freddy's laugh sound
            reloadPosition();
        }

        void reloadPosition() {
            sprite::UI::office::freddyPosition = position;
            setReload();
        }
    }
    namespace bonnie {
        int levelOnes = 0;
        int levelTenths = 0;
        float totalLevel = 0;
        int randomNumber = 0;

        bool inOtherRoom = false;
        float position = 0;
        float delay = 389;

        bool atDoor = false;

        void wait() {
            if (delay > 0) {
                delay -= 1;
            } else {
                generateRandom();
                delay = 389;
            }
        }

        void incrementDifficulty() {
            totalLevel += 1;
        }

        void generateRandom() {
            randomNumber = rand() % 20; // Generate random number in [0, 19]
            processMovementDecision();
        }

        void processMovementDecision() {
            if (shouldMoveOrAttack()) {
                if (!atDoor) {
                    if (position == 7) {
                        resetToStart();
                    } else {
                        evaluateOpportunity();
                    }
                }
            }
        }

        bool shouldMoveOrAttack() {
            return (randomNumber < totalLevel || position == 6);
        }

        void resetToStart() {
            if (inOtherRoom) {
                position = 2;
                inOtherRoom = false;
                reloadPosition();
            }
        }

        void evaluateOpportunity() {
            if (randomNumber == 2 && (position == 2 || position == 3)) {
                moveToRoom(7);
            } else if (position >= 6 && position != 7) {
                handleAtDoor();
            } else if (!isMoving) {
                moveForward();
            }
        }

        void moveToRoom(int targetRoom) {
            position = targetRoom;
            inOtherRoom = true;
            isMoving = true;
            reloadPosition();
        }

        void handleAtDoor() {
            atDoor = true;

            if (!jumpscaring && !leftClosed) {
                triggerJumpscare();
            } else if (!jumpscaring && leftClosed) {
                blockAttack();
            }
        }

        void triggerJumpscare() {
            jumpscaring = true;
            sprite::n_jumpscare::whichJumpscare = 2;
            unloadMain(); // Transition to jumpscare sequence
        }

        void blockAttack() {
            atDoor = false;
            position = 1;
            reloadPosition();
        }

        void moveForward() {
            position += 1;
            reloadPosition();
        }

        void reloadPosition() {
            sprite::UI::office::bonniePosition = position;
            setReload();
        }
    }

    namespace chika {
        int levelOnes = 0;
        int levelTenths = 0;
        float totalLevel = 0;
        int randomNumber = 0;

        bool inOtherRoom = false;

        float position = 0;

        float delay = 432;

        bool atDoor = false;

        void wait() {
            if (delay > 0) {
                delay -= 1;
            } else {
                inOtherRoom = false;
                generateRandom();
                delay = 432;
            }
        }

        void incrementDifficulty() {
            totalLevel += 1;
        }

        void generateRandom() {
            randomNumber = rand() % 20; // Generate a random number in [0, 19]
            processMovementDecision();
        }

        void processMovementDecision() {
            if (shouldMoveOrAttack()) {
                if (!atDoor) {
                    if (position == 8 || position == 9) {
                        resetToStart();
                    } else {
                        evaluateOpportunity();
                    }
                }
            }
        }

        bool shouldMoveOrAttack() {
            return (randomNumber < totalLevel || position == 6);
        }

        void resetToStart() {
            if (inOtherRoom) {
                position = 1;
                inOtherRoom = false;
                reloadPosition();
            }
        }

        void evaluateOpportunity() {
            if (randomNumber == 3 && position == 1) {
                moveToRoom(7);
            } else if (randomNumber == 6 && position == 2) {
                moveToRoom(9); // Possibly kitchen?
            } else if (position >= 6 && position != 7 && position != 8 && position != 9) {
                handleAtDoor();
            } else if (!isMoving) {
                moveForward();
            }
        }

        void moveToRoom(int targetRoom) {
            position = targetRoom;
            inOtherRoom = true;
            isMoving = true;
            reloadPosition();
        }

        void handleAtDoor() {
            atDoor = true;

            if (!jumpscaring && !rightClosed) {
                triggerJumpscare();
            } else if (!jumpscaring && rightClosed) {
                blockAttack();
            }
        }

        void triggerJumpscare() {
            jumpscaring = true;
            sprite::n_jumpscare::whichJumpscare = 3;
            unloadMain(); // Transition to jumpscare sequence
        }

        void blockAttack() {
            atDoor = false;
            position = 1;
            reloadPosition();
        }

        void moveForward() {
            position += 1;
            reloadPosition();
        }

        void reloadPosition() {
            sprite::UI::office::chicaPosition = position;
            setReload();
        }
    }

    namespace foxy {
        int levelOnes = 0;
        int levelTenths = 0;
        float totalLevel = 0;
        int randomNumber = 0;

        float position = 0;

        float delay = 460;

        bool atDoor = false;
        bool wasAttacking = false;

        void wait() {
            if (delay > 0) {
                delay -= 1;
            } else {
                generateRandomEvent();
                delay = 460;
            }
        }

        void incrementDifficulty() {
            // Currently no implementation. Add logic here if needed.
        }

        void generateRandomEvent() {
            randomNumber = rand() % 20; // Generate a random number in [0, 19]
            processRandomEvent();
        }

        void processRandomEvent() {
            if (randomNumber <= totalLevel || (position >= 3 && !isMoving() && !atDoor)) {
                attemptMoveOrAttack();
            }
        }

        void attemptMoveOrAttack() {
            if (position >= 4) {
                handleAtDoor();
            } else {
                handleMovement();
            }
        }

        void handleAtDoor() {
            if (!atDoor) {
                atDoor = true;
                wasAttacking = true;
            }

            if (atDoor && !jumpscaring) {
                if (!leftClosed) {
                    triggerJumpscare();
                } else {
                    blockAttack();
                }
            }
        }

        void handleMovement() {
            if (!isMoving() && ((position < 4 && !usingCams) || (position >= 3 && usingCams))) {
                position += 1;
                reloadPosition();
            }
        }

        void triggerJumpscare() {
            jumpscaring = true;
            sprite::n_jumpscare::whichJumpscare = 4;
            unloadMain(); // Transition to jumpscare sequence
        }

        void blockAttack() {
            sfx::office::playKnock();
            resetToIdle();
        }

        void resetToIdle() {
            atDoor = false;
            position = 0;
            reloadPosition();
        }

        void reloadPosition() {
            sprite::UI::office::foxyPosition = position;
            setReload();
        }

        inline bool isMoving() {
            return isMoving;
        }
    }


    void setDefault() {
        static const int levels[6][4] = {
            {0, 0, 0, 0},   // Night 1
            {0, 3, 1, 1},   // Night 2
            {1, 0, 5, 2},   // Night 3
            {1, 2, 4, 6},   // Night 4
            {3, 5, 7, 5},   // Night 5
            {4, 10, 12, 6}  // Night 6
        };

        switch (save::whichNight) {
            case 1: case 2: case 3: case 4: case 5: case 6: {
                int nightIndex = save::whichNight - 1;

                freddy::totalLevel = levels[nightIndex][0];
                bonnie::totalLevel = levels[nightIndex][1];
                chika::totalLevel = levels[nightIndex][2];
                foxy::totalLevel = levels[nightIndex][3];
                break;
            }
            case 7:
                std::cout << "Night 7: nothing to set." << std::endl;
                break;
            default:
                std::cout << "Invalid night: " << save::whichNight << ". No levels set." << std::endl;
                break;
        }
    }
}