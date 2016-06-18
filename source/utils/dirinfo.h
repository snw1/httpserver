/**
 * \file dirinfo.h
 * \brief Directory information
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

#ifndef UTILS_DIRINFO_H
#define UTILS_DIRINFO_H

#include <vector>
#include <string>
#include <utils/fileinfo.h>

namespace Utils
{

namespace FileSystem
{

/**
 * \class DirInfo
 * \brief Directory information
 */
class DirInfo
{
public:
    /**
     * Constructor
     * \param[in] path Path
     */
    DirInfo(const std::string &path);
    /**
     * Desctructor
     */
    virtual ~DirInfo();
    /**
     * Scans a directory contents
     */
    void scan();
    /**
     * Returns subdirectories
     * \return Subdirectories
     */
    const std::vector<std::string> subdirs() const;
    /**
     * Returns files
     * \return Files
     */
    const std::vector<FileInfo> files() const;
private:
    std::string m_path; /**< Path */
    std::vector<std::string> m_subdirs; /**< Subdirectories */
    std::vector<FileInfo> m_files; /**< Files */
};

}

}

#endif // UTILS_DIRINFO_H
