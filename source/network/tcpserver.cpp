/**
 * \file tcpserver.cpp
 * \brief TCP server
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

#include <utils/exceptions.h>
#include <utils/strings.h>
#include <utils/logger.h>
#include <utils/funclogger.h>
#include <utils/scopedcounter.h>
#include <network/tcpserver.h>

using namespace std;

namespace Network
{

TCPServer::TCPServer()
        : m_workers(0)
{
}

TCPServer::~TCPServer()
{
}

void TCPServer::start(int port)
{
    start(LOCALIP, port);
}

void TCPServer::start(const string &ip, int port)
{
    TCPServerSocket socket;
    socket.bind(ip, port);
    socket.listen();
    thread connector = thread(connect, this, ref<TCPServerSocket>(socket));
    thread exchanger = thread(exchange, this);
    connector.join();
    exchanger.join();
}

void TCPServer::connect(TCPServer *server, TCPServerSocket &socket)
{
    while (true)
    {
        TCPClientSocket client = move(socket.accept());
        if (client.fd() >= 0 && client.fd() < FD_SETSIZE)
        {
            unique_lock<mutex> lock(server->m_lock);
            server->m_clients.add(client);
        }
    }
}

void TCPServer::exchange(TCPServer *server)
{
    while (true)
    {
        {
            unique_lock<mutex> lock(server->m_lock);
            server->m_clients.selectReadable();
            for (list<TCPClientSocket>::iterator it = server->m_clients.begin(); it != server->m_clients.end();)
                if (server->m_clients.isSelected(*it) && server->m_workers < thread::hardware_concurrency())
                {
                    thread(worker, server, move(*it)).detach();
                    it = server->m_clients.erase(it);
                }
                else
                {
                    ++it;
                }
        }
    }
}

void TCPServer::worker(TCPServer *server, TCPClientSocket client)
{
    Utils::ScopedCounter<atomic<int> > counter(server->m_workers);
    try
    {
        LOG(Utils::Strings::format("Client %s connected", client.debugStr().c_str()));
        server->process(client);
        if (client.connected())
        {
            unique_lock<mutex> lock(server->m_lock);
            server->m_clients.add(client);
        }
        else
        {
            LOG(Utils::Strings::format("Client %s disconnected", client.debugStr().c_str()));
        }
    }
    catch (const SocketDisconnectedException &ex)
    {
        LOG(Utils::Strings::format("Client %s closed connection itself", client.debugStr().c_str()));
    }
    catch (const exception &ex)
    {
        LOG(Utils::Strings::format("Client %s error: %s", client.debugStr().c_str(), ex.what()));
    }
    catch (...)
    {
        LOG(Utils::Strings::format("Client %s unknown error!", client.debugStr().c_str()));
    }
}

}
