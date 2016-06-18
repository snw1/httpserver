/**
 * \file wsa.h
 * \brief WSA wrapper
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

#ifndef NETWORK_WSA_H
#define NETWORK_WSA_H

#define FD_SETSIZE 1024
#include <winsock2.h>
#include <windows.h>
typedef int socklen_t;

namespace Network
{

/**
 * \class WSA
 * \brief WSA wrapper
 */
class WSA
{
public:
    /**
     * Inializes WSA
     * \return WSA data
     */
    static WSAData &init();
private:
    /**
     * Constructor
     */
    WSA();
    /**
     * Copy constructor
     * \param[in] wsa Source WSA
     * \warning Deleted!
     */
    WSA(const WSA &wsa) = delete;
    /**
     * Destructor
     */
    virtual ~WSA();
    /**
     * Copy assignment
     * \param[in] wsa Source WSA
     * \return This WSA
     * \warning Deleted!
     */
    WSA &operator=(const WSA &wsa) = delete;
    /**
     * Starts WSA
     */
    void startup();
    /**
     * Releases WSA
     */
    void cleanup();
    WSAData m_data; /**< WSA data */
};

}

#endif // NETWORK_WSA_H
