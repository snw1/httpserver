#include <iostream>
#include <thread>
#include <mutex>
#include <utils/strings.h>
#include <utils/exceptions.h>
#include <utils/timer.h>
#include <network/common.h>
#include <network/tcpclientsocket.h>
#include <threads/threadpool.h>

using namespace std;

const string HOST = "127.0.0.1";
const int PORT = 7788;
const string REQUEST = "GET /.profile HTTP/1.1\r\n\r\n";
const int RESPLEN = 737;
const bool MULTITHREADED = true;
const int REQUESTS = 1000000;
const int WORKERS = thread::hardware_concurrency();

class Stats
{
public:
    Stats() : m_total(0), m_good(0)
    {
    }
    virtual ~Stats()
    {
    }
    double performance() const
    {
        lock_guard<mutex> lock(m_mutex);
        if (m_timer.dt() <= 0)
            return 0.0;
        return 1000.0 * m_good / m_timer.dt();
    }
    int good() const
    {
        lock_guard<mutex> lock(m_mutex);
        return m_good;
    }
    int total() const
    {
        lock_guard<mutex> lock(m_mutex);
        return m_total;
    }
    double quality() const
    {
        lock_guard<mutex> lock(m_mutex);
        if (m_total == 0)
            return 0.0;
        return m_good * 100.0 / m_total;
    }
    void add(bool good)
    {
        lock_guard<mutex> lock(m_mutex);
        ++m_total;
        if (good)
            ++m_good;
    }
    void reset()
    {
        lock_guard<mutex> lock(m_mutex);
        m_total = 0;
        m_good = 0;
        m_timer.reset();
    }
private:
    int m_total;
    int m_good;
    Utils::Timer m_timer;
    mutable mutex m_mutex;
};

void query(Stats &stats)
{
    string resp;
    try
    {
        Network::TCPClientSocket socket;
        socket.connect(HOST, PORT);
        socket.send(REQUEST);
        while (true)
            resp += socket.receive();
    }
    catch (const SocketDisconnectedException &ex)
    {
    }
    catch (const exception &ex)
    {
    }
    catch (...)
    {
    }
    //cout << resp.length() << endl;
    stats.add(resp.length() == RESPLEN);
}

void printstats(int count, const Stats &stats)
{
    cout << Utils::Strings::format("%d%% done, %d good of %d, performance: %0.2lf q/s, quality: %0.2lf%%", stats.total() * 100 / count, stats.good(), stats.total(), stats.performance(), stats.quality()) << endl;
}

void singlethreaded(int count)
{
    Stats stats;
    for (int i = 1; i <= count; ++i)
    {
        query(stats);
        if (i % 1000 == 0)
            printstats(count, stats);
    }
    if (count % 1000 != 0)
        printstats(count, stats);
}

void multithreaded(int count, int workers)
{
    Stats stats;
    {
        Threads::ThreadPool pool(workers);
        for (int i = 0; i < count; ++i)
            pool.execute(&query, ref<Stats>(stats));
        while (pool.busy())
        {
            printstats(count, stats);
            this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    printstats(count, stats);
}

int main()
{
    if (MULTITHREADED)
        multithreaded(REQUESTS, WORKERS);
    else
        singlethreaded(REQUESTS);
    return 0;
}
