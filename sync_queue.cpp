#include <iostream>
//#include <cstdio>
#include <chrono>
#include "sync_queue.h"
#include "tree.h"

//using namespace std;
using namespace std::chrono;

int CPU::_cpu_count = 0;
CPU::CPU(const int id) : _id(id)
{
    _cpu_count++;
    cout << "CPU #" << _id << " is created, _cpu_count[" << _cpu_count << "]"<< endl;
}

CPU::~CPU()
{
    _cpu_count--;
    cout << "CPU #" << _id << " is deleted, _cpu_count[" << _cpu_count << "]"<< endl;
}

int CPU::print(void)
{
    return _id;
}

void CPU::do_something(int arg)
{
    cout << "CPU #" << _id << " is doing something. arg=[" << arg << "] "<< endl;
}

sync_queue::sync_queue()
{
    cout << "sync_queue() created..." << endl;
    for (int i = 0; i < 32; i++)
        _queue[i] = 0;
}

sync_queue::~sync_queue()
{
    cout << "sync_queue() destroyed..." << endl;
}

void sync_queue::runThread(int idx)
{
    int i = 0;
    for(i=0; i<8; i++) {
        _cpu_info.push_back(std::make_unique<CPU>(i));
    }
    cout << "Die..." << endl;
    for (auto &cpu: _cpu_info1) {
        cout << "Hello id = " << cpu->print() << endl;
    }
    cout << "Nothing..." << endl;
    _t.emplace_back(&sync_queue::_event_center, this, idx);
    _t.emplace_back(&sync_queue::_data_center, this, idx);
}

void sync_queue::put(int value)
{
    cout << "put" << endl;
}

void sync_queue::terminate(void)
{
    unique_lock<mutex> lk(_mtx, defer_lock);
    lk.lock();
    cout << "terminate _event_center() & _data_center()" << endl;
    _terminate_flag = true;
    lk.unlock();

    for (auto& t : _t) {
        if (t.joinable()) {
            cout << "t.join()..." << endl;
            t.join();
        } else {
            cout << "t.detach()..." << endl;
            t.detach();
        }
    }
}

void sync_queue::_delay(int delay)
{
    condition_variable timer;
    mutex mtx;
    auto t0 = std::chrono::steady_clock::now();
    unique_lock<mutex> lck(mtx);
    timer.wait_for(lck, std::chrono::seconds{delay});
    auto t1 = std::chrono::steady_clock::now();
    cout << "wait " << std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count() << " second" << endl;
}

void sync_queue::_data_center(int idx)
{
//#define _DATA_CENTER_DEBUG
    bool ret = false;
    unique_lock<mutex> lk(_mtx, defer_lock);
    unique_lock<mutex> data_lk(_data_mtx, defer_lock);
    cout << "[_data_center] arg = " << idx << endl;
    while (1)
    {
        //
        // check whether queue is empty?
        //
        data_lk.lock();
        if (!_is_queue_empty()) {
            //
            // process data & update _ep to the next one
            //
            cout << "[_data_center]  <-- get _queue[" << _ep << "] = " << _queue[_ep] << endl;
            _ep = (_ep+1)%MAX_QUEUE_LENGTH;
        }
        data_lk.unlock();
        //
        // check whether this thread is terminated?
        //
        auto now = steady_clock::now();
        auto wait_t = seconds(1);
        lk.lock();
        ret = _cond.wait_until(lk, now + wait_t,
                             [&]{return _terminate_flag == true;});
        lk.unlock();
#ifdef _DATA_CENTER_DEBUG
        auto after = steady_clock::now();
        cout << "[_data_center] wait "
             << duration_cast<seconds>(after - now).count() << " second" << endl;
#endif
        if (ret == true) {
            //
            // this thread is terminated.
            // - Bye bye, cruel world!
            //
            break;
        }
    }
    cout << "[_data_center] bye bye" << endl;
}

void sync_queue::_is_queue_full(void)
{
    while (1) {
        if (_ep != (_sp ^ (MAX_QUEUE_LENGTH-1))) {
            //
            // queue is not full
            //
            break;
        }
        //
        // queue is full
        // - take a break, and try again
        //
        this_thread::sleep_for(milliseconds(100));
    }
}

inline bool sync_queue::_is_queue_empty(void)
{
    return _ep == _sp;
}

void sync_queue::_event_center(int idx)
{
//#define _EVENT_CENTER_DEBUG
    bool ret = false;
    int val = 0;
    unique_lock<mutex> lk(_mtx, defer_lock);
    unique_lock<mutex> data_lk(_data_mtx, defer_lock);
    cout << "[_event_center] arg = "<< idx << endl;
    while (1)
    {
        for (const auto &cpu : _cpu_info) {
            val++;
            cpu->do_something(val);
        }
        //
        // put memory error data to _data_center
        //
        if ((val%3) == 0) {
            while (1) {
                data_lk.lock();
                if (_ep == (_sp ^ (MAX_QUEUE_LENGTH-1))) {
                    //
                    // queue is full
                    // - take a break, and try again
                    //
                    data_lk.unlock();
                    this_thread::sleep_for(milliseconds(100));
                    continue;
                 }
                 //
                 // queue is not full
                 //
                 _queue[_sp] = val;
                 cout << "[_event_center] --> put "
                      << "_queue[" << _sp << "] = " << _queue[_sp] << endl;
                 _sp = (_sp+1)%MAX_QUEUE_LENGTH;
                 data_lk.unlock();
                break;
            }
        }
        //
        // check whether this thread is terminated?
        //
        auto now = steady_clock::now();
        auto wait_t = seconds(1);
        lk.lock();
        ret = _cond.wait_until(lk, now + wait_t,
                             [&]{return _terminate_flag == true;});
        lk.unlock();
#ifdef _EVENT_CENTER_DEBUG
        auto after = steady_clock::now();
        cout << "[data_center] wait "
             << duration_cast<seconds>(after - now).count() << " second" << endl;
#endif
        if (ret == true) {
            //
            // this thread is terminated.
            // - Bye bye, cruel world!
            //
            break;
        }
    }
    cout << "[_event_center] bye bye" << endl;
}

