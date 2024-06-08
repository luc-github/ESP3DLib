/*
    This file is part of ESP3DLib library for 3D printer.

    ESP3DLib library for Marlin 3D printer  for 3D printer is free software: you
   can redistribute it and/or modify it under the terms of the GNU General
   Public License as published by the Free Software Foundation, either version 3
   of the License, or (at your option) any later version.

    ESP3DLib library for Marlin 3D printer is distributed in the hope that it
   will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
   Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this Firmware.  If not, see <http://www.gnu.org/licenses/>.

    Main author: luc lebosse

*/

#ifndef ESP3DLIB_H
#define ESP3DLIB_H
#if !defined(ARDUINO_ARCH_ESP32)
#error Oops!  Make sure you have 'ESP32' compatible board selected
#endif
#include "modules/serial2socket/serial2socket.h"
/*! Esp3DLib main class */
class Esp3DLib {
 public:
  /**
   * Constructor.
   */
  Esp3DLib();
  /**
   * @brief Initializes the task used by \link esp3dlib \endlink.
   */
  void init();
  /**
   * Parser for commmand.
   * @param[in] cmd - the string to parse
   *
   * @return true - if it is seen as ESP command.
   * @return false - if not ESP command.
   */
  bool parse(char* cmd);
  /**
   * idletask function.
   */
  void idletask();
  /**
   * test if SD card is currently used by esp3dlib.
   */
  bool isSdUsed();
};

/**
 * @brief You must call esp3dlib.init() before using this variable.
 */
extern Esp3DLib esp3dlib;

#endif
