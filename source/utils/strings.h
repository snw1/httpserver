/**
 * \file strings.h
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

#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H

#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <cstdio>
#include <cstdarg>
#include <string.h>

namespace Utils
{

namespace Strings
{

/**
 * Converts anything to a string
 * \param[in] t Anything :)
 * \return String
 */
template<typename T> inline std::string tostring(T t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}
/**
 * Converts a string to anything
 * \param[in] s String
 * \return Anything :)
 */
template<typename T> inline T fromstring(const std::string &s)
{
    std::stringstream ss(s);
    T t;
    ss >> t;
    return t;
}
/**
 * Determines if a string begins with a substring
 * \param[in] str String
 * \param[in] sstr Substring
 * \return Is begins
 */
bool begins(const std::string &str, const std::string &sstr);
/**
 * Determines if a string ends with a substring
 * \param[in] str String
 * \param[in] sstr Substring
 * \return Is ends
 */
bool ends(const std::string &str, const std::string &sstr);
/**
 * Returns a formatted string
 * \param[in] str Format
 * \param[in] ... Parameters
 * \return Formatted string
 */
std::string format(const char *fmt, ...);
/**
 * Returns a hex representation of a string
 * \param[in] str String
 * \param[in] delim Delimiter between two character's hex values
 * \param[in] upper Use capital hex letters
 * \return Hex representation
 */
std::string hex(const std::string &str, const std::string &delim = " ", bool upper = false);
/**
 * Returns a string representation of a hex
 * \param[in] str Hex
 * \param[in] delim Delimiter characters
 * \return String representation
 */
std::string unhex(std::string str, const std::string &delim = " ");
/**
 * Returns a part of a string
 * \param[in] str String
 * \param[in] pos Part begin position
 * \param[in] delim Delimiter characters
 * \param[in] empty Empty parts allowed
 * \return Part of a string
 */
std::string part(const std::string &str, int pos = 0, const std::string &delim = " ", bool empty = false);
/**
 * Splits a string
 * \param[in] str String
 * \param[in] delim Delimiter characters
 * \param[in] empty Empty parts allowed
 * \return Parts of a string
 */
std::vector<std::string> split(const std::string &str, const std::string &delim = " ", bool empty = false);

}

}

#endif // UTILS_STRINGS_H
