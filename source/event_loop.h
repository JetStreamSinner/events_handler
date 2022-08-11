#pragma once

#include "event.h"
#include "scheduler.h"
#include <memory>
class Event;

class EventLoop {
public:
    using EventHandler = std::function<void()>;

    EventLoop();

    EventLoop(const EventLoop &other) = delete;
    EventLoop &operator=(const EventLoop &other) = delete;
    EventLoop(const EventLoop &&other) = delete;
    EventLoop &operator=(const EventLoop &&other) = delete;

    void register_event(const Event &event, const std::vector<EventHandler> &handlers);
    void remove_event(const Event &event);

    void start();
    void stop();

    void notifyEvent(const Event& event) const;

private:
    struct EventInfo {
        Event event;
        std::vector<EventHandler> handlers;
        template<typename Handlers>
        explicit EventInfo(const Event &event, Handlers &&handlers) : event(event), handlers(handlers) {
        }
    };
    std::unique_ptr<Scheduler> _scheduler;
    std::vector<EventInfo> _events_repository;
};