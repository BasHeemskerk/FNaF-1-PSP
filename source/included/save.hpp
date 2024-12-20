#include "global.hpp"

namespace save{

    extern int whichNight;
    extern int mode1Unlocked;
    extern int mode2Unlocked;
    extern float starAmount;

    extern bool loadedData;

    extern std::string night;
    extern std::string mode1;
    extern std::string mode2;
    extern std::string stars;

    void file();
    void readData();
    void saveData();
    void clearData();
    
    /*
    void createFile();
    void saveData();
    void readData();
    void loadData();
    */
}