/**
 * \file datetime.cpp
 * \brief Date and time utilities
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

#include <chrono>
#include <utils/datetime.h>
#include <utils/strings.h>

using namespace std;

namespace Utils
{

string now()
{
    chrono::system_clock::time_point tp = chrono::system_clock::now();
    time_t tt = chrono::system_clock::to_time_t(tp);
    struct tm *t = localtime(&tt);
    return Utils::Strings::format("%02d.%02d.%04d %02d:%02d:%02d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, t->tm_hour, t->tm_min, t->tm_sec);
}

}
