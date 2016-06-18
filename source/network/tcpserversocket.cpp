/**
 * \file tcpserversocket.cpp
 * \brief TCP server socket
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

#include <utils/exceptions.h>
#include <utils/strings.h>
#include <network/tcpserversocket.h>
#include <network/common.h>

using namespace std;

namespace Network
{

TCPServerSocket::TCPServerSocket()
        : TCPSocket(true),
          m_listen(false)
{
}

TCPServerSocket::TCPServerSocket(TCPServerSocket &&rhs)
        : TCPSocket(true)
{
    move(rhs);
}

TCPServerSocket::~TCPServerSocket()
{
}

TCPServerSocket &TCPServerSocket::operator=(TCPServerSocket &&rhs)
{
    if (this != &rhs)
        move(rhs);
    return *this;
}

void TCPServerSocket::bind(int port)
{
    bind(LOCALIP, port);
}

void TCPServerSocket::bind(const string &ip, int port)
{
    TCPSocket::connect(ip, port);
}

void TCPServerSocket::listen()
{
    if (!m_connected)
        throw SocketNotBoundException("socket not bound");
    if (::listen(m_fd, SOMAXCONN) == SOCKET_ERROR)
        throw SocketListenException(Utils::Strings::format("error listening socket: %s (%d)", strerror(errno), errno));
    m_listen = true;
}

TCPClientSocket TCPServerSocket::accept()
{
    if (!m_connected)
        throw SocketNotBoundException("socket not bound");
    if (!m_listen)
        throw SocketNotListenException("socket not listen");
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t size = sizeof(addr);
    int socket = ::accept(m_fd, (struct sockaddr *)&addr, &size);
    if (socket == SOCKET_ERROR)
        throw SocketAcceptException(Utils::Strings::format("error accepting connection: %s (%d)", strerror(errno), errno));
    return TCPClientSocket(socket, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
}

void TCPServerSocket::move(TCPServerSocket &rhs)
{
    TCPSocket::move(rhs);
    if (m_connected)
        m_listen = rhs.m_listen;
}

}
