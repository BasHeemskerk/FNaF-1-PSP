#include "global.hpp"
#include "image2.hpp"
#include "audio.hpp"
#include "office.hpp"

namespace camera{
    extern int whichCamera;
    extern bool isUsing;

    extern bool opening;
    extern bool closing;

    extern std::string buttonState;

    void reset();

    namespace render{
        void renderCamFlip();
        void renderCamera();
        void renderUi();
    }

    namespace n_static{
        void renderStatic();
        void animateStatic();
    }

    namespace animation{
        
        void camera();
        void openCams();
        void closeCams();
    }

    namespace system{

        void left();
        void right();
        void up();
        void down();

        //void plus();
        //void minus();
        void setReticle();
    }
}