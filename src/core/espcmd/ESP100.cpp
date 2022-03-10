/*
 ESP100.cpp - ESP3D command class

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
#if defined (WIFI_FEATURE)
#include "../commands.h"
#include "../esp3doutput.h"
#include "../settings_esp3d.h"
#include "../../modules/wifi/wificonfig.h"
#include "../../modules/authentication/authentication_service.h"
//STA SSID
//[ESP100]<SSID>[json=yes][pwd=<admin password>]
bool Commands::ESP100(const char* cmd_params, level_authenticate_type auth_type, ESP3DOutput * output)
{
    bool noError = true;
    bool json = has_tag (cmd_params, "json");
    String response;
    String parameter;
#ifdef AUTHENTICATION_FEATURE
    if (auth_type == LEVEL_GUEST) {
        response = format_response(100, json, false, "Guest user can't use this command");
        noError = false;
    }
#else
    (void)auth_type;
#endif //AUTHENTICATION_FEATURE
    if (noError) {
        parameter = clean_param(get_param (cmd_params, ""));
        //get
        if (parameter.length() == 0) {
            response = format_response(100, json, true, Settings_ESP3D::read_string(ESP_STA_SSID));
        } else { //set
#ifdef AUTHENTICATION_FEATURE
            if (auth_type != LEVEL_ADMIN) {
                response = format_response(100, json, false, "Wrong authentication level");
                noError = false;
            }
#endif //AUTHENTICATION_FEATURE
            if (noError) {
                if (!WiFiConfig::isSSIDValid (parameter.c_str() ) ) {
                    response = format_response(100, json, false, "Incorrect SSID");
                    noError = false;
                } else {
                    if(!Settings_ESP3D::write_string(ESP_STA_SSID, parameter.c_str())) {
                        response = format_response(100, json, false, "Set failed");
                        noError = false;
                    } else {
                        response = format_response(100, json, true, "ok");
                    }
                }
            }
        }
    }
    if (noError) {
        output->printMSG (response.c_str() );
    } else {
        output->printERROR(response.c_str(), 401);
    }
    return noError;
}

#endif //WIFI_FEATURE
