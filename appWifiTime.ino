// Set time from WiFi.

#include <WiFi.h>
#include "time.h"
#include "user_cfg.h"

void appWiFiTime() {

  // WiFi settings ******* Use your network values **********
  const char* ssid     = wlSSID1;
  const char* password = wlPASS1;

  const char* ntpServer = "pool.ntp.org";
  const long  gmtOffset_sec = offsetNTP;
  const int   daylightOffset_sec = 3600;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {}

  configTime(offsetNTP, 3600 , "pool.ntp.org", "time.nis.gov");
  delay(3000);

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    ttgo->tft->drawString("Failed",  5, 30, 1);
  } else {
    ttgo->tft->setCursor(0, 130);
    ttgo->tft->print(&timeinfo, "%A, %B %d %Y\n%H:%M:%S");
    ttgo->rtc->setDateTime(timeinfo.tm_year, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  }

  delay(5000);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  ttgo->tft->fillScreen(TFT_BLACK);
}
