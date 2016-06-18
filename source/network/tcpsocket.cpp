/**
 * \file tcpsocket.cpp
 * \brief TCP socket
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

#include <utils/strings.h>
#include <utils/exceptions.h>
#include <network/common.h>
#include <network/tcpsocket.h>

using namespace std;

namespace Network
{

TCPSocket::TCPSocket(bool server)
        : m_server(server),
#if defined(_WIN32)
          m_wsa(WSA::init()),
#endif
          m_connected(false),
          m_fd(INVALID_SOCKET),
          m_ip(""),
          m_port(-1)
{
}

TCPSocket::TCPSocket(bool server, SOCKET fd, const string &ip, int port)
        : m_server(server),
#if defined(_WIN32)
          m_wsa(WSA::init()),
#endif
          m_connected(true),
          m_fd(fd),
          m_ip(ip),
          m_port(port)
{
}

TCPSocket::TCPSocket(TCPSocket &&rhs)
#if defined(_WIN32)
        : m_wsa(WSA::init())
#endif
{
    move(rhs);
}

TCPSocket::~TCPSocket()
{
    disconnect();
}

TCPSocket &TCPSocket::operator=(TCPSocket &&rhs)
{
    if (this != &rhs)
        move(rhs);
    return *this;
}

void TCPSocket::disconnect()
{
    if (!m_connected)
        return;
    closeTCPSocket(m_fd);
    m_connected = false;
}

void TCPSocket::nonblock()
{
#if defined(_WIN32)
    unsigned long flags = 1;
    if (ioctlsocket(m_fd, FIONBIO, &flags) == SOCKET_ERROR)
        throw IOControlException(Utils::Strings::format("i/o control error: %s (%d)", strerror(errno), errno));
#elif defined(__unix__)
#if defined(O_NONBLOCK)
    int flags = fcntl(m_fd, F_GETFL, 0);
    if (flags == SOCKET_ERROR)
        throw FileControlException(Utils::Strings::format("file control error: %s (%d)", strerror(errno), errno));
    flags |= O_NONBLOCK;
    if (fcntl(m_fd, F_SETFL, flags) == SOCKET_ERROR)
        throw FileControlException(Utils::Strings::format("file control error: %s (%d)", strerror(errno), errno));
#else
    int flags = 1;
    if (ioctl(m_fd, FIONBIO, &flags) == SOCKET_ERROR)
        throw IOControlException(Utils::Strings::format("i/o control error: %s (%d)", strerror(errno), errno));
#endif
#else
    #error Unsupported platform!
#endif
}

SOCKET TCPSocket::fd() const
{
    return m_fd;
}

bool TCPSocket::connected() const
{
    return m_connected;
}

const string &TCPSocket::ip() const
{
    return m_ip;
}

int TCPSocket::port() const
{
    return m_port;
}

string TCPSocket::debugStr() const
{
    return Utils::Strings::format("%s:%d [%d]", m_ip.c_str(), m_port, m_fd);
}

void TCPSocket::move(TCPSocket &rhs)
{
    disconnect();
    m_server = rhs.m_server;
    m_connected = rhs.m_connected;
    m_fd = rhs.m_fd;
    m_ip = rhs.m_ip;
    m_port = rhs.m_port;
    rhs.m_connected = false;
}

void TCPSocket::connect(const string &ip, int port)
{
    if (m_connected)
    {
        if (m_server)
            throw SocketAlreadyBindedException("socket already binded");
        else
            throw SocketAlreadyConnectedException("socket already connected");
    }
    m_fd = createTCPSocket();
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    if (m_server)
    {
#if defined(__unix__)
        int enable = 1;
        if (::setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == SOCKET_ERROR)
        {
            closeTCPSocket(m_fd);
            throw SocketSetOptionException(Utils::Strings::format("error setting socket option: %s (%d)", strerror(errno), errno));
        }
#endif
        if (::bind(m_fd, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
        {
            closeTCPSocket(m_fd);
            throw SocketConnectException(Utils::Strings::format("error binding socket: %s (%d)", strerror(errno), errno));
        }
    }
    else
    {
        if (::connect(m_fd, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
        {
            closeTCPSocket(m_fd);
            throw SocketConnectException(Utils::Strings::format("error connecting socket: %s (%d)", strerror(errno), errno));
        }
    }
    m_ip = ip;
    m_port = port;
    m_connected = true;
}

}
