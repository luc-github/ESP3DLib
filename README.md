# ESP3DLib 1.0 (Marlin version)

<img src="https://github.com/luc-github/ESP3DLib/blob/master/images/ESP3D_social.png">
Library for ESP32 boards


Library should work with any 3D printer using Marlin 2.x

The web interface files are present in data directory but UI has it's own repository [ESP3D-WEBUI](https://github.com/luc-github/ESP3D-WEBUI/tree/2.1).

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

 
## Default Configuration      
Default Settings:    
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
Check wiki :https://raw.githubusercontent.com/luc-github/ESP3DLib/master/docs/Commands.txt

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
