#include "included/office.hpp"

namespace office{

    int wichOfficeFrame = 0; //3 = bonnie, 4 = chica at door
    float xPos[6];
    float speed = 1;
    float speedMultiplier = 5;
    std::string dir = "none";


    float usageCountdown = 10;
    bool leftEdge = false;
    bool rightEdge = true;

    bool leftOn = false;
    bool rightOn = false;
    bool leftClosed = false;
    bool rightClosed = false;

    bool closingLeft = false;
    bool openingLeft = false;
    bool closingRight = false;
    bool openingRight = false;

    std::string state = "none";
    std::string buttonState = "up";
    std::string doorButtonState = "up";

    int leftButtonFrame = 0;
    int rightButtonFrame = 0;

    float doorAnimTime = 1;
    int leftDoorFrame = 0;
    int rightDoorFrame = 0;

    void reset(){
        wichOfficeFrame = 0;

        main::setX();

        leftOn = false;
        rightOn = false;
        leftClosed = false;
        rightClosed = false;
        closingLeft = false;
        openingLeft = false;
        closingRight = false;
        openingRight = false;

        state = "none";
        buttonState = "up";
        doorButtonState = "up";

        leftButtonFrame = 0;
        rightButtonFrame = 0;

        doorAnimTime = 1;
        leftDoorFrame = 0;
        rightDoorFrame = 0;
    }

    namespace render{
        void renderOffice(){
            drawSpriteAlpha(0, 0, 480, 272, officeImage::office1Sprites[wichOfficeFrame], xPos[0], 0, 0);
            drawSpriteAlpha(0, 0, 124, 272, officeImage::office2Sprites[wichOfficeFrame], xPos[1], 0, 0);
        }
        void renderButtons(){
            drawSpriteAlpha(0, 0, 50, 90, sprite::office::buttonsLeft[leftButtonFrame], xPos[2], 105, 0);
            drawSpriteAlpha(0, 0, 50, 90, sprite::office::buttonsRight[rightButtonFrame], xPos[3], 100, 0);
        }
        void renderDoors(){
            drawSpriteAlpha(0, 0, 84, 272, sprite::office::doorLeft[leftDoorFrame], xPos[4], 0, 0);
            drawSpriteAlpha(0, 0, 84, 272, sprite::office::doorRight[rightDoorFrame], xPos[5], 0, 0);
        }
    }

    namespace buttons {
        void setButtonFrame() {
            leftButtonFrame = (leftOn ? 2 : 0) + (leftClosed ? 1 : 0);
            rightButtonFrame = (rightOn ? 2 : 0) + (rightClosed ? 1 : 0);
        }
    }


    namespace main {
        void setX() {
            xPos[0] = 0;
            xPos[1] = 480;
            xPos[2] = -5;
            xPos[3] = 550;
            xPos[4] = 30;
            xPos[5] = 480;
        }

        void moveOffice() {
            const float delta = speed * speedMultiplier;

            if (dir == "left" && xPos[1] > 364) {
                for (int i = 0; i < 6; ++i) {
                    xPos[i] -= delta;
                }
                rightEdge = true;
            } else if (dir == "right" && xPos[0] < 0) {
                for (int i = 0; i < 6; ++i) {
                    xPos[i] += delta;
                }
            }

            if (xPos[0] == -120) {
                leftEdge = true;
                rightEdge = false;
            } else if (xPos[0] == 0) {
                rightEdge = true;
                leftEdge = false;
            } else if (xPos[0] < 0 && xPos[0] > -120) {
                leftEdge = false;
                rightEdge = false;
            }
        }
    }


    namespace lights {
        void lights() {
            if (buttonState == "down") {
                if (leftEdge) { // Light logic for the right side (inverted for reasons)
                    wichOfficeFrame = (animatronic::chika::position == 6) ? 4 : 1;
                    rightOn = true;
                    if (animatronic::chika::position == 6 && !rightClosed) {
                        sfx::office::playScare();
                    }
                    sfx::office::playLightOn();
                }

                if (rightEdge) { // Light logic for the left side (inverted for reasons)
                    wichOfficeFrame = (animatronic::bonnie::position == 6) ? 3 : 2;
                    leftOn = true;
                    if (animatronic::bonnie::position == 6 && !leftClosed) {
                        sfx::office::playScare();
                    }
                    sfx::office::playLightOn();
                }
            } else if (buttonState == "up") {
                wichOfficeFrame = 0;

                if (leftOn) {
                    leftOn = false;
                    sfx::office::playLightOff();
                }
                if (rightOn) {
                    rightOn = false;
                    sfx::office::playLightOff();
                }
            }
        }
    }



    namespace doors{

        void doors(){
            if (rightEdge){
                if (closingLeft == false && leftClosed == false){
                    closingLeft = true;
                    sfx::office::playDoor();
                }
                else if (openingLeft == false && leftClosed == true){
                    openingLeft = true;
                    sfx::office::playDoor();
                }
            }
            else if (leftEdge){
                if (closingRight == false && rightClosed == false){
                    closingRight = true;
                    sfx::office::playDoor();
                }
                else if (openingRight == false && rightClosed == true){
                    openingRight = true;
                    sfx::office::playDoor();
                }
            }
        }


        void closeLeft(){
            if (doorAnimTime <= 0){
                if (leftDoorFrame < 6){
                    leftDoorFrame += 1;
                    doorAnimTime = 1;
                }
                else{
                    closingLeft = false;
                    leftClosed = true;
                    animatronic::leftClosed = true;
                }
            }
            else{
                doorAnimTime -= 1;
            }
        }
        void openLeft(){
            if (doorAnimTime <= 0){
                if (leftDoorFrame > 0){
                    leftDoorFrame -= 1;
                    doorAnimTime = 1;
                }
                else{
                    openingLeft = false;
                    leftClosed = false;
                    animatronic::leftClosed = false;
                }
            }
            else{
                doorAnimTime -= 1;
            }
        }


        void closeRight(){
            if (doorAnimTime <= 0){
                if (rightDoorFrame < 6){
                    rightDoorFrame += 1;
                    doorAnimTime = 1;
                }
                else{
                    closingRight = false;
                    rightClosed = true;
                    animatronic::rightClosed = true;
                }
            }
            else{
                doorAnimTime -= 1;
            }
        }
        void openRight(){
            if (doorAnimTime <= 0){
                if (rightDoorFrame > 0){
                    rightDoorFrame -= 1;
                    doorAnimTime = 1;
                }
                else{
                    openingRight = false;
                    rightClosed = false;
                    animatronic::rightClosed = false;
                }
            }
            else{
                doorAnimTime -= 1;
            }
        }
    }
}