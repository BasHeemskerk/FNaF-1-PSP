#include "included/customnight.hpp"

namespace customnight{

    float reticlePosition = 0;
    float actualReticlePosition;
    std::string editing = "freddy";

    float crashDelay = 300;
    bool mustCrash = false;

    void reset(){
        reticlePosition = 0;
        actualReticlePosition = 60;
        editing = "freddy";
    }

    namespace render {
        // Helper function to draw sprites with null checks
        inline void drawCheckedSprite(Image *sprite, int srcX, int srcY, int width, int height, int destX, int destY, int options) {
            if (sprite) {
                drawSpriteAlpha(srcX, srcY, width, height, sprite, destX, destY, options);
            } else {
                std::cerr << "Warning: Null sprite passed to drawCheckedSprite!" << std::endl;
            }
        }

        void renderHeads() {
            if (!mustCrash) {
                for (int i = 0; i < 4; ++i) {
                    drawCheckedSprite(sprite::UI::customnight::icons[i], 0, 0, 60, 60, 60 + (i * 100), 80, 0);
                }
            }
        }

        void renderReticle() {
            if (!mustCrash) {
                drawCheckedSprite(sprite::UI::customnight::reticle, 0, 0, 60, 60, actualReticlePosition, 80, 0);
            }
        }

        void renderInstructions() {
            if (!mustCrash) {
                drawCheckedSprite(sprite::UI::customnight::instructions[0], 0, 0, 13, 20, 10, 10, 0);
                drawCheckedSprite(sprite::UI::customnight::instructions[1], 0, 0, 13, 20, 457, 10, 0);
            }
        }

        void renderTitle() {
            if (!mustCrash) {
                drawCheckedSprite(sprite::UI::customnight::title, 0, 0, 175, 24, 153, 25, 0);
            }
        }

        void renderNames() {
            if (!mustCrash) {
                for (int i = 0; i < 4; ++i) {
                    drawCheckedSprite(sprite::UI::customnight::names[i], 0, 0, 60, 17, 60 + (i * 100), 63 + (i == 0 || i == 3 ? 1 : 0), 0);
                }
            }
        }

        void renderArrows() {
            if (!mustCrash) {
                for (int i = 0; i < 4; ++i) {
                    int xBase = 60 + (i * 100);
                    drawCheckedSprite(sprite::UI::customnight::arrows[0], 0, 0, 13, 20, xBase, 160, 0);
                    drawCheckedSprite(sprite::UI::customnight::arrows[1], 0, 0, 13, 20, xBase + 48, 160, 0);
                }
            }
        }

        void renderText() {
            if (!mustCrash) {
                for (int i = 0; i < 4; ++i) {
                    drawCheckedSprite(sprite::UI::customnight::levelDesc, 0, 0, 60, 10, 60 + (i * 100), 145, 0);
                }
                drawCheckedSprite(sprite::UI::customnight::difficulty, 0, 0, 300, 11, 60, 212, 0);
            }
        }

        void renderLevels() {
            if (!mustCrash) {
                struct Animatronic {
                    float totalLevel;
                    int levelOnes;
                    int levelTenths;
                    int offsetX;
                };

                const Animatronic animatronics[] = {
                    {animatronic::freddy::totalLevel, animatronic::freddy::levelOnes, animatronic::freddy::levelTenths, 88},
                    {animatronic::bonnie::totalLevel, animatronic::bonnie::levelOnes, animatronic::bonnie::levelTenths, 188},
                    {animatronic::chika::totalLevel, animatronic::chika::levelOnes, animatronic::chika::levelTenths, 288},
                    {animatronic::foxy::totalLevel, animatronic::foxy::levelOnes, animatronic::foxy::levelTenths, 388},
                };

                for (const auto& ani : animatronics) {
                    drawCheckedSprite(text::global::nightNumbersNormal[ani.levelOnes], 0, 0, 20, 20, ani.offsetX, 160, 0);
                    if (ani.totalLevel > 9) {
                        drawCheckedSprite(text::global::nightNumbersNormal[ani.levelTenths], 0, 0, 20, 20, ani.offsetX - 15, 160, 0);
                    }
                }
            }
        }

