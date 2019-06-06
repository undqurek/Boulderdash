#include "socket.h"

#include "intermediary/time.h"
#include "basic/cleaner.h"
#include "basic/memory.h"
#include "basic/string.h"


namespace core { namespace network
{
    using namespace core::basic;
    using namespace core::intermediary;

    Socket::Socket()
    {
#if SYSTEM == LINUX
        this->_descriptor = -1;
#endif // LINUX

#if SYSTEM == WINDOWS
        this->_descriptor = INVALID_SOCKET;
#endif // WINDOWS

		this->_readBytes = 0;
        this->_writtenBytes = 0;

		this->_ip = NULL;
    }

#if SYSTEM == LINUX
    Socket::Socket(int descriptor, char *_ip)
    {
        this->_descriptor = descriptor;

        this->_readBytes = 0;
        this->_writtenBytes = 0;

        this->_ip = _ip;
    }
#endif // LINUX

#if SYSTEM == WINDOWS
    Socket::Socket(::SOCKET descriptor, char *_ip)
	{
        this->_descriptor = descriptor;

		this->_readBytes = 0;
        this->_writtenBytes = 0;

		this->_ip = _ip;
	}
#endif // WINDOWS

    Socket::~Socket()
    {
        this->close();
    }

    const char *Socket::__getIP()
    {
        return this->_ip;
    }

    bool Socket::close()
    {
        if(this->isOpen())
        {
            //TODO: poprawne zwalnainie pamieci
//            Cleaner::deleteArray(this->_ip);

#if SYSTEM == LINUX
            if(::shutdown(this->_descriptor, SHUT_RDWR) == 0
                && ::close(this->_descriptor) == 0)
            {
                this->_descriptor = -1;

                this->_readBytes = 0;
                this->_writtenBytes = 0;

                return true;
            }
#endif // LINUX

#if SYSTEM == WINDOWS
            if(::shutdown(this->_descriptor, SD_BOTH) == 0
                && ::closesocket(this->_descriptor) == 0)
            {
                this->_descriptor = INVALID_SOCKET;

                this->_readBytes = 0;
                this->_writtenBytes = 0;

                return true;
            }
#endif // WINDOWS
        }

        return false;
    }

    bool Socket::isOpen()
    {
#if SYSTEM == LINUX
        return this->_descriptor != -1;
#endif // LINUX

#if SYSTEM == WINDOWS
        return this->_descriptor != INVALID_SOCKET;
#endif // WINDOWS
    }

    bool Socket::read(const uint8_t *buffer, uint32_t length)
    {
        if(this->isOpen())
        {
#if SYSTEM == LINUX
            int readBytes = ::recv(this->_descriptor, (void *)buffer, length, MSG_WAITALL);

            if(readBytes == -1)
                return false;
#endif

#if SYSTEM == WINDOWS
            //TODO: rozwiazac problem MSG_WAITALL i blocking==false
            int readBytes = ::recv(this->_descriptor, (char *)buffer, length, MSG_WAITALL);

            if(readBytes == SOCKET_ERROR)
                return false;
#endif
            this->_readBytes += readBytes;

            if(readBytes == length)
                return true;
        }

        return false;
    }

    bool Socket::write(const uint8_t *buffer, uint32_t length)
    {
        if(this->isOpen())
        {
#if SYSTEM == LINUX
            int writtenBytes = ::send(this->_descriptor, buffer, length, 0);

            if(writtenBytes == -1)
                return false;
#endif

#if SYSTEM == WINDOWS
            int writtenBytes = ::send(this->_descriptor, (char *)buffer, length, 0);

            if(writtenBytes == SOCKET_ERROR)
                return false;
#endif
            this->_writtenBytes += writtenBytes;

            if(writtenBytes == length)
                return true;
        }

        return false;
    }

    uint32_t Socket::available()
    {
        if(this->isOpen())
        {
#if SYSTEM == LINUX
            int count = 0;

            if (::ioctl(this->_descriptor, FIONREAD, &count) == -1)
                return 0;
#endif

#if SYSTEM == WINDOWS
            u_long count = 0;

            if (::ioctlsocket(this->_descriptor, FIONREAD, &count) == SOCKET_ERROR)
                return 0;
#endif

            return (uint32_t)count;
        }

        return 0;
    }

    bool Socket::readByte(uint8_t &outValue)
    {
        if(this->read(&outValue, 1))
            return true;

        outValue = 0;

        return false;
    }

    bool Socket::wait(int bytesCount)
    {
#if SYSTEM == LINUX
//        // polityka dodatkowych zmiennych w metodzie złuży czesciowemu rozwiązaniu problemu hazardu dla wielu watków

//        // zmienna przechowujaca ilosc odczytanych byte'ów
//        int readBytes = this->_readBytes;

//        // informacja o dostępnych byte'ach
//        int available = this->available();

//        // pobieramy czas po ktorym nastepuje zatrzymanie nasluchiwania
//        long stop = Time::getTotalMicroseconds() + this->_timeout;

//        // nasluchujemy
//        while(this->isOpen())
//        {
//            // sprawdzamy czy nieminal czas nasluchiwania
//            if(Helpers::getMicrosecondTime() < stop)
//            {
//                // jesli nie dotarla kompletna ilosc danych to czekamy dalej
//                if(this->available() < bytesCount)
//                {
//                    basic::Helpers::sleepMicroseconds(this->_timeoutStep);
//                }
//                else
//                {
//                    // jesli dotarl naglowek to przerywany nasluchiwanie
//                    return true;
//                }
//            }
//            else
//            {
//                // zmienna pomocnicza przechowujaca ilosc odczytanych byte'ów
//                int tmpReadBytes = this->_readBytes;

//                // zmienna pomocnicza przechowujaca ilosc ostatnio dostepnych byte'ow
//                int tmpAvailable = this->available();

//                // jeśli w ciągu osttniego czasu przybyły jakies byte'y to wydłużamy czas czekania o kolejny timeout
//                if((tmpReadBytes - readBytes) + available > tmpAvailable)
//                {
//                    // aktualizujemy ilosc odczytanych byteów
//                    readBytes = tmpReadBytes;

//                    // aktualizujemy informacje o dostępnych byte'ach
//                    available = tmpAvailable;

//                    // pobieramy nowy czas po którym nastąpi zaczymanie petli oczekujacej okreslonej ilosci byte'ow
//                    stop = basic::Helpers::getMicrosecondTime() + this->_timeout;
//                }
//                else
//                {
//                    return false;
//                }
//            }
//        }
#endif

        return false;
    }
}}
