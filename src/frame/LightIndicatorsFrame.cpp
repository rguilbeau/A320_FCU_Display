#include "LightIndicatorsFrame.h"

/**
 * @brief Construction d'une nouvelle frame pour la gestion du mode test
 * 
 */
LightIndicatorsFrame::LightIndicatorsFrame()
{

}

/**
 * @brief Décode la frame du CAN Bus en frame utilisable via les données membres
 * 
 * @param frame 
 */
void LightIndicatorsFrame::decode(struct can_frame *frame)
{
    bool binaryIndicators[] = {0,0,0,0,0,0,0,0};
    binaryConvert(frame->data[0], binaryIndicators);

    isTestLight = binaryIndicators[0];
}

/**
 * @brief Convertisseur d'une valeur décimale en tableau de binaires
 * 
 * @param decimal La valeur déciamle à convertire
 * @param binaryArray Le tableau binaire qui sera convertit
 */
void LightIndicatorsFrame::binaryConvert(int decimal, bool binaryArray[])
{
    for(int i = 7 ; i >= 0 ; i--) {
        if(pow(2, i) <= decimal) {
            decimal = decimal - pow(2, i);
            binaryArray[8-(i+1)] = 1;
        }
    }
}