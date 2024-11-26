#include "global.hpp"
#include "image2.hpp"
#include "save.hpp"
#include "state.hpp"
#include "audio.hpp"

namespace menu{
    namespace render{
        void renderBackground();
        void animateBackground();
        void renderCopyright();
        void renderLogo();
        void renderStars();
    }

    namespace n_static{
        void renderStatic();
        void animateStatic();
    }

    namespace menuCursor{
        extern int cursorPos;

        void renderCursor();
        void moveCursor();
        void select();

        void initNewspaper();
        void initNightinfo();
        void initCustomNight();
    }
}

