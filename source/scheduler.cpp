#include "../include/scheduler.h"
#include "../include/event.h"
#include <iomanip>
#include <iostream>

Scheduler::Scheduler() : _running(false) {

}

void Scheduler::start() {
    _worker = std::make_unique<std::thread>([this]() {
        _running = true;
        while (_running) {
            std::lock_guard<std::mutex> lock(_mutex);
            std::for_each(_exec_queue.begin(), _exec_queue.end(), [](Executable &exec) {
                const auto current_time = std::chrono::steady_clock::now();
                if (current_time - exec.start_measure >= exec.delay) {
                    exec.executor();
                    exec.remove_later = true;
                }
            });
            auto erase_from = std::remove_if(_exec_queue.begin(), _exec_queue.end(), [](const Executable &exec) {
                return exec.remove_later;
            });
            if (erase_from != _exec_queue.end())
                _exec_queue.erase(erase_from, _exec_queue.end());
        }
    });
}

void Scheduler::stop() {
    _running = false;
    if (_worker && _worker->joinable())
        _worker->join();
}

void Scheduler::execute(std::function<void()> &&executor, std::chrono::milliseconds &&delay) {
    execute(executor, delay);
}

void Scheduler::execute(const std::function<void()> &executor, const std::chrono::milliseconds &delay) {
    std::lock_guard<std::mutex> lock(_mutex);
    Executable exec;
    exec.executor = executor;
    exec.start_measure = std::chrono::steady_clock::now();
    exec.delay = delay;
    exec.remove_later = false;

    _exec_queue.emplace_back(std::move(exec));
}

Scheduler::~Scheduler() {
    stop();
}