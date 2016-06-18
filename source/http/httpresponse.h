/**
 * \file httpresponse.h
 * \brief HTTP response
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

#ifndef HTTP_HTTPRESPONSE_H
#define HTTP_HTTPRESPONSE_H

#include <ostream>
#include <memory>
#include <utils/filesystem.h>

namespace HTTP
{

/**
 * \class HTTPResponse
 *
 */
class HTTPResponse
{
public:
    /**
     * Constructor
     * \param[in] code Response code
     * \param[in] data Response content
     */
    HTTPResponse(const std::string &code, const std::string &data);
    /**
     * Destructor
     */
    virtual ~HTTPResponse();
    /**
     * Converts an HTTP response to a string
     * \return String
     */
    operator std::string() const;
    /**
     * Returns an HTTP response code
     * \return HTTP response code
     */
    const std::string &code() const;
    /**
     * Returns an HTTP response content
     * \return HTTP response content
     */
    const std::string &data() const;
    /**
     * Returns a debug string
     * \return Debug string
     */
    std::string debugStr() const;
private:
    std::string m_code; /**< HTTP response code */
    std::string m_data; /**< HTTP response content */
    Utils::FileSystem::FileType m_type; /**< HTTP response content type */
};

}

#endif // HTTP_HTTPRESPONSE_H
