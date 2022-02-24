#ifndef SerialPort_H
#define SerialPort_H

#include "common.hpp"
#include <cstring>

namespace SerialPort
{
	class Serial
	{
	public:

		static std::string getSerialPorts();

		static int write(const char buffer[]);

		static int write(const char* buffer, int buffLen);

		static int read(char* buffer, int buffLen, bool nullTerminate = true);

		static bool openSerialPort(LPCSTR commPortName, int bitRate);

		static bool closeSerialPort();

		static void serialPortInfo();

		static void flush();
	};

};

#endif