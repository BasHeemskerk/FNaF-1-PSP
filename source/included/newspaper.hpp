#include "global.hpp"
#include "image2.hpp"
#include "audio.hpp"
#include "state.hpp"

namespace newspaper{

    void reset();
    
    namespace render{
        void renderNewspaper();
    }
    namespace next{
        void initNightinfo();
    }
}