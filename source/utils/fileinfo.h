/**
 * \file fileinfo.h
 * \brief File information
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

#ifndef UTILS_FILEINFO_H
#define UTILS_FILEINFO_H

#include <string>
#include <utils/filetype.h>

namespace Utils
{

namespace FileSystem
{

/**
 * \class FileInfo
 * \brief File information
 */
class FileInfo
{
public:
    /**
     * Constructor
     * \param[in] name File name
     * \param[in] size File size
     * \param[in] type File type
     */
    FileInfo(const std::string &name, long long size, FileType type);
    /**
     * Destructor
     */
    virtual ~FileInfo();
    /**
     * Determines if this file information less than another one
     * \param[in] rhs Another file information
     * \return Is less
     */
    bool operator<(const FileInfo &rhs) const;
    /**
     * Returns a file name
     * \return File name
     */
    const std::string &name() const;
    /**
     * Returns a file size
     * \return File size
     */
    long long size() const;
    /**
     * Returns a file type
     * \return File type
     */
    FileType type() const;
private:
    std::string m_name; /**< File name */
    long long m_size; /**< File size */
    FileType m_type; /**< File type */
};

}

}

#endif // UTILS_FILEINFO_H
