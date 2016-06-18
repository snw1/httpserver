/**
 * \file httpparser.cpp
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

#include <utils/exceptions.h>
#include <utils/stringset.h>
#include <http/httpparser.h>

using namespace std;

namespace HTTP
{

HTTPParser::HTTPParser()
{
}

HTTPParser::~HTTPParser()
{
}

void HTTPParser::process(const string &str)
{
    m_buf += str;
}

bool HTTPParser::isMethod(const string &str)
{
    static Utils::Strings::StringSet methods({"GET", "HEAD", "POST", "PUT", "DELETE", "TRACE", "CONNECT"});
    return methods.exists(str);
}

void HTTPParser::parseURI(string &uri, map<string, string> &params)
{
    params.clear();
    int pos = uri.find("?");
    if (pos == string::npos)
        return;
    string str = uri.substr(pos + 1, uri.length() - pos - 1);
    uri.erase(pos, uri.length() - pos);
    vector<string> parts = Utils::Strings::split(str, "&");
    for (const string &part : parts)
    {
        int pos = part.find("=");
        if (pos == string::npos)
            params.insert(make_pair<string, string>(string(part), string("")));
        else
            params.insert(make_pair<string, string>(part.substr(0, pos), part.substr(pos + 1, part.length() - pos - 1)));
    }
}

bool HTTPParser::parse(HTTPRequest &request)
{
    static const string delim = "\r\n\r\n";
    int pos = m_buf.find(delim);
    if (pos == string::npos)
        return false;
    string data = m_buf.substr(0, pos);
    m_buf.erase(0, pos + delim.length());
    vector<string> lines = move(Utils::Strings::split(data, "\r\n"));
    vector<string> parts = move(Utils::Strings::split(lines[0]));
    if (parts.size() != 3)
        throw HTTPIncompleteRequest(Utils::Strings::format("Invalid HTTP request \"%s\"", lines[0].c_str()));
    string method = parts[0];
    if (!isMethod(method))
        throw HTTPInvalidMethod(Utils::Strings::format("Invalid HTTP method \"%s\"", method.c_str()));
    string uri = parts[1];
    map<string, string> params;
    parseURI(uri, params);
    string version = parts[2];
    if (version != "HTTP/1.1")
        throw HTTPUnsupportedVersion(Utils::Strings::format("Unsupported HTTP version \"%s\"", version.c_str()));
    request = HTTPRequest(method, uri, version, params);
    return true;
}

}
