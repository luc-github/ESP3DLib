/*
  serial2socket.cpp -  serial 2 socket functions class

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


#include "../../include/esp3dlib_config.h"

#if defined(ESP3D_WIFISUPPORT)
#include "serial2socket.h"

Serial_2_Socket Serial2Socket;


Serial_2_Socket::Serial_2_Socket()
{
    _web_socket = NULL;
    _TXbufferSize = 0;
    _RXbufferSize = 0;
    _RXbufferpos = 0;
}
Serial_2_Socket::~Serial_2_Socket()
{
    end();
}
void Serial_2_Socket::begin(long speed)
{
    _TXbufferSize = 0;
    _RXbufferSize = 0;
    _RXbufferpos = 0;
}

void Serial_2_Socket::end()
{
    _TXbufferSize = 0;
    _RXbufferSize = 0;
    _RXbufferpos = 0;
}

long Serial_2_Socket::baudRate()
{
    return 0;
}


Serial_2_Socket::operator bool() const
{
    return true;
}
int Serial_2_Socket::available()
{
    return _RXbufferSize;
}


size_t Serial_2_Socket::write(uint8_t c)
{
    if(!_web_socket) {
        return 0;
    }
    write(&c,1);
    return 1;
}

size_t Serial_2_Socket::write(const uint8_t *buffer, size_t size)
{

    return size;
}

int Serial_2_Socket::peek(void)
{
    if (_RXbufferSize > 0) {
        return _RXbuffer[_RXbufferpos];
    } else {
        return -1;
    }
}

bool Serial_2_Socket::push (const char * data)
{
    return true;
}

int Serial_2_Socket::read(void)
{
    return -1;

}

void Serial_2_Socket::handle_flush()
{

}
void Serial_2_Socket::flush(void)
{

}

#endif // ESP3D_WIFISUPPORT
