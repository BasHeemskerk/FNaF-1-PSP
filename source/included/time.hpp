#include "global.hpp"
#include "image2.hpp"
#include "save.hpp"
#include "animatronic.hpp"
#include "state.hpp"
#include "sixam.hpp"

namespace timegame{

    extern int gtime;

    void reset();
    
    namespace render{
        void renderTime();
    }
    namespace update{
        void updateTime();
        void initSixAm();
    }
}