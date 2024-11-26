#include "included/audio.hpp"

namespace music{
    namespace menu{
        OSL_SOUND* menuMusic;

        void loadMenuMusic(){
            menuMusic = oslLoadSoundFileWAV("romfs/music/menu/music.wav", OSL_FMT_NONE);
        }
        void playMenuMusic(){
            oslPlaySound(menuMusic, 0);

            oslSetSoundLoop(menuMusic, 1);
            if (oslGetSoundChannel(menuMusic) == -1){
                oslPlaySound(menuMusic, 0);
            }
        }
        void unloadMenuMusic(){
            oslDeleteSound(menuMusic);
        }
    }

    namespace n_ending{
        OSL_SOUND* endingSong;
        bool stopped = false;

        void loadEndingSong(){
            endingSong = oslLoadSoundFileWAV("romfs/music/ending/music.wav", OSL_FMT_STREAM);
        }
        void playEndingSong(){
            oslPlaySound(endingSong, 0);

            /*
            if (oslGetSoundChannel(endingSong) == -1){
                unloadEndingSong();
            }
            */
        }
        void stopEndingSong(){
            //oslPauseSound(endingSong, 1);
            unloadEndingSong();
        }
        void unloadEndingSong(){
            oslDeleteSound(endingSong);
        }
    }
}

namespace ambience{
    namespace office{
        OSL_SOUND* ambience;

        void loadAmbience(){
            ambience = oslLoadSoundFileWAV("romfs/ambience/office/ambience_mix.wav", OSL_FMT_STREAM);
        }
        void playAmbience(){
            oslPlaySound(ambience, 0);

            oslSetSoundLoop(ambience, 1);
            if (oslGetSoundChannel(ambience) == -1){
                oslPlaySound(ambience, 0);
            }
        }
        void unloadAmbience(){
            oslDeleteSound(ambience);
        }

        
        OSL_SOUND* fan;

        void loadFanSound(){
            fan = oslLoadSoundFileWAV("romfs/ambience/office/fan.wav", OSL_FMT_STREAM);
        }
        void playFanSound(){
            oslPlaySound(fan, 2);

            oslSetSoundLoop(fan, 1);
            if (oslGetSoundChannel(fan) == -1){
                oslPlaySound(fan, 2);
            }
        }
        void unloadFanSound(){
            oslDeleteSound(fan);
        }
    }
}

namespace call {
    OSL_SOUND* phoneCalls[5] = {nullptr, nullptr, nullptr, nullptr, nullptr}; // Initialize with null
    bool stopped = false;

    void loadPhoneCalls() {
        int nightIndex = save::whichNight - 1; // Map night number to array index (0-based)
        if (nightIndex >= 0 && nightIndex < 5) { // Ensure valid night range
            std::string filePath = "romfs/ambience/office/call/call" + toString(nightIndex + 1) + ".wav";
            phoneCalls[nightIndex] = oslLoadSoundFileWAV(filePath.c_str(), OSL_FMT_STREAM);
        }
    }

    void playPhoneCalls() {
        int nightIndex = save::whichNight - 1; // Map night number to array index (0-based)
        if (nightIndex >= 0 && nightIndex < 5 && phoneCalls[nightIndex] != nullptr) {
            oslPlaySound(phoneCalls[nightIndex], 1);
            if (oslGetSoundChannel(phoneCalls[nightIndex]) == -1) {
                unloadPhoneCalls(); // Unload if the sound channel is done
            }
        }
    }

    void unloadPhoneCalls() {
        int nightIndex = save::whichNight - 1; // Map night number to array index (0-based)
        if (nightIndex >= 0 && nightIndex < 5 && phoneCalls[nightIndex] != nullptr) {
            oslDeleteSound(phoneCalls[nightIndex]);
            phoneCalls[nightIndex] = nullptr; // Clear pointer after deletion
        }
        stopped = true;
    }
}


namespace sfx{
    namespace office{
        OSL_SOUND* buzz;
        OSL_SOUND* door;
        OSL_SOUND* scare;
        OSL_SOUND* switchCam;
        OSL_SOUND* laugh;
        OSL_SOUND* move;
        OSL_SOUND* walk;
        OSL_SOUND* kitchen;
        OSL_SOUND* run;
        OSL_SOUND* knock;
        OSL_SOUND* camera[2];

