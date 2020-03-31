//
// Created by toi on 27/03/2020.
//

#include "Time.hpp"

Time::Time(unsigned hours, unsigned minutes, unsigned seconds) {
    normalize(hours, minutes, seconds);
}

Time::Time(std::istream &in) {
    char buff;
    in >> m_hours >> buff >> m_minutes >> buff >> m_seconds;
    normalize(m_hours, m_minutes, m_seconds);
}

unsigned Time::getTotal() const {
    unsigned total = m_hours * 60;
    total += m_minutes;
    total *= 60;
    total += m_seconds;
    return total;
}

int Time::difference(Time const &other) const {
    return getTotal() - other.getTotal();
}

bool Time::operator==(Time const& other) const {
    return difference(other) == 0;
}

bool Time::operator!=(Time const& other) const {
    return !(*this == other);
}

bool Time::operator>(Time const& other) const {
    return difference(other) > 0;
}

bool Time::operator<(Time const& other) const {
    return difference(other) < 0;
}

bool Time::operator>=(Time const& other) const {
    return !(*this < other);
}

bool Time::operator<=(Time const& other) const {
    return !(*this > other);
}

Time::operator int() const {
    return (int)getTotal();
}

void Time::print(std::ostream &out) const {
    out << m_hours << ':' << m_minutes << ':' << m_seconds;
}

void Time::normalize(unsigned hours, unsigned minutes, unsigned seconds) {
    m_seconds = seconds % 60;
    seconds /= 60;

    m_minutes = (minutes % 60) + (seconds % 60);
    seconds /= 60;
    minutes /= 60;

    m_hours = hours + minutes + seconds;
    m_hours %= 24;
}

std::ostream& operator<<(std::ostream& out, Time const& obj){
    obj.print(out);
    return out;
}