#include "global.hpp"
#include "image2.hpp"
#include "save.hpp"
#include "camera.hpp"
#include "state.hpp"

#include "office.hpp"
//#include "powerout.hpp"

namespace power{
    extern int usage;

    void reset();

    namespace render{
        void renderPowerLeft();
    }

    namespace update{
        void checkDrain();
        void drainConstant();
        void setDrainTime();
        void initPowerOut();
    }
}