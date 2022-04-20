/*
    This file is part of ESP3DLib library for 3D printer.

    ESP3DLib library for Marlin 3D printer  for 3D printer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ESP3DLib library for Marlin 3D printer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this Firmware.  If not, see <http://www.gnu.org/licenses/>.

    Main author: luc lebosse

*/
//#define ESP_DEBUG_FEATURE DEBUG_OUTPUT_SERIAL0
#include "include/esp3d_config.h"

#if defined(ESP3DLIB_ENV)
#include "esp3dlib.h"
//to make it work with Platformio library detection
//TODO: remove as soon as Platformio library detection is fixed
#if FILESYSTEM_FEATURE == ESP_LITTLEFS_FILESYSTEM
#include <LittleFS.h>
#endif //FILESYSTEM_FEATURE
#include "core/esp3d.h"
#include "core/esp3doutput.h"
#include "core/commands.h"
#include <soc/rtc_wdt.h>
#ifdef SDSUPPORT
#include "modules/filesystem/esp_sd.h"
#endif //SDSUPPORT


Esp3DLib esp3dlib;

Esp3D myesp3d;

void ESP3DLibTaskfn( void * parameter )
{
    //Start esp3d
    myesp3d.begin();
    //Main loop
    for(;;) {
        myesp3d.handle();
        rtc_wdt_feed();
        vTaskDelay(1 / portTICK_RATE_MS);
    }
    vTaskDelete( Hal::xHandle );
}


//Contructor
Esp3DLib::Esp3DLib()
{
    //nothing to do
}

//Begin which setup everything
void Esp3DLib::init()
{


}
//Parse command
bool Esp3DLib::parse(char * cmd)
{
    if (myesp3d.started() && esp3d_commands.is_esp_command((uint8_t *)cmd, strlen(cmd))) {
        //command come from other serial port
        ESP3DOutput  output(ESP_ECHO_SERIAL_CLIENT);
        esp3d_commands.process((uint8_t *)cmd, strlen(cmd),& output, LEVEL_ADMIN);
        return true;
    }
    return false;
}

bool Esp3DLib::isSdUsed()
{
#ifdef SDSUPPORT
    return ESP_SD::isEnabled();
#else
    return false;
#endif //SDSUPPORT

}

//Idletask when setup is done
void Esp3DLib::idletask()
{
    static uint8_t count=0;
    if (count < 5) {
        count++;
        if (count==4) {
            //Create esp3d task
            xTaskCreatePinnedToCore(
                ESP3DLibTaskfn, /* Task function. */
                "ESP3DLib Task", /* name of task. */
                8192, /* Stack size of task */
                NULL, /* parameter of the task */
                ESP3DLIB_RUNNING_PRIORITY, /* priority of the task */
                &(Hal::xHandle), /* Task handle to keep track of created task */
                ESP3DLIB_RUNNING_CORE    /* Core to run the task */
            );
#ifdef DISABLE_WDT_ESP3DLIB_TASK
            esp_task_wdt_delete(Hal::xHandle);
#endif //DISABLE_WDT_ESP3DLIB_TASK 
        }
    }
    Hal::wait (0);  // Yield to other tasks
}
#endif //ESP3DLIB_ENV
