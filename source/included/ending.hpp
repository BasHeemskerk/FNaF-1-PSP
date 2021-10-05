#include "global.hpp"
#include "image2.hpp"
#include "audio.hpp"
#include "menu.hpp"
#include "save.hpp"

namespace ending{

    void reset();
    
    namespace render{
        void renderEnding();
    }

    namespace wait{
        void waitForFrames();
        void initMenu();
    }
}