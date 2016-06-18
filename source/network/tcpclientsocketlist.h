/**
 * \file tcpclientsocketlist.h
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

#ifndef NETWORK_TCPCLIENTSOCKETLIST_H
#define NETWORK_TCPCLIENTSOCKETLIST_H

#include <list>
#include <network/common.h>
#include <network/tcpclientsocket.h>

namespace Network
{

/**
 * \class TCPClientSocketList
 * \brief List of TCP client sockets
 */
class TCPClientSocketList : public std::list<TCPClientSocket>
{
public:
    /**
     * Constructor
     */
    TCPClientSocketList();
    /**
     * Destructor
     */
    virtual ~TCPClientSocketList();
    /**
     * Adds a client socket
     * \param[in] socket Client socket
     */
    void add(TCPClientSocket &socket);
    /**
     * Returns if client socket is selected as readable or writeable
     * \param[in] socket Client socket
     * \return Selected?
     */
    bool isSelected(const TCPClientSocket &socket) const;
    /**
     * Selects readable client sockets
     */
    void selectReadable();
    /**
     * Selects writeable client sockets
     */
    void selectWriteable();
private:
    /**
     * Checks if socket descriptior is valid
     * \param[in] fd Socket descriptor
     */
    static void checkFD(SOCKET fd);
    fd_set m_fdset; /**< Socket descriptor set */
};

}

#endif // NETWORK_TCPCLIENTSOCKETLIST_H
