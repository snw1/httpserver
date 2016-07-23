/**
 * \file common.cpp
 * \brief Common HTTP utilities
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

#include <utils/dirinfo.h>
#include <utils/strings.h>
#include <http/common.h>
#include <http/httpokresponse.h>
#include <http/httpnotfoundresponse.h>
#include <utils/charset.h>

using namespace std;

namespace HTTP
{

string uriEncode(const string &uri)
{
    string res;
    Utils::Strings::CharSet safe("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=");
    for (char c : uri)
        if (safe.exists(c))
            res += c;
        else
            res += Utils::Strings::format("%%%02X", static_cast<unsigned char>(c));
    return res;
}

string uriDecode(const string &uri)
{
    string res;
    string buf;
    for (char c : uri)
        if (!buf.empty())
        {
            if (c >= '0' && c <= '9')
                c -= '0';
            else
                c -= 'A' - 10;
            buf += c;
            if (buf.length() >= 3)
            {
                res += (buf[1] << 4) + buf[2];
                buf.clear();
            }
        }
        else
        {
            if (c == '%')
                buf += c;
            else
                res += c;
        }
    return res;
}

string fileTypeToMimeType(Utils::FileSystem::FileType type)
{
    if (type == Utils::FileSystem::FileTypeImageBMP)
        return "image/bmp";
    if (type == Utils::FileSystem::FileTypeImageJPEG)
        return "image/jpeg";
    if (type == Utils::FileSystem::FileTypeImagePNG)
        return "image/png";
    if (type == Utils::FileSystem::FileTypeImageGIF)
        return "image/gif";
    if (type == Utils::FileSystem::FileTypeTextPDF)
        return "application/pdf";
    if (type == Utils::FileSystem::FileTypeTextHTML)
        return "text/html";
    if (type == Utils::FileSystem::FileTypeTextTXT)
        return "text/plain";
    if (type == Utils::FileSystem::FileTypeAudioMP3)
        return "audio/mpeg";
    if (type == Utils::FileSystem::FileTypeVideoMP4)
        return "video/mp4";
    return "application/octet-stream";
}

string dirToHTML(string relpath, const string &path)
{
    if (!Utils::Strings::ends(relpath, "/"))
        relpath += "/";
    string html;
    html += "<!DOCTYPE html>\n";
    html += "<html>\n";
#if defined(_WIN32)
    html += "<head><meta http-equiv='Content-Type' content='text/html; charset=windows-1251'></head>\n";
#elif defined(__unix__) || defined(__MACH__)
    html += "<head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'></head>\n";
#else
    #error Unsupported platform!
#endif
    html += "<body>\n";
    html += Utils::Strings::format("<h1><b>Directory: %s</b></h1><br>\n", relpath.c_str());
    html += "<table>\n";
    Utils::FileSystem::DirInfo dir(path);
    dir.scan();
    bool color = true;
    for (const auto &subdir : dir.subdirs())
        if (subdir != "." && subdir != "..")
        {
            html += Utils::Strings::format("<tr bgcolor=%s>", color ? "#ccccff" : "#ffffff");
            string uri = uriEncode(relpath + subdir);
            html += Utils::Strings::format("<td><a href='%s'>%s</a></td>", uri.c_str(), subdir.c_str());
            html += "<td align=center>DIR</td>";
            html += "<td align=right>&nbsp;</td>";
            html += "</tr>\n";
            color = !color;
        }
    for (const auto &file : dir.files())
    {
        html += Utils::Strings::format("<tr bgcolor=%s>", color ? "#ccccff" : "#ffffff");
        string uri = uriEncode(relpath + file.name());
        html += Utils::Strings::format("<td><a href='%s'>%s</a></td>", uri.c_str(), file.name().c_str());
        html += Utils::Strings::format("<td align=center>%s</td>", Utils::FileSystem::fileTypeToString(file.type()).c_str());
        html += Utils::Strings::format("<td align=right>%s</td>", Utils::FileSystem::fileSizeToString(file.size()).c_str());
        html += "</tr>\n";
        color = !color;
    }
    html += "</table>\n";
    html += "</body>\n";
    html += "</html>\n";
    return html;
}

unique_ptr<HTTPResponse> createHTTPResponse(const string &relpath, const string &path)
{
    if (Utils::FileSystem::isDirectory(path))
        return unique_ptr<HTTPResponse>(new HTTPOKResponse(dirToHTML(relpath, path)));
    if (Utils::FileSystem::isFile(path))
    {
        string content;
        if (Utils::FileSystem::readFile(path, content))
            return unique_ptr<HTTPResponse>(new HTTPOKResponse(content));
    }
    return unique_ptr<HTTPResponse>(new HTTPNotFoundResponse());
}

}
