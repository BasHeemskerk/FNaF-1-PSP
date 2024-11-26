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

PSP_MODULE_INFO("FNaF 1 PSP v1.4.0", 0, 1, 0);

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

float cursorMoveTime = 5;

void handleMenuState(SceCtrlData ctrlData){
    menu::render::renderBackground();
    menu::render::animateBackground();
    menu::render::renderLogo();
    menu::render::renderCopyright();
    menu::render::renderStars();
    menu::menuCursor::renderCursor();

    menu::n_static::renderStatic();
    menu::n_static::animateStatic();

    if (cursorMoveTime <= 0){
        switch (ctrlData.Buttons){
            case PSP_CTRL_CROSS:
                menu::menuCursor::select();
                cursorMoveTime = 7;
                break;
            case PSP_CTRL_UP:
                menu::menuCursor::cursorPos -= 1;
                menu::menuCursor::moveCursor();
                cursorMoveTime = 7;
                break;
            case PSP_CTRL_DOWN:
                menu::menuCursor::cursorPos += 1;
                menu::menuCursor::moveCursor();
                cursorMoveTime = 7;
                break;
            default:
                break;
        }
    }
    else{
        cursorMoveTime -= 1;
    }

    resetMain();
}

void handleNewspaperState(){
    newspaper::render::renderNewspaper();
    newspaper::next::initNightinfo();

    resetMain();
}

void handleNightInfoState(){
    nightinfo::render::renderNightinfo();

    nightinfo::next::preloadOffice();
    nightinfo::next::initOffice();

    resetMain();
}

void handleOfficeState(SceCtrlData ctrlData) {
    // Render the office when the camera is not in use or closing
    if (!camera::isUsing || camera::closing) {
        office::render::renderOffice();
        office::main::moveOffice();
        office::lights::lights();
        office::buttons::setButtonFrame();
        office::render::renderButtons();
        office::render::renderDoors();
    }

    // Render camera flipping and UI
    camera::render::renderCamFlip();
    if (camera::isUsing && animatronic::reloaded && sprite::UI::office::loaded &&
        animatronic::foxy::position != 3 && animatronic::foxy::position != 4) {
        camera::render::renderCamera();
    }

    // Run AI logic
    animatronic::runAiLoop();
    animatronic::forceAnimatronicAiReset();

    // Render UI and static effects
    camera::render::renderUi();
    camera::n_static::renderStatic();
    camera::n_static::animateStatic();

    // Handle power updates
    power::render::renderPowerLeft();
    power::update::drainConstant();
    power::update::checkDrain();

    // Render and update time
    timegame::render::renderTime();
    timegame::update::updateTime();

    // Door animations
    if (office::closingLeft) {
        office::doors::closeLeft();
    } else if (office::openingLeft) {
        office::doors::openLeft();
    }

    if (office::closingRight) {
        office::doors::closeRight();
    } else if (office::openingRight) {
        office::doors::openRight();
    }

    // Camera animations
    if (camera::opening) {
        camera::animation::openCams();
    } else if (camera::closing) {
        camera::animation::closeCams();
    }

    // Office directional controls
    if (!camera::isUsing) {
        switch (ctrlData.Buttons) {
            case PSP_CTRL_LEFT:
                office::dir = "right";
                break;
            case PSP_CTRL_RIGHT:
                office::dir = "left";
                break;
            default:
                office::dir = "none";
                break;
        }

        office::buttonState = (ctrlData.Buttons & PSP_CTRL_SQUARE) ? "down" : "up";

        if (ctrlData.Buttons & PSP_CTRL_CROSS) {
            if (office::doorButtonState == "up") {
                office::doors::doors();
            }
            office::doorButtonState = "held";
        } else {
            office::doorButtonState = "up";
        }
    }

    // Handle phone call stop
    if (ctrlData.Buttons & PSP_CTRL_CIRCLE) {
        if (!call::stopped) {
            call::unloadPhoneCalls();
        }
    }

    // Camera directional and button controls
    switch (ctrlData.Buttons) {
        case PSP_CTRL_TRIANGLE:
            if (camera::buttonState == "up") {
                camera::animation::camera();
            }
            camera::buttonState = "held";
            break;

        case PSP_CTRL_UP:
            if (camera::buttonState == "up") {
                camera::system::up();
            }
            camera::buttonState = "held";
            break;

        case PSP_CTRL_DOWN:
            if (camera::buttonState == "up") {
                camera::system::down();
            }
            camera::buttonState = "held";
            break;

        case PSP_CTRL_LEFT:
            if (camera::buttonState == "up") {
                camera::system::left();
            }
            camera::buttonState = "held";
            break;

        case PSP_CTRL_RIGHT:
            if (camera::buttonState == "up") {
                camera::system::right();
            }
            camera::buttonState = "held";
            break;

        default:
            camera::buttonState = "up";
            break;
    }

    reseted = false;
}

