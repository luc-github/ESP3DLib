# ESP3DLib 1.0

<img src="https://github.com/luc-github/ESP3DLib/blob/master/images/ESP3D_social.png">
Library for ESP32 used with 3D printer using [[ESP32 core version](https://github.com/espressif/arduino-esp32)   


Firmware should work with any 3D printer using Marlin 2.0

The web interface files are present in data directory but UI has it's own repository [ESP3D-WEBUI](https://github.com/luc-github/ESP3D-WEBUI/tree/2.1).

## Donate
Every support is welcome: [<img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG_global.gif" border="0" alt="PayPal – The safer, easier way to pay online.">](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=Y8FFE7NA4LJWQ)    
Especially if need to buy new modules for testing.

## Features
* Serial/Wifi bridge using configurable port 8888, here to enable/disable [TCP_IP_DATA_FEATURE](https://github.com/luc-github/ESP3D/blob/master/esp3d/config.h)
* Use GPIO2 to ground to reset all settings in hard way - 2-6 sec after boot / not before!! Set GPIO2 to ground before boot change boot mode and go to special boot that do not reach FW. Currently boot take 10 sec - giving 8 seconds to connect GPIO2 to GND and do an hard recovery for settings, here to enable/disable [RECOVERY_FEATURE](https://github.com/luc-github/ESP8266/blob/master/esp8266/config.h)   
* Complete configuration by web browser (Station or Access point) or by Serial commands
* Authentication for sensitive pages, here to enable/disable [AUTHENTICATION_FEATURE](https://github.com/luc-github/ESP3D/blob/master/esp3d/config.h)
* Update firmware by web browser, here to enable/disable [WEB_UPDATE_FEATURE](https://github.com/luc-github/ESP3D/blob/master/esp3d/config.h)
* Control ESP module using commands on serial or data port, here to enable/disable [SERIAL_COMMAND_FEATURE](https://github.com/luc-github/ESP3D/blob/master/esp3d/config.h)
* Captive portal in Access point mode which redirect all unknow call to main page, here to enable/disable [CAPTIVE_PORTAL_FEATURE](https://github.com/luc-github/ESP3D/blob/master/esp3d/config.h) 
* mDNS which allows to key the name defined in web browser and connect only with bonjour installed on computer, here to enable/disable [MDNS_FEATURE](https://github.com/luc-github/ESP3D/blob/master/esp3d/config.h)
* SSDP, this feature is a discovery protocol, supported on Windows out of the box, here to enable/disable [SSDP_FEATURE](https://github.com/luc-github/ESP3D/blob/master/esp3d/config.h)
* Fail safe mode (Access point)is enabled if cannot connect to defined station at boot.
* Choice of web server Async or Sync   
* Websocket support   
* OLED screen support   
* The web ui add even more feature : https://github.com/luc-github/ESP3D-WEBUI/blob/master/README.md#features  


## Web configuration      
*Wifi Mode : Access point / Client station  
*IP Generation: DHCP/Static IP      
*IP/MASK/GATEWAY for static data    
*Baud Rate for serial (supported : 9600, 19200, 38400, 57600, 115200, 230400, 250000)    
*web port and data port      

    
## Default Configuration      
Default Settings:    
AP:ESP8266    
PW:12345678   
Authentification: WPA     
Mode: g (n is not supported by AP, just by STA)    
channel: 11    
AP: visible    
Sleep Mode: Modem    
IP Mode: Static IP    
IP: 192.168.0.1   
Mask: 255.255.255.0   
GW:192.168.0.1    
Baud rate: 115200   
Web port:80 
the websocket is web port + 1 => 80+1 : 81  
Data port: 8888     
Web Page refresh: 3 secondes    
User: admin   
Password: admin   
User:user   
Password: user   



## Direct commands:    
Check wiki : https://github.com/luc-github/ESP3DLib/wiki/Direct-ESP3D-commands

h your Printer fw with ESP connected on Serial - it bring troubles, at least on DaVinci, but no issue if you update using web UI</H3>

## Contribution/customization
* To style the code before pushing PR please use [astyle --style=otbs *.h *.cpp *.ino](http://astyle.sourceforge.net/)   
* The embedded page is created using nodejs then gulp to generate a compressed html page (tool.html.gz), all necessary modules can be installed using the install.bat file content, then it is included using bin2c (https://sourceforge.net/projects/bin2c/) to generate the  h file used to create the file nofile.h, update the array and size according new out.h.   
* The current UI is located [here](https://github.com/luc-github/ESP3D-WEBUI)
 
# :question:Any question ?   
Check [Wiki](https://github.com/luc-github/ESP3DLib/wiki) or [![Join the chat at https://gitter.im/luc-github/ESP3D](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/luc-github/ESP3D?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)   

## :exclamation:Any issue/feedback ?    
Check [FAQ](https://github.com/luc-github/ESP3DLib/issues?utf8=%E2%9C%93&q=label%3AFAQ+) or [submit ticket](https://github.com/luc-github/ESP3DLib/issues)    


## TODO/On going  :   
-- Put feature at same level as ESP3D V2.1 / V3.0