        void loadSfx(){
            buzz = oslLoadSoundFileWAV("romfs/sfx/office/buzz.wav", OSL_FMT_NONE);
            door = oslLoadSoundFileWAV("romfs/sfx/office/door.wav", OSL_FMT_NONE);
            scare = oslLoadSoundFileWAV("romfs/sfx/office/scare.wav", OSL_FMT_NONE);
            switchCam = oslLoadSoundFileWAV("romfs/sfx/office/switch.wav", OSL_FMT_NONE);
            laugh = oslLoadSoundFileWAV("romfs/sfx/office/laugh.wav", OSL_FMT_STREAM);
            move = oslLoadSoundFileWAV("romfs/sfx/office/move.wav", OSL_FMT_NONE);
            walk = oslLoadSoundFileWAV("romfs/sfx/office/walk.wav", OSL_FMT_NONE);
            //kitchen = oslLoadSoundFileWAV("romfs/sfx/office/kitchen.wav", OSL_FMT_STREAM);
            run = oslLoadSoundFileWAV("romfs/sfx/office/run.wav", OSL_FMT_STREAM);
            knock = oslLoadSoundFileWAV("romfs/sfx/office/knock.wav", OSL_FMT_STREAM);

            camera[0] = oslLoadSoundFileWAV("romfs/sfx/office/openCam.wav", OSL_FMT_NONE);
            camera[1] = oslLoadSoundFileWAV("romfs/sfx/office/closeCam.wav", OSL_FMT_NONE);
        }
        void stopSfx(){
            /*
            oslPauseSound(buzz, 1);
            oslPauseSound(door, 1);
            oslPauseSound(scare, 1);
            oslPauseSound(switchCam, 1);
            oslPauseSound(laugh, 1);
            oslPauseSound(move, 1);
            oslPauseSound(walk, 1);
            oslPauseSound(kitchen, 1);
            oslPauseSound(run, 1);
            oslPauseSound(knock, 1);

            oslPauseSound(camera[0], 1);
            oslPauseSound(camera[1], 1);
            */

            unloadSfx();
        }
        void unloadSfx(){
            oslDeleteSound(buzz);
            oslDeleteSound(door);
            oslDeleteSound(scare);
            oslDeleteSound(switchCam);
            oslDeleteSound(laugh);
            oslDeleteSound(move);
            oslDeleteSound(walk);
            //oslDeleteSound(kitchen);
            oslDeleteSound(run);
            oslDeleteSound(knock);

            oslDeleteSound(camera[0]);
            oslDeleteSound(camera[1]);
        }

        void playLightOn(){
            oslPlaySound(buzz, 3);

            oslSetSoundLoop(buzz, 1);
            /*
            if (oslGetSoundChannel(buzz) == -1){
                oslPlaySound(buzz, 3);
            */
        }
        void playLightOff(){
            oslPauseSound(buzz, -1);
        }

        void playDoor(){
            oslPlaySound(door, 4);
        }

        void playCamOpen(){
            oslPlaySound(camera[0], 5);
        }
        void playCamClose(){
            oslPlaySound(camera[1], 5);
        }
        void playSwitch(){
            oslPlaySound(switchCam, 5);
        }
        void playMove(){
            oslPlaySound(move, 5);
        }

        void playLaugh(){
            oslPlaySound(laugh, 6);
        }
        void playWalk(){
            oslPlaySound(walk, 7);
        }
        void playKitchen(){
            //oslPlaySound(kitchen, 6);
            std::cout << "removed kitchen sound to prevent crashing" << std::endl;
        }
        void playScare(){
            oslPlaySound(scare, 7);
        }

        void playRun(){
            oslPlaySound(run, 7);
        }
        void playKnock(){
            oslPlaySound(knock, 7);
        }
    }
    namespace sixam{

        OSL_SOUND* chimes;
        //OSL_SOUND* hooray;

        void loadSixAm(){
            chimes = oslLoadSoundFileWAV("romfs/sfx/sixam/chimes.wav", OSL_FMT_STREAM);
            //hooray = oslLoadSoundFileWAV("romfs/sfx/sixam/hooray.wav");
        }
        void unloadSixAm(){
            oslDeleteSound(chimes);
            //oslDeleteSound(hooray);
        }
        
        void playSixAm(){
            oslPlaySound(chimes, 0);
        }
    }

    namespace jumpscare{
        OSL_SOUND *jumpscare;
        OSL_SOUND *jumpscare2; //only used in custom night!
        OSL_SOUND *dead;

        void loadJumpscareSound(){
            jumpscare = oslLoadSoundFileWAV("romfs/sfx/jumpscare/jumpscare.wav", OSL_FMT_STREAM);
        }
        void playJumpscareSound(){
            oslPlaySound(jumpscare, 0);

            if (oslGetSoundChannel(jumpscare) == -1){
                unloadJumpscareSound();
            }
        }
        void unloadJumpscareSound(){
            oslDeleteSound(jumpscare);
        }

        void loadJumpscare2Sound(){
            jumpscare2 = oslLoadSoundFileWAV("romfs/sfx/jumpscare/jumpscare2.wav", OSL_FMT_STREAM);
        }
        void playJumpscare2Sound(){
            oslPlaySound(jumpscare2, 0);
        }
        void unloadJumpscare2Sound(){
            oslDeleteSound(jumpscare2);
        }

        void loadDeadSound(){
            dead = oslLoadSoundFileWAV("romfs/sfx/jumpscare/dead.wav", OSL_FMT_STREAM);
        }
        void playDeadSound(){
            oslPlaySound(dead, 0);

            if (oslGetSoundChannel(dead) == -1){
                unloadDeadSound();
            }
        }
        void unloadDeadSound(){
            oslDeleteSound(dead);
        }
    }
}