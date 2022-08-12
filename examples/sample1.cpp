#include "event_loop.h"
#include <iostream>

void foo() {
    std::cout << "Call foo handler" << std::endl;
}

void bar() {
    std::cout << "Call bar handler" << std::endl;
}

void bar1() {
    std::cout << "Call second bar handler" << std::endl;
}

void too() {
    std::cout << "Call too handler" << std::endl;
}

int main(int argc, char *argv[]) {
    EventLoop loop;
    Event foo_event("foo_event");
    Event bar_event("bar_event");
    Event too_event("too_event");

    loop.register_event(foo_event, {foo});
    loop.register_event(bar_event, {bar, bar1});
    loop.register_event(too_event, {too});

    loop.start();
    std::thread first_notifier([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        loop.notifyEvent(foo_event);
        loop.notifyEvent(too_event);
        loop.notifyEvent(bar_event);
    });
    std::thread second_notifier([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        loop.notifyEvent(foo_event);
        loop.notifyEvent(foo_event);
        loop.notifyEvent(bar_event);
        loop.notifyEvent(too_event);
    });

    std::thread third_notifier([&]() {
        loop.notifyEvent(foo_event);
        loop.notifyEvent(bar_event);
        loop.notifyEvent(too_event);
    });


    first_notifier.join();
    second_notifier.join();
    third_notifier.join();
    return 0;
}