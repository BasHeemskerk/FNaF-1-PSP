#include "global.hpp"
#include "image2.hpp"
#include "audio.hpp"
#include "save.hpp"
#include "state.hpp"
#include "jumpscare.hpp"

namespace animatronic{

    extern bool isMoving;
    extern bool reloaded;
    extern bool usingCams;
    extern bool leftClosed;
    extern bool rightClosed;

    extern bool jumpscaring;
    extern bool unloaded;

    void forceAnimatronicAiReset();
    
    void reset();

    void runAiLoop();

    void unloadMain();
    void initJumpscare();

    namespace freddy{
        extern int levelOnes;
        extern int levelTenths;
        extern float totalLevel;

        extern float position;

        extern float delay;

        extern bool atDoor;

        void wait();

        void incrementDifficulty();

        void genRandom();

        void compare();

        void oppurtunity();

        void reload();
    }
    namespace bonnie{
        extern int levelOnes;
        extern int levelTenths;
        extern float totalLevel;

        extern float position;

        extern float delay;

        extern bool inOtherRoom;

        extern bool atDoor;

        void wait();

        void incrementDifficulty();

        void genRandom();

        void compare();

        void oppurtunity();

        void reload();
    }
    namespace chika{
        extern int levelOnes;
        extern int levelTenths;
        extern float totalLevel;

        extern float position;

        extern float delay;

        extern bool inOtherRoom;

        extern bool atDoor;

        void wait();

        void incrementDifficulty();

        void genRandom();

        void compare();

        void oppurtunity();

        void reload();
    }
    namespace foxy{
        extern int levelOnes;
        extern int levelTenths;
        extern float totalLevel;

        extern float position;

        extern float delay;

        extern bool atDoor;
        extern bool wasAttacking;

        void wait();

        void incrementDifficulty();

        void genRandom();

        void compare();

        void oppurtunity();

        void reload();
    }

    void setDefault();
}