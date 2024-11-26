#include "global.hpp"
#include "image2.hpp"
#include "audio.hpp"
#include "state.hpp"
#include "save.hpp"
#include "power.hpp"
#include "camera.hpp"

#include "nightinfo.hpp"
#include "menu.hpp"
#include "office.hpp"

namespace sixam{

    void reset();

    namespace saveIt{
        void saveTheData();
    }
    namespace render{
        void renderSixAm();
    }
    namespace animate{
        void wait();
    }
    namespace next{
        void wait();
        void resetGameScene();
        void clearRest();
        void initNightinfo();
        void initEnding();
        void initMenu();
    }
}