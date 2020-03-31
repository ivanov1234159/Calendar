//
// Created by toi on 27/03/2020.
//

#ifndef CALENDAR_TIME_HPP
#define CALENDAR_TIME_HPP

#include <iostream>
//for: istream, ostream

class Time {
    unsigned m_hours;
    unsigned m_minutes;
    unsigned m_seconds;
public:
    Time(unsigned hours = 0, unsigned minutes = 0, unsigned seconds = 0);
    Time(std::istream& in);

    unsigned getTotal() const;

    int difference(Time const& other) const;

    bool operator==(Time const& other) const;
    bool operator!=(Time const& other) const;
    bool operator>(Time const& other) const;
    bool operator<(Time const& other) const;
    bool operator>=(Time const& other) const;
    bool operator<=(Time const& other) const;

    operator int() const;
    void print(std::ostream& out) const;

private:
    void normalize(unsigned hours, unsigned minutes, unsigned seconds);
};

std::ostream& operator<<(std::ostream& out, Time const& obj);

#endif //CALENDAR_TIME_HPP
