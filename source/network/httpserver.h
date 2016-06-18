/**
 * \file httpserver.h
 * \brief HTTP server
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

#ifndef NETWORK_HTTPSERVER_H
#define NETWORK_HTTPSERVER_H

#include <string>
#include <network/tcpserver.h>

namespace Network
{

/**
 * \class HTTPServer
 * \brief HTTP server
 */
class HTTPServer : public TCPServer
{
public:
    /**
     * Constructor
     */
    HTTPServer();
    /**
     * Destructor
     */
    virtual ~HTTPServer();
    /**
     * Starts a server
     * \param[in] port Server port
     * \param[in] dir Server home directory
     */
    void start(int port, const std::string &dir);
    /**
     * Starts a server
     * \param[in] ip Server IP address
     * \param[in] port Server port
     * \param[in] dir Server home directory
     */
    void start(const std::string &ip, int port, const std::string &dir);
    /**
     * Processes a client request
     * \param[in] client Client socket
     */
    virtual void process(TCPClientSocket &client);
private:
    std::string m_dir; /**< Server home directory */
};

}

#endif // NETWORK_HTTPSERVER_H
