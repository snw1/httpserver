/**
 * \file tcpserversocket.h
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

#ifndef NETWORK_TCPSERVERSOCKET_H
#define NETWORK_TCPSERVERSOCKET_H

#include <string>
#include <memory>
#include <network/tcpclientsocket.h>

namespace Network
{

/**
 * \class TCPServerSocket
 * \brief TCP server socket
 */
class TCPServerSocket : public TCPSocket
{
public:
    /**
     * Constructor
     */
    TCPServerSocket();
    /**
     * Copy constructor
     * \param[in] rhs Source socket
     * \warning Deleted!
     */
    TCPServerSocket(const TCPServerSocket &rhs) = delete;
    /**
     * Move constructor
     * \param[in] rhs Source socket
     */
    TCPServerSocket(TCPServerSocket &&rhs);
    /**
     * Destructor
     */
    virtual ~TCPServerSocket();
    /**
     * Copy assignment
     * \param[in] rhs Source socket
     * \return This socket
     * \warning Deleted!
     */
    TCPServerSocket &operator=(const TCPServerSocket &rhs) = delete;
    /**
     * Move assignment
     * \param[in] rhs Source socket
     * \return This socket
     */
    TCPServerSocket &operator=(TCPServerSocket &&rhs);
    /**
     * Binds a socket
     * \param[in] port Server port
     */
    void bind(int port);
    /**
     * Binds a socket
     * \param[in] ip Server IP address
     * \param[in] port Server port
     */
    void bind(const std::string &ip, int port);
    /**
     * Listens a socket
     */
    void listen();
    /**
     * Accepts a client connection
     * \return Client socket
     */
    TCPClientSocket accept();
private:
    /**
     * Moves source socket to this one
     * \param[in] rhs Source socket
     */
    void move(TCPServerSocket &rhs);
    bool m_listen; /**< Client workers counter */
};

}

#endif // NETWORK_TCPSERVERSOCKET_H
