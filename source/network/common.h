/**
 * \file common.h
 * \brief Common network utilities
 * \author Andrew Sheetov <andrew.sheetov@gmail.com>
 * \date 2014
 * \version 0.0
 * \copyright GPL <http://www.gnu.org/licenses/gpl.txt>
 *
 * This file is part of HTTPServer.
 * HTTPServer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HTTPServer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HTTPServer. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NETWORK_COMMON_H
#define NETWORK_COMMON_H

#include <string>

#if defined(_WIN32)
    #include <network/wsa.h>
#elif defined(__unix__)
    #include <netdb.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
    typedef int SOCKET;
    const int INVALID_SOCKET = -1;
    const int SOCKET_ERROR = -1;
#else
    #error Unsupported platform!
#endif

namespace Network
{

const std::string LOCALHOST = "localhost"; /**< Local host name */
const std::string LOCALIP = "127.0.0.1"; /**< Local host IP address */

/**
 * Creates a new TCP socket
 * \return Socket descriptor
 */
SOCKET createTCPSocket();
/**
 * Closes a TCP socket
 * \param[in] Socket descriptor
 */
void closeTCPSocket(SOCKET &socket);

/**
 * Resolves a host name
 * \param[in] Host name
 * \return Host IP address
 */
std::string host2ip(const std::string &host);
/**
 * Resolves a host IP address
 * \param[in] Host IP address
 * \return Host name
 * \warning Not implemented yet!
 */
std::string ip2host(const std::string &ip);

}

#endif // NETWORK_COMMON_H
