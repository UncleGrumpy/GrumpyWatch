// An advanced Time Display
// This is a drop-in replacement for the displayTime()
// In the original Instructable. s such, it redraws GUI
// every minute so you will see a little flicker.

#include <esp_sleep.h>

void displayTime(boolean fullUpdate) {
  ttgo->power->adc1Enable(AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_BATT_VOL_ADC1, true);

  //bool irq = false;

  // Get the current date
  RTC_Date tnow = ttgo->rtc->getDateTime();

  hh = tnow.hour;
  mm = tnow.minute;
  ss = tnow.second;
  dday = tnow.day;
  mmonth = tnow.month;
  yyear = tnow.year;

  ttgo->tft->setTextSize(1);

  if (fullUpdate) {

    //Draw the back graphics - Top of display
    ttgo->tft->fillScreen(TFT_BLACK);
    ttgo->tft->fillRoundRect(0, 0, 239, 120, 40, TFT_PURPLE);
    ttgo->tft->fillRoundRect(40, 20, 196, 80, 20, TFT_BLACK);
    ttgo->tft->fillRect(80, 20, 159, 80, TFT_BLACK);
    ttgo->tft->fillRect(170, 0, 45, 20, TFT_BLACK);
    ttgo->tft->fillRect(110, 0, 4, 20, TFT_BLACK);
    ttgo->tft->fillRect(0, 45, 50, 7, TFT_BLACK);
    ttgo->tft->fillRect(0, 70, 50, 7, TFT_BLACK);
    ttgo->tft->fillRect(215, 0, 24, 20, TFT_DARKCYAN);

    //Draw the back graphics - Bottom of display
    ttgo->tft->fillRoundRect(0, 130, 239, 109, 40, TFT_MAROON);
    ttgo->tft->fillRoundRect(40, 150, 199, 88, 20, TFT_BLACK);
    ttgo->tft->fillRect(0, 179, 50, 10, TFT_BLACK);
    ttgo->tft->fillRect(100, 160, 40, 10, TFT_YELLOW);
    ttgo->tft->fillRect(140, 160, 40, 10, TFT_DARKGREEN);
    ttgo->tft->fillRect(180, 160, 40, 10, TFT_RED);
    ttgo->tft->setTextColor(TFT_WHITE, TFT_BLACK);
    ttgo->tft->drawString("Temp", 66, 158, 2);
    ttgo->tft->fillRoundRect(119, 210, 120, 29, 15, TFT_DARKCYAN);

    // Display Temp Marker - you may need to adjust the x value based on your normal ADC results
    float temp = ttgo->power->getTemp();
    ttgo->tft->fillRoundRect(int(temp) + 124, 160, 10, 20, 5, TFT_WHITE);

    // Display Time
    // Font 7 is a 7-seg display but only contains
    // characters [space] 0 1 2 3 4 5 6 7 8 9 0 : .

    ttgo->tft->setTextColor(0xFBE0, TFT_BLACK);
    int xpos = 55;
    if (hh < 10) xpos += ttgo->tft->drawChar('0', xpos, 35, 7);
    xpos += ttgo->tft->drawNumber(hh, xpos, 35, 7);
    xpos += 3;
    xpos += ttgo->tft->drawChar(':', xpos, 35, 7);
    if (mm < 10) xpos += ttgo->tft->drawChar('0', xpos, 35, 7);
    ttgo->tft->drawNumber(mm, xpos, 35, 7);

    // Display Battery Level
    ttgo->tft->setTextSize(1);
    ttgo->tft->setTextColor(TFT_YELLOW);
    ttgo->tft->drawString("Power", 124, 2, 2);
    ttgo->tft->setTextColor(TFT_GREEN);
    int per = ttgo->power->getBattPercentage();
    per = ttgo->power->getBattPercentage();
    ttgo->tft->drawString(String(per) + "%", 179, 2, 2);
    ttgo->tft->setTextColor(TFT_GREENYELLOW);
    ttgo->tft->drawString(String(dday), 50, 188, 6);

    // Turn off the battery adc <-- WHY!!!!
    ttgo->power->adc1Enable(AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_BATT_VOL_ADC1, false);

    // Draw Month
    String mStr;
    switch (mmonth) {
      case 1: mStr = "Jan"; break;
      case 2: mStr = "Feb"; break;
      case 3: mStr = "Mar"; break;
      case 4: mStr = "Apr"; break;
      case 5: mStr = "May"; break;
      case 6: mStr = "Jun"; break;
      case 7: mStr = "Jul"; break;
      case 8: mStr = "Aug"; break;
      case 9: mStr = "Sep"; break;
      case 10: mStr = "Oct"; break;
      case 11: mStr = "Nov"; break;
      case 12: mStr = "Dec"; break;
    }
    ttgo->tft->setTextColor(TFT_WHITE);
    ttgo->tft->drawString(mStr, 9, 194, 2);
  }

  // Build a bargraph for 10 seconds...
  // makinkg sure to show at least 1 complete cycle.
  //count = 0;
  rs = tnow.second;
  int secmod = rs % 10; // Show growing bar for 10 seconds
  if (secmod) { 
    ttgo->tft->fillRect(126 + secmod * 10, 215, 6, 15, TFT_ORANGE);  
  } else {
      ttgo->tft->fillRoundRect(119, 210, 120, 29, 15, TFT_DARKCYAN);
      count = count + 1;
    }
  if (count > disptime) {
    count = 0;
    ttgo->displaySleep();
    WiFi.mode(WIFI_OFF);
    //setCpuFrequencyMhz(20);
    ttgo->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ, true);
    ttgo->power->setPowerOutPut(AXP202_LDO2, false);
    ttgo->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ, true);
    ttgo->power->clearIRQ();
    esp_sleep_enable_ext1_wakeup(GPIO_SEL_35, ESP_EXT1_WAKEUP_ALL_LOW);
    count = 0;
    //ttgo->powerOff();
    esp_deep_sleep_start();
  } else {
      count = count + 1;
    }
}
