/**
 * \file tcpsocket.h
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

#ifndef NETWORK_TCPSOCKET_H
#define NETWORK_TCPSOCKET_H

#include <string>
#include <network/common.h>

namespace Network
{

/*
 * \class TCPSocket
 * \brief TCP socket
 * \warning Objects of this class cannot be created!
 */
class TCPSocket
{
public:
    /**
     * Destructor
     */
    virtual ~TCPSocket();
    /**
     * Copy assignment
     * \param[in] rhs Source socket
     * \return This socket
     * \warning Deleted!
     */
    TCPSocket &operator=(const TCPSocket &rhs) = delete;
    /**
     * Move assignment
     * \param[in] rhs Source socket
     * \return This socket
     */
    TCPSocket &operator=(TCPSocket &&rhs);
    /**
     * Disconnects socket
     */
    void disconnect();
    /**
     * Sets non-blocking socket mode
     */
    void nonblock();
    /**
     * Returns a socket connection status
     * \return Is socket connected
     */
    bool connected() const;
    /**
     * Returns a socket descriptor
     * \return Socket descriptor
     */
    SOCKET fd() const;
    /**
     * Returns a socket IP address
     * \return Socket IP address
     */
    const std::string &ip() const;
    /**
     * Returns a socket port
     * \return Socket port
     */
    int port() const;
    /**
     * Returns a debug string
     * \return Debug string
     */
    std::string debugStr() const;
protected:
    /**
     * Constructor
     * \param[in] server Is server or client
     */
    TCPSocket(bool server);
    /**
     * Constructor
     * \param[in] server Is server or client
     * \param[in] fd Socket descriptor
     * \param[in] ip Socket IP address
     * \param[in] port Socket port
     */
    TCPSocket(bool server, SOCKET fd, const std::string &ip, int port);
    /**
     * Copy constructor
     * \param[in] rhs Source socket
     * \warning Deleted!
     */
    TCPSocket(const TCPSocket &rhs) = delete;
    /**
     * Move constructor
     * \param[in] rhs Source socket
     */
    TCPSocket(TCPSocket &&rhs);
    /**
     * Moves source socket to this one
     * \param[in] rhs Source socket
     */
    void move(TCPSocket &rhs);
    /*!
     * Performs connect or bind (for client or server socket)
     * \param[in] ip Socket IP address
     * \param[in] port Socket port
     */
    void connect(const std::string &ip, int port);
    bool m_server; /**< Is server or client socket */
#if defined(_WIN32)
    WSAData &m_wsa;
#endif
    bool m_connected; /**< Is socket connected */
    SOCKET m_fd; /**< Socket descriptor */
    std::string m_ip; /**< Socket IP address */
    int m_port; /**< Socket port */
};

}

#endif // NETWORK_TCPSOCKET_H
