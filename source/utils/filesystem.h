/**
 * \file filesystem.h
 * \brief File system utilities
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

#ifndef UTILS_FILESYSTEM_H
#define UTILS_FILESYSTEM_H

#include <string>
#include <vector>
#include <utils/filetype.h>
#include <utils/fileinfo.h>

namespace Utils
{

namespace FileSystem
{

/**
 * Converts \n into <br> in a string
 * \param[in] str String
 * \return Converted string
 */
std::string nl2br(const std::string &str);
/**
 * Reads a file content
 * \param[in] path Path to a file
 * \param[out] content File content
 * \param[in] size Bytes to read
 * \return Read succeeded
 */
bool readFile(const std::string &path, std::string &content, long long size = 0);
/**
 * Returns content type
 * \param[in] content Content
 * \return File type
 */
FileType getFileType(const std::string &content);
/**
 * Determines if path is file
 * \param[in] path Path
 * \return Is path a file
 */
bool isFile(const std::string &path);
/**
 * Determines if path is directory
 * \param[in] path Path
 * \return Is path a directory
 */
bool isDirectory(const std::string &path);
/**
 * Returns file size
 * \param[in] path Path to the file
 * \return File size
 */
long long getFileSize(const std::string &path);
/**
 * Returns file type
 * \param[in] path Path to the file
 * \param[in] name File name
 * \return File type
 */
FileInfo getFileInfo(const std::string &path, const std::string &name);
/**
 * Returns string name of the file type
 * \param[in] type File type
 * \return String name
 */
std::string fileTypeToString(Utils::FileSystem::FileType type);
/**
 * Returns human readable file size string
 * \param[in] size File size
 * \return FIle size string
 */
std::string fileSizeToString(long long size);

}

}

#endif // UTILS_FILESYSTEM_H
