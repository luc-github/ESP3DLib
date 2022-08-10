# Configuration

Because ESP3DLib is a library you must put the configuration settings in Configuration.h and Configuration_adv.h

In Marlin configuration files :  
[Configuration.h](https://github.com/MarlinFirmware/Marlin) 

* Select an ESP32 based board.   

* Enable the virtual serial port
Uncomment the second serial port to allow esp3d to get all printer feedback 
```
/**
 * Select a secondary serial port on the board to use for communication with the host.
 * :[-1, 0, 1, 2, 3, 4, 5, 6, 7]
 */
#define SERIAL_PORT_2 -1
```

* Enable ESP3DLib as wifi solution provider
[Configuration_adv.h](https://github.com/MarlinFirmware/Marlin)  

Uncomment `#define ESP3D_WIFISUPPORT   // ESP3D Library WiFi management (https://github.com/luc-github/ESP3DLib)`   
also  enable following settings by uncomment them

Enable ESP3DLib WebUI (Recommended):
```
#define WEBSUPPORT          // Start a webserver (which may include auto-discovery)
```
Update by OTA (optional):
```
#define OTASUPPORT          // Support over-the-air firmware updates
```
Enable ESP3DLib commands (Mandatory):
```
#define  WIFI_CUSTOM_COMMAND // Accept feature config commands (e.g., WiFi ESP3D) from the host
```

* Configure your WiFi (optional)   
Define to which access point your board need to connect to:
```
  #define WIFI_SSID "Wifi SSID"
  #define WIFI_PWD  "Wifi Password"
```
if not defined or you left like this the board will act as an Access Point instead.


* Enable / Disable ESP3DLib features

    * Authentication (default off)   
        To enable add:
        ```
        //AUTHENTICATION_FEATURE: protect pages by login password.
        #define AUTHENTICATION_FEATURE
        ```


    * mDNS discovery service (default on)   
        To disable add:
        ```
        //MDNS_FEATURE: this feature allow  type the name defined
        //in web browser by default: http:\\marlinesp.local and connect
        #define DISABLE_MDNS_FEATURE

        ```

    * SSDP discovery service (default on)   
        To disable add:
        ```
        //SSDD_FEATURE: this feature is a discovery protocol, supported on Windows out of the box
        //Rely on Configuration_adv.h
        #define DISABLE_SSDP_FEATURE
        ```

    * Captive portable for AP mode (default on)  
        To disable add:
        ```
        //CAPTIVE_PORTAL_FEATURE: In SoftAP redirect all unknow call to main page
        #define DISABLE_CAPTIVE_PORTAL_FEATURE
        ```  

    * Web Update (default on)   
        To disable add:
        ```
        #define DISABLE_WEB_UPDATE_FEATURE
        ```

    * SD Update (default on)   
        - put on SD `esp3dcnf.ini` to configure settings
        - put on SD `esp3dfw.bin` to update FW
        - put on SD `esp3dfs.bin` to update filesystem
        To disable add:  
        ```
        #define DISABLE_SD_UPDATE_FEATURE
        ```

    * Notifications (default on)  
        To disable add:
        ```
        #define DISABLE_NOTIFICATION_FEATURE
        ```
    * Telnet (default on)
        To disable add:
        ```
        #define DISABLE_TELNET_FEATURE
        ```

    * WebDav (default on, and use virtual FS with SD and ESP3D FS)  
        - To disable add:
            ```
            #define  DISABLE_WEBDAV_FEATURE
            ```
        - To change the target Filesystem to ESP3D FS only, add:
            ```
            #define  WEBDAV_FEATURE 1
            ```
        - To change the target Filesystem to SD only, add:
            ```
            #define  WEBDAV_FEATURE 2
            ```

    * Time (default on)  
        - To enable time on SD files, add:
            ```
            #define SD_TIMESTAMP_FEATURE
            ```
        -  To enable time on local filesytem files, add:
            ```
            #define FILESYSTEM_TIMESTAMP_FEATURE
            ```

    * FTP server
        - To enable ftp on virtual file sytem with SD and ESP3D FS, add:
            ```
            #define FTP_FEATURE 0
            ```

        - To enable ftp on ESP3D FS only add:
            ```
            #define FTP_FEATURE 1
            ```

        - To enable ftp on ESP3D SD only add:
            ```
            #define FTP_FEATURE 2
            ```
    * WebSocket
        To enable WebSocket server add:
        ```
        #define WS_DATA_FEATURE
        ```

    * SSDP
        to customize the SSDP description add and mofify any/all of:
        ```
        /* Model name
        * Modele name of device
        */
        #define ESP_MODEL_NAME "ESP32"

        /* Model number
        * Modele number of device
        */
        #define ESP_MODEL_NUMBER "Marlin with ESP3DLib"

        /* Model url
        * Modele url of device
        */
        #define ESP_MODEL_URL "https://www.espressif.com/en/products/devkits"

        /* Manufacturer name
        * Manufacturer name of device
        */
        #define ESP_MANUFACTURER_NAME "Espressif Systems"

        /* Manufacturer url
        * Manufacturer url of device
        */
        #define ESP_MANUFACTURER_URL "https://www.espressif.com"
        ```