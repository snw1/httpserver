/**
 * \file httpresponse.cpp
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

#include <utils/strings.h>
#include <http/common.h>

using namespace std;

namespace HTTP
{

HTTPResponse::HTTPResponse(const string &code, const string &data)
        : m_code(code),
          m_data(data),
          m_type(Utils::FileSystem::getFileType(m_data))
{
}

HTTPResponse::~HTTPResponse()
{
}

const string &HTTPResponse::code() const
{
    return m_code;
}

const string &HTTPResponse::data() const
{
    return m_data;
}

HTTPResponse::operator string() const
{
    string header = Utils::Strings::format("HTTP/1.0 %s\n" \
            "Content-Type: %s\n" \
            "Content-Length: %d\n" \
            "\n", m_code.c_str(), fileTypeToMimeType(m_type).c_str(), m_data.length());
    return header + m_data;
}

string HTTPResponse::debugStr() const
{
    return Utils::Strings::format("code: %s, data: %d bytes", m_code.c_str(), m_data.length());
}

}
