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


#include "esp3dlibconfig.h"

#if defined(ESP3D_WIFISUPPORT)
#include "serial2socket.h"
#include "wificonfig.h"
#include <WebSocketsServer.h>
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
Serial_2_Socket Serial2Socket;


Serial_2_Socket::Serial_2_Socket()
{
    _web_socket = NULL;
    _TXmutex = xSemaphoreCreateMutex();
    _flushrequested = false;
    _TXbufferSize = 0;
    _RXbufferSize = 0;
    _RXbufferpos = 0;
}
Serial_2_Socket::~Serial_2_Socket()
{
    if (_web_socket) {
        detachWS();
    }
    _TXbufferSize = 0;
    _RXbufferSize = 0;
    _RXbufferpos = 0;
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

bool Serial_2_Socket::attachWS(void * web_socket)
{
    if (web_socket) {
        _web_socket = web_socket;
        _TXbufferSize=0;
        return true;
    }
    return false;
}

bool Serial_2_Socket::detachWS()
{
    _web_socket = NULL;
    return true;
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
    if((buffer == NULL) ||(!_web_socket)) {
        if(buffer == NULL) {
            log_i("[SOCKET]No buffer");
        }
        if(!_web_socket) {
            log_i("[SOCKET]No socket");
        }
        return 0;
    }
#if defined(ENABLE_SERIAL2SOCKET_OUT)
    //This runs in the caller's task (Marlin's loop), so only buffer here:
    //sending can wait seconds on a client that doesn't read.
    //handle_flush() sends from the ESP3DLib task.
    //Output that doesn't fit is dropped.
    if (xSemaphoreTake((SemaphoreHandle_t)_TXmutex, pdMS_TO_TICKS(10)) != pdTRUE) {
        return size;
    }
    if (_TXbufferSize + size <= TXBUFFERSIZE) {
        if (_TXbufferSize==0) {
            _lastflush = millis();
        }
        memcpy(&_TXbuffer[_TXbufferSize], buffer, size);
        _TXbufferSize += size;
    }
    xSemaphoreGive((SemaphoreHandle_t)_TXmutex);
    log_i("[SOCKET]buffer size %d",_TXbufferSize);
#endif
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
#if defined(ENABLE_SERIAL2SOCKET_IN)
    int data_size = strlen(data);
    if ((data_size + _RXbufferSize) <= RXBUFFERSIZE) {
        int current = _RXbufferpos + _RXbufferSize;
        if (current > RXBUFFERSIZE) {
            current = current - RXBUFFERSIZE;
        }
        for (int i = 0; i < data_size; i++) {
            if (current > (RXBUFFERSIZE-1)) {
                current = 0;
            }
            _RXbuffer[current] = data[i];
            current ++;
        }
        _RXbufferSize+=strlen(data);
        return true;
    }
    return false;
#else
    return true;
#endif
}

int Serial_2_Socket::read(void)
{
    if (_RXbufferSize > 0) {
        int v = _RXbuffer[_RXbufferpos];
        _RXbufferpos++;
        if (_RXbufferpos > (RXBUFFERSIZE-1)) {
            _RXbufferpos = 0;
        }
        _RXbufferSize--;
        return v;
    } else {
        return -1;
    }
}

//Called from the ESP3DLib task
void Serial_2_Socket::handle_flush()
{
    if (_TXbufferSize > 0) {
        if (_flushrequested || (_TXbufferSize>=TXBUFFERSIZE/2) || ((millis()- _lastflush) > FLUSHTIMEOUT)) {
            log_i("[SOCKET]need flush, buffer size %d",_TXbufferSize);
            send_buffer();
        }
    }
}

//May be called from any task, so only ask the ESP3DLib task to send
void Serial_2_Socket::flush(void)
{
    _flushrequested = true;
}

void Serial_2_Socket::send_buffer()
{
    if (!_web_socket || xSemaphoreTake((SemaphoreHandle_t)_TXmutex, pdMS_TO_TICKS(10)) != pdTRUE) {
        return;
    }
    uint16_t size = _TXbufferSize;
    memcpy(_TXsendbuffer, _TXbuffer, size);
    _TXbufferSize = 0;
    _flushrequested = false;
    xSemaphoreGive((SemaphoreHandle_t)_TXmutex);
    log_i("[SOCKET]flush data, buffer size %d",size);
    WebSocketsServer * ws = (WebSocketsServer *)_web_socket;
    for (uint8_t num = 0; num < WEBSOCKETS_SERVER_CLIENT_MAX; num++) {
        //A client that stops reading would stall every later send, so drop it
        if (ws->clientIsConnected(num) && !ws->sendBIN(num, _TXsendbuffer, size)) {
            log_i("[SOCKET]send failed, disconnect %d",num);
            ws->disconnect(num);
        }
    }
}

#endif // ESP3D_WIFISUPPORT
