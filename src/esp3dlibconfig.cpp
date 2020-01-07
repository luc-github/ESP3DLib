/*
  esp3dconfig.cpp -  wifi functions class

  Copyright (c) 2014 Luc Lebosse. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "esp3dlibconfig.h"
#if defined(ESP3D_WIFISUPPORT)
#include <Arduino.h>
#ifdef __cplusplus
extern "C" {
#endif
esp_err_t esp_task_wdt_reset();
#ifdef __cplusplus
}
#endif

bool Esp3DLibConfig::restart_ESP_module = false;

/*
 * delay is to avoid sometimes and may not enough neither
 */
void Esp3DLibConfig::wait(uint32_t milliseconds){
    uint32_t timeout = millis();
    vTaskDelay(1 / portTICK_RATE_MS);  // Yield to other tasks
    esp_task_wdt_reset(); //for a wait 0;
    //wait feeding WDT
    while ( (millis() - timeout) < milliseconds) {
       esp_task_wdt_reset();
       vTaskDelay(1 / portTICK_RATE_MS);  // Yield to other tasks
    }
}

/**
 * Restart ESP
 */
void Esp3DLibConfig::restart_ESP(){
    restart_ESP_module=true;
}

/**
 * Handle not critical actions that must be done in sync environement
 */
void Esp3DLibConfig::handle() {
    //in case of restart requested
    if (restart_ESP_module) {
        ESP.restart();
        while (1) {};
    }
}

#endif // ESP3D_WIFISUPPORT
