/*
 ESP410.cpp - ESP3D command class

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
//Get available AP list (limited to 30)
//output is JSON or plain text according parameter
//[ESP410]json=<no>
#define COMMANDID   410
bool Commands::ESP410(const char* cmd_params, level_authenticate_type auth_type, ESP3DOutput * output)
{
    bool noError = true;
    bool json = has_tag (cmd_params, "json");
    String response;
    String parameter;
    int errorCode = 200; //unless it is a server error use 200 as default and set error in json instead

#ifdef AUTHENTICATION_FEATURE
    if (auth_type == LEVEL_GUEST) {
        response = format_response(COMMANDID, json, false, "Guest user can't use this command");
        noError = false;
        errorCode = 401;
    }
#else
    (void)auth_type;
#endif //AUTHENTICATION_FEATURE
    if (noError) {
        parameter = clean_param(get_param (cmd_params, ""));
        if (parameter.length() == 0) {
            //Backup current mode
            uint8_t currentmode = WiFi.getMode();
            bool plain = has_tag(cmd_params,"plain");
            int n = 0;
            uint8_t total = 0;
            if (!json) {
                output->printLN ("Start Scan");
            }
            if(currentmode==WIFI_AP) {
                WiFi.mode(WIFI_AP_STA);
            }
            n = WiFi.scanNetworks ();
            if(currentmode==WIFI_AP) {
                WiFi.mode((WiFiMode_t)currentmode);
            }
            if (json) {
                output->print ("{\"cmd\":\"410\",\"status\":\"ok\",\"data\":[");
            }
            for (int i = 0; i < n; ++i) {
                if (WiFi.RSSI (i)>= MIN_RSSI) {
                    if (total > 0) {
                        if (json) {
                            output->print (",");
                        } else {
                            output->printLN ("");
                        }
                    }
                    total++;
                    if (json) {
                        output->print ("{\"SSID\":\"");
                        output->print (ESP3DOutput::encodeString(WiFi.SSID (i).c_str()));
                    } else {
                        output->print (WiFi.SSID (i).c_str());
                    }
                    if (json) {
                        output->print ("\",\"SIGNAL\":\"");
                    } else {
                        output->print ("\t");
                    }
                    output->print (String(WiFiConfig::getSignal (WiFi.RSSI (i) )));
                    if (!json) {
                        output->print("%");
                    }
                    if (json) {
                        output->print ("\",\"IS_PROTECTED\":\"");
                    }
                    if (WiFi.encryptionType (i) == ENC_TYPE_NONE) {
                        if (json) {
                            output->print ("0");
                        } else {
                            output->print ("\tOpen");
                        }
                    } else {
                        if (json) {
                            output->print ("1");
                        } else {
                            output->print ("\tSecure");
                        }
                    }
                    if (json) {
                        output->print ("\"}");
                    }
                }
            }
            WiFi.scanDelete();
            if (json) {
                output->printLN ("]}");
            } else {
                if(total>0) {
                    output->printLN ("");
                }
                output->printLN ("End Scan");
            }
            return true;
        } else {
            response = format_response(COMMANDID, json, false, "This command doesn't take parameters");
            noError = false;
        }
    }
    if (noError) {
        if (json) {
            output->printLN (response.c_str() );
        } else {
            output->printMSG (response.c_str() );
        }
    } else {
        output->printERROR(response.c_str(), errorCode);
    }
    return noError;
}

#endif //WIFI_FEATURE
