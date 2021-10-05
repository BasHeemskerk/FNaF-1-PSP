#include "global.hpp"
#include "audio.hpp"
#include "image2.hpp"
#include "animatronic.hpp"

namespace office{
    extern int wichOfficeFrame;
    extern std::string dir;
    extern std::string state;
    extern std::string buttonState;
    extern std::string doorButtonState;

    extern float usageCountdown;
    extern bool leftEdge;
    extern bool rightEdge;

    extern bool leftOn;
    extern bool rightOn;
    extern bool leftClosed;
    extern bool rightClosed;

    extern bool closingLeft;
    extern bool openingLeft;
    extern bool closingRight;
    extern bool openingRight;

    void reset();


    namespace render{
        void renderOffice();
        void renderButtons();
        void renderDoors();
    }

    namespace buttons{
        void setButtonFrame();
    }
    
    namespace main{
        void setX();
        void moveOffice();
    }

    namespace lights{
        void lights();
    }

    namespace doors{
        void doors();
        void closeLeft();
        void openLeft();
        void closeRight();
        void openRight();
    }

    //void animateLeft();
}