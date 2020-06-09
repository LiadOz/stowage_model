#pragma once

#include <thread>
#include <vector>
#include <atomic>

#include "./AlgTravelProducer.h"

using std::vector;
using std::atomic_int;
using std::atomic_bool;

class ThreadPoolExecuter {
private:
    AlgTravelProducer& producer;
    const int numThreads = -1;
    std::vector<std::thread> workers;
    std::atomic_bool running = false;
    std::atomic_bool stopped = false;
    static thread_local int num_tasks_finished;
    std::atomic_int total_num_tasks_finished { 0 };

    void worker_function();
public:
    ThreadPoolExecuter(AlgTravelProducer& producer, int numThreads)
    : producer(producer), numThreads(numThreads) {
        workers.reserve(numThreads);
    }
    bool start();
    void stop_gracefully();
    void wait_till_finish();
};