        void renderActions() {
            if (!mustCrash) {
                drawCheckedSprite(sprite::UI::customnight::create, 0, 0, 78, 18, 380, 242, 0);
                drawCheckedSprite(sprite::UI::customnight::exit, 0, 0, 69, 18, 10, 242, 0);
            }
        }

        void renderGoldenFreddy() {
            if (mustCrash) {
                std::cout << "CRASHHHH (well its not an actual crash, just exits the game)" << std::endl;
                drawCheckedSprite(sprite::UI::customnight::goldFreddy, 0, 0, 480, 272, 0, 0, 0);

                if (crashDelay <= 0) {
                    sceKernelExitGame();
                } else {
                    crashDelay -= 1;
                }
            }
        }
    }

    namespace edit {
        // Define a map for plus and minus operations.
        std::unordered_map<std::string, std::function<void()>> operations = {
            {"freddy", []() {
                if (animatronic::freddy::totalLevel < 20) {
                    animatronic::freddy::totalLevel += 1;
                    animatronic::freddy::levelOnes += 1;
                }
            }},
            {"bonnie", []() {
                if (animatronic::bonnie::totalLevel < 20) {
                    animatronic::bonnie::totalLevel += 1;
                    animatronic::bonnie::levelOnes += 1;
                }
            }},
            {"chika", []() {
                if (animatronic::chika::totalLevel < 20) {
                    animatronic::chika::totalLevel += 1;
                    animatronic::chika::levelOnes += 1;
                }
            }},
            {"foxy", []() {
                if (animatronic::foxy::totalLevel < 20) {
                    animatronic::foxy::totalLevel += 1;
                    animatronic::foxy::levelOnes += 1;
                }
            }}
        };

        std::unordered_map<std::string, std::function<void()>> decrementOperations = {
            {"freddy", []() {
                if (animatronic::freddy::totalLevel > 0) {
                    animatronic::freddy::totalLevel -= 1;
                    animatronic::freddy::levelOnes -= 1;
                }
            }},
            {"bonnie", []() {
                if (animatronic::bonnie::totalLevel > 0) {
                    animatronic::bonnie::totalLevel -= 1;
                    animatronic::bonnie::levelOnes -= 1;
                }
            }},
            {"chika", []() {
                if (animatronic::chika::totalLevel > 0) {
                    animatronic::chika::totalLevel -= 1;
                    animatronic::chika::levelOnes -= 1;
                }
            }},
            {"foxy", []() {
                if (animatronic::foxy::totalLevel > 0) {
                    animatronic::foxy::totalLevel -= 1;
                    animatronic::foxy::levelOnes -= 1;
                }
            }}
        };

        std::unordered_map<std::string, std::function<void()>> valueAdjustments = {
            {"freddy", []() {
                if (animatronic::freddy::levelOnes == 10) {
                    animatronic::freddy::levelOnes = 0;
                    animatronic::freddy::levelTenths += 1;
                } else if (animatronic::freddy::levelOnes < 0 && animatronic::freddy::levelTenths > 0) {
                    animatronic::freddy::levelOnes = 9;
                    animatronic::freddy::levelTenths -= 1;
                }
            }},
            {"bonnie", []() {
                if (animatronic::bonnie::levelOnes == 10) {
                    animatronic::bonnie::levelOnes = 0;
                    animatronic::bonnie::levelTenths += 1;
                } else if (animatronic::bonnie::levelOnes < 0 && animatronic::bonnie::levelTenths > 0) {
                    animatronic::bonnie::levelOnes = 9;
                    animatronic::bonnie::levelTenths -= 1;
                }
            }},
            {"chika", []() {
                if (animatronic::chika::levelOnes == 10) {
                    animatronic::chika::levelOnes = 0;
                    animatronic::chika::levelTenths += 1;
                } else if (animatronic::chika::levelOnes < 0 && animatronic::chika::levelTenths > 0) {
                    animatronic::chika::levelOnes = 9;
                    animatronic::chika::levelTenths -= 1;
                }
            }},
            {"foxy", []() {
                if (animatronic::foxy::levelOnes == 10) {
                    animatronic::foxy::levelOnes = 0;
                    animatronic::foxy::levelTenths += 1;
                } else if (animatronic::foxy::levelOnes < 0 && animatronic::foxy::levelTenths > 0) {
                    animatronic::foxy::levelOnes = 9;
                    animatronic::foxy::levelTenths -= 1;
                }
            }}
        };

