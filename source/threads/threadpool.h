/**
 * \file threadpool.h
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

#ifndef THREADS_THREADPOOL_H
#define THREADS_THREADPOOL_H

#include <thread>
#include <vector>
#include <queue>
#include <memory>
#include <mutex>
#include <atomic>
#include <functional>
#include <condition_variable>

namespace Threads
{

/**
 * \class ThreadPool
 * \brief Thread pool
 */
class ThreadPool
{
public:
    /**
     * Constructor
     * \param[in] workers Maximum worker count
     */
    ThreadPool(int workers);
    /**
     * Destructor
     */
    virtual ~ThreadPool();
    /**
     * Adds a new job to execution queue
     * \param[in] func Function to execute
     * \param[in] args Function arguments
     */
    template<typename Func, typename... Args> void execute(Func func, Args... args)
    {
        std::unique_lock<std::mutex> lock(m_lock);
        m_jobs.push(std::bind(func, args...));
        m_queued.notify_one();
    };
    /**
     * Returns are there any jobs in queue
     * \return Is pool busy
     */
    bool busy() const;
    /**
     * Returns jobs in queue
     * \return Jobs in queue
     */
    int jobs() const;
private:
    /**
     * Pool working loop
     */
    void loop();
    /**
     * Returns a next job in queue
     * \return Next job in queue
     */
    std::function<void()> nextjob();
    std::vector<std::unique_ptr<std::thread> > m_workers; /**< Workers */
    std::queue<std::function<void()> > m_jobs; /**< Job queue */
    mutable std::mutex m_lock; /**< Lock */
    std::condition_variable m_queued; /**< Job queued condition variable */
    std::atomic<bool> m_terminate; /**< Terminate flag */
};

}

#endif // THREADS_THREADPOOL_H
