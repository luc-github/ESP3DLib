/*
  gcode_host.cpp -  gcode host functions class

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

#include "../../include/esp3d_config.h"
#if defined(GCODE_HOST_FEATURE)
#include "gcode_host.h"
#include "../../core/settings_esp3d.h"
#include "../../core/commands.h"
#include "../../core/esp3doutput.h"
#if defined(FILESYSTEM_FEATURE)
#include "../filesystem/esp_filesystem.h"
#endif //FILESYSTEM_FEATURE
#if defined(SD_DEVICE)
#include "../filesystem/esp_sd.h"
#endif //FILESYSTEM_FEATURE

#define TYPE_SCRIPT_STREAM 0
#define TYPE_FS_STREAM     1
#define TYPE_SD_STREAM     2

#define ESP_HOST_TIMEOUT 16000
#define MAX_TRY_2_SEND 5


GcodeHost esp3d_gcode_host;

GcodeHost::GcodeHost()
{
    end();
}

GcodeHost::~GcodeHost()
{
    end();
}

bool GcodeHost::begin()
{
    end();
    return true;
}

void GcodeHost::end()
{
    _commandNumber = 0;
    _error = ERROR_NO_ERROR;
    _step = HOST_NO_STREAM;
    _currentPosition = 0;
    _bufferSize = 0;
    _output.client(ESP_STREAM_HOST_OUTPUT);
    _totalSize = 0;
    _processedSize = 0;
}

bool GcodeHost::push(uint8_t * sbuf, size_t len)
{
    if (_step == HOST_NO_STREAM) {
        return false;
    }
    for (size_t i = 0; i < len; i++) {
        //it is a line process it
        if (sbuf[i]=='\n' || sbuf[i]=='\r') {
            flush();
        } else {
            //fill buffer until it is full
            if (_bufferSize < ESP_HOST_BUFFER_SIZE) {
                _buffer[_bufferSize++] = sbuf[i];
            } else {
                //buffer is full flush it
                flush();
                _buffer[_bufferSize++] = sbuf[i];
            }
            _buffer[_bufferSize] =0;
            _bufferSize++;
        }
    }
    flush();

    return true;
}

void GcodeHost::flush()
{
    //analyze buffer and do action if needed
    //look for \n, ok , error, ack
    //then clean buffer accordingly

    //in case response has not been processed

    if(_bufferSize==0) {
        return;
    }
    if (_response.length() > 0) {
        handle();
    }
    _response = (const char*)_buffer;
    _response.toLowerCase();
    if (_response.indexOf("ok") != -1) {
        _step = HOST_WAIT4_ACK;
    } else {
        if (_response.indexOf("error") != -1) {
            _step = HOST_ERROR_STREAM;
        }
    }
    _bufferSize = 0;
}

void GcodeHost::handle()
{
    static uint32_t startTimout = 0;
    if (_step == HOST_NO_STREAM) {
        return;
    }
    switch(_step) {
    case HOST_START_STREAM:
        //TODO open file or process array of commands
        _step = HOST_READ_LINE;
        _currentPosition = 0;
        break;
    case HOST_READ_LINE:
        //TODO read line from file or array of commands
        if (_nextStep==HOST_PAUSE_STREAM) {
            _step = HOST_PAUSE_STREAM;
            _nextStep = HOST_READ_LINE;
        } else {
            //TODO read command and put it to line to process
            _step = HOST_PROCESS_LINE;
        }
        break;
    case HOST_PROCESS_LINE:
        //TODO process line
        //Send command to serial or execute it on ESP3D or send to main FW (Marlin/GRBL_ESP32)
        startTimout =millis();
        _step = HOST_WAIT4_ACK;
        break;
    case HOST_WAIT4_ACK:
        //TODO wait for ack
        //is _response expected ?
        //check timeout also
        _response = "";
        if (_needCommandNumber) {

        }
        _step = HOST_READ_LINE;
        if (millis() - startTimout > ESP_HOST_TIMEOUT) {
            _step = HOST_ERROR_STREAM;
        }
        break;
    case HOST_PAUSE_STREAM:
        //TODO pause stream
        break;
    case HOST_RESUME_STREAM:
        //TODO resume stream
        break;
    case HOST_ABORT_STREAM:
    case HOST_STOP_STREAM:
        //TODO stop stream
        break;
    case HOST_ERROR_STREAM:
        //TODO stream error
        //Process error then stop stream
        _response = "";
        _error = ERROR_UNKNOW; //TODO:put right error
        _step = HOST_STOP_STREAM;
        break;
    default: //Not handled step
        log_esp3d("Not handled step %d", _step);
        break;
    }
}

bool  GcodeHost::abort()
{
    if (_step == HOST_NO_STREAM) {
        return false;
    }
    _step = HOST_ABORT_STREAM;
    return true;
}

bool GcodeHost::pause()
{
    if (_step == HOST_NO_STREAM) {
        return false;
    }
    _nextStep = HOST_PAUSE_STREAM;
    return true;
}
bool GcodeHost::resume()
{
    if (_step != HOST_PAUSE_STREAM) {
        return false;
    }
    _step = HOST_PAUSE_STREAM;
    return true;
}

uint8_t GcodeHost::Checksum(const char * command, uint32_t commandSize)
{
    uint8_t checksum_val =0;
    if (command == NULL) {
        return 0;
    }
    for (uint32_t i=0; i < commandSize; i++) {
        checksum_val = checksum_val ^ ((uint8_t)command[i]);
    }
    return checksum_val;
}

String GcodeHost::CheckSumCommand(const char* command, uint32_t commandnb)
{
    String commandchecksum = "N" + String((uint32_t)commandnb)+ " " + command;
    uint8_t crc = Checksum(commandchecksum.c_str(), commandchecksum.length());
    commandchecksum+="*"+String(crc);
    return commandchecksum;
}


bool GcodeHost::resetCommandNumbering()
{
    String resetcmd = "M110 N0";
    if (Settings_ESP3D::GetFirmwareTarget() == SMOOTHIEWARE) {
        resetcmd = "N0 M110";
    } else {
        resetcmd = "M110 N0";
    }
    _commandNumber = 1;
    return _output.printLN(resetcmd.c_str());
}

/*
bool GcodeHost::sendCommand(const char* command, bool checksum, bool wait4ack, const char * ack)
{
    log_esp3d("Send command: %s", command);
    String s;
    if(checksum) {
        s = CheckSumCommand(command, _commandNumber);
    } else {
        s = command;
    }
    for(uint8_t try_nb = 0; try_nb < MAX_TRY_2_SEND; try_nb ++) {
        _error = ERROR_NO_ERROR;
        purge();
        if ((_error != ERROR_NO_ERROR) && wait4ack) {
            return false;
        } else {
            //if no need to wait for ack the purge has no real impact but clear buffer
            _error = ERROR_NO_ERROR;
        }
        uint32_t start = millis();
        //to give a chance to not overload buffer
        bool done = false;
        while (((millis() - start) < DEFAULT_TIMOUT) && !done) {
            if ((size_t)serial_service.availableForWrite() > s.length()) {
                if (strlen(command) == serial_service.write((const uint8_t*)s.c_str(), s.length())) {
                    if (serial_service.write('\n')==1) {
                        if(!wait4ack) {
                            log_esp3d("No need ack");
                            return true;
                        }
                        //process answer
                        if (wait_for_ack(DEFAULT_TIMOUT, ack)) {
                            log_esp3d("Command got ack");
                            return true;
                        } else {
                            //what is the error ?
                            log_esp3d("Error: %d", _error);
                            //no need to retry for this one
                            if ((_error == ERROR_MEMORY_PROBLEM) || (_error == ERROR_TIME_OUT)) {
                                return false;
                            }
                            //need to resend command
                            if (_error == ERROR_RESEND) {
                                done = true;
                            }
                            //the printer ask for another command line so exit
                            if ((_error == ERROR_NUMBER_MISMATCH) || (_error == ERROR_LINE_IGNORED)) {
                                return false;
                            }
                        }
                    }
                }
            }
            Hal::wait(0);
        }
    }
    if (_error == ERROR_NO_ERROR) {
        _error = ERROR_CANNOT_SEND_DATA;
        log_esp3d("Error: %d", _error);
    }
    return false;
}*/