void handleCustomNightState(SceCtrlData ctrlData) {
    // Render all Custom Night elements
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

    // Update the position of the reticle
    customnight::reticle::updatePosition();

    // Handle input only when the cursor is ready to move
    if (cursorMoveTime <= 0) {
        switch (ctrlData.Buttons) {
            case PSP_CTRL_RTRIGGER:
                customnight::reticle::moveReticleRight();
                cursorMoveTime = 10;
                break;

            case PSP_CTRL_LTRIGGER:
                customnight::reticle::moveReticleLeft();
                cursorMoveTime = 10;
                break;

            case PSP_CTRL_RIGHT:
                customnight::edit::plus();
                cursorMoveTime = 10;
                break;

            case PSP_CTRL_LEFT:
                customnight::edit::minus();
                cursorMoveTime = 10;
                break;

            case PSP_CTRL_CROSS:
                customnight::actions::create();
                cursorMoveTime = 10;
                break;

            case PSP_CTRL_CIRCLE:
                customnight::actions::exit();
                cursorMoveTime = 10;
                break;

            default:
                break;
        }
    } else {
        cursorMoveTime -= 1; // Decrease the cursor move timer
    }

    resetMain(); // Reset any game-related states
}

void handleSixAmState(){
    sixam::render::renderSixAm();
    sixam::animate::wait();
    sixam::next::wait();

    resetMain();
}

void handlePoweroutState(){
    powerout::render::renderPowerout();
    powerout::animate::animatePowerOut();

    resetMain();
}

void handleJumpscareState(){
    jumpscare::load::loadWithDelay();
    jumpscare::render::renderJumpscare();
    jumpscare::animate::animateJumpscare();

    reseted = false;

}

void handleEndingState(){
    ending::render::renderEnding();
    ending::wait::waitForFrames();

    resetMain();
}

void handleDeadState(){
    dead::n_static::renderStatic();
    dead::n_static::animateStatic();

    dead::wait::waitForFrames();

    resetMain();
}

void handleState(SceCtrlData ctrlData) {
    if (state::isMenu){
        handleMenuState(ctrlData);
    }
    else if (state::isNewspaper){
        handleNewspaperState();
    }
    else if (state::isNightinfo){
        handleNightInfoState();
    }
    else if (state::isOffice){
        handleOfficeState(ctrlData);
    }
    else if (state::isCustomNight){
        handleCustomNightState(ctrlData);
    }
    else if (state::isSixAm){
        handleSixAmState();
    }
    else if (state::isPowerOut){
        handlePoweroutState();
    }
    else if (state::isJumpscare){
        handleJumpscareState();
    }
    else if (state::isEnding){
        handleEndingState();
    }
    else if (state::isDead){
        handleDeadState();
    }
}


auto main() -> int{

    SceCtrlData ctrlData;

    initEngine();
    initGame();


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

        handleState(ctrlData);
        
        sceDisplayWaitVblankStart();
            
        sceGuFinish();
        sceGuSync(0,0);

        sceGuSwapBuffers();
    }
}