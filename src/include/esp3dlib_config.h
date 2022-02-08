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
//config reference, do not touch
#ifndef ESP_XSTR
#define ESP_XSTR_(M) #M
#define ESP_XSTR(M) ESP_XSTR_(M)
#endif
#define MARLIN_HAL_PATH(PATH) HAL_PATH( ../../../../../../Marlin/src/HAL, PATH)
#define MARLIN_PATH(PATH) ESP_XSTR(../../../../../../Marlin/src/PATH)
#include MARLIN_PATH(inc/MarlinConfigPre.h)
#undef DISABLED
#undef _BV
//version
#define LIB_VERSION "2.0.0"

//Allow to override the default core used by ESP3DLIB
#ifndef ESP3DLIB_RUNNING_CORE
#define  ESP3DLIB_RUNNING_CORE 0
#endif //ESP3DLIB_RUNNING_CORE

//Allow to override the default priority task used by ESP3DLIB_RUNNING_PRIORITY
#ifndef ESP3DLIB_RUNNING_PRIORITY
#define  ESP3DLIB_RUNNING_PRIORITY 1
#endif //ESP3DLIB_RUNNING_PRIORITY

//AUTHENTICATION_FEATURE: protect pages by login password
//Rely on Configuration_adv.h

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
//Rely on Configuration_adv.h
#ifndef DISABLE_MDNS_FEATURE
#define MDNS_FEATURE
#endif //DISABLE_MDNS_FEATURE

//SSDD_FEATURE: this feature is a discovery protocol, supported on Windows out of the box
//Rely on Configuration_adv.h
#ifndef DISABLE_SSDP_FEATURE
#define SSDP_FEATURE
#endif //DISABLE_SSDP_FEATURE

//CAPTIVE_PORTAL_FEATURE: In SoftAP redirect all unknow call to main page
//Rely on Configuration_adv.h
#ifndef DISABLE_CAPTIVE_PORTAL_FEATURE
#define CAPTIVE_PORTAL_FEATURE
#endif //DISABLE_CAPTIVE_PORTAL_FEATURE



