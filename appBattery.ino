// Display Battery Data

void appBattery()
{
    TFT_eSPI *tft;
    AXP20X_Class *power;

    //Serial.begin(115200);
    //  Receive as a local variable for easy writing
    tft = ttgo->tft;
    power = ttgo->power;

    // ADC monitoring must be enabled to use the AXP202 monitoring function
    power->adc1Enable(AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_BATT_VOL_ADC1, true);

    // Some display setting
    tft->setTextFont(0);
    tft->setTextColor(TFT_GREEN, TFT_BLACK);

    int16_t x, y;
    while (!ttgo->getTouch(x, y)) {
      // A simple clear screen will flash a bit
      tft->fillRect(0, 0, 210, 130, TFT_BLACK);
      tft->setTextFont(1);
      tft->setCursor(0, 0);
      tft->print("CHARGE STATUS: ");
      // You can use isVBUSPlug to check whether the USB connection is normal
      if (power->isVBUSPlug()) {
          tft->println("CONNECTED");

          // Get USB voltage
          tft->print("VBUS Voltage:");
          tft->print(power->getVbusVoltage());
          tft->println(" mV");

          // Get USB current
          tft->print("VBUS Current: ");
          tft->print(power->getVbusCurrent());
          tft->println(" mA");

      } else {

          tft->setTextColor(TFT_RED, TFT_BLACK);
          tft->println("DISCONNECTED");
          tft->setTextColor(TFT_GREEN, TFT_BLACK);
      }

      tft->println();

      tft->print("BATTERY ");
      // You can use isBatteryConnect() to check whether the battery is connected properly
      if (power->isBatteryConnect()) {
          tft->println("CONNECTED:");

          // Get battery voltage
          tft->print("BAT Voltage:");
          tft->print(power->getBattVoltage());
          tft->println(" mV");

          // To display the charging status, you must first discharge the battery,
          // and it is impossible to read the full charge when it is fully charged
          if (power->isChargeing()) {
              tft->print("Charge:");
              tft->print(power->getBattChargeCurrent());
              tft->println(" mA");
              tft->print("Full: ");
              tft->print(power->getBattPercentage());
              tft->println(" %");
          } else {
              // Show current consumption
              tft->print("Discharge:");
              tft->print(power->getBattDischargeCurrent());
              tft->println(" mA");
              tft->print("Power: ");
              tft->print(power->getBattPercentage());
              tft->println(" %");

          }
      } else {
          tft->setTextColor(TFT_RED, TFT_BLACK);
          tft->println("FAILURE:");
          tft->println("NOT DETECTED!");
          tft->setTextColor(TFT_GREEN, TFT_BLACK);
      }
      delay(1000);
    }
    // Wait for touch
    //while (!ttgo->getTouch(x, y)) {}
    //while (ttgo->getTouch(x, y)) {}  // Wait for release to exit
    //Clear screen 
    ttgo->tft->fillScreen(TFT_BLACK);
}
