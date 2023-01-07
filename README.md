# A320_FCU_Display

## Documentation générale
Voir Doc https://rguilbeau.github.io/A320_Documentation

## Hack
Les libraries Adafruit pour la gestion des afficheurs est copié/collé dans les libs pour permettre  un
hack afin de gerer le contrast des écrans :

```
void Adafruit_SSD1306::setContrast(short contrast) {
  TRANSACTION_START
    ssd1306_command(SSD1306_SETCONTRAST);
    ssd1306_command((contrast * 159) / 100);
  TRANSACTION_END
}
```