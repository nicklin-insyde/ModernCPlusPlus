#ifndef SYNC_QUEUE_H
#define SYNC_QUEUE_H

#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
using namespace std;

#define MAX_QUEUE_LENGTH 32
//#define MAX_DATA_LENGTH MAX_QUEUE_LENGTH-1

class CPU
{
public:
    CPU(const int id);
    ~CPU();
    void do_something(int arg);
    int print(void);
    static int _cpu_count;
private:
    int _id = 0;
};

class sync_queue
{
public:
    sync_queue();
    ~sync_queue();

    void put(int value);
    void terminate(void);
    void runThread(int idx);

private:
    int _queue[MAX_QUEUE_LENGTH];
    int _sp = 0;
    int _ep = 0;
    bool _terminate_flag = false;
    vector<std::unique_ptr<CPU>> _cpu_info;
    vector<std::unique_ptr<CPU>> _cpu_info1;

    void _event_center(int idx);
    void _data_center(int idx);
    void _delay(int delay);
    void _is_queue_full(void);
    inline bool _is_queue_empty(void);

    mutex _mtx;
    mutex _data_mtx;
    condition_variable _data_cond;
    condition_variable _cond;
    vector<thread> _t;
};

#endif