        void plus() {
            if (mustCrash == false) {
                if (operations.find(editing) != operations.end()) {
                    operations[editing]();
                }
                editValue();
            }
        }

        void minus() {
            if (mustCrash == false) {
                if (decrementOperations.find(editing) != decrementOperations.end()) {
                    decrementOperations[editing]();
                }
                editValue();
            }
        }

        void editValue() {
            if (valueAdjustments.find(editing) != valueAdjustments.end()) {
                valueAdjustments[editing]();
            }
        }
    }

    namespace reticle{
        std::string dir = "none";

        void moveReticleLeft(){
            if (mustCrash == false){
                if (reticlePosition > 0){
                    reticlePosition -= 1;
                }
            }
        }
        void moveReticleRight(){
            if (mustCrash == false){
                if (reticlePosition < 3){
                    reticlePosition += 1;
                }
            }
        }
        void updatePosition(){
            if (mustCrash == false){
                if (reticlePosition == 0){
                    actualReticlePosition = 60;
                    editing = "freddy";
                }
                else if (reticlePosition == 1){
                    actualReticlePosition = 160;
                    editing = "bonnie";
                }
                else if (reticlePosition == 2){
                    actualReticlePosition = 260;
                    editing = "chika";
                }
                else if (reticlePosition == 3){
                    actualReticlePosition = 360;
                    editing = "foxy";
                }
            }
        }
    }

    namespace actions{

        void create(){
            if (animatronic::freddy::totalLevel == 1 && animatronic::bonnie::totalLevel == 9 && animatronic::chika::totalLevel == 8 && animatronic::foxy::totalLevel == 7){
                if (mustCrash == false){
                    state::isCustomNight = false;

                    sfx::jumpscare::loadJumpscare2Sound();

                    sprite::UI::customnight::unloadIcons();
                    sprite::UI::customnight::unloadReticle();
                    sprite::UI::customnight::unloadInstructions();
                    sprite::UI::customnight::unloadTitle();
                    sprite::UI::customnight::unloadArrows();
                    sprite::UI::customnight::unloadText();
                    sprite::UI::customnight::unloadNames();
                    sprite::UI::customnight::unloadActions();

                    sfx::jumpscare::playJumpscare2Sound();

                    state::isCustomNight = true;

                    mustCrash = true;
                }
            }
            else{
                save::whichNight = 7;
                state::isCustomNight = false;
                
                sprite::UI::customnight::unloadIcons();
                sprite::UI::customnight::unloadReticle();
                sprite::UI::customnight::unloadInstructions();
                sprite::UI::customnight::unloadTitle();
                sprite::UI::customnight::unloadArrows();
                sprite::UI::customnight::unloadText();
                sprite::UI::customnight::unloadNames();
                sprite::UI::customnight::unloadActions();
                sprite::UI::customnight::unloadGoldenFreddy();

                sprite::nightinfo::loadNightInfoSprite();
                state::isNightinfo = true;
            }
        }
        void exit(){
            if (mustCrash == false){
                if (save::whichNight > 5){
                    save::readData();
                }
                state::isCustomNight = false;

                sprite::UI::customnight::unloadIcons();
                sprite::UI::customnight::unloadReticle();
                sprite::UI::customnight::unloadInstructions();
                sprite::UI::customnight::unloadTitle();
                sprite::UI::customnight::unloadArrows();
                sprite::UI::customnight::unloadText();
                sprite::UI::customnight::unloadNames();
                sprite::UI::customnight::unloadActions();
                sprite::UI::customnight::unloadGoldenFreddy();

                image::menu::loadMenuBackground();
                image::menu::loadLogo();
                image::menu::loadCopyright();
                image::menu::loadTextAndCursor();
                sprite::menu::loadStar();

                menu::menuCursor::moveCursor();

                music::menu::loadMenuMusic();
                music::menu::playMenuMusic();

                state::isMenu = true;
            }
        }
    }
}