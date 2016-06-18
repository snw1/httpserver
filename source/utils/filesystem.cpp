/**
 * \file filesystem.cpp
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

#include <fstream>
#include <sys/stat.h>
#include <utils/filesystem.h>
#include <utils/exceptions.h>
#include <utils/strings.h>

using namespace std;

namespace Utils
{

namespace FileSystem
{

string nl2br(const string &str)
{
    string res;
    for (char c : str)
        if (c == '\n')
            res += "<br>";
        else
            res += c;
    return res;
}

long long getFileSize(istream &is)
{
    long long pos = is.tellg();
    is.seekg(0, ios_base::end);
    long long size = is.tellg();
    is.seekg(pos);
    return size;
}

bool readFile(const string &path, string &content, long long size)
{
    ifstream is(path, ios::binary);
    if (!is.is_open())
        return false;
    if (size == 0)
        size = getFileSize(is);
    vector<char> buf(size);
    is.read(&*buf.begin(), size);
    is.close();
    content = string(buf.begin(), buf.begin() + is.gcount());
    return true;
}

bool isTextFile(const string &content)
{
    long long lines = 1;
    long long size = min(512LL, static_cast<long long>(content.length()));
    for (long long i = 0; i < size; ++i)
        if (content[i] == '\n')
            ++lines;
        else if (content[i] == '\0')
            return false;
    return size / lines <= 200;
}

bool isHtmlFile(const string &content)
{
    return content.find("<html") != string::npos || content.find("<HTML") != string::npos;
}

FileType getFileType(const string &content)
{
    if (Utils::Strings::begins(content, Utils::Strings::unhex("42 4D")))
        return FileTypeImageBMP;
    if (Utils::Strings::begins(content, Utils::Strings::unhex("FF D8 FF DB")) || Utils::Strings::begins(content, Utils::Strings::unhex("FF D8 FF E0")) || Utils::Strings::begins(content, Utils::Strings::unhex("FF D8 FF E1")))
        return FileTypeImageJPEG;
    if (Utils::Strings::begins(content, Utils::Strings::unhex("89 50 4E 47 0D 0A 1A 0A")))
        return FileTypeImagePNG;
    if (Utils::Strings::begins(content, Utils::Strings::unhex("47 49 46 38 37 61")) || Utils::Strings::begins(content, Utils::Strings::unhex("47 49 46 38 39 61")))
        return FileTypeImageGIF;
    if (Utils::Strings::begins(content, Utils::Strings::unhex("25 50 44 46")))
        return FileTypeTextPDF;
    if (Utils::Strings::begins(content, Utils::Strings::unhex("FF FB")) || Utils::Strings::begins(content, Utils::Strings::unhex("49 44 33")))
        return FileTypeAudioMP3;
    if (content.length() >= 8 && content.substr(4, 4) == "ftyp")
        return FileTypeVideoMP4;
    if (isTextFile(content))
    {
        if (isHtmlFile(content))
            return FileTypeTextHTML;
        return FileTypeTextTXT;
    }
    return FileTypeBinary;
}

string fileTypeToString(Utils::FileSystem::FileType type)
{
    if (type == Utils::FileSystem::FileTypeImageBMP)
        return "BMP";
    if (type == Utils::FileSystem::FileTypeImageJPEG)
        return "JPEG";
    if (type == Utils::FileSystem::FileTypeImagePNG)
        return "PNG";
    if (type == Utils::FileSystem::FileTypeImageGIF)
        return "GIF";
    if (type == Utils::FileSystem::FileTypeTextPDF)
        return "PDF";
    if (type == Utils::FileSystem::FileTypeTextHTML)
        return "HTML";
    if (type == Utils::FileSystem::FileTypeTextTXT)
        return "TXT";
    if (type == Utils::FileSystem::FileTypeAudioMP3)
        return "MP3";
    if (type == Utils::FileSystem::FileTypeVideoMP4)
        return "MP4";
    return "BIN";
}

bool isFile(const string &path)
{
    struct stat st;
    if (stat(path.c_str(), &st) == -1)
        return false;
    return S_ISREG(st.st_mode);
}

bool isDirectory(const string &path)
{
    struct stat st;
    if (stat(path.c_str(), &st) == -1)
        return false;
    return S_ISDIR(st.st_mode);
}

long long getFileSize(const string &path)
{
    struct stat st;
    if (stat(path.c_str(), &st) == -1)
        throw StatException(Utils::Strings::format("stat error: %s (%d)", strerror(errno), errno));
    return st.st_size;
}

FileInfo getFileInfo(const string &path, const string &name)
{
    struct stat st;
    if (stat(path.c_str(), &st) == -1)
        throw StatException(Utils::Strings::format("stat error: %s (%d)", strerror(errno), errno));
    string content;
    readFile(path, content, 512);
    return FileInfo(name, st.st_size, getFileType(content));
}

string fileSizeToString(long long size)
{
    char suffix[] = "KMGTP";
    if (size < 1024)
        return Utils::Strings::tostring(size);
    double ds = size / 1024.0;
    int i = 0;
    while (ds >= 1024.0 && i < sizeof(suffix) - 2)
    {
        ds /= 1024.0;
        ++i;
    }
    return Utils::Strings::format("%0.2lf%c", ds, suffix[i]);
}

}

}
