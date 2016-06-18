/**
 * \file options.cpp
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

#include <options.h>
#include <unistd.h>
#include <utils/strings.h>
#include <utils/exceptions.h>

using namespace std;

Options::Options()
{
}

Options::~Options()
{
}

Options Options::parse(int argc, char *argv[])
{
    Options opt;
    string hostval;
    string portval;
    string dirval;
    bool daemon = false;
    opterr = 0;
    int c;
    while ((c = getopt(argc, argv, ":h:p:d:z")) != -1)
    {
        switch (c)
        {
            case 'h':
                hostval = optarg;
                break;
            case 'p':
                portval = optarg;
                break;
            case 'd':
                dirval = optarg;
                break;
            case 'z':
                daemon = true;
                break;
            case '?':
                if (optopt == 'h' || optopt == 'p' || optopt == 'd')
                    throw InvalidOptionsException(Utils::Strings::format("no argument for option \"%c\"", optopt));
                if (isprint(optopt))
                    throw InvalidOptionsException(Utils::Strings::format("unknown option \"%c\"", optopt));
                throw InvalidOptionsException(Utils::Strings::format("unknown option character \"\\x%x\"", optopt));
                break;
            default:
                break;
        }
    }
    if (hostval.empty())
        throw InvalidOptionsException("no host specified");
    if (portval.empty())
        throw InvalidOptionsException("no port specified");
    if (dirval.empty())
        throw InvalidOptionsException("no directory specified");
    int port = Utils::Strings::fromstring<int>(portval);
    if (port < 0 || port > 65535)
        throw InvalidOptionsException(Utils::Strings::format("invalid port %s", portval.c_str()));
    opt.m_host = hostval;
    opt.m_port = port;
    opt.m_dir = dirval;
    opt.m_daemon = daemon;
    return opt;
}

const string &Options::host() const
{
    return m_host;
}

int Options::port() const
{
    return m_port;
}

const string &Options::dir() const
{
    return m_dir;
}

bool Options::daemon() const
{
    return m_daemon;
}
