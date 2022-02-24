#ifndef enumerateSubKeys_H
#define enumerateSubKeys_H

#include "common.hpp"
#include "enumerateValues.hpp"


namespace RegKeys {

    void EnumerateSubKeys(HKEY RootKey,
        const char* subKey, unsigned int tabs = 0) {
        HKEY hKey;
        DWORD cSubKeys;
        DWORD maxSubkeyLen;
        DWORD cValues;
        DWORD maxValueLen;
        DWORD retCode;

        result =
            RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_READ, &hKey);
        if (result != ERROR_SUCCESS) {
            std::cout << "\nError RegOpenKeyEx > " << result;
            return;
        }

        result =
            RegQueryInfoKey(hKey,
                NULL,
                NULL,
                NULL, &
                cSubKeys, &
                maxSubkeyLen,
                NULL, &
                cValues, &
                maxValueLen,
                NULL,
                NULL,
                NULL);

        if (result != ERROR_SUCCESS) {
            std::cout << "\nError RegQueryInfoKey > " << result;
            return;
        }

        if (cSubKeys > 0) {
            char currentSubkey[MAX_PATH];

            for (unsigned int i = 0; i < cSubKeys; i++) {
                DWORD currentSubLen = MAX_PATH;

                retCode = RegEnumKeyExA(hKey,
                    i,
                    currentSubkey, &
                    currentSubLen,
                    NULL,
                    NULL,
                    NULL,
                    NULL);

                if (retCode == ERROR_SUCCESS) {
                    for (unsigned int i = 0; i < tabs; i++)
                        printf("\t(%d) %s\n", i + 1, currentSubkey);
                    char* subKeyPath = new char[currentSubLen + strlen(subKey)];
                    sprintf(subKeyPath, "%s\\%s", subKey, currentSubkey);
                    EnumerateSubKeys(HKEY_LOCAL_MACHINE, subKeyPath, (tabs + 1));
                }
            }
        }
        else {
            EnumerateValues(hKey, cValues);
        }

        RegCloseKey(hKey);
    }

};

#endif