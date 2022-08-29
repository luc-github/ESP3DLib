# ESP3DLib 3.0 for Marlin [<img src="https://img.shields.io/liberapay/patrons/ESP3D.svg?logo=liberapay">](https://liberapay.com/ESP3D)

<img src="https://github.com/luc-github/ESP3DLib/blob/master/images/ESP3D_social_mini.png">
Library for ESP32 boards using Marlin 2.x : 

[ESP32 Controller](https://github.com/simon-jouet/ESP32Controller),
[FYSETC-E4](https://github.com/FYSETC/FYSETC-E4),
[MRR_ESPA](https://github.com/maplerainresearch/MRR_ESPA), 
[MRR_ESPE](https://github.com/maplerainresearch/MRR_ESPE),
[Panda Zhu](https://github.com/markniu/PandaZHU),
[MKS Tinybee](https://github.com/makerbase-mks/MKS-TinyBee)

The web interface files has it's own repository [ESP3D-WEBUI](https://github.com/luc-github/ESP3D-WEBUI/tree/3.0).

[Latest development version ![Development Version](https://img.shields.io/badge/3.0-yellow?style=plastic) ![GitHub last commit (branch)](https://img.shields.io/github/last-commit/luc-github/ESP3DLib/3.0?style=plastic)](https://github.com/luc-github/ESP3DLib/tree/3.0) [![Travis (.org) branch](https://img.shields.io/travis/luc-github/ESP3DLib/devt?style=plastic)](https://travis-ci.org/luc-github/ESP3DLib) [![Release Version](https://img.shields.io/github/v/release/luc-github/ESP3D-WEBUI?color=green&include_prereleases&label=WebUI&style=plastic)](https://github.com/luc-github/ESP3D-WEBUI/tree/3.0) [![Marlin](https://img.shields.io/github/release/MarlinFirmware/Marlin.svg?style=plastic&label=Marlin)](https://github.com/MarlinFirmware/Marlin)    

To use ESP3Lib V3 you need an updated version of Marlin which is here: https://github.com/luc-github/Marlin, necessary will be pushed when library V3 is considered as stable enough.   

<h4>:warning: This is not for ESP8266 boards neither standalone ESP3D installation</h4>   

for them go [here](https://github.com/luc-github/ESP3D)

[All releases](https://github.com/luc-github/ESP3DLib/releases)


## Sponsors 
[<img width="200px" src="https://raw.githubusercontent.com/luc-github/ESP3DLib/master/images/sponsors-supporters/MKS/mksmakerbase.jpg" title="MKS Makerbase">](https://github.com/makerbase-mks)&nbsp;&nbsp;

## Supporters

## Become a sponsor or a supporter
 * A sponsor is a recurent donator    
If your tier is `10 US$/month` or more, to thank you for your support, your logo / avatar will be added to the readme page with eventually with a link to your site.    
 * A supporter is per time donator 
 If your donation is over `120 US$` per year, to thank you for your support, your logo / avatar will be added to the readme page with eventually with a link to your site.  

 Every support is welcome, indeed helping users / developing new features need time and devices, donations contribute a lot to make things happen, thank you.

* liberapay <a href="https://liberapay.com/ESP3D/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a> 
* Paypal [<img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG_global.gif" border="0" alt="PayPal – The safer, easier way to pay online.">](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=FQL59C749A78L)
* ko-fi [![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/G2G0C0QT7)


## Features
* Complete configuration by web browser (Station or Access point) or by Serial commands
* Authentication for sensitive pages
* Update firmware by web browser or OTA
* Captive portal in Access point mode which redirect all unknow call to main page 
* mDNS which allows to key the name defined in web browser and connect only with bonjour installed on computer
* SSDP, this feature is a discovery protocol, supported on Windows out of the box
* Fail safe mode (Access point)is enabled if cannot connect to defined station at boot.  
* The web ui add even more feature : https://github.com/luc-github/ESP3D-WEBUI/blob/master/README.md#features  

## Coming Features
As side project of ESP3D, it follows ESP3D features: https://github.com/luc-github/ESP3DLib/blob/3.0/Features.md

## How to enable ?

Check the document : https://github.com/luc-github/ESP3DLib/blob/3.0/Configuration.md



## Default Configuration      
Default Settings if not modified in Configuration_adv.h:    
AP:MARLIN_ESP    
PW:12345678   
Authentification: WPA     
Mode: g (n is not supported by AP, but by STA)    
channel: 1         
IP: 192.168.0.1   
Mask: 255.255.255.0   
GW:192.168.0.1    
Web port:80 
the webUI websocket is web port + 1 => 80+1 : 81  
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
Check [Wiki](https://github.com/luc-github/ESP3DLib/wiki) or Join the chat at [![Discord server](https://img.shields.io/discord/752822148795596940?color=blue&label=discord&logo=discord)](https://discord.gg/Z4ujTwE)   
you can also check [discussions panel](https://github.com/luc-github/ESP3DLib/discussions) 

## :exclamation:Any issue ?    
[submit ticket](https://github.com/luc-github/ESP3DLib/issues)    


## TODO/On going  :   
- Test test test....
- Update Marlin to support it officially the V3 using latest ESP32 arduino / platformIO core version
