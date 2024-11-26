#include "global.hpp"
#include "image2.hpp"
#include "animatronic.hpp"
#include "save.hpp"
#include "state.hpp"
#include "menu.hpp"

namespace customnight{

    void reset();
    
    namespace render {
        // Helper function to draw sprites with null checks
        inline void drawCheckedSprite(Image *sprite, int srcX, int srcY, int width, int height, int destX, int destY, int options);
        void renderHeads();
        void renderReticle();
        void renderInstructions();
        void renderTitle();
        void renderNames();
        void renderArrows();
        void renderText();
        void renderLevels();
        void renderActions();
        void renderGoldenFreddy();
    }

    namespace edit{
        void plus();
        void minus();

        void editValue();
    }

    namespace reticle{
        //extern float reticlePosition;
        //extern float actualReticlePosition;
        //extern std::string dir;

        void moveReticleRight();
        void moveReticleLeft();
        void updatePosition();
        void loadTitle();
        void unloadTitle();
    }

    namespace actions{
        void create();
        void exit();
    }
}