#include "global.hpp"
#include "image2.hpp"
#include "audio.hpp"
#include "save.hpp"
#include "menu.hpp"
#include "state.hpp"

namespace dead{

    void reset();
    
    namespace n_static{
        void renderStatic();
        void animateStatic();
    }

    namespace wait{
        void waitForFrames();
        void initMenu();
    }
}