#pragma once

#include <thread>
#include <vector>
#include <functional>
#include <atomic>

#include "./AlgTravelProducer.h"
#include "./SimulationManager.h"

using std::vector;
using std::atomic_int;
using std::atomic_bool;

// executes algorithm travel pair using a mehtod given in the constructor
class ThreadPoolExecuter {
private:
    AlgTravelProducer& producer;
    const int numThreads = -1;
    std::vector<std::thread> workers;
    std::atomic_bool running = false;
    std::atomic_bool stopped = false;
    static thread_local int num_tasks_finished;
    std::atomic_int total_num_tasks_finished { 0 };
    std::function<void(int, string)> func;

    void worker_function();
public:
    ThreadPoolExecuter(AlgTravelProducer& producer, int numThreads,
            std::function<void(int, string)> func)
    : producer(producer), numThreads(numThreads), func(func){
        workers.reserve(numThreads);
    }
    bool start();
    void stop_gracefully();
    void wait_till_finish();
};
