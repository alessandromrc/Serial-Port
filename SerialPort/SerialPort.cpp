#include "common.hpp"

#include "SerialPort.hpp"

#include "enumerateSubKeys.hpp"

namespace SerialPort {

    HANDLE hComm;
    DCB dcb;

    std::string Serial::getSerialPorts() {
        RegKeys::EnumerateSubKeys(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM");
        return RegKeys::SerialPorts;
    }

    bool Serial::closeSerialPort() {

        bool closeSP = CloseHandle(hComm);

        if (closeSP)
            printf("Serial Port closed successfuly\n");
        else
            printf("Error closing serial port\n");

        return closeSP;

    }

    bool Serial::openSerialPort(LPCSTR commPortName, int bitRate) {
        hComm = CreateFileA(commPortName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

        if (hComm == INVALID_HANDLE_VALUE)
            printf("[ERROR] - Error opening serial port\n");
        else
            printf("Serial Port opened successfuly\n");

        COMMTIMEOUTS cto = {
          MAXDWORD,
          0,
          0,
          0,
          0
        };

        if (hComm == INVALID_HANDLE_VALUE)
        {
            printf("[ERROR] - Can't open Serial Port\n");
            return 0;
        }

        if (!SetCommTimeouts(hComm, &cto)) {
            throw ("[ERROR] - Could not set com port timeout");
        }

        bool Status = GetCommState(hComm, &dcb);
        if (Status == FALSE)
        {
            printf("[ERROR] - Cannot get the Serial Port status\n");
            return 0;
        }

        // Serial Port Configuration
        memset(&dcb, 0, sizeof(dcb));
        dcb.DCBlength = sizeof(dcb);
        dcb.BaudRate = bitRate;
        dcb.fBinary = 1;
        dcb.fDtrControl = DTR_CONTROL_ENABLE;
        dcb.fRtsControl = RTS_CONTROL_ENABLE;

        dcb.Parity = NOPARITY;
        dcb.StopBits = ONESTOPBIT;
        dcb.ByteSize = 8;

        if (!SetCommState(hComm, &dcb)) {
            throw ("[ERROR] - Could not set com port parameters");
        }
        return !(hComm == INVALID_HANDLE_VALUE);
    }

    int Serial::write(const char buffer[]) {
        DWORD numWritten;
        WriteFile(hComm, buffer, (DWORD)strlen(buffer), &numWritten, NULL);
        return numWritten;
    }

    int Serial::write(const char* buffer, int buffLen) {
        DWORD numWritten;
        WriteFile(hComm, buffer, buffLen, &numWritten, NULL);
        return numWritten;
    }

    int Serial::read(char* buffer, int buffLen, bool nullTerminate) {
        DWORD numRead;
        if (nullTerminate) {
            --buffLen;
        }

        BOOL ret = ReadFile(hComm, buffer, buffLen, &numRead, NULL);

        if (!ret) {
            return 0;
        }

        if (nullTerminate) {
            buffer[numRead] = '\0';
        }

        return numRead;
    }


    void Serial::flush()
    {
        char buffer[10];
        int numBytes = read(buffer, 10, false);
        while (numBytes != 0)
        {
            numBytes = read(buffer, 10, false);
        }
    }


    void Serial::serialPortInfo() {
        printf("Baudrate=%ld ByteSize=%d Parity=%d StopBits=%d\n", dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);
    }

};