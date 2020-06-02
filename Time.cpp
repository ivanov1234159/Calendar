//
// Created by toi on 27/03/2020.
//

#include "Time.hpp"

const Time Time::MAX_TIME = Time((24 * 3600) - 1);

Time::Time(unsigned seconds, unsigned minutes, unsigned hours) {
    normalize(hours, minutes, seconds);
}

Time::Time(std::istream &in) {
    char buff;
    in >> m_hours >> buff >> m_minutes >> buff >> m_seconds;
    normalize(m_hours, m_minutes, m_seconds);
}

Time::Time(std::ifstream &ifs) {
    ifs.read((char*) &m_hours, sizeof(m_hours));
    ifs.read((char*) &m_minutes, sizeof(m_minutes));
    ifs.read((char*) &m_seconds, sizeof(m_seconds));
}

unsigned Time::getTotal() const {
    unsigned total = m_hours * 60;
    total += m_minutes;
    total *= 60;
    total += m_seconds;
    return total;
}

int Time::difference(Time const &other) const {
    int diff = (m_hours - other.m_hours) * 60;
    diff += m_minutes - other.m_minutes;
    diff *= 60;
    diff += m_seconds - other.m_seconds;
    return diff;
}

bool Time::serialize(std::ofstream &ofs) const {
    ofs.write((char const*) &m_hours, sizeof(m_hours));
    ofs.write((char const*) &m_minutes, sizeof(m_minutes));
    ofs.write((char const*) &m_seconds, sizeof(m_seconds));
    return ofs.good();
}

bool Time::operator==(Time const& other) const {
    return m_hours == other.m_hours && m_minutes == other.m_minutes && m_seconds == other.m_seconds;
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

Time const& Time::operator+=(Time const &other) {
    m_hours += other.m_hours;
    m_minutes += other.m_minutes;
    m_seconds += other.m_seconds;
    normalize(m_hours, m_minutes, m_seconds);
    return *this;
}

Time Time::operator+(Time const &other) const {
    Time temp = *this;
    return temp += other;
}

Time& Time::operator++() {
    normalize(m_hours, m_minutes, m_seconds+1);
}

Time Time::operator++(int) {
    Time temp = *this;
    ++(*this);
    return temp;
}

Time::operator int() const {
    return (int)getTotal();
}

void Time::print(std::ostream &out) const {
    out << (m_hours < 10 ? "0" : "") << m_hours
        << (m_minutes < 10 ? ":0" : ":") << m_minutes
        << (m_seconds < 10 ? ":0" : ":") << m_seconds;
}

bool Time::max() const {
    return *this == Time::MAX_TIME;
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

std::istream& operator>>(std::istream& in, Time& obj){
    char dots;
    return in >> obj.m_hours >> dots >> obj.m_minutes >> dots >> obj.m_seconds;
}