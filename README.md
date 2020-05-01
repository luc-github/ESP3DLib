# ESP3DLib 1.0 Marlin version

<img src="https://github.com/luc-github/ESP3DLib/blob/master/images/ESP3D_social_mini.png">
Library for ESP32 boards using Marlin 2.x : 

[MRR_ESPA](https://github.com/maplerainresearch/MRR_ESPA), 
[MRR_ESPE](https://github.com/maplerainresearch/MRR_ESPE), 
[ESP32 Controller](https://github.com/simon-jouet/ESP32Controller)

The web interface files has it's own repository [ESP3D-WEBUI](https://github.com/luc-github/ESP3D-WEBUI/tree/2.1).

[Latest development version ![Development Version](https://img.shields.io/badge/Devt-v1.x-yellow?style=plastic) ![GitHub last commit (branch)](https://img.shields.io/github/last-commit/luc-github/ESP3DLib/devt?style=plastic)](https://github.com/luc-github/ESP3DLib/tree/devt) [![Travis (.org) branch](https://img.shields.io/travis/luc-github/ESP3DLib/devt?style=plastic)](https://travis-ci.org/luc-github/ESP3DLib) [![Release Version](https://img.shields.io/github/v/release/luc-github/ESP3D-WEBUI?color=green&include_prereleases&label=WebUI&style=plastic)](https://github.com/luc-github/ESP3D-WEBUI/tree/2.1) ![Marlin](https://img.shields.io/github/release/MarlinFirmware/Marlin.svg?style=plastic&label=Marlin)    

To use development version just add `#devt` at the end of ESP3DLib git address in your platformio.ini

`ESP3DLib=https://github.com/luc-github/ESP3DLib.git#devt`   

<h4>:warning: This is not for ESP8266 boards neither standalone ESP3D installation</h4>   

for them go [here](https://github.com/luc-github/ESP3D)

[All releases](https://github.com/luc-github/ESP3DLib/releases)



## Donate
Every support is welcome: [<img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG_global.gif" border="0" alt="PayPal – The safer, easier way to pay online.">](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=Y8FFE7NA4LJWQ)    
Especially if need to buy new modules for testing.

## Features
* Complete configuration by web browser (Station or Access point) or by Serial commands
* Authentication for sensitive pages
* Update firmware by web browser or OTA
* Captive portal in Access point mode which redirect all unknow call to main page 
* mDNS which allows to key the name defined in web browser and connect only with bonjour installed on computer
* SSDP, this feature is a discovery protocol, supported on Windows out of the box
* Fail safe mode (Access point)is enabled if cannot connect to defined station at boot.  
* The web ui add even more feature : https://github.com/luc-github/ESP3D-WEBUI/blob/master/README.md#features  

## How to enable ?
In Marlin configuration file : [Configuration_adv.h](https://github.com/MarlinFirmware/Marlin/blob/bugfix-2.0.x/Marlin/Configuration_adv.h#L2823-L2835)  

enable `#define ESP3D_WIFISUPPORT   // ESP3D Library WiFi management (https://github.com/luc-github/ESP3DLib)`    

Define to which access point your board need to connect to:
```
  #define WIFI_SSID "Wifi SSID"
  #define WIFI_PWD  "Wifi Password"
```
if not defined or you left like this the board will act as an Access Point instead.

and finally
```
#define WEBSUPPORT          // Start a webserver (which may include auto-discovery)
#define OTASUPPORT          // Support over-the-air firmware updates
#define WIFI_CUSTOM_COMMAND // Accept feature config commands (e.g., WiFi ESP3D) from the host
```


For advanced configuration add in same section:

to enable this feature which is disabled by default:
```
//AUTHENTICATION_FEATURE: protect pages by login password.
#define AUTHENTICATION_FEATURE
```

to disable any of these features which are enabled by default:

```
//MDNS_FEATURE: this feature allow  type the name defined
//in web browser by default: http:\\marlinesp.local and connect
#define DISABLE_MDNS_FEATURE

//SSDD_FEATURE: this feature is a discovery protocol, supported on Windows out of the box
//Rely on Configuration_adv.h
#define DISABLE_SSDP_FEATURE

//CAPTIVE_PORTAL_FEATURE: In SoftAP redirect all unknow call to main page
#define DISABLE_CAPTIVE_PORTAL_FEATURE
```  



## Default Configuration      
Default Settings if not modified in Configuration_adv.h:    
AP:MARLIN_ESP    
PW:12345678   
Authentification: WPA     
Mode: g (n is not supported by AP, just by STA)    
channel: 1         
IP: 192.168.0.1   
Mask: 255.255.255.0   
GW:192.168.0.1    
Web port:80 
the websocket is web port + 1 => 80+1 : 81  
User: admin   
Password: admin   
User:user   
Password: user   

## Direct commands:    
Check [wiki](https://raw.githubusercontent.com/luc-github/ESP3DLib/master/docs/Commands.txt)

## Contribution/customization
* To style the code before pushing PR please use [astyle --style=otbs *.h *.cpp *.ino](http://astyle.sourceforge.net/)   
* The embedded page is created using nodejs then gulp to generate a compressed html page (tool.html.gz), all necessary modules can be installed using the install.bat file content, then it is included using bin2c (https://sourceforge.net/projects/bin2c/) to generate the  h file used to create the file nofile.h, update the array and size according new out.h.   
* The current UI is located [here](https://github.com/luc-github/ESP3D-WEBUI)
 
# :question:Any question ?   
Check [Wiki](https://github.com/luc-github/ESP3DLib/wiki) or [![Join the chat at https://gitter.im/luc-github/ESP3D](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/luc-github/ESP3D?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)   

## :exclamation:Any issue/feedback ?    
Check [FAQ](https://github.com/luc-github/ESP3DLib/issues?utf8=%E2%9C%93&q=label%3AFAQ+) or [submit ticket](https://github.com/luc-github/ESP3DLib/issues)    


## TODO/On going  :   
--Import all ESP3D 2.1/3.0 features
