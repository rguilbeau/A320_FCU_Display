# A320_FCU_Display

## Description
Module de gestion des 5 écrans du FCU

> **Microcontrolleur**: ESP8266

## Schéma électronique

*en cours*

## Impression 3D

| Type | Buse | Hauteur | Température extrudeur | Température plateau | Fichier
|-|-|-|-|-|-
| PLA+ | 0.2 | 0.12 | 205°C | 60 °C | 3d/CE3PRO_support_fcu_display.gcode


        // [0] SPD_SHOW | [1] SPD_HIDDEN
        // [0] HDG_SHOW | [1] HDG_HIDDEN
        // [0] ALT_SHOW | [1] ALT_HIDDEN
        // [0] VS_SHOW  | [1] VS_HIDDEN
        // 0 always
        // 0 always
        // 0 always
        // 0 always


| Pos | Bit | Description
|-|-|-
| 4 | 0-8 | Altitude
| 5 | 0-8 | Altitude à aditionner avec la position 4 
| 6 | 0-8 | Vitesse verticale <br> Si FPA alors V/S = x / 10 <br> Sinon V/S = x * 100
| 7 | 1 | [0] Vitesse affiché <br> [1] Vitesse non affiché "---"  
| 7 | 2 | [0] Cap affiché <br> [1] Cap non affiché "---"  
| 7 | 3 | [0] Altitude affiché <br> [1] Altitude non affiché "-----"  
| 7 | 4 | [0] Vitesse verticale affiché <br> [1] Vitesse verticale non affiché "-----"  
| 7 | 5 | Toujours à 0
| 7 | 6 | Toujours à 0
| 7 | 7 | Toujours à 0
| 7 | 8 | Toujours à 0


| 50 | 60 | 00000000 | 00000000 | 250 | 60 | 26 | 00000000 |
| - | - | -| - | - | -| - | - |
| Vitesse | Multiplicteur | Indicateurs | Altitude | Altitude | Vitesse verticale | Valeur managé / géré |

```
 

0x64    60    00000000      00000000    250     60      26      00000000
|       |                                                        |||||||
|       |                                                        |||||||___ Toujours 0
|       |                                                        ||||||___ Toujours 0
|       |                                                        |||||___ Toujours 0
|                                                                ||||___ Toujours 0
|                                                                |||
|                                                                |||_ 0: V/S affiché
|                                                                ||   1: V/S non affiché "-----"
|                                                                ||
|                                                                ||_ 0: Altitude affiché
|                                                                |   1: Altitude non affiché "---"
|                                                                |
|                                                                |_ 0: Cap affiché
|                                                                   1: Cap non affiché "---"
|                                                                 
|
|
|
| Identifiant
```