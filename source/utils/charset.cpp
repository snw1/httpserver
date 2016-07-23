/**
 * \file charset.cpp
 * \brief Set of characters
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

#include <string.h>
#include <utils/charset.h>

using namespace std;

namespace Utils
{

namespace Strings
{

CharSet::CharSet()
{
    memset(m_data, 0, sizeof(m_data));
}

CharSet::CharSet(char ch)
{
    memset(m_data, 0, sizeof(m_data));
    *this += ch;
}

CharSet::CharSet(const string &str)
{
    memset(m_data, 0, sizeof(m_data));
    *this += str;
}

CharSet::~CharSet()
{
}

CharSet &CharSet::operator+=(char ch)
{
    m_data[static_cast<unsigned char>(ch)] = 1;
    return *this;
}

CharSet &CharSet::operator+=(const string &str)
{
    for (char ch : str)
        *this += ch;
    return *this;
}

bool CharSet::exists(char ch) const
{
    return m_data[static_cast<unsigned char>(ch)];
}

}

}
