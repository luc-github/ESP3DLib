# Serial2Socket API

Serial2Socket is a class that allows to emulate serial port but transfert data so the class is used to connect to wifi and so facilitate the data between ESP3DLib and Marlin, ESP3DLib is in charge to dispatch/collect the data and send it to the right place. ESP3DLib can get data over wifi by telnet, http, websocket and forward them to Marlin using the serial2socket class. in same way Marlin can send data to ESP3DLib using the serial2socket class and ESP3DLib will forward them to the right place (websocket, telnet, http).

To achieve this it emulate serial port functions to communicate with Marlin:
 - begin
    The begin function take the baudrate as parameter for compatibility but do not use it. It is used to initialize the serial2socket class and prepare it for communication.
 - end
    The end function is used to close the serial2socket class and free the resources used by it.
- available
    The available function is used to check if there is data available to read from the RX circular buffer. It returns the number of bytes available to read.
- read
    The read function is used to read a byte from the RX circular buffer. It returns the byte read or -1 if there is no data available.
- peek
    The peek function is used to read a byte from the RX circular buffer without removing it. It returns the byte read or -1 if there is no data available.
To transfer data to Marlin the class use the dispatch(ESP3DMessage *message), the message contain the data and the size of the data to be send. To transfer data, the class feed an RX circular buffer by using the function push2RX(const uint8_t *buffer, size_t size), it will push an array of size bytes to the RX circular buffer.

Marlin periodicaly check the available() function to see if there is data available to read. If there is data available, it will call the read() function to read the data and process it. each call to read move the read pointer to the next byte in the RX circular buffer.


To collect data from Marlin, the class rely on usage of the function write(const uint8_t *buffer, size_t size) to send data to the TX circular buffer. The function write is used to send data to the TX circular buffer. The function will push the data to the TX circular buffer and return the number of bytes written. The function will chunk the data in  strings if there a `\n`, the string will be transformed to a ESP3DMessage and send by the flush function which will send the new message using  esp3d_commands.process(msg);
the flush is also done in addition of \n detection if:
1 - the buffer is full
2 - the buffer is not empty but has not been flushed for S2S_FLUSHTIMEOUT milliseconds (500ms by default)

The  esp3d_commands.process(msg); function will process the message and send it to the right place (websocket, telnet, http) or if it is an ESP3D command, to the ESP3D command processor.