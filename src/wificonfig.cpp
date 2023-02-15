/*
  wificonfig.cpp -  wifi functions class

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
#include <WiFi.h>
#include <esp_wifi.h>
#include <ESPmDNS.h>
#include <FS.h>
#include <SPIFFS.h>
#include "espcom.h"
#include <Preferences.h>
#include "wificonfig.h"
#include "wifiservices.h"

/**
 * Helper to convert  IP string to int
 */

uint32_t WiFiConfig::IP_int_from_string(String & s)
{
    uint32_t ip_int = 0;
    IPAddress ipaddr;
    if (ipaddr.fromString(s)) {
        ip_int = ipaddr;
    }
    return ip_int;
}

/**
 * Helper to convert int to IP string
 */

String WiFiConfig::IP_string_from_int(uint32_t ip_int)
{
    IPAddress ipaddr(ip_int);
    return ipaddr.toString();
}

/**
 * Get current IP
 */
const char * WiFiConfig::currentIP()
{
    static String ip;
    if (WiFi.getMode() == WIFI_OFF) {
        ip = "";
    } else if (WiFi.getMode() == WIFI_STA) {
        ip =  WiFi.localIP().toString();
    } else {
        ip = WiFi.softAPIP().toString();
    }
    return ip.c_str();
}

/**
 * Check if Hostname string is valid
 */

bool WiFiConfig::isHostnameValid (const char * hostname)
{
    //limited size
    char c;
    if (strlen (hostname) > MAX_HOSTNAME_LENGTH || strlen (hostname) < MIN_HOSTNAME_LENGTH) {
        return false;
    }
    //only letter and digit
    for (int i = 0; i < strlen (hostname); i++) {
        c = hostname[i];
        if (! (isdigit (c) || isalpha (c) || c == '_') ) {
            return false;
        }
        if (c == ' ') {
            return false;
        }
    }
    return true;
}

/**
 * Check if SSID string is valid
 */

bool WiFiConfig::isSSIDValid (const char * ssid)
{
    //limited size
    //char c;
    if (strlen (ssid) > MAX_SSID_LENGTH || strlen (ssid) < MIN_SSID_LENGTH) {
        return false;
    }
    //only printable
    for (int i = 0; i < strlen (ssid); i++) {
        if (!isPrintable (ssid[i]) ) {
            return false;
        }
    }
    return true;
}

/**
 * Check if password string is valid
 */

bool WiFiConfig::isPasswordValid (const char * password)
{
    if (strlen (password) == 0) {
        return true;    //open network
    }
    //limited size
    if ((strlen (password) > MAX_PASSWORD_LENGTH) || (strlen (password) < MIN_PASSWORD_LENGTH)) {
        return false;
    }
    //no space allowed ?
    /*  for (int i = 0; i < strlen (password); i++)
          if (password[i] == ' ') {
              return false;
          }*/
    return true;
}

/**
 * Check if IP string is valid
 */
bool WiFiConfig::isValidIP(const char * string)
{
    IPAddress ip;
    return ip.fromString(string);
}


/**
 * WiFi events
 * SYSTEM_EVENT_WIFI_READY               < ESP32 WiFi ready
 * SYSTEM_EVENT_SCAN_DONE                < ESP32 finish scanning AP
 * SYSTEM_EVENT_STA_START                < ESP32 station start
 * SYSTEM_EVENT_STA_STOP                 < ESP32 station stop
 * SYSTEM_EVENT_STA_CONNECTED            < ESP32 station connected to AP
 * SYSTEM_EVENT_STA_DISCONNECTED         < ESP32 station disconnected from AP
 * SYSTEM_EVENT_STA_AUTHMODE_CHANGE      < the auth mode of AP connected by ESP32 station changed
 * SYSTEM_EVENT_STA_GOT_IP               < ESP32 station got IP from connected AP
 * SYSTEM_EVENT_STA_LOST_IP              < ESP32 station lost IP and the IP is reset to 0
 * SYSTEM_EVENT_STA_WPS_ER_SUCCESS       < ESP32 station wps succeeds in enrollee mode
 * SYSTEM_EVENT_STA_WPS_ER_FAILED        < ESP32 station wps fails in enrollee mode
 * SYSTEM_EVENT_STA_WPS_ER_TIMEOUT       < ESP32 station wps timeout in enrollee mode
 * SYSTEM_EVENT_STA_WPS_ER_PIN           < ESP32 station wps pin code in enrollee mode
 * SYSTEM_EVENT_AP_START                 < ESP32 soft-AP start
 * SYSTEM_EVENT_AP_STOP                  < ESP32 soft-AP stop
 * SYSTEM_EVENT_AP_STACONNECTED          < a station connected to ESP32 soft-AP
 * SYSTEM_EVENT_AP_STADISCONNECTED       < a station disconnected from ESP32 soft-AP
 * SYSTEM_EVENT_AP_PROBEREQRECVED        < Receive probe request packet in soft-AP interface
 * SYSTEM_EVENT_GOT_IP6                  < ESP32 station or ap or ethernet interface v6IP addr is preferred
 * SYSTEM_EVENT_ETH_START                < ESP32 ethernet start
 * SYSTEM_EVENT_ETH_STOP                 < ESP32 ethernet stop
 * SYSTEM_EVENT_ETH_CONNECTED            < ESP32 ethernet phy link up
 * SYSTEM_EVENT_ETH_DISCONNECTED         < ESP32 ethernet phy link down
 * SYSTEM_EVENT_ETH_GOT_IP               < ESP32 ethernet got IP from connected AP
 * SYSTEM_EVENT_MAX
 */

