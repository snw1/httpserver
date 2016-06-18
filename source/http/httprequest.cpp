/**
 * \file httprequest.cpp
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

#include <utils/strings.h>
#include <http/httprequest.h>

using namespace std;

namespace HTTP
{

HTTPRequest::HTTPRequest()
{
}

HTTPRequest::HTTPRequest(const string &method, const string &uri, const string &version, const map<string, string> &params)
        : m_method(method),
          m_uri(uri),
          m_version(version),
          m_params(params)
{
}

HTTPRequest::~HTTPRequest()
{
}

const string &HTTPRequest::method() const
{
    return m_method;
}

const string &HTTPRequest::uri() const
{
    return m_uri;
}

const string &HTTPRequest::version() const
{
    return m_version;
}

const map<string, string> &HTTPRequest::params() const
{
    return m_params;
}

string HTTPRequest::debugStr()
{
    string params;
    if (!m_params.empty())
        for (const pair<string, string> &param : m_params)
        {
            if (!params.empty())
                params += ", ";
            if (param.second.empty())
                params += param.first;
            else
                params += param.first + " = " + param.second;
        }
    return Utils::Strings::format("method: %s, uri: %s, params: {%s}, version: %s", m_method.c_str(), m_uri.c_str(), params.c_str(), m_version.c_str());
}

}
