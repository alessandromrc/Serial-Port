#ifndef enumerateValues_H
#define enumerateValues_H

#include "common.hpp"


namespace RegKeys {
    LSTATUS result;

    char* SerialPorts;

    BYTE databuffer[256];

    void EnumerateValues(HKEY hKey, DWORD numValues) {
        DWORD dwIndex = 0;
        LPSTR valueName = new CHAR[256];
        DWORD valNameLen = 0;
        DWORD dataType;
        BYTE* data = databuffer;
        DWORD dataSize = 1024;

        for (unsigned int i = 0; i < numValues; i++) {
            DWORD valNameLen = 256;
            dataSize = 256;
            dataType = 0;
            result =
                RegEnumValueA(hKey,
                    dwIndex,
                    valueName, &
                    valNameLen,
                    NULL, &
                    dataType,
                    data, &
                    dataSize);

            if (result != ERROR_SUCCESS) {
                std::cout << "\nError RegEnumValue > " << result;
                return;
            }

            char serialPortArray[sizeof(data) + sizeof((char)
                '\0')] = {
                '\0'
            };

            memcpy(serialPortArray, data, sizeof(data));

            puts(serialPortArray);

            SerialPorts = serialPortArray;

            dwIndex++;
        }
    }

};

#endif