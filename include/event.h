#pragma once

#include <vector>
#include <functional>
#include <algorithm>


class Event {
public:
    explicit Event(const std::string& event_name);
    std::string name() const;
    bool operator==(const Event& other) const;
private:
    std::string _event_name;
};