uint32_t GcodeHost::getCommandNumber(String & response)
{
    uint32_t l = 0;
    String sresend = "Resend:";
    if ( Settings_ESP3D::GetFirmwareTarget() == SMOOTHIEWARE) {
        sresend = "rs N";
    }
    int pos = response.indexOf(sresend);
    if (pos == -1 ) {
        log_esp3d("Cannot find label %d", _error);
        return -1;
    }
    pos+=sresend.length();
    int pos2 = response.indexOf("\n", pos);
    String snum = response.substring(pos, pos2);
    //remove potential unwished char
    snum.replace("\r", "");
    l = snum.toInt();
    log_esp3d("Command number to resend is %s", String((uint32_t)l).c_str());
    return l;
}

/*bool GcodeHost::processFSFile(const char * filename, level_authenticate_type auth_type, ESP3DOutput * output)
{
    bool res = true;
    log_esp3d("Processing FS : %s", filename);
    if (!ESP_FileSystem::exists(filename)) {
        log_esp3d("Cannot find file");
        return false;
    }
    ESP_File f = ESP_FileSystem::open(filename);
    if (!f.isOpen()) {
        log_esp3d("Cannot open file");
        return false;
    }
    size_t filesize  = f.size();
    int8_t ch;
    String cmd = "";
    for (size_t c = 0; c< filesize ; c++) {
        ch = f.read();
        if (ch == -1) {
            log_esp3d("Error reading file");
            f.close();
            return false;
        }
        if ((ch == 13)||(ch == 10) || (c==(filesize-1))) {
            //for end of file without \n neither \r
            if (!((ch == 13)||(ch == 10)) && (c==(filesize-1))) {
                cmd+=(char)ch;
            }
            cmd.trim();
            if(cmd.length() > 0) {
                //ignore  comments
                if (cmd[0]!=';') {
                    //it is internal or not ?
                    if(esp3d_commands.is_esp_command((uint8_t *)cmd.c_str(), cmd.length())) {
                        esp3d_commands.process((uint8_t *)cmd.c_str(), cmd.length(), output, auth_type);
                    } else {
                        if (!sendCommand(cmd.c_str(),false, true)) {
                            log_esp3d("Error sending command");
                            //To stop instead of continue may need some trigger
                            res = false;
                        }
                    }
                }
                cmd="";
            }

        } else {
            cmd+=(char)ch;
        }
    }
    f.close();
    return res;
}*/

