/**
 * \file httpparser.h
 * \brief HTTP parser
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

#ifndef HTTP_HTTPPARSER_H
#define HTTP_HTTPPARSER_H

#include <string>
#include <map>
#include <utils/strings.h>
#include <http/httprequest.h>

namespace HTTP
{

/**
 * \class HTTPParser
 * \brief HTTP request parser
 */
class HTTPParser
{
public:
    /**
     * Constructor
     */
    HTTPParser();
    /**
     * Destructor
     */
    virtual ~HTTPParser();
    /**
     * Adds a HTTP request part to a temporary buffer
     * \param[in] str HTTP request part
     */
    void process(const std::string &str);
    /**
     * Parses temporary buffer contents
     * On success, erases parsed content from a buffer
     * \param[out] request Resulting HTTP request
     * \result Parsing success
     */
    bool parse(HTTPRequest &request);
private:
    /**
     * Determines if a string contains a valid HTTP method name
     * \param[in] str String
     * \result Is HTTP method
     */
    static bool isMethod(const std::string &str);
    /**
     * Parses URI parameters
     * If an URI string contains parameters, moves them from an URI string to a map
     * \param[inout] uri URI
     * \param[out] params Parameters map (name, value)
     */
    static void parseURI(std::string &uri, std::map<std::string, std::string> &params);
    std::string m_buf; /**< Temporary HTTP request buffer */
};

}

#endif // HTTP_HTTPPARSER
