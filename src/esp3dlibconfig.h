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
#define LIB_VERSION "0.9.0"

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
#define ESP_RADIO_MODE "WIFI_MODE"
#define AP_SSID_ENTRY "AP_SSID"
#define AP_PWD_ENTRY "AP_PWD"
#define AP_IP_ENTRY "AP_IP"
#define AP_CHANNEL_ENTRY "AP_CHANNEL"
#define HTTP_ENABLE_ENTRY "HTTP_ON"
#define HTTP_PORT_ENTRY "HTTP_PORT"
#define TELNET_ENABLE_ENTRY "TELNET_ON"
#define TELNET_PORT_ENTRY "TELNET_PORT"
#define STA_IP_MODE_ENTRY "STA_IP_MODE"

//Wifi Mode
#define ESP_RADIO_OFF 0
#define ESP_WIFI_STA 1
#define ESP_WIFI_AP  2

#define DHCP_MODE   0
#define STATIC_MODE   0

//defaults values
#define DEFAULT_HOSTNAME "marlinesp"
#define DEFAULT_STA_SSID "MARLIN_ESP"
#define DEFAULT_STA_PWD "12345678"
#define DEFAULT_STA_IP "0.0.0.0"
#define DEFAULT_STA_GW "0.0.0.0"
#define DEFAULT_STA_MK "0.0.0.0"
#define DEFAULT_STA_IP_MODE DHCP_MODE
#define DEFAULT_RADIO_MODE ESP_WIFI_AP
#define DEFAULT_AP_SSID "MARLIN_ESP"
#define DEFAULT_AP_PWD "12345678"
#define DEFAULT_AP_IP "192.168.0.1"
#define DEFAULT_AP_MK "255.255.255.0"
#define DEFAULT_AP_CHANNEL 1
#define DEFAULT_WEBSERVER_PORT 80
#define DEFAULT_HTTP_STATE 1
#define HIDDEN_PASSWORD "********"

//boundaries
#define MAX_SSID_LENGTH         32
#define MIN_SSID_LENGTH         1
#define MAX_PASSWORD_LENGTH     64
//min size of password is 0 or upper than 8 char
//so let set min is 8
#define MIN_PASSWORD_LENGTH     8
#define MAX_HOSTNAME_LENGTH     32
#define MIN_HOSTNAME_LENGTH     1
#define MAX_HTTP_PORT			65001
#define MIN_HTTP_PORT			1
#define MAX_TELNET_PORT			65001
#define MIN_TELNET_PORT			1
#define MIN_CHANNEL			1
#define MAX_CHANNEL			14

#ifndef ESP3DLIBCONFIG_H
#define ESP3DLIBCONFIG_H
class Esp3DLibConfig {
public:
    static void wait(uint32_t milliseconds);
    static void restart_ESP();
    static void handle();
    static void reset_settings();
private:
	static bool restart_ESP_module;
};
#endif //ESP3DLIBCONFIG_H
