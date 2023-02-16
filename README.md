# ESP3DLib 1.0 Marlin version [<img src="https://img.shields.io/liberapay/patrons/ESP3D.svg?logo=liberapay">](https://liberapay.com/ESP3D)
<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-8-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->

<img src="https://github.com/luc-github/ESP3DLib/blob/master/images/ESP3D_social_mini.png">
Library for ESP32 boards using Marlin 2.x : 

[ESP32 Controller](https://github.com/simon-jouet/ESP32Controller),
[FYSETC-E4](https://github.com/FYSETC/FYSETC-E4),
[MRR_ESPA](https://github.com/maplerainresearch/MRR_ESPA), 
[MRR_ESPE](https://github.com/maplerainresearch/MRR_ESPE),
[Panda Zhu](https://github.com/markniu/PandaZHU),
[MKS Tinybee](https://github.com/makerbase-mks/MKS-TinyBee)


[Current version: ![Current Version](https://img.shields.io/badge/ESPDLib-1.0-green?style=plastic) ![GitHub last commit (branch)](https://img.shields.io/github/last-commit/luc-github/ESP3DLib/master?style=plastic)](https://github.com/luc-github/ESP3DLib/tree/master) [![Release Version](https://img.shields.io/github/v/release/luc-github/ESP3D-WEBUI?color=green&label=WebUI&style=plastic)](https://github.com/luc-github/ESP3D-WEBUI/tree/2.1/languages) [![Marlin](https://img.shields.io/github/release/MarlinFirmware/Marlin.svg?style=plastic&label=Marlin)](https://github.com/MarlinFirmware/Marlin)  

[Development version: ![Development Version](https://img.shields.io/badge/ESPDLib-3.0-yellow?style=plastic) ![GitHub last commit (branch)](https://img.shields.io/github/last-commit/luc-github/ESP3DLib/3.0?style=plastic)](https://github.com/luc-github/ESP3DLib/tree/3.0)  [![Release Version](https://img.shields.io/github/v/release/luc-github/ESP3D-WEBUI?color=green&include_prereleases&label=WebUI&style=plastic)](https://github.com/luc-github/ESP3D-WEBUI/tree/3.0) [![Project Page ESP3D 3.0](https://img.shields.io/badge/Project%20page-ESP3D%203.0-blue?style=plastic)](https://github.com/users/luc-github/projects/1/views/1) [![Marlin](https://img.shields.io/badge/Marlin-2.0.9.3(luc)-yellow?style=plastic)](https://github.com/luc-github/Marlin/tree/ESP3DLibV3.0)

:warning:Currently the development version need special version of Marlin which may not sync with latest version of Marlin yet : https://github.com/luc-github/Marlin/tree/ESP3DLibV3.0

<h4>:warning: This is not for ESP8266 boards neither standalone ESP3D installation</h4>   

for them go [here](https://github.com/luc-github/ESP3D)

[All releases](https://github.com/luc-github/ESP3DLib/releases)

## Sponsors 
[<img width="200px" src="https://raw.githubusercontent.com/luc-github/ESP3DLib/master/images/sponsors-supporters/MKS/mksmakerbase.jpg" title="MKS Makerbase">](https://github.com/makerbase-mks)&nbsp;&nbsp;
[<img width="140px" src="https://raw.githubusercontent.com/luc-github/ESP3DLib/master/images/sponsors-supporters/patrickS.png" title="Patrick S.">](https://github.com/PendulumPit)&nbsp;&nbsp;

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
As side project of ESP3D, it follows ESP3D features: https://github.com/luc-github/ESP3D/blob/3.0/ESP3D-features.xls?raw=true

## How to enable ?
In Marlin configuration files :  
[Configuration.h](https://github.com/MarlinFirmware/Marlin/blob/bugfix-2.0.x/Marlin/Configuration.h) 

Select an ESP32 based board.   

Uncomment the second serial port to allow esp3d to get all printer feedback 
```
/**
 * Select a secondary serial port on the board to use for communication with the host.
 * :[-1, 0, 1, 2, 3, 4, 5, 6, 7]
 */
#define SERIAL_PORT_2 -1
```

[Configuration_adv.h](https://github.com/MarlinFirmware/Marlin/blob/bugfix-2.0.x/Marlin/Configuration_adv.h)  

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
Check [Wiki](https://github.com/luc-github/ESP3DLib/wiki) or Join the chat at [![Discord server](https://img.shields.io/discord/752822148795596940?color=blue&label=discord&logo=discord)](https://discord.gg/Z4ujTwE)   
you can also check [discussions panel](https://github.com/luc-github/ESP3DLib/discussions) 

## :exclamation:Any issue ?    
[submit ticket](https://github.com/luc-github/ESP3DLib/issues)    


## TODO/On going  :   
--Import all ESP3D 2.1/3.0 features

## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tbody>
    <tr>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/ellensp"><img src="https://avatars.githubusercontent.com/u/530024?v=4?s=100" width="100px;" alt="ellensp"/><br /><sub><b>ellensp</b></sub></a><br /><a href="https://github.com/luc-github/ESP3DLib/issues?q=author%3Aellensp" title="Bug reports">🐛</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/eduard-sukharev"><img src="https://avatars.githubusercontent.com/u/3235378?v=4?s=100" width="100px;" alt="Eduard Sukharev"/><br /><sub><b>Eduard Sukharev</b></sub></a><br /><a href="https://github.com/luc-github/ESP3DLib/commits?author=eduard-sukharev" title="Code">💻</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://honuputters.com"><img src="https://avatars.githubusercontent.com/u/4861133?v=4?s=100" width="100px;" alt="Mitch Bradley"/><br /><sub><b>Mitch Bradley</b></sub></a><br /><a href="https://github.com/luc-github/ESP3DLib/issues?q=author%3AMitchBradley" title="Bug reports">🐛</a> <a href="https://github.com/luc-github/ESP3DLib/commits?author=MitchBradley" title="Code">💻</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://discord.gg/yNwksQvZmQ"><img src="https://avatars.githubusercontent.com/u/12979070?v=4?s=100" width="100px;" alt="makerbase"/><br /><sub><b>makerbase</b></sub></a><br /><a href="#financial-makerbase-mks" title="Financial">💵</a> <a href="https://github.com/luc-github/ESP3DLib/issues?q=author%3Amakerbase-mks" title="Bug reports">🐛</a> <a href="#platform-makerbase-mks" title="Packaging/porting to new platform">📦</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/vivian-ng"><img src="https://avatars.githubusercontent.com/u/24537694?v=4?s=100" width="100px;" alt="vivian-ng"/><br /><sub><b>vivian-ng</b></sub></a><br /><a href="https://github.com/luc-github/ESP3DLib/commits?author=vivian-ng" title="Code">💻</a> <a href="https://github.com/luc-github/ESP3DLib/issues?q=author%3Avivian-ng" title="Bug reports">🐛</a> <a href="#platform-vivian-ng" title="Packaging/porting to new platform">📦</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/markniu"><img src="https://avatars.githubusercontent.com/u/13879340?v=4?s=100" width="100px;" alt="Mark"/><br /><sub><b>Mark</b></sub></a><br /><a href="#platform-markniu" title="Packaging/porting to new platform">📦</a></td>
      <td align="center" valign="top" width="14.28%"><a href="http://www.fysetc.com"><img src="https://avatars.githubusercontent.com/u/36067086?v=4?s=100" width="100px;" alt="FYSETC.COM"/><br /><sub><b>FYSETC.COM</b></sub></a><br /><a href="#financial-FYSETC" title="Financial">💵</a> <a href="https://github.com/luc-github/ESP3DLib/issues?q=author%3AFYSETC" title="Bug reports">🐛</a> <a href="#platform-FYSETC" title="Packaging/porting to new platform">📦</a></td>
    </tr>
    <tr>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/PendulumPit"><img src="https://avatars.githubusercontent.com/u/112519244?v=4?s=100" width="100px;" alt="PendulumPit"/><br /><sub><b>PendulumPit</b></sub></a><br /><a href="#financial-PendulumPit" title="Financial">💵</a></td>
    </tr>
  </tbody>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!
