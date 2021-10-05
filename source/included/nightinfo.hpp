#include "global.hpp"
#include "audio.hpp"
#include "image2.hpp"
#include "save.hpp"
#include "state.hpp"
#include "office.hpp"
#include "power.hpp"
#include "animatronic.hpp"

namespace nightinfo{

    void reset();
    
    namespace render{
        void renderNightinfo();
    }
    namespace next{
        void preloadOffice();
        void initOffice();
    }
}