/**
 * \file fileinfo.cpp
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

#include <utils/fileinfo.h>

using namespace std;

namespace Utils
{

namespace FileSystem
{

FileInfo::FileInfo(const string &name, long long size, FileType type)
        : m_name(name),
          m_size(size),
          m_type(type)
{
}

FileInfo::~FileInfo()
{
}

bool FileInfo::operator<(const FileInfo &rhs) const
{
    return m_name < rhs.m_name;
}

const string &FileInfo::name() const
{
    return m_name;
}

long long FileInfo::size() const
{
    return m_size;
}

FileType FileInfo::type() const
{
    return m_type;
}

}

}
