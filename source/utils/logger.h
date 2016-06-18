/**
 * \file logger.h
 * \brief Logger
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

#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <fstream>
#include <string>
#include <thread>
#include <mutex>

#ifdef LOGGING
#define LOG(x) Utils::Logger::instance() << (x)
#else
#define LOG(x)
#endif

namespace Utils
{

/**
 * \class Logger
 * \brief Logger
 */
class Logger
{
public:
    /**
     * Copy constructor
     * \param rhs Source
     * \warning Deleted!
     */
    Logger(const Logger &rhs) = delete;
    /**
     * Copy assignment
     * \param rhs Source
     * \return This logger
     * \warning Deleted!
     */
    Logger &operator=(const Logger &rhs) = delete;
    /**
     * Returns a logger instance
     * \return Logger instance
     */
    static Logger &instance();
    /**
     * Logs a string message
     * \param msg String message
     * \return This logger
     */
    Logger &operator<<(const std::string &msg);
private:
    /**
     * Constructor
     */
    Logger();
    /**
     * Destructor
     */
    virtual ~Logger();
    std::ofstream m_os; /**< Output stream */
    std::mutex m_mutex; /**< Lock */
};

}

#endif // UTILS_LOGGER_H
