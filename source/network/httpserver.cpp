/**
 * \file httpserver.cpp
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

#include <network/httpserver.h>
#include <utils/strings.h>
#include <utils/logger.h>
#include <http/common.h>
#include <http/httpparser.h>
#include <http/httpokresponse.h>
#include <http/httpnotfoundresponse.h>

using namespace std;

namespace Network
{

HTTPServer::HTTPServer()
{
}

HTTPServer::~HTTPServer()
{
}

void HTTPServer::start(int port, const string &dir)
{
    m_dir = dir;
    TCPServer::start(port);
}

void HTTPServer::start(const string &ip, int port, const string &dir)
{
    m_dir = dir;
    TCPServer::start(ip, port);
}

void HTTPServer::process(TCPClientSocket &client)
{
    HTTP::HTTPParser parser;
    while (true)
    {
        string str = client.receive();
        LOG(Utils::Strings::format("Client %s data: %s", client.debugStr().c_str(), str.c_str()));
        parser.process(str);
        HTTP::HTTPRequest request;
        if (parser.parse(request))
        {
            LOG(Utils::Strings::format("Client %s request: %s", client.debugStr().c_str(), request.debugStr().c_str()));
            string path = m_dir + "/" + HTTP::uriDecode(request.uri());
            unique_ptr<HTTP::HTTPResponse> response = HTTP::createHTTPResponse(HTTP::uriDecode(request.uri()), HTTP::uriDecode(path));
            LOG(Utils::Strings::format("Client %s response: %s", client.debugStr().c_str(), response->debugStr().c_str()));
            client.send(*response);
            client.disconnect();
            break;
        }
    }
}

}
