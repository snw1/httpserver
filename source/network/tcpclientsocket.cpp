/**
 * \file tcpclientsocket.cpp
 * \brief TCP client socket
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

#include <string.h>
#include <errno.h>
#include <utils/exceptions.h>
#include <utils/strings.h>
#include <network/common.h>
#include <network/tcpclientsocket.h>

using namespace std;

namespace Network
{

TCPClientSocket::TCPClientSocket()
        : TCPSocket(false)
{
}

TCPClientSocket::TCPClientSocket(SOCKET fd, const string &ip, int port)
        : TCPSocket(false, fd, ip, port)
{
}

TCPClientSocket::TCPClientSocket(TCPClientSocket &&rhs)
        : TCPSocket(false)
{
    move(rhs);
}

TCPClientSocket::~TCPClientSocket()
{
}

TCPClientSocket &TCPClientSocket::operator=(TCPClientSocket &&rhs)
{
    if (this != &rhs)
        move(rhs);
    return *this;
}

void TCPClientSocket::connect(const string &ip, int port)
{
    TCPSocket::connect(ip, port);
}

int TCPClientSocket::send(const char *data, int size) const
{
    if (!m_connected)
        throw SocketNotConnectedException("socket not connected");
    int res = ::send(m_fd, data, size, 0);
    if (res == 0)
        throw SocketDisconnectedException("socket disconnected");
    if (res == SOCKET_ERROR)
        throw SocketSendException(Utils::Strings::format("error sending data: %s (%d)", strerror(errno), errno));
    return res;
}

int TCPClientSocket::receive(char *data, int size) const
{
    if (!m_connected)
        throw SocketNotConnectedException("socket not connected");
    int res = ::recv(m_fd, data, size, 0);
    if (res == 0)
        throw SocketDisconnectedException("socket disconnected");
    if (res == SOCKET_ERROR)
        throw SocketSendException(Utils::Strings::format("error receiving data: %s (%d)", strerror(errno), errno));
    return res;
}

void TCPClientSocket::send(const string &str) const
{
    const char *data = &*str.begin();
    int size = str.length();
    while (size > 0)
    {
        int ns = send(data, size);
        data += ns;
        size -= ns;
    }
}

string TCPClientSocket::receive() const
{
    string str;
    str.resize(4096);
    int nr = receive(&*str.begin(), str.length());
    str.resize(nr);
    return str;
}

}
