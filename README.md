# GrumpyWatch

Based on Dan Geiger's Instructable found on: https://www.instructables.com/Lilygo-T-Watch-2020-Arduino-Framework/
-
This firmware for the Lilygo TTGO-T-Watch-2020-v1 uses the LCARS interface, and has a several additional features.
Most importantly there is improved power management, implementing the ESP32's sleep funtion.

Touching the screen brings up the menu. Time can be set manually or by NTP with a configured wifi connection, see
above. The Jupiter app shows the current arrangement of Jupiter's four largest moons. The battery app gives the
volage, current, and battery percent remaining. Temp gives the board temperature. There are pointless demos of the
acceleronmeter, touch and hall sensor.  The wifi scanner shows signal strength and marks encrypted networks with *.

## Warning:
#### Before opening the GrumpyWatch.ino in Arduino:
	copy user_cfg.h.example >> user_cfg.h


user_cfg.h is used to configure wifi and timezone info for setting the clock with NTP. The display timeout is also set here.
	
I strongly recommend adding user_cfg.h to .gitignore in case you want to contribute you don't want to risk exposing
your credentials.
	
