/**
 * \file funclogger.h
 * \brief Function logger
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

#ifndef UTILS_FUNCLOGGER_H
#define UTILS_FUNCLOGGER_H

#include <string>

#define FUNCLOG() Utils::FuncLogger(__PRETTY_FUNCTION__)

namespace Utils
{

/**
 * \class FuncLogger
 * \brief Function logger
 */
class FuncLogger
{
public:
    /**
     * Constructor
     * \param[in] name Function name
     */
    FuncLogger(const std::string &name);
    /**
     * Destructor
     */
    virtual ~FuncLogger();
private:
    std::string m_name; /**< Function name */
};

}

#endif // UTILS_FUNCLOGGER_H
