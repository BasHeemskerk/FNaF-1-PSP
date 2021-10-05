#include "global.hpp"
#include "audio.hpp"
#include "image2.hpp"
#include "state.hpp"

//#include "sixam.hpp" //we only run the reset part, nothing more!
#include "dead.hpp"


namespace jumpscare{

    //extern float whichJumpscare;
    extern bool reloaded;
    extern bool loading;

    void reset();

    namespace render{
        void renderJumpscare();
    }

    namespace animate{
        void animateJumpscare();
        void initDeathScreen();
    }

    namespace load{
        void loadWithDelay();
    }
}