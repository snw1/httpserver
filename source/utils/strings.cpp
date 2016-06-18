/**
 * \file strings.cpp
 * \brief String utilities
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

#include <set>
#include <utils/strings.h>
#include <utils/charset.h>
#include <utils/exceptions.h>

using namespace std;

namespace Utils
{

namespace Strings
{

bool begins(const string &str, const string &sstr)
{
    if (str.length() < sstr.length())
        return false;
    if (sstr.empty())
        return true;
    return str.substr(0, sstr.length()) == sstr;
}

bool ends(const string &str, const string &sstr)
{
    if (str.length() < sstr.length())
        return false;
    if (sstr.empty())
        return true;
    return str.substr(str.length() - sstr.length(), sstr.length()) == sstr;
}

string format(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vector<char> v(256, '\0');
    while (true)
    {
        va_list args2;
        va_copy(args2, args);
        int res = vsnprintf(&*v.begin(), v.size(), fmt, args2);
        if ((res >= 0) && (res < (int)v.size()))
        {
            va_end(args);
            va_end(args2);
            return string(&*v.begin());
        }
        if (res < 0)
            v.resize(v.size() * 2, '\0');
        else
            v.resize(res + 1, '\0');
    }
}

string hex(const string &str, const string &delim, bool upper)
{
    string res;
    for (char c : str)
        res += format(upper ? "%02X" : "%02x", static_cast<unsigned char>(c)) + delim;
    return res;
}

int unhex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

string unhex(string str, const string &delim)
{
    if (!delim.empty())
    {
        CharSet d(delim);
        int l = 0;
        for (int i = 0; i < str.length(); ++i)
            if (!d.exists(str[i]))
                str[l++] = str[i];
        str.resize(l);
    }
    string res;
    if (str.length() % 2 != 0)
        throw InvalidHexStringException(Utils::Strings::format("invalid hex string %s", str.c_str()));
    for (int i = 0; i < str.length(); i += 2)
    {
        int h = unhex(str[i]);
        int l = unhex(str[i + 1]);
        if (h == -1 || l == -1)
            throw InvalidHexStringException(Utils::Strings::format("invalid hex string %s", str.c_str()));
        res += static_cast<char>((h << 4) + l);
    }
    return res;
}

string part(const string &str, int &pos, const CharSet &d, bool empty)
{
    string p;
    for (; pos < str.length(); ++pos)
        if (d.exists(str[pos]))
        {
            if (!p.empty() || empty)
            {
                ++pos;
                break;
            }
            p.clear();
        }
        else
        {
            p += str[pos];
        }
    return p;
}

string part(const string &str, int &pos, const string &delim, bool empty)
{
    return part(str, pos, CharSet(delim), empty);
}

vector<string> split(const string &str, const string &delim, bool empty)
{
    CharSet d(delim);
    vector<string> parts;
    for (int pos = 0; pos < str.length();)
    {
        string p = part(str, pos, d, empty);
        if (!p.empty() || empty)
            parts.push_back(p);
    }
    return move(parts);
}

}

}
