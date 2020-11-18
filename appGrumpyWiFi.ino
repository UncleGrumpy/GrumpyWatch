/*
 * 
 * The MIT License (MIT)
 * 
 *
 * Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
 * Copyright (c) 2018 by Fabrice Weinberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ThingPulse invests considerable time and money to develop these open source libraries.
 * Please support us by buying our products (and not the clones) from
 * https://thingpulse.com
 * 
 * 
 * TTGO-T-Watch2020 Wifi Network Scanner v1.0
 * 
 * Copyright (c) 2020 by UncleGrumpy (Winford)
 * 
 * This is a WiFi network scanner written for TTGO-T-Watch2020
 * This code was construced entirely from the examples provided by the standard and
 * TTGO-T-Watch libraries.
 *
 */

#include <WiFi.h>
#include "time.h"


void appGrumpyWiFi() {  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  ttgo->tft->setTextSize(1);
  delay(100);
  int l = 6;
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  if (n == 0) {
    ttgo->tft->drawString("No networks!", 24, 32, 4);
  } else {
    String netNum = String("Networks Found: " + String((n)));
    ttgo->tft->drawString(netNum, 0, l, 4);
    l = l + 32;
    for (int i = 0; i < n; ++i) {
      // Print SSID, RSSI and encryption for each network found
      String netName = String((WiFi.SSID(i)));
      String netChn = String((WiFi.channel(i)));
      String netDb = String((WiFi.RSSI(i)));
      String netEnc = String(((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*" ));
      ttgo->tft->drawString(netName+" ("+netChn+") "+netDb+ "% "+netEnc, 0, l, 2 );
      l = l + 24;
      }
  }
   // Wait for touch to return
  int16_t x, y;
  while (!ttgo->getTouch(x, y)) {} // Wait for touch
  while (ttgo->getTouch(x, y)) {}  // Wait for release
  ttgo->tft->fillScreen(TFT_BLACK);
}
