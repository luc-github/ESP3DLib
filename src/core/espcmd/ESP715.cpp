/*
 ESP715.cpp - ESP3D command class

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
#include "../../modules/authentication/authentication_service.h"
#include "../../modules/filesystem/esp_sd.h"
//Format SD Filesystem
//[ESP715]FORMATSD pwd=<admin password>
bool Commands::ESP715(const char* cmd_params, level_authenticate_type auth_type, ESP3DOutput * output)
{
    bool noError = true;
    String res;
    bool json = has_tag(cmd_params, "json");
    bool formatSD = has_tag (cmd_params, "FORMATSD");
#ifdef AUTHENTICATION_FEATURE
    if (auth_type != LEVEL_ADMIN) {
        output->printERROR("Wrong authentication!", 401);
        response = false;
    } else
#else
    (void)auth_type;
#endif //AUTHENTICATION_FEATURE
    {
        if (formatSD) {
            if (!ESP_SD::accessSD()) {
                res ="Not available!";
                noError = false;
            } else {
                ESP_SD::setState(ESP_SDCARD_BUSY);
                if (!json) {
                    output->print("Start Formating...");
                }
                if (ESP_SD::format(output)) {
                    res= "Format Done";
                } else {
                    res="Format failed!";
                    noError = false;
                }
                ESP_SD::releaseSD();
            }
        } else {
            res = "Invalid parameter!";
            noError = false;
        }
    }
    if (json) {
        output->print("{\"status\":\"");
        output->print(noError ? "ok" : "error");
        output->print("\",\"message\":\"");
        output->print(res.c_str());
        output->printLN("\"}");
    } else {
        if(noError) {
            output->printMSG(res.c_str());
        } else {
            output->printERROR(res.c_str());
        }
    }
    return noError;
}

#endif //SD_DEVICE
