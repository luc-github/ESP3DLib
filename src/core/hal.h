/*
  hal.h - esp3d hal class

  Copyright (c) 2014 Luc Lebosse. All rights reserved.

  This code is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with This code; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _ESP3D_HAL_H
#define _ESP3D_HAL_H
#include "WiFi.h"
#include <Arduino.h>

class Hal
{
public:
    static bool begin();
    static void end();
    static void wait (uint32_t milliseconds);
    static uint16_t getChipID();
    static bool has_temperature_sensor();
    static float temperature();
    static bool is_pin_usable(uint pin);
private:
    static void wdtFeed();
};
#endif //_ESP3D_HAL_H
