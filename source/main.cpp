#include "included/global.hpp"

//globally used
#include "included/image2.hpp"
#include "included/audio.hpp"
#include "included/state.hpp"
#include "included/save.hpp"
#include "included/power.hpp"
#include "included/time.hpp"
#include "included/camera.hpp"

//only for certain areas
#include "included/menu.hpp"
#include "included/newspaper.hpp"
#include "included/nightinfo.hpp"
#include "included/office.hpp"
#include "included/customnight.hpp"
#include "included/sixam.hpp"
#include "included/dead.hpp"
#include "included/ending.hpp"
#include "included/jumpscare.hpp"
#include "included/powerout.hpp"


#include <cstdlib>

using namespace std;

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) 
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2)

PSP_MODULE_INFO("FNaF 1 PSP v1.3.1", 0, 1, 0);

PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-1024);

#if _PSP_FW_VERSION >= 200
PSP_HEAP_SIZE_KB(20480);
#endif

static unsigned int __attribute__((aligned(16))) DisplayList[262144];

int exit_callback(int arg1, int arg2, void* common){
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void* argp){
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();
    return 0;
}

void setupCallbacks(){
    int thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, NULL);
    if (thid >= 0){
        sceKernelStartThread(thid, 0, NULL);
    }
}

void* fbp0 = NULL;
void* fbp1 = NULL;
void* renderTarget = NULL;
void* zbp = NULL;

void InitGU(){    
    fbp0 = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
    fbp1 = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
    zbp = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_4444);

    renderTarget = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);

    sceGuInit();
    sceGuStart(GU_DIRECT,DisplayList);

    sceGuDrawBuffer(GU_PSM_5650,fbp0,BUF_WIDTH);
    sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,fbp1,BUF_WIDTH);
    sceGuDepthBuffer(zbp,BUF_WIDTH);

    sceGuDepthRange(65535,0);
    sceGuDepthMask(GU_FALSE);

    sceGuOffset(2048 - (SCR_WIDTH / 2),2048 - (SCR_HEIGHT / 2));

    sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);

    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

    sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);

    sceGuAlphaFunc(GU_GREATER,0,0xff);
    sceGuEnable(GU_ALPHA_TEST);

    sceGuDepthFunc(GU_GEQUAL);
    sceGuEnable(GU_DEPTH_TEST);

    sceGuFrontFace(GU_CW);

    sceGuTexMode(GU_PSM_5650,0,0,0); 
    sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
    sceGuTexFilter(GU_NEAREST,GU_NEAREST);

    sceGuEnable(GU_CULL_FACE);
    
    sceGuEnable(GU_TEXTURE_2D);

    sceGuEnable(GU_DITHER);

    sceGuEnable(GU_CLIP_PLANES);
    
    sceGuEnable(GU_LIGHTING);
    sceGuEnable(GU_LIGHT0);
    sceGuEnable(GU_LIGHT1);
    sceGuEnable(GU_LIGHT2);
    sceGuEnable(GU_LIGHT3);
    
    sceGuEnable(GU_FOG);

    sceGuEnable(GU_BLEND);
    sceGuBlendFunc(GU_ADD,GU_SRC_ALPHA,GU_ONE_MINUS_SRC_ALPHA,0,0);

    sceGuShadeModel(GU_SMOOTH); 

    sceGuFinish();

    sceGuSync(0,0);

    sceDisplayWaitVblankStart();

    sceGuDisplay(GU_TRUE);
}

void initEngine(){
    setupCallbacks();
    pspDebugScreenInit();

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    InitGU();

    //oslInit();
    VirtualFileInit();
    oslInitAudio();
}

void initGame(){
    //state::isMenu = false;

    save::file();
    //save::readData();

    image::global::n_static::loadStatic();

    image::menu::loadMenuBackground();
    image::menu::loadLogo();
    sprite::menu::loadStar();
    image::menu::loadTextAndCursor();
    image::menu::loadCopyright();
    text::global::loadNightText();

    menu::menuCursor::moveCursor();

    music::menu::loadMenuMusic();
    music::menu::playMenuMusic();

    //state::isMenu = true;
}

bool reseted = true;

