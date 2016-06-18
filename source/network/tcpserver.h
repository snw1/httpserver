/**
 * \file tcpserver.h
 * \brief TCP server
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

#ifndef NETWORK_TCPSERVER_H
#define NETWORK_TCPSERVER_H

#include <string>
#include <map>
#include <list>
#include <utility>
#include <thread>
#include <mutex>
#include <atomic>
#include <network/tcpserversocket.h>
#include <network/tcpclientsocket.h>
#include <network/tcpclientsocketlist.h>

namespace Network
{

/**
 * \class TCPServer
 * \brief TCP server
 * \warning Objects of this class cannot be created!
 */
class TCPServer
{
public:
    /**
     * Constructor
     */
    TCPServer();
    /**
     * Destructor
     */
    virtual ~TCPServer();
    /**
     * Starts a server
     * \param[in] port Server port
     */
    void start(int port);
    /**
     * Starts a server
     * \param[in] ip Server IP address
     * \param[in] port Server port
     */
    void start(const std::string &ip, int port);
    /**
     * Processes a client request
     * \param[in] client Client socket
     * \warning Pure virtual method, must be overridden!
     */
    virtual void process(TCPClientSocket &client) = 0;
private:
    /**
     * Client connecting thread routine
     * \param[in] server Server
     * \param[in] socket Server socket
     */
    static void connect(TCPServer *server, TCPServerSocket &socket);
    /**
     * Client data exchanging thread routine
     * \param[in] server Server
     */
    static void exchange(TCPServer *server);
    /**
     * Client worker thread routine
     * \param[in] server Server
     * \param[in] client Client socket
     */
    static void worker(TCPServer *server, TCPClientSocket client);
    TCPClientSocketList m_clients; /**< Client socket list */
    std::mutex m_lock; /**< Lock */
    std::atomic<int> m_workers; /**< Client workers counter */
};

}

#endif // NETWORK_TCPSERVER_H
