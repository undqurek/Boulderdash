#include "networkutils.h"

#if SYSTEM == LINUX
#   include <stddef.h>
#endif // LINUX

#if SYSTEM == WINDOWS
#   include <winsock2.h>
#   include <ws2tcpip.h>
#endif // WINDOWS


namespace core { namespace network
{
	NetworkUtils::NetworkUtils()
    {
    }

	uint32_t NetworkUtils::getHostIPv4(const char *host)
    {
        if(host == NULL)
            return 0;

#if SYSTEM == LINUX

#endif // LINUX

#if SYSTEM == WINDOWS
        //TODO: ta metoda jest przestarzala wiec trzeba ja zmienic na inna
        struct hostent *entry = ::gethostbyname(host);

        if(entry == NULL || entry->h_addrtype != AF_INET || entry->h_length == 0)
            return 0;

        char *ip = entry->h_addr_list[entry->h_length - 1];

        return *(uint32_t *)ip;
#endif // WINDOWS
    }

    static uint32_t getCStringLength(uint8_t value)
    {
        if(value < 10)
            return 1;

        if(value < 100)
            return 2;

        return 3;
    }

    static bool writeCStrign(char *buffer, uint32_t availableLength, uint8_t value)
    {
        uint32_t length = getCStringLength(value);

        if(length > availableLength)
            return false;

        uint8_t tmp = value / 10;

        length -= 1;
        buffer[length] = (value - tmp * 10) + 48;

        if(length == 0)
            return true;

        value = tmp;
        tmp = value / 10;

        length -= 1;
        buffer[length] = (value - tmp * 10) + 48;

        if(length == 0)
            return true;

        length -= 1;
        buffer[length] = tmp + 48;

        return true;
    }

	char *NetworkUtils::createIPv4CString(uint32_t ip)
    {
        uint8_t *pointer = (uint8_t *)&ip;

        uint32_t aLength = getCStringLength(pointer[0]);
        uint32_t bLength = getCStringLength(pointer[1]);
        uint32_t cLength = getCStringLength(pointer[2]);
        uint32_t dLength = getCStringLength(pointer[3]);

        uint32_t cStringLength = aLength + bLength + cLength + dLength + 3;
        char *result = new char[cStringLength + 1];

        uint32_t offset = 0;

        writeCStrign(result, cStringLength, pointer[0]);
        offset += aLength;

        result[offset] = '.';
        offset += 1;

        writeCStrign(result + offset, cStringLength, pointer[1]);
        offset += bLength;

        result[offset] = '.';
        offset += 1;

        writeCStrign(result + offset, cStringLength, pointer[2]);
        offset += cLength;

        result[offset] = '.';
        offset += 1;

        writeCStrign(result + offset, cStringLength, pointer[3]);
        result[cStringLength] = '\0';

        return result;
    }
}}
