#include "../include/event.h"

Event::Event(const std::string &event_name) : _event_name(event_name) {

}

std::string Event::name() const {
    return _event_name;
}

bool Event::operator==(const Event &other) const {
    return _event_name == other._event_name;
}