void WiFiConfig::WiFiEvent(WiFiEvent_t event)
{
    switch (event) {
    case SYSTEM_EVENT_STA_GOT_IP:
        Esp3DCom::echo ("Connected");
        Esp3DCom::echo(WiFi.localIP().toString());
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Esp3DCom::echo("WiFi not connected");
        break;
    default:
        break;
    }
}

/*
 * Get WiFi signal strength
 */
int32_t WiFiConfig::getSignal (int32_t RSSI)
{
    if (RSSI <= -100) {
        return 0;
    }
    if (RSSI >= -50) {
        return 100;
    }
    return (2 * (RSSI + 100) );
}

/*
 * Connect client to AP
 */

bool WiFiConfig::ConnectSTA2AP()
{
    String msg, msg_out;
    uint8_t count = 0;
    uint8_t dot = 0;
    wl_status_t status = WiFi.status();
    while (status != WL_CONNECTED && count < 40) {

        switch (status) {
        case WL_NO_SSID_AVAIL:
            msg="No SSID";
            break;
        case WL_CONNECT_FAILED:
            msg="Connection failed";
            break;
        case WL_CONNECTED:
            break;
        default:
            if ((dot>3) || (dot==0) ) {
                dot=0;
                msg_out = "Connecting";
            }
            msg_out+=".";
            msg= msg_out;
            dot++;
            break;
        }
        Esp3DCom::echo(msg.c_str());
        Esp3DLibConfig::wait (500);
        count++;
        status = WiFi.status();
    }
    return (status == WL_CONNECTED);
}

/*
 * Start client mode (Station)
 */

bool WiFiConfig::StartSTA()
{
    String defV;
    Preferences prefs;
    //stop active service
    wifi_services.end();
    //Sanity check
    if((WiFi.getMode() == WIFI_STA) || (WiFi.getMode() == WIFI_AP_STA)) {
        WiFi.disconnect();
    }
    if((WiFi.getMode() == WIFI_AP) || (WiFi.getMode() == WIFI_AP_STA)) {
        WiFi.softAPdisconnect();
    }
    WiFi.enableAP (false);
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    //Get parameters for STA
    prefs.begin(NAMESPACE, true);
    defV = DEFAULT_HOSTNAME;
    String h = prefs.getString(HOSTNAME_ENTRY, defV);
    WiFi.setHostname(h.c_str());
    //SSID
    defV = DEFAULT_STA_SSID;
    String SSID = prefs.getString(STA_SSID_ENTRY, defV);
    if (SSID.length() == 0) {
        SSID = DEFAULT_STA_SSID;
    }
    //password
    defV = DEFAULT_STA_PWD;
    String password = prefs.getString(STA_PWD_ENTRY, defV);
    int8_t IP_mode = prefs.getChar(STA_IP_MODE_ENTRY, DEFAULT_STA_IP_MODE);
    //IP
    defV = DEFAULT_STA_IP;
    int32_t IP = prefs.getInt(STA_IP_ENTRY, IP_int_from_string(defV));
    //GW
    defV = DEFAULT_STA_GW;
    int32_t GW = prefs.getInt(STA_GW_ENTRY, IP_int_from_string(defV));
    //MK
    defV = DEFAULT_STA_MK;
    int32_t MK = prefs.getInt(STA_MK_ENTRY, IP_int_from_string(defV));
    prefs.end();
    //if not DHCP
    if (IP_mode != DHCP_MODE) {
        IPAddress ip(IP), mask(MK), gateway(GW);
        WiFi.config(ip, gateway,mask, gateway);
    }
    if (WiFi.begin(SSID.c_str(), (password.length() > 0)?password.c_str():NULL)) {
        Esp3DCom::echo("WiFi station started");
        SSID = "Connecting " + SSID;
        Esp3DCom::echo(SSID.c_str());
        return ConnectSTA2AP();
    } else {
        Esp3DCom::echo("Starting station failed");
        return false;
    }
}

