#include "BrightnessFrame.h"

/**
 * @brief Construction d'une nouvelle frame pour le rétrp-éclairage des écrans
 * 
 */
BrightnessFrame::BrightnessFrame()
{

}

/**
 * @brief Décode la frame du CAN Bus en frame utilisable via les données membres
 * 
 * @param frame 
 */
void BrightnessFrame::decode(struct can_frame *frame)
{
    fcuDisplayContrast = (short)frame->data[0];
    if(fcuDisplayContrast > 100) {
        fcuDisplayContrast = 100;
    }
}

/**
 * @brief Convertisseur d'une valeur décimale en tableau de binaires
 * 
 * @param decimal La valeur déciamle à convertire
 * @param binaryArray Le tableau binaire qui sera convertit
 */
void BrightnessFrame::binaryConvert(int decimal, bool binaryArray[])
{
    for(int i = 7 ; i >= 0 ; i--) {
        if(pow(2, i) <= decimal) {
            decimal = decimal - pow(2, i);
            binaryArray[8-(i+1)] = 1;
        }
    }
}