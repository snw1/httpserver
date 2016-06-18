/**
 * \file timer.h
 * \brief Timer
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

#ifndef UTILS_TIMER_H
#define UTILS_TIMER_H

#include <chrono>

namespace Utils
{

/**
 * \class Timer
 * \brief Timer
 */
class Timer
{
public:
    /**
     * Constructor
     */
    Timer();
    /**
     * Destructor
     */
    virtual ~Timer();
    /**
     * Resets a timer
     */
    void reset();
    /**
     * Returns elapsed time from timer creation or last reset
     * \return Elapsed time in milliseconds
     */
    long long dt() const;
private:
    std::chrono::time_point<std::chrono::system_clock> m_t0; /**< Set of strings */
};

}

#endif // UTILS_TIMER_H
