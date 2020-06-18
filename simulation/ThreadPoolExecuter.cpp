#include "ThreadPoolExecuter.h"

void ThreadPoolExecuter::worker_function() {
    while(!stopped) {
        auto task = producer.getTask();
        if(!task) break;
        //(*task)();
        auto p = task.value();
        func(p.first, p.second);
        ++num_tasks_finished;
        ++total_num_tasks_finished;
    }
    if(stopped) {
        //std::cout << std::this_thread::get_id() << " - stopped gracefully after processing " << num_tasks_finished << " task(s)" << std::endl;
    }
    else {
        //std::cout << std::this_thread::get_id() << " - finished after processing " << num_tasks_finished << " task(s)" << std::endl;
    }
}
bool ThreadPoolExecuter::start() {
    bool running_status = false;
    // see: https://en.cppreference.com/w/cpp/atomic/atomic/compare_exchange
    if(!running.compare_exchange_strong(running_status, true)) {
        return false;
    }
    for(int i=0; i<numThreads; ++i) {
        workers.push_back(std::thread([this]{
            worker_function();
        }));
    }
    return true;
}
void ThreadPoolExecuter::stop_gracefully() {
    stopped = true;
    wait_till_finish();
}
void ThreadPoolExecuter::wait_till_finish() {
    for(auto& t : workers) {
        t.join();
    }
    //std::cout << "thread pool finished/stopped after processing " << total_num_tasks_finished << " task(s)" << std::endl;
}

thread_local int ThreadPoolExecuter::num_tasks_finished { 0 };
