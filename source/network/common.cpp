/**
 * \file common.cpp
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

#include <network/common.h>
#include <utils/strings.h>
#include <utils/exceptions.h>

using namespace std;

namespace Network
{

SOCKET createTCPSocket()
{
    SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket == INVALID_SOCKET)
        throw SocketCreateException("error creating socket");
    return socket;
}

void closeTCPSocket(SOCKET &socket)
{
#if defined(_WIN32)
    ::shutdown(socket, SD_BOTH);
    ::closesocket(socket);
#elif defined(__unix__) || defined(__MACH__)
    ::shutdown(socket, SHUT_RDWR);
    ::close(socket);
#else
    #error Unsupported platform!
#endif
}

string host2ip(const string &host)
{
#if defined(_WIN32)
    WSAData &wsa = WSA::init();
#endif
    struct hostent *hp = gethostbyname(host.c_str());
    if (!hp)
        throw HostResolveException(Utils::Strings::format("server name resolving failed: %s (%d)", strerror(errno), errno));
    struct in_addr *addr = (in_addr *)hp->h_addr;
    return inet_ntoa(*addr);
}

string ip2host(const string &ip)
{
    return "";
}

}
