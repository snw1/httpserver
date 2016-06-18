/**
 * \file httprequest.h
 * \brief HTTP request
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

#ifndef HTTP_HTTPREQUEST_H
#define HTTP_HTTPREQUEST_H

#include <string>
#include <map>

namespace HTTP
{

/**
 * \class HTTPRequest
 * \brief HTTP request
 */
class HTTPRequest
{
public:
    /**
     * Constructor
     */
    HTTPRequest();
    /**
     * Constructor
     * \param[in] method HTTP method
     * \param[in] uri URI
     * \param[in] version HTTP version
     * \param[in] params URI parameters (name, value)
     */
    HTTPRequest(const std::string &method, const std::string &uri, const std::string &version, const std::map<std::string, std::string> &params);
    /**
     * Destructor
     */
    virtual ~HTTPRequest();
    /**
     * Returns HTTP method
     * \return HTTP method
     */
    const std::string &method() const;
    /**
     * Returns URI
     * \return URI
     */
    const std::string &uri() const;
    /**
     * Returns HTTP version
     * \return HTTP version
     */
    const std::string &version() const;
    /**
     * Returns URI parameters (name, value)
     * \return URI parameters
     */
    const std::map<std::string, std::string> &params() const;
    /**
     * Returns debug string
     * \return Debug string
     */
    std::string debugStr();
private:
    std::string m_method; /**< HTTP method */
    std::string m_uri; /**< URI */
    std::string m_version; /**< HTTP version */
    std::map<std::string, std::string> m_params; /**< URI parameters (name, value) */
};

}

#endif // HTTP_HTTPREQUEST_H
