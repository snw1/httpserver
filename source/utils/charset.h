/**
 * \file charset.h
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

#ifndef UTILS_CHARSET_H
#define UTILS_CHARSET_H

#include <string>
#include <array>

namespace Utils
{

namespace Strings
{

/**
 * \class CharSet
 * \brief Set of characters
 */
class CharSet
{
public:
    /**
     * Constructor
     */
    CharSet();
    /**
     * Constructor
     * \param[in] ch Character
     */
    CharSet(char ch);
    /**
     * Constructor
     * \param[in] str String
     */
    CharSet(const std::string &str);
    /**
     * Destructor
     */
    virtual ~CharSet();
    /**
     * Adds a character to set
     * \param[in] ch Character
     * \return This set
     */
    CharSet &operator+=(char ch);
    /**
     * Adds a string characters to set
     * \param[in] ch String
     * \return This set
     */
    CharSet &operator+=(const std::string &str);
    /**
     * Determines if character is in set
     * \param[in] ch Character
     * \return Is character in set
     */
    bool exists(char ch) const;
private:
    unsigned char m_data[256]; /**< Set data */
};

}

}

#endif // UTILS_CHARSET_H
