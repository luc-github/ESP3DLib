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
#include "include/esp3dlib_config.h"

#if defined(ESP3D_WIFISUPPORT)
#include "esp3dlib.h"
#include "core/hal.h"

Esp3DLib esp3dlib;

#ifndef DELAY_START_ESP3D
#define DELAY_START_ESP3D 100
#endif //DELAY_START_ESP3D

void ESP3DLibTaskfn( void * parameter )
{
    Hal::wait (DELAY_START_ESP3D);  // Yield to other tasks
    //Setup Network
    //TODO

    //Main loop
    for(;;) {
        Hal::wait (0);  // Yield to other tasks
    }
    vTaskDelete( NULL );
}


//Contructor
Esp3DLib::Esp3DLib()
{
    //nothing to do
}

//Begin which setup everything
void Esp3DLib::init()
{
    xTaskCreatePinnedToCore(
        ESP3DLibTaskfn, /* Task function. */
        "ESP3DLib Task", /* name of task. */
        8192, /* Stack size of task */
        NULL, /* parameter of the task */
        ESP3DLIB_RUNNING_PRIORITY, /* priority of the task */
        NULL, /* Task handle to keep track of created task */
        ESP3DLIB_RUNNING_CORE    /* Core to run the task */
    );
}
//Parse command
bool Esp3DLib::parse(char * cmd)
{
    //TODO
    return false;
}

//Idletask when setup is done
void Esp3DLib::idletask()
{
    static bool setupdone = false;
    if (!setupdone) {
        //Setup wifi
        //TODO
        setupdone = true;
    }
}
#endif //ESP3D_WIFISUPPORT
