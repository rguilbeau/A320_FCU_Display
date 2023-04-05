#include "FcuDisplayFrame.h"

/**
 * @brief Construction d'une nouvelle frame pour les afficheurs du FCU
 * 
 */
FcuDisplayFrame::FcuDisplayFrame()
{

}

/**
 * @brief Décode la frame du CAN Bus en frame utilisable via les données membres
 * 
 * @param frame 
 */
void FcuDisplayFrame::decode(struct can_frame *frame)
{
    bool binaryIndicators[] = {0,0,0,0,0,0,0,0};
    binaryConvert(frame->data[3], binaryIndicators);

    bool binaryMultiplicator[] = {0,0,0,0,0,0,0,0};
    binaryConvert(frame->data[2], binaryMultiplicator);

    bool binaryDigitHidden[] = {0,0,0,0,0,0,0,0};
    binaryConvert(frame->data[7], binaryDigitHidden);

    isMachSpeed = binaryIndicators[0];
    isTrackMode = binaryIndicators[1];
    isLatNavigation = binaryIndicators[2];
    isFpa = binaryIndicators[3];
    isSpeedForced = binaryIndicators[4];
    isHeadingForced = binaryIndicators[5];
    isAltitudeForced = binaryIndicators[6];
    isVerticalSpeedPositive = binaryIndicators[7];

    speed = frame->data[0];
    heading = frame->data[1];

    for(short i = 0; i < 5; i++) {
        if(binaryMultiplicator[i] == true) {
            speed = speed + ((i + 1) * 100);
            break;
        }
    }

    for(short i = 5; i < 8; i++) {
        if(binaryMultiplicator[i] == true) {
            heading = heading + ((i - 4) * 100);
            break;
        }
    }

    if(isMachSpeed) {
        speed = speed / 100;
    }

    altitude = (frame->data[4] + frame->data[5]) * 100;

    verticalSpeed = 0;
    if(isFpa) {
        verticalSpeed = ((float)frame->data[6]) / 10;
    } else {
        verticalSpeed = frame->data[6] * 100;
    }

    isSpeedHidden = binaryDigitHidden[0];
    isHeadingHidden = binaryDigitHidden[1];
    isAltitudeHidden = binaryDigitHidden[2];
    isVerticalSpeedHidden = binaryDigitHidden[3];
    isPowerOn = binaryDigitHidden[7];
}

/**
 * @brief Convertisseur d'une valeur décimale en tableau de binaires
 * 
 * @param decimal La valeur déciamle à convertire
 * @param binaryArray Le tableau binaire qui sera convertit
 */
void FcuDisplayFrame::binaryConvert(int decimal, bool binaryArray[])
{
    for(int i = 7 ; i >= 0 ; i--) {
        if(pow(2, i) <= decimal) {
            decimal = decimal - pow(2, i);
            binaryArray[8-(i+1)] = 1;
        }
    }
}