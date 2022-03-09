/*
 ESP200.cpp - ESP3D command class

 Copyright (c) 2014 Luc Lebosse. All rights reserved.

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with This code; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "../../include/esp3d_config.h"
#if defined (SD_DEVICE)
#include "../commands.h"
#include "../esp3doutput.h"
#include "../settings_esp3d.h"
#include "../../modules/filesystem/esp_sd.h"
#include "../../modules/authentication/authentication_service.h"
//Get SD Card Status
//[ESP200] json=<YES/NO> <RELEASESD> <REFRESH> pwd=<user/admin password>
bool Commands::ESP200(const char* cmd_params, level_authenticate_type auth_type, ESP3DOutput * output)
{
    (void)cmd_params;
#ifdef AUTHENTICATION_FEATURE
    if (auth_type == LEVEL_GUEST) {
        output->printERROR("Wrong authentication!", 401);
        return false;
    }
#else
    (void)auth_type;
#endif //AUTHENTICATION_FEATURE
    String resp = "No SD card";
    bool json = has_tag (cmd_params, "json");
    bool releaseSD = has_tag (cmd_params, "RELEASE");
    bool refreshSD = has_tag (cmd_params, "REFRESH");
    if (releaseSD) {
        ESP_SD::releaseSD();
        if (!json) {
            output->printMSG ("SD card released");
        } else {
            resp = "{\"status\": \"released\"}";
            output->printMSG (resp.c_str());
        }
        return true;
    }
    if (!ESP_SD::accessSD()) {
        if (ESP_SD::getState() == ESP_SDCARD_BUSY) {
            resp="Busy";
        } else {
            resp = "Not available";
        }
    } else {
        int8_t state = ESP_SD::getState(true);
        if (state == ESP_SDCARD_IDLE) {
            resp="SD card detected";
            if (refreshSD) {
                ESP_SD::refreshStats(true);
            }
        }
        ESP_SD::releaseSD();
    }
    if (json) {
        resp = "{\"status\": \""+resp+"\"}";
    }
    output->printMSG (resp.c_str());
    return true;
}

#endif //SD_DEVICE
