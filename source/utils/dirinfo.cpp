/**
 * \file dirinfo.cpp
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

#include <algorithm>
#include <dirent.h>
#include <utils/dirinfo.h>
#include <utils/filesystem.h>

using namespace std;

namespace Utils
{

namespace FileSystem
{

DirInfo::DirInfo(const string &path)
        : m_path(path)
{
}

DirInfo::~DirInfo()
{
}

void DirInfo::scan()
{
    m_files.clear();
    m_subdirs.clear();
    DIR *dir = opendir(m_path.c_str());
    if (!dir)
        return;
    while (struct dirent *dent = readdir(dir))
    {
        string name = dent->d_name;
        string path = m_path + "/" + name;
        if (isFile(path))
        {
            try
            {
                FileInfo info = getFileInfo(path, name);
                m_files.push_back(info);
            }
            catch (...)
            {
            }
        }
        else if (isDirectory(path))
        {
            m_subdirs.push_back(name);
        }
    }
    closedir(dir);
    sort(m_files.begin(), m_files.end());
    sort(m_subdirs.begin(), m_subdirs.end());
}

const vector<string> DirInfo::subdirs() const
{
    return m_subdirs;
}

const vector<FileInfo> DirInfo::files() const
{
    return m_files;
}

}

}