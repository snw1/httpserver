/**
 * \file common.h
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

#ifndef HTTP_COMMON_H
#define HTTP_COMMON_H

#include <string>
#include <utils/filesystem.h>
#include <http/httpresponse.h>

namespace HTTP
{
/**
 * Encodes URI, replaces an "unsafe" characters to a %HEX form
 * \param[in] uri URI
 * \return encoded URI
 */
std::string uriEncode(const std::string &uri);
/**
 * Decodes encoded URI
 * \param[in] uri URI
 * \return decoded URI
 */
std::string uriDecode(const std::string &uri);
/**
 * Converts a file type to a MIME type
 * \param[in] type File type
 * \return MIME type
 */
std::string fileTypeToMimeType(Utils::FileSystem::FileType type);
/**
 * Converts directory information to a HTML content
 * \param[in] relpath Relative to server home directory path
 * \param[in] path Absolute directory path
 * \return HTML content
 */
std::string dirToHTML(std::string relpath, const std::string &path);
/**
 * Creates a HTTP response for a path request
 * \param[in] relpath Relative to server home directory path
 * \param[in] path Absolute directory path
 * \return HTTP response
 */
std::unique_ptr<HTTPResponse> createHTTPResponse(const std::string &relpath, const std::string &path);
};

#endif // HTTP_COMMON_H
