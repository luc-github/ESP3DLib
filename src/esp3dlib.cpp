/*
    This file is part of ESP3DLib library for 3D printer.

    ESP3D Firmware for 3D printer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ESP3D Firmware for 3D printer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this Firmware.  If not, see <http://www.gnu.org/licenses/>.

    This firmware is using the standard arduino IDE with module to support ESP8266/ESP32:
    https://github.com/esp8266/Arduino
    https://github.com/espressif/arduino-esp32

    Latest version of the code and documentation can be found here :
    https://github.com/luc-github/ESP3D

    Main author: luc lebosse

*/
#include "esp3dlibconfig.h"

#if defined(ESP3D_WIFISUPPORT)
#include "esp3dlib.h"
#include "wificonfig.h"

#include MARLIN_PATH(core/serial.h)

Esp3DLib esp3dlib;

void WiFiTaskfn( void * parameter )
{
    wifi_config.wait(100);  // Yield to other tasks
    WiFiConfig::begin();
    for(;;) {
        wifi_config.handle();
        wifi_config.wait(0);  // Yield to other tasks
    }
    vTaskDelete( NULL );
}


//Contructor
Esp3DLib::Esp3DLib()
{

}

//Begin which setup everything
void Esp3DLib::init()
{
    xTaskCreatePinnedToCore(
        WiFiTaskfn, /* Task function. */
        "WiFi Task", /* name of task. */
        10000, /* Stack size of task */
        NULL, /* parameter of the task */
        1, /* priority of the task */
        NULL, /* Task handle to keep track of created task */
        0 	 /* Core to run the task */
    );
}
//Parse command
bool Esp3DLib::parse(char * cmd)
{
	String scmd = cmd;
	if (scmd.startsWith("[ESP")) {
		
		return true;
	} else {
		return false;
	}
	
}
#endif //ESP3D_WIFISUPPORT
