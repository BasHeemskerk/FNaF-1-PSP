#include "global.hpp"
#include "image2.hpp"
#include "audio.hpp"
#include "state.hpp"
#include "jumpscare.hpp"

#include "camera.hpp"
#include "office.hpp"
#include "power.hpp"

//#include "sixam.hpp"

namespace powerout{

    void reset();
    
    namespace resetAll{
        void reset();
    }
    namespace render{
        void renderPowerout();
    }
    namespace animate{
        void animatePowerOut();
        void initJumpscare();
    }
}