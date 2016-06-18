/**
 * \file stringset.cpp
 * \brief Set of strings
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

#include <utils/stringset.h>

using namespace std;

namespace Utils
{

namespace Strings
{

StringSet::StringSet()
{
}

StringSet::StringSet(const string &str)
{
    *this += str;
}

StringSet::StringSet(const initializer_list<string> &strs)
{
    *this += strs;
}

StringSet::~StringSet()
{
}

StringSet &StringSet::operator+=(const string &str)
{
    m_data.insert(str);
}

StringSet &StringSet::operator+=(const initializer_list<string> &strs)
{
    for (const string &str : strs)
        *this += str;
}

bool StringSet::exists(const string &str) const
{
    return m_data.find(str) != m_data.end();
}


}

}
