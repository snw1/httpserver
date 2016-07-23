/**
 * \file main.cpp
 * \brief Main source
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

#include <iostream>
#include <options.h>
#include <utils/exceptions.h>
#include <utils/strings.h>
#include <utils/logger.h>
#include <network/common.h>
#include <network/tcpclientsocket.h>
#include <network/tcpserver.h>
#include <network/httpserver.h>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__unix__) || defined(__MACH__)
    #include <unistd.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
#else
    #error Unsupported platform!
#endif

using namespace std;

enum ReturnCode
{
    ReturnCodeOK = 0, ReturnCodeError = 1, ReturnCodeInfo = 2
};

int startServer(const Options &opt);

#if defined(__unix__) || defined(__MACH__)

void sighandler(int signum)
{
    switch (signum)
    {
        case SIGCHLD:
            waitpid(0, 0, WNOHANG);
            break;
    }
}

void daemonize()
{
    setsid();
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &sighandler;
    sigaction(SIGCHLD, &sa, 0);
    signal(SIGHUP, SIG_IGN);
    chdir("/");
    umask(0);
    for (int i = getdtablesize(); i >= 0; --i)
        close(i);
}

int startDaemon(const Options &opt)
{
    int pid = fork();
    switch (pid)
    {
        case 0:
            daemonize();
            return startServer(opt);
        case -1:
            cout << Utils::Strings::format("Error creating daemon: %s (%d)", strerror(errno), errno) << endl;
            return ReturnCodeError;
        default:
            cout << Utils::Strings::format("Server successfully started, pid = %d", pid) << endl;
            break;
    }
    return ReturnCodeOK;
}

#endif

int startServer(const Options &opt)
{
    try
    {
        Network::HTTPServer server;
        server.start(Network::host2ip(opt.host()), opt.port(), opt.dir());
    }
    catch (const exception &ex)
    {
        LOG(Utils::Strings::format("Error: %s", ex.what()));
        return ReturnCodeError;
    }
    catch (...)
    {
        LOG("Unknown error!");
        return ReturnCodeError;
    }
    return ReturnCodeOK;
}

int getOptions(int argc, char *argv[], Options &opt)
{
    if (argc <= 1)
    {
        cout << "HTTPServer v0.0, a simple Linux/Windows/MacOS HTTP server" << endl;
        cout << "Andrew Sheetov <andrew.sheetov@gmail.com> 2014" << endl;
        cout << "Licensed under the GPL <http://www.gnu.org/licenses/gpl.txt>" << endl;
        cout << endl;
        cout << Utils::Strings::format("Usage: %s -h <ip> -p <port> -d <directory> [-z]", argv[0]) << endl;
        cout << "-h <ip> server ip address" << endl;
        cout << "-p <port> server port number" << endl;
        cout << "-d <directory> server home directory" << endl;
        cout << "[-z] run server as daemon (doesn't work on Windows)" << endl;
        cout << endl;
        return ReturnCodeInfo;
    }
    try
    {
        opt = Options::parse(argc, argv);
    }
    catch (const InvalidOptionsException &ex)
    {
        cout << Utils::Strings::format("Invalid options: %s", ex.what()) << endl;
        return ReturnCodeError;
    }
    return ReturnCodeOK;
}

int main(int argc, char *argv[])
{
    Options opt;
    int res = getOptions(argc, argv, opt);
    if (res != ReturnCodeOK)
        return res;
#if defined(__unix__) || defined(__MACH__)
    if (opt.daemon())
        return startDaemon(opt);
#endif
    return startServer(opt);
}
