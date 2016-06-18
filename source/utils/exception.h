/**
 * \file exception.h
 * \brief Custom exception
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

#ifndef UTILS_EXCEPTION_H
#define UTILS_EXCEPTION_H

#include <exception>
#include <string>

#define DEFINE_EXCEPTION(Type, Parent) class Type : public Parent \
{ \
public: \
    Type(const std::string &message) : Parent(message) {} \
}

namespace Utils
{

/**
 * class Exception
 * \brief Custom exception
 */
class Exception : public std::exception
{
public:
    /**
     * Constructor
     * \param[in] msg Error message
     */
    Exception(const std::string &msg);
    /**
     * Destructor
     */
    virtual ~Exception() noexcept;
    /**
     * Returns a error message
     * \return Error message
     */
    virtual const char *what() const noexcept;
protected:
    std::string m_msg; /**< Error message */
};

}

#endif // UTILS_EXCEPTION_H
