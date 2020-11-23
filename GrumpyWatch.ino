// An Arduino based framework for the Lilygo T-Watch 2020
// Much of the code is based on the sample apps for the
// T-watch that were written and copyrighted by Lewis He.
//(Copyright (c) 2019 lewis he)


// Based on Dan Geiger's modifications, found on:
// https://www.instructables.com/Lilygo-T-Watch-2020-Arduino-Framework/
// Hacks and mods by Uncle Grumpy 2020

#include "config.h"
#include <soc/rtc.h>

TTGOClass *ttgo;

uint32_t targetTime = 0;       // for next 1 second display update
// uint32_t clockUpTime = 0;      // track the time the clock is displayed

uint8_t hh, mm, rs, ss, mmonth, dday; // H, M, S variables
uint16_t yyear; // Year is 16 bit int
int step_counter, last_step_counter;
bool irq = false;
int count = 0;


void setup() {
  //initSetup();
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->tft->setTextFont(1);
  ttgo->tft->fillScreen(TFT_BLACK);
  ttgo->tft->setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour
  //Initialize lvgl
  ttgo->lvgl_begin();

  //Check if the RTC clock matches, if not, use compile time
  ttgo->rtc->check();

  //Synchronize time to system time
  ttgo->rtc->syncToSystem();

  //Enable Buzzer/motor
  pinMode(4, OUTPUT);

  pinMode(AXP202_INT, INPUT_PULLUP);
    attachInterrupt(AXP202_INT, [] {
        irq = true;
    }, FALLING);

  // Turn on the IRQ used
  ttgo->power->adc1Enable(AXP202_BATT_VOL_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1, AXP202_ON);
  //ttgo->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ, true);
  //ttgo->power->clearIRQ();

  // Turn off unused power  
  ttgo->power->setPowerOutPut(AXP202_EXTEN, AXP202_OFF);
  ttgo->power->setPowerOutPut(AXP202_DCDC2, AXP202_OFF);
  ttgo->power->setPowerOutPut(AXP202_LDO3, AXP202_OFF); // audio device
  ttgo->power->setPowerOutPut(AXP202_LDO4, AXP202_OFF);

  ttgo->openBL(); // Turn on the backlight
 // displayTime(true); // Our GUI to show the time

}

void buzz() {
  digitalWrite(4, HIGH);
  delay(30);
  digitalWrite(4, LOW);
  delay(10);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(4, LOW);

}

void update_step_counter (void) {
  // updateStepCounter(ttgo->bma->getCounter());
  step_counter = ttgo->bma->getCounter();

}

void resetStepCounter(void) {
  ttgo->bma->resetStepCounter();
  step_counter = 0;

}

void loop() {

  if (targetTime < millis()) {
    targetTime = millis() + 1000;
    displayTime(ss == 0); // Call every second but only update time every minute
  }

  int16_t x, y;
  if (ttgo->getTouch(x, y)) {
    while (ttgo->getTouch(x, y)) {} // wait for user to release

    // This is where the app selected from the menu is launched
    // If you add an app, follow the variable update instructions
    // at the beginning of the menu code and then add a case
    // statement on to this switch to call your paticular
    // app routine.

    switch (modeMenu()) { // Call modeMenu. The return is the desired app number
      case 0: // Zero is the clock, just exit the switch
        break;
      case 1:
        jSats();
        break;
      case 2:
        appAccel();
        break;
      case 3:
        appBattery();
        break;
      case 4:
        HallRead();
        break;
      case 5:
        appSetTime();
        break;
      case 6:
        buzz();
        break;
      case 7:
        appTemp();
        break;
      case 8:
        appGrumpyWiFi();
        break;
      case 9:
        appWiFiTime();
        break;
      case 10:
        resetStepCounter();
        break;
    }
    displayTime(true);
  }

}
