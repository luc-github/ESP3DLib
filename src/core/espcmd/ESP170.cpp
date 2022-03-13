/*
 ESP122.cpp - ESP3D command class

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
#if defined (CAMERA_DEVICE)
#include "../commands.h"
#include "../esp3doutput.h"
#include "esp_camera.h"
#include "../settings_esp3d.h"
#include "../../modules/authentication/authentication_service.h"
#include "../../modules/camera/camera.h"
#define COMMANDID   170
//Set Camera command value / list all values in JSON/plain
//[ESP170]<plain><label=value> pwd=<admin password>
//label can be: light/framesize/quality/contrast/brightness/saturation/gainceiling/colorbar
//             /awb/agc/aec/hmirror/vflip/awb_gain/agc_gain/aec_value/aec2/cw/bpc/wpc
//             /raw_gma/lenc/special_effect/wb_mode/ae_level
bool Commands::ESP170(const char* cmd_params, level_authenticate_type auth_type, ESP3DOutput * output)
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
    if(noError) {
        if (!esp3d_camera.started()) {
            response = format_response(COMMANDID, json, false, "No camera initialized");
            noError = false;
        } else {
            parameter = clean_param(get_param (cmd_params, ""));
            //get
            if (parameter.length() == 0)) {
                sensor_t * s = esp_camera_sensor_get();
                if (s == nullptr) {
                    response = format_response(COMMANDID, json, false, "No camera initialized");
                    noError = false;
                } else {
                    if (json) {
                        output->print ("{\"cmd\":\"170\",\"status\":\"ok\",\"data\":\"[");
                    }
                    //framesize
                    if (json) {
                        output->print ("{\"id\":\"framesize\",\"value\":\"");
                    } else {
                        output->print ("framesize:");
                    }
                    output->print (s->status.framesize);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //quality
                    if (json) {
                        output->print ("{\"id\":\"quality\",\"value\":\"");
                    } else {
                        output->print ("quality:");
                    }
                    output->print (s->status.quality);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //brightness
                    if (json) {
                        output->print ("{\"id\":\"brightness\",\"value\":\"");
                    } else {
                        output->print ("brightness:");
                    }
                    output->print (s->status.brightness);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //contrast
                    if (json) {
                        output->print ("{\"id\":\"contrast\",\"value\":\"");
                    } else {
                        output->print ("contrast:");
                    }
                    output->print (s->status.contrast);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //saturation
                    if (json) {
                        output->print ("{\"id\":\"saturation\",\"value\":\"");
                    } else {
                        output->print ("saturation:");
                    }
                    output->print (s->status.saturation);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //sharpness
                    if (json) {
                        output->print ("{\"id\":\"sharpness\",\"value\":\"");
                    } else {
                        output->print ("sharpness:");
                    }
                    output->print (s->status.sharpness);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //special_effect
                    if (json) {
                        output->print ("{\"id\":\"special_effect\",\"value\":\"");
                    } else {
                        output->print ("special_effect:");
                    }
                    output->print (s->status.special_effect);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //wb_mode
                    if (json) {
                        output->print ("{\"id\":\"wb_mode\",\"value\":\"");
                    } else {
                        output->print ("wb_mode:");
                    }
                    output->print (s->status.wb_mode);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //awb
                    if (json) {
                        output->print ("{\"id\":\"awb\",\"value\":\"");
                    } else {
                        output->print ("awb:");
                    }
                    output->print (s->status.awb);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //awb_gain
                    if (json) {
                        output->print ("{\"id\":\"awb_gain\",\"value\":\"");
                    } else {
                        output->print ("awb_gain:");
                    }
                    output->print (s->status.awb_gain);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //aec
                    if (json) {
                        output->print ("{\"id\":\"aec\",\"value\":\"");
                    } else {
                        output->print ("aec:");
                    }
                    output->print (s->status.aec);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //aec2
                    if (json) {
                        output->print ("{\"id\":\"aec2\",\"value\":\"");
                    } else {
                        output->print ("aec2:");
                    }
                    output->print (s->status.aec2);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //ae_level
                    if (json) {
                        output->print ("{\"id\":\"ae_level\",\"value\":\"");
                    } else {
                        output->print ("ae_level:");
                    }
                    output->print (s->status.ae_level);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //aec_value
                    if (json) {
                        output->print ("{\"id\":\"aec_value\",\"value\":\"");
                    } else {
                        output->print ("aec_value:");
                    }
                    output->print (s->status.aec_value);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //agc
                    if (json) {
                        output->print ("{\"id\":\"agc\",\"value\":\"");
                    } else {
                        output->print ("agc:");
                    }
                    output->print (s->status.agc);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //agc_gain
                    if (json) {
                        output->print ("{\"id\":\"agc_gain\",\"value\":\"");
                    } else {
                        output->print ("agc_gain:");
                    }
                    output->print (s->status.agc_gain);
                    if (!plain) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //gainceiling
                    if (json) {
                        output->print ("{\"id\":\"gainceiling\",\"value\":\"");
                    } else {
                        output->print ("gainceiling:");
                    }
                    output->print (s->status.gainceiling);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //bpc
                    if (json) {
                        output->print ("{\"id\":\"bpc\",\"value\":\"");
                    } else {
                        output->print ("bpc:");
                    }
                    output->print (s->status.bpc);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //wpc
                    if (json) {
                        output->print ("{\"id\":\"wpc\",\"value\":\"");
                    } else {
                        output->print ("wpc:");
                    }
                    output->print (s->status.wpc);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //raw_gma
                    if (json) {
                        output->print ("{\"id\":\"raw_gma\",\"value\":\"");
                    } else {
                        output->print ("raw_gma:");
                    }
                    output->print (s->status.raw_gma);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //lenc
                    if (json) {
                        output->print ("{\"id\":\"lenc\",\"value\":\"");
                    } else {
                        output->print ("lenc:");
                    }
                    output->print (s->status.lenc);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //vflip
                    if (json) {
                        output->print ("{\"id\":\"vflip\",\"value\":\"");
                    } else {
                        output->print ("vflip:");
                    }
                    output->print (s->status.vflip);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //hmirror
                    if (json) {
                        output->print ("{\"id\":\"hmirror\",\"value\":\"");
                    } else {
                        output->print ("hmirror:");
                    }
                    output->print (s->status.hmirror);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //dcw
                    if (json) {
                        output->print ("{\"id\":\"dcw\",\"value\":\"");
                    } else {
                        output->print ("dcw:");
                    }
                    output->print (s->status.dcw);
                    if (json) {
                        output->print ("\"},");
                    } else {
                        output->printLN("");
                    }
                    //colorbar
                    if (json) {
                        output->print ("{\"id\":\"colorbar\",\"value\":\"");
                    } else {
                        output->print ("colorbar:");
                    }
                    output->print (s->status.colorbar);
                    if (json) {
                        output->print ("\"}");
                    } else {
                        output->printLN("");
                    }
#if CAM_LED_PIN != -1
                    //light
                    if (json) {
                        output->print ("{\"id\":\"light\",\"value\":\"");
                    } else {
                        output->print ("light:");
                    }
                    output->print (digitalRead(CAM_LED_PIN)==HIGH?1:0);
                    if (json) {
                        output->print ("\"}");
                    } else {
                        output->printLN("");
                    }
#endif //CAM_LED_PIN 
                    if (json) {
                        output->print ("]}");
                    }
                    return true
                }
            } else { //set
#ifdef AUTHENTICATION_FEATURE
                if (auth_type != LEVEL_ADMIN) {
                    response = format_response(COMMANDID, json, false, "Wrong authentication level");
                    noError = false;
                    errorCode = 401;
                }
#endif //AUTHENTICATION_FEATURE
                if (noError) {
                    String label = get_label (parameter.c_str(), "=");
                    if (label.length()==0) {
                        response = format_response(COMMANDID, json, false, "Missing command");
                        noError = false;
                    } else {
                        String labels = label+"=";
                        String value = get_param (cmd_params,labels.c_str());
                        if (value.length()==0) {
                            response = format_response(COMMANDID, json, false, "Invalid value");
                            noError = false;
                        }
                        if (noError) {
                            int r = esp3d_camera.command(label.c_str(), value.c_str());
                            if (r == -1) {
                                response = format_response(COMMANDID, json, false, "Unknow command");
                                noError = false;
                            } else if (r == 1) {
                                response = format_response(COMMANDID, json, false, "Invalid value");
                                noError = false;
                            } else {
                                response = format_response(COMMANDID, json, true, "ok");
                            }
                        }
                    }
                }
            }
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

#endif //CAMERA_DEVICE
