# GrumpyWatch
Based on Dan Geiger's Instructable found on: https://www.instructables.com/Lilygo-T-Watch-2020-Arduino-Framework/

This firmware for the Lilygo TTGO-T-Watch-2020-v1 uses the LCARS interface, and has a wifi network scanner.
Wifi network and local timezone information are stored in user_cfg.h for setting the time from NTP.

Touching the screen brings up the menu. Time can be set manually or by NTP with a configured wifi connection, see
above. The Jupiter app shows the current arrangement of Jupiter's four largest moons. The battery app gives the
volage, current, and battery percent remaining. Temp gives the board temperature. There is a pointless demo of the
acceleronmeter.  The wifi scanner shows signal strength and marks encrypted networks with *.
	
This should work with ofher TTGO watches if config.h is edited to match your model.

