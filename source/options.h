/**
 * \file options.h
 * \brief Options
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

#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

/**
 * \class Options
 * \brief Options
 */
class Options
{
public:
    /**
     * Constructor
     */
    Options();
    /**
     * Destructor
     */
    virtual ~Options();
    /**
     * Parses command line arguments
     * \param argc Argument count
     * \param argv Arguments
     * \return Options
     */
    static Options parse(int argc, char *argv[]);
    /**
     * Returns host
     * \return Host
     */
    const std::string &host() const;
    /**
     * Returns port
     * \return Port
     */
    int port() const;
    /**
     * Returns directory
     * \return Directory
     */
    const std::string &dir() const;
    /**
     * Returns daemonize flag
     * \return Daemonize flag
     */
    bool daemon() const;
private:
    std::string m_host; /**< Host */
    int m_port; /**< Port */
    std::string m_dir; /**< Directory */
    bool m_daemon; /**< Daemonize flag */
};

#endif // OPTIONS_H
