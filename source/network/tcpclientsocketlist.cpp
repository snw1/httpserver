/**
 * \file tcpclientsocketlist.cpp
 * \brief List of TCP client sockets
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
#include <network/tcpclientsocketlist.h>

using namespace std;

namespace Network
{

TCPClientSocketList::TCPClientSocketList()
{
    FD_ZERO(&m_fdset);
}

TCPClientSocketList::~TCPClientSocketList()
{
}

void TCPClientSocketList::add(TCPClientSocket &socket)
{
    checkFD(socket.fd());
    emplace_back(move(socket));
}

bool TCPClientSocketList::isSelected(const TCPClientSocket &socket) const
{
    checkFD(socket.fd());
    return FD_ISSET(socket.fd(), &m_fdset);
}

void TCPClientSocketList::selectReadable()
{
    FD_ZERO(&m_fdset);
    if (empty())
        return;
    SOCKET maxfd = INVALID_SOCKET;
    for (auto &socket : *this)
    {
        FD_SET(socket.fd(), &m_fdset);
        maxfd = max(maxfd, socket.fd());
    }
    if (select(maxfd + 1, &m_fdset, 0, 0, 0) == SOCKET_ERROR)
        throw SocketSelectException(Utils::Strings::format("error selecting sockets: %s (%d)", strerror(errno), errno));
}

void TCPClientSocketList::selectWriteable()
{
    FD_ZERO(&m_fdset);
    if (empty())
        return;
    SOCKET maxfd = INVALID_SOCKET;
    for (auto &socket : *this)
    {
        FD_SET(socket.fd(), &m_fdset);
        maxfd = max(maxfd, socket.fd());
    }
    if (select(maxfd + 1, &m_fdset, 0, 0, 0) == SOCKET_ERROR)
        throw SocketSelectException(Utils::Strings::format("error selecting sockets: %s (%d)", strerror(errno), errno));
}

void TCPClientSocketList::checkFD(SOCKET fd)
{
    if (fd < 0 || fd >= FD_SETSIZE)
        throw InvalidFileDescriptorException(Utils::Strings::format("bad file descriptor %d", fd));
}

}
