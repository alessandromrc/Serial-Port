#include "common.hpp"
#include "SerialPort.hpp"
#include "logger.hpp"

/*
* Arduino Code Example
* 
* void setup() {
*   Serial.begin(9600);
* }
*
* void loop() {
*   Serial.println("test");
* }
*  
*/

char buf[MAXCHAR];

int main()
{

	if (SerialPort::Serial::openSerialPort("COM3", 9600))
	{
		while (true)
		{
			SerialPort::Serial::read(buf, sizeof(buf), true);

			std::cout << buf;
		}

	}

	return 0;
}