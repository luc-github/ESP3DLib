/*
  espcom.cpp - esp3d communication serial/tcp/etc.. class

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

#include MARLIN_PATH(HAL/HAL_ESP32/FlushableHardwareSerial.h)
#include MARLIN_PATH(HAL/HAL_ESP32/HAL.h)
#include "espcom.h"

void Esp3DCom::echo(const char * data)
{
	SERIAL_ECHO_START();
	SERIAL_ECHOLNPAIR("", data);
}


#endif //ESP3D_WIFISUPPORT
