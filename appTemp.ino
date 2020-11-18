
void appTemp() {
  int16_t x, y;
  while (ttgo->getTouch(x, y)) { }
  while (!ttgo->getTouch(x, y)) { // Wait for press
    float temp = ttgo->power->getTemp();
    ttgo->tft->fillScreen(TFT_BLACK);
    ttgo->tft->setTextColor(TFT_YELLOW, TFT_BLACK);
    ttgo->tft->setCursor(40, 100);
    ttgo->tft->print("Temp: ");
    ttgo->tft->print(temp);
    delay(300);
  }
  while (ttgo->getTouch(x, y)) {} // wait until you stop touching
  ttgo->tft->fillScreen(TFT_BLACK);
}
 
