/**
 * \file tcpclientsocket.h
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

#ifndef NETWORK_TCPCLIENTSOCKET_H
#define NETWORK_TCPCLIENTSOCKET_H

#include <string>
#include <utils/filesystem.h>
#include <network/tcpsocket.h>

namespace Network
{

/**
 * \class TCPClientSocket
 * \brief TCP client socket
 */
class TCPClientSocket : public TCPSocket
{
public:
    /**
     * Constructor
     */
    TCPClientSocket();
    /**
     * Constructor
     * \param[in] fd Socket descriptor
     * \param[in] ip IP address
     * \param[in] port Port
     */
    TCPClientSocket(SOCKET fd, const std::string &ip, int port);
    /**
     * Copy constructor
     * \param[in] rhs Source socket
     * \warning Deleted!
     */
    TCPClientSocket(const TCPClientSocket &rhs) = delete;
    /**
     * Move constructor
     * \param[in] rhs Source socket
     */
    TCPClientSocket(TCPClientSocket &&rhs);
    /**
     * Destructor
     */
    virtual ~TCPClientSocket();
    /**
     * Copy assignment
     * \param[in] rhs Source socket
     * \return This socket
     * \warning Deleted!
     */
    TCPClientSocket &operator=(const TCPClientSocket &rhs) = delete;
    /**
     * Move assignment
     * \param[in] rhs Source socket
     * \return This socket
     */
    TCPClientSocket &operator=(TCPClientSocket &&rhs);
    /**
     * Connects a socket to a server
     * \param[in] ip Server IP address
     * \param[in] port Server port
     */
    void connect(const std::string &ip, int port);
    /**
     * Sends a data to a server
     * \param[in] data Data
     * \param[in] size Data size
     * \return Bytes sent
     */
    int send(const char *data, int size) const;
    /**
     * Sends a string to a server
     * \param[in] str String
     */
    void send(const std::string &str) const;
    /**
     * Receives a data from a server
     * \param[in] data Data
     * \param[in] size Data size
     * \return Bytes received
     */
    int receive(char *data, int size) const;
    /**
     * Receives a string from a server
     * \return String
     */
    std::string receive() const;
};

}

#endif // NETWORK_TCPCLIENTSOCKET_H
