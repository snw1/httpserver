/**
 * \file stringset.h
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

#ifndef UTILS_STRINGSET_H
#define UTILS_STRINGSET_H

#include <string>
#include <unordered_set>

namespace Utils
{

namespace Strings
{

/**
 * \class StringSet
 * \brief Set of strings
 */
class StringSet
{
public:
    /**
     * Constructor
     */
    StringSet();
    /**
     * Constructor
     * \param[in] str String
     */
    StringSet(const std::string &str);
    /**
     * Constructor
     * \param[in] strs Strings
     */
    StringSet(const std::initializer_list<std::string> &strs);
    /**
     * Destructor
     */
    virtual ~StringSet();
    /**
     * Adds a string to a set
     * \param[in] str String
     * \return This set
     */
    StringSet &operator+=(const std::string &str);
    /**
     * Adds strings to a set
     * \param[in] strs Strings
     * \return This set
     */
    StringSet &operator+=(const std::initializer_list<std::string> &strs);
    /**
     * Determines if there is a string in a set
     * \param str String
     * \return Is there a string in a set
     */
    bool exists(const std::string &str) const;
private:
    std::unordered_set<std::string> m_data; /**< Set of strings */
};

}

}

#endif // UTILS_STRINGSET_H