/**
 * Setup and start Access point
 */

bool WiFiConfig::StartAP()
{
    String defV;
    Preferences prefs;
    //stop active services
    wifi_services.end();
    //Sanity check
    if((WiFi.getMode() == WIFI_STA) || (WiFi.getMode() == WIFI_AP_STA)) {
        WiFi.disconnect();
    }
    if((WiFi.getMode() == WIFI_AP) || (WiFi.getMode() == WIFI_AP_STA)) {
        WiFi.softAPdisconnect();
    }
    WiFi.enableSTA (false);
    WiFi.mode(WIFI_AP);
    WiFi.setSleep(false);
    //Get parameters for AP
    prefs.begin(NAMESPACE, true);
    //SSID
    defV = DEFAULT_AP_SSID;
    String SSID = prefs.getString(AP_SSID_ENTRY, defV);
    if (SSID.length() == 0) {
        SSID = DEFAULT_AP_SSID;
    }
    //password
    defV = DEFAULT_AP_PWD;
    String password = prefs.getString(AP_PWD_ENTRY, defV);
    //channel
    int8_t channel = prefs.getChar(AP_CHANNEL_ENTRY, DEFAULT_AP_CHANNEL);
    if (channel == 0) {
        channel = DEFAULT_AP_CHANNEL;
    }
    //IP
    defV = DEFAULT_AP_IP;
    int32_t IP = prefs.getInt(AP_IP_ENTRY, IP_int_from_string(defV));
    if (IP==0) {
        IP = IP_int_from_string(defV);
    }
    prefs.end();
    IPAddress ip(IP);
    IPAddress gw(0,0,0,0);
    IPAddress mask;
    mask.fromString(DEFAULT_AP_MK);
    //Start AP
    if(WiFi.softAP(SSID.c_str(), (password.length() > 0)?password.c_str():NULL, channel)) {
        Esp3DCom::echo("AP started ");
        Esp3DLibConfig::wait (100);
        //Set static IP
        WiFi.softAPConfig(ip, gw, mask);
        Esp3DCom::echo(WiFi.softAPIP().toString());
        return true;
    } else {
        Esp3DCom::echo("Starting AP failed");
        return false;
    }
}

/**
 * Stop WiFi
 */

void WiFiConfig::StopWiFi()
{
    //Sanity check
    if((WiFi.getMode() == WIFI_STA) || (WiFi.getMode() == WIFI_AP_STA)) {
        WiFi.disconnect(true);
    }
    if((WiFi.getMode() == WIFI_AP) || (WiFi.getMode() == WIFI_AP_STA)) {
        WiFi.softAPdisconnect(true);
    }
    wifi_services.end();
    WiFi.mode(WIFI_OFF);
    Esp3DCom::echo("WiFi Off");
}

/**
 * begin WiFi setup
 */
void WiFiConfig::begin()
{
    Preferences prefs;
    //stop active services
    wifi_services.end();
    //setup events
    WiFi.onEvent(WiFiConfig::WiFiEvent);
    //open preferences as read-only
    prefs.begin(NAMESPACE, true);
    int8_t wifiMode = prefs.getChar(ESP_RADIO_MODE, DEFAULT_RADIO_MODE);
    prefs.end();
    if (wifiMode == ESP_WIFI_AP) {
        StartAP();
        //start services
        wifi_services.begin();
    } else if (wifiMode == ESP_WIFI_STA) {
        if(!StartSTA()) {
            Esp3DCom::echo("Cannot connect to AP");
            StartAP();
        }
        //start services
        wifi_services.begin();
    } else {
        WiFi.mode(WIFI_OFF);
    }
}

/**
 * End WiFi
 */
void WiFiConfig::end()
{
    StopWiFi();
}


/**
 * Handle not critical actions that must be done in sync environement
 */
void WiFiConfig::handle()
{
    //in case of restart requested
    Esp3DLibConfig::handle();

    //Services
    wifi_services.handle();
}


#endif // ENABLE_WIFI