bool GcodeHost::processScript(const char * line)
{
    //TODO
    //check line is a script
    //if yes  process it
    //and send true
    //if not send false
    return false;
}

//split line of command separated by '\n'
bool GcodeHost::processLine(const char * line, level_authenticate_type auth_type, ESP3DOutput * output)
{
    bool res = true;
    /*  String s = "";
      for (uint p = 0; p < strlen(line); p++) {
          if ((line[p]==10) || (line[p]==13) || (p == (strlen(line)-1))) {
              if (!((line[p]==10) || (line[p]==13)) && (p == (strlen(line)-1))) {
                  s+=line[p];
              }
              s.trim();
              if (s.length()>0) {
                  //ignore  comments
                  if (s[0]!=';') {
                      //it is internal or not ?
                      if(esp3d_commands.is_esp_command((uint8_t *)s.c_str(), s.length())) {
                          esp3d_commands.process((uint8_t *)s.c_str(), s.length(), output, auth_type);
                      } else {
                          //no check sum no ack
                          if (!sendCommand(s.c_str(),false, false)) {
                              log_esp3d("Error sending command");
                              //To stop instead of continue may need some trigger
                              res = false;
                          }
                      }
                  }
              }
              s = "";
          } else {
              s+=line[p];
          }
      }*/
    return res;
}

bool GcodeHost::processFile(const char * filename, level_authenticate_type auth_type, ESP3DOutput * output)
{
    _fileName = filename;
    _fileName.trim();
    log_esp3d("Processing file: %s", filename);
    if (_fileName.length() == 0) {
        log_esp3d("No file to process");
        return false;
    }
    if (_fileName[0]!='/') {
        _fileName = "/" + _fileName;
    }
    //TODO UD = USB DISK
#if defined(SD_DEVICE)
    if (_fileName.startsWith(ESP_SD_FS_HEADER)) {
        _fileName= _fileName.substring(strlen(ESP_SD_FS_HEADER),_fileName.length());
        _fsType = TYPE_SD_STREAM;
        _step = HOST_START_STREAM;
        return true;
    }
#endif //SD_DEVICE
#if defined(FILESYSTEM_FEATURE)
    if (_fileName.startsWith(ESP_FLASH_FS_HEADER)) {
        _fileName= _fileName.substring(strlen(ESP_FLASH_FS_HEADER),_fileName.length());
        _fsType = TYPE_FS_STREAM;
        _step = HOST_START_STREAM;
        return true;
    }
    //if no header it is also an FS file
    _fsType = TYPE_FS_STREAM;
    _step = HOST_START_STREAM;
    return true;
#endif //FILESYSTEM_FEATURE
    _fileName = "";
    return false;
}

#endif //GCODE_HOST_FEATURE
