#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
class Event;

class Scheduler {
public:
    explicit Scheduler();

    Scheduler(const Scheduler &other) = delete;
    Scheduler &operator=(const Scheduler &other) = delete;
    Scheduler(const Scheduler &&other) = delete;
    Scheduler &operator=(const Scheduler &&other) = delete;

    void start();
    void stop();

    void execute(std::function<void()> &&executor, std::chrono::milliseconds &&delay);
    void execute(const std::function<void()> &executor, const std::chrono::milliseconds &delay);

    ~Scheduler();
private:
    std::mutex _mutex;
    std::unique_ptr<std::thread> _worker;
    bool _running;

    struct Executable {
        std::function<void()> executor;
        std::chrono::time_point<std::chrono::steady_clock> start_measure;
        std::chrono::milliseconds delay;
        bool remove_later;
    };
    std::vector<Executable> _exec_queue;
};