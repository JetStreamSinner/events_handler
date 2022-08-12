#include "../include/event_loop.h"

EventLoop::EventLoop() : _scheduler(std::make_unique<Scheduler>()) {
}

void EventLoop::register_event(const Event &event, const std::vector<EventHandler> &handlers) {
    EventInfo register_info(event, handlers);
    _events_repository.emplace_back(std::move(register_info));
}

void EventLoop::remove_event(const Event &event) {
    auto event_to_erase = std::remove_if(_events_repository.begin(), _events_repository.end(), [&event](const EventInfo &info) {
        return info.event == event;
    });
    if (event_to_erase != _events_repository.end())
        _events_repository.erase(event_to_erase);
}

void EventLoop::start() {
    if (!_scheduler)
        throw std::runtime_error("Scheduler is`nt initialized");
    _scheduler->start();
}

void EventLoop::stop() {
    if (!_scheduler)
        throw std::runtime_error("Scheduler is`nt initialized");
    _scheduler->stop();
}

void EventLoop::notifyEvent(const Event &event) const {
    auto invoke_event = std::find_if(_events_repository.begin(), _events_repository.end(), [&](const EventInfo &info) {
        return info.event == event;
    });

    if (invoke_event == _events_repository.end())
        throw std::runtime_error("Unknown event");

    const auto &handlers = invoke_event->handlers;
    std::for_each(handlers.begin(), handlers.end(), [this](const auto &handler) {
        const auto exec_without_delay = std::chrono::milliseconds(0);
        _scheduler->execute(handler, exec_without_delay);
    });
}