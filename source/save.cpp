#include "included/save.hpp"

namespace save{

    int whichNight = 1;
    float mode1Unlocked = 0;
    float mode2Unlocked = 0;
    float starAmount = 0;

    bool loadedData = false;

    std::string night;
    std::string mode1;
    std::string mode2;
    std::string stars;

    void file(){
        std::fstream nightData("saves/night.bin");
        std::fstream extraMode1Data("saves/mode1.bin");
        std::fstream extraMode2Data("saves/mode2.bin");
        std::fstream starData("saves/star.bin");
        

        if (!nightData && !extraMode1Data && !extraMode2Data && !starData){
            clearData();
            
        }

        std::getline(nightData, night);
        std::getline(extraMode1Data, mode1);
        std::getline(extraMode2Data, mode2);
        std::getline(starData, stars);

        if (whichNight != 7){
            readData();
        }
    }

    
    void readData(){
        if (night == "01101110 01101001 01100111 01101000 01110100 00100000 00110001"){ //night 1
            whichNight = 1;
        }
        else if (night == "01101110 01101001 01100111 01101000 01110100 00100000 00110010"){ //night 2
            whichNight = 2;
        }
        else if (night == "01101110 01101001 01100111 01101000 01110100 00100000 00110011"){ //night 3
            whichNight = 3;
        }
        else if (night == "01101110 01101001 01100111 01101000 01110100 00100000 00110100"){ //night 4
            whichNight = 4;
        }
        else if (night == "01101110 01101001 01100111 01101000 01110100 00100000 00110101"){ //night 5
            whichNight = 5;
        }


        if (mode1 == "01101100 01101111 01100011 01101011 01100101 01100100"){ //locked m1
            mode1Unlocked = 0;
        }
        else if (mode1 == "01110101 01101110 01101100 01101111 01100011 01101011 01100101 01100100"){ //unlocked m1
            mode1Unlocked = 1;
        }


        if (mode2 == "01101100 01101111 01100011 01101011 01100101 01100100"){ //locked m2
            mode2Unlocked = 0;
        }
        else if (mode2 == "01110101 01101110 01101100 01101111 01100011 01101011 01100101 01100100"){ //unlocked m2
            mode2Unlocked = 1;
        }


        if (stars == "01110011 01110100 01100001 01110010 00100000 00110000"){ //star 0
            starAmount = 0;
        }
        else if (stars == "01110011 01110100 01100001 01110010 00100000 00110001"){ //star 1
            starAmount = 1;
        }
        else if (stars == "01110011 01110100 01100001 01110010 00100000 00110010"){ //star 2
            starAmount = 2;
        }
        else if (stars == "01110011 01110100 01100001 01110010 00100000 00110011"){ //star 3
            starAmount = 3;
        }

        loadedData = true;
    }


    void saveData(){
        if (whichNight == 1){
            std::remove("saves/night.bin");
            std::ofstream nightData("saves/night.bin");
            nightData << "01101110 01101001 01100111 01101000 01110100 00100000 00110010" << std::endl;
        }
        else if (whichNight == 2){
            std::remove("saves/night.bin");
            std::ofstream nightData("saves/night.bin");
            nightData << "01101110 01101001 01100111 01101000 01110100 00100000 00110011" << std::endl;
        }
        else if (whichNight == 3){
            std::remove("saves/night.bin");
            std::ofstream nightData("saves/night.bin");
            nightData << "01101110 01101001 01100111 01101000 01110100 00100000 00110100" << std::endl;
        }
        else if (whichNight == 4){
            std::remove("saves/night.bin");
            std::ofstream nightData("saves/night.bin");
            nightData << "01101110 01101001 01100111 01101000 01110100 00100000 00110101" << std::endl;
        }
        else if (whichNight == 5){
            std::remove("saves/mode1.bin");
            std::ofstream extraMode1Data("saves/mode1.bin");
            extraMode1Data << "01110101 01101110 01101100 01101111 01100011 01101011 01100101 01100100" << std::endl;

            std::remove("saves/star.bin");
            std::ofstream starData("saves/star.bin");
            starData << "01110011 01110100 01100001 01110010 00100000 00110001" << std::endl;
        }
        else if (whichNight == 6){
            std::remove("saves/mode2.bin");
            std::ofstream extraMode2Data("saves/mode2.bin");
            extraMode2Data << "01110101 01101110 01101100 01101111 01100011 01101011 01100101 01100100" << std::endl;

            std::remove("saves/star.bin");
            std::ofstream starData("saves/star.bin");
            starData << "01110011 01110100 01100001 01110010 00100000 00110010" << std::endl;
        }
        else if (whichNight == 7){
            std::remove("saves/star.bin");
            std::ofstream starData("saves/star.bin");
            starData << "01110011 01110100 01100001 01110010 00100000 00110011" << std::endl;
        }
    }

    void clearData(){
        std::remove("saves/night.bin");
        std::remove("saves/mode1.bin");
        std::remove("saves/mode2.bin");
        std::remove("saves/star.bin");        
        
        std::ofstream nightData("saves/night.bin");
        std::ofstream extraMode1Data("saves/mode1.bin");
        std::ofstream extraMode2Data("saves/mode2.bin");
        std::ofstream starData("saves/star.bin");

        nightData << "01101110 01101001 01100111 01101000 01110100 00100000 00110001" << std::endl;
        extraMode1Data << "01101100 01101111 01100011 01101011 01100101 01100100" << std::endl;
        extraMode2Data << "01101100 01101111 01100011 01101011 01100101 01100100" << std::endl;
        starData << "01110011 01110100 01100001 01110010 00100000 00110000" << std::endl;
    }
}