void resetMain(){

    if (reseted == false){
        sprite::UI::office::freddyPosition = 0;
        sprite::UI::office::bonniePosition = 0;
        sprite::UI::office::chicaPosition = 0;
        sprite::UI::office::foxyPosition = 0;
                
        timegame::reset();
        office::reset();
        camera::reset();
        power::reset();
        animatronic::reset();
        nightinfo::reset();
        sixam::reset();
        jumpscare::reset();
        powerout::reset();
        newspaper::reset();
        dead::reset();
        customnight::reset();
        ending::reset();

        reseted = true;
    }
}

auto main() -> int{

    SceCtrlData ctrlData;

    initEngine();
    initGame();

    float cursorMoveTime = 5;


    while(true){

        sceCtrlReadBufferPositive(&ctrlData, 1);

        //running = isRunning();

        sceGuStart(GU_DIRECT,DisplayList);

        // clear screen

        sceGuClearColor(0x000000);
        sceGuClearDepth(0);
        sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

        // setup aspect ratio

        sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumPerspective(70.0f,16.0f/9.0f,0.5f,1000.0f);
            
            // setup camera
        sceGumMatrixMode(GU_VIEW);
        {
            ScePspFVector3 pos = {0, 0, 0};
            ScePspFVector3 rot = { 0, 0, 0 };

            sceGumLoadIdentity();
            sceGumTranslate(&pos);
            sceGumRotateXYZ(&rot);
        }

        if (state::isMenu == true){

            menu::render::renderBackground();
            menu::render::animateBackground();
            menu::render::renderLogo();
            menu::render::renderCopyright();
            menu::render::renderStars();
            menu::menuCursor::renderCursor();

            menu::n_static::renderStatic();
            menu::n_static::animateStatic();

            if (ctrlData.Buttons & PSP_CTRL_CROSS){
                menu::menuCursor::select();
            }

            if (cursorMoveTime <= 0){
                if (ctrlData.Buttons & PSP_CTRL_UP){
                    menu::menuCursor::cursorPos -= 1;
                    menu::menuCursor::moveCursor();
                }
                else if (ctrlData.Buttons & PSP_CTRL_DOWN){
                    menu::menuCursor::cursorPos += 1;
                    menu::menuCursor::moveCursor();
                }

                cursorMoveTime = 10;
            }
            else{
                cursorMoveTime -= 1;
            }

            resetMain();
        }
        else if (state::isNewspaper == true){
            newspaper::render::renderNewspaper();
            newspaper::next::initNightinfo();

            resetMain();
        }
        else if (state::isNightinfo == true){
            nightinfo::render::renderNightinfo();

            nightinfo::next::preloadOffice();
            nightinfo::next::initOffice();

            resetMain();
        }
        else if (state::isOffice == true){
            if (camera::isUsing == false || camera::closing == true){
                office::render::renderOffice();
                office::main::moveOffice();

                office::lights::lights();

                office::buttons::setButtonFrame();

                office::render::renderButtons();
                office::render::renderDoors();
            }

            camera::render::renderCamFlip();
            if (camera::isUsing == true && animatronic::reloaded == true && sprite::UI::office::loaded == true && animatronic::foxy::position != 3 && animatronic::foxy::position != 4){
                camera::render::renderCamera();
            }

            animatronic::runAiLoop();
            animatronic::forceAnimatronicAiReset();

            //camera::system::loading::setupUnload();

            camera::render::renderUi();

            camera::n_static::renderStatic();
            camera::n_static::animateStatic();

            power::render::renderPowerLeft();
            power::update::drainConstant();
            power::update::checkDrain();

            timegame::render::renderTime();
            timegame::update::updateTime();


            if (office::closingLeft == true){
                office::doors::closeLeft();
            }
            else if (office::openingLeft == true){
                office::doors::openLeft();
            }

            if (office::closingRight == true){
                office::doors::closeRight();
            }
            else if (office::openingRight == true){
                office::doors::openRight();
            }

            if (camera::opening == true){
                camera::animation::openCams();
            }
            else if (camera::closing == true){
                camera::animation::closeCams();
            }


            if (camera::isUsing == false){
                if (ctrlData.Buttons & PSP_CTRL_LEFT){
                    office::dir = "right";
                }
                else if (ctrlData.Buttons & PSP_CTRL_RIGHT){
                    office::dir = "left";
                }
                else{
                    office::dir = "none";
                }

                if (ctrlData.Buttons & PSP_CTRL_SQUARE){
                    office::buttonState = "down";
                }
                else{
                    office::buttonState = "up";
                }
                
                if (ctrlData.Buttons & PSP_CTRL_CROSS){
                    if (office::doorButtonState == "up"){
                        office::doors::doors();
                    }
                    
                    office::doorButtonState = "held";
                }
                else{
                    office::doorButtonState = "up";
                }
            }

            if (ctrlData.Buttons & PSP_CTRL_CIRCLE){
                if (call::stopped == false){
                    call::unloadPhoneCalls();
                }
            }

            if (ctrlData.Buttons & PSP_CTRL_TRIANGLE){
                if (camera::buttonState == "up"){
                    camera::animation::camera();
                }

                camera::buttonState = "held";
            }
            else if (ctrlData.Buttons & PSP_CTRL_UP){
                if (camera::buttonState == "up"){
                    camera::system::up();
                }

                camera::buttonState = "held";
            }
            else if (ctrlData.Buttons & PSP_CTRL_DOWN){
                if (camera::buttonState == "up"){
                    camera::system::down();
                }

                camera::buttonState = "held";
            }
            else if (ctrlData.Buttons & PSP_CTRL_LEFT){
                if (camera::buttonState == "up"){
                    camera::system::left();
                }

                camera::buttonState = "held";
            }
            else if (ctrlData.Buttons & PSP_CTRL_RIGHT){
                if (camera::buttonState == "up"){
                    camera::system::right();
                }

                camera::buttonState = "held";
            }
            else{
                camera::buttonState = "up";
            }

            reseted = false;

            //sprite::n_jumpscare::whichJumpscare = jumpscare::whichJumpscare;
        }
        else if (state::isCustomNight == true){
            customnight::render::renderHeads();
            customnight::render::renderReticle();
            customnight::render::renderInstructions();
            customnight::render::renderTitle();
            customnight::render::renderNames();
            customnight::render::renderArrows();
            customnight::render::renderText();
            customnight::render::renderLevels();
            customnight::render::renderActions();
            customnight::render::renderGoldenFreddy();

            customnight::reticle::updatePosition();

            if (cursorMoveTime <= 0){
                if (ctrlData.Buttons & PSP_CTRL_RTRIGGER){
                    customnight::reticle::moveReticleRight();
                    cursorMoveTime = 10;
                }
                else if (ctrlData.Buttons & PSP_CTRL_LTRIGGER){
                    customnight::reticle::moveReticleLeft();
                    cursorMoveTime = 10;
                }
                
                if (ctrlData.Buttons & PSP_CTRL_RIGHT){
                    customnight::edit::plus();
                    cursorMoveTime = 10;
                }
                else if (ctrlData.Buttons & PSP_CTRL_LEFT){
                    customnight::edit::minus();
                    cursorMoveTime = 10;
                }

                if (ctrlData.Buttons & PSP_CTRL_CROSS){
                    customnight::actions::create();
                    cursorMoveTime = 10;
                }
                else if (ctrlData.Buttons & PSP_CTRL_CIRCLE){
                    customnight::actions::exit();
                    cursorMoveTime = 10;
                }
            }
            else{
                cursorMoveTime -= 1;
            }

            resetMain();
        }
        else if (state::isSixAm == true){
            sixam::render::renderSixAm();
            sixam::animate::wait();
            sixam::next::wait();

            resetMain();
        }
        else if (state::isPowerOut == true){
            powerout::render::renderPowerout();
            powerout::animate::animatePowerOut();

            resetMain();
        }
        else if (state::isJumpscare == true){
            jumpscare::load::loadWithDelay();
            jumpscare::render::renderJumpscare();
            jumpscare::animate::animateJumpscare();

            reseted = false;

            //resetMain();
        }
        else if (state::isEnding == true){
            ending::render::renderEnding();
            ending::wait::waitForFrames();

            resetMain();
        }
        else if (state::isDead == true){
            dead::n_static::renderStatic();
            dead::n_static::animateStatic();

            dead::wait::waitForFrames();

            resetMain();
        }
        
        sceDisplayWaitVblankStart();
            
        sceGuFinish();
        sceGuSync(0,0);

        sceGuSwapBuffers();
    }
}