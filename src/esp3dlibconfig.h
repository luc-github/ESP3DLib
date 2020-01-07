/*
  esp3dlibconfig.h -  esp3dlib functions class

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
//config reference, do not touxh
#define XSTR_(M) #M
#define XSTR(M) XSTR_(M)
#define MARLIN_PATH(PATH) XSTR(../../../../../Marlin/src/PATH)
#include MARLIN_PATH(inc/MarlinConfigPre.h)
#undef DISABLED
#undef _BV
//version
#define LIB_VERSION "1.0.0"

//Editable configuration part

//AUTHENTICATION_FEATURE: protect pages by login password
//#define AUTHENTICATION_FEATURE

//HTTP_FEATURE: enable Web Server
//Rely on Configuration_adv.h 
#ifdef WEBSUPPORT
#define HTTP_FEATURE
#endif //WEBSUPPORT

//OTA_FEATURE: this feature is arduino update over the air
//Rely on Configuration_adv.h 
#ifdef OTASUPPORT
#define OTA_FEATURE
#endif //OTASUPPORT

//MDNS_FEATURE: this feature allow  type the name defined
//in web browser by default: http:\\marlinesp.local and connect
#define MDNS_FEATURE

//SSDD_FEATURE: this feature is a discovery protocol, supported on Windows out of the box
#define SSDP_FEATURE

//CAPTIVE_PORTAL_FEATURE: In SoftAP redirect all unknow call to main page
#define CAPTIVE_PORTAL_FEATURE

//for Debug this can be disabled
#define ENABLE_SERIAL2SOCKET_OUT
#define ENABLE_SERIAL2SOCKET_IN

//Preferences entries
#define NAMESPACE "MARLIN"
#define HOSTNAME_ENTRY "ESP_HOSTNAME"
#define STA_SSID_ENTRY "STA_SSID"
#define STA_PWD_ENTRY "STA_PWD"
#define STA_IP_ENTRY "STA_IP"
#define STA_GW_ENTRY "STA_GW"
#define STA_MK_ENTRY "STA_MK"
#define ESP_WIFI_MODE "WIFI_MODE"
#define AP_SSID_ENTRY "AP_SSID"
#define AP_PWD_ENTRY "AP_PWD"
#define AP_IP_ENTRY "AP_IP"
#define AP_CHANNEL_ENTRY "AP_CHANNEL"
#define HTTP_ENABLE_ENTRY "HTTP_ON"
#define HTTP_PORT_ENTRY "HTTP_PORT"
#define TELNET_ENABLE_ENTRY "TELNET_ON"
#define TELNET_PORT_ENTRY "TELNET_PORT"
#define STA_IP_MODE_ENTRY "STA_IP_MODE"

//Switch 
#define ESP_SAVE_ONLY 0
#define ESP_APPLY_NOW 1


