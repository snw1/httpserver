/**
 * \file threadpool.cpp
 * \brief Thread pool
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

#include <threads/threadpool.h>

using namespace std;

namespace Threads
{

class Terminated
{
};

ThreadPool::ThreadPool(int workers)
        : m_workers(workers),
          m_terminate(false)
{
    for (unique_ptr<thread> &worker : m_workers)
        worker.reset(new thread(&ThreadPool::loop, this));
}

ThreadPool::~ThreadPool()
{
    {
        unique_lock<mutex> lock(m_lock);
        m_terminate = true;
        m_queued.notify_all();
    }
    for (unique_ptr<thread> &worker : m_workers)
        worker->join();
}

bool ThreadPool::busy() const
{
    unique_lock<mutex> lock(m_lock);
    return !m_jobs.empty();
}

int ThreadPool::jobs() const
{
    unique_lock<mutex> lock(m_lock);
    return m_jobs.size();
}

function<void()> ThreadPool::nextjob()
{
    unique_lock<mutex> lock(m_lock);
    while (!m_terminate)
    {
        if (!m_jobs.empty())
        {
            function<void()> job = m_jobs.front();
            m_jobs.pop();
            return job;
        }
        m_queued.wait(lock);
    }
    throw Terminated();
}

void ThreadPool::loop()
{
    try
    {
        for (; ;)
        {
            function<void()> job = nextjob();
            job();
        }
    }
    catch (const Terminated &ex)
    {
    }
}

}
