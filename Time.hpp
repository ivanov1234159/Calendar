//
// Created by toi on 27/03/2020.
//

#ifndef CALENDAR_TIME_HPP
#define CALENDAR_TIME_HPP

#include <iostream>
//for: istream, ostream
#include <fstream>
//for: ifstream, ofstream

class Time {
    unsigned m_hours;
    unsigned m_minutes;
    unsigned m_seconds;
public:
    static const Time MAX_TIME;
    Time(unsigned seconds = 0, unsigned minutes = 0, unsigned hours = 0);
    Time(std::istream& in);
    Time(std::ifstream& ifs);

    unsigned getTotal() const;

    int difference(Time const& other) const;

    bool serialize(std::ofstream& ofs) const;

    bool operator==(Time const& other) const;
    bool operator!=(Time const& other) const;
    bool operator>(Time const& other) const;
    bool operator<(Time const& other) const;
    bool operator>=(Time const& other) const;
    bool operator<=(Time const& other) const;

    Time const& operator+=(Time const& other);
    Time operator+(Time const& other) const;

    Time& operator++();
    Time operator++(int);

    operator int() const;
    void print(std::ostream& out) const;

    bool max() const;

    friend std::istream& operator>>(std::istream& in, Time& obj);
private:
    void normalize(unsigned hours, unsigned minutes, unsigned seconds);
};

std::ostream& operator<<(std::ostream& out, Time const& obj);
std::istream& operator>>(std::istream& in, Time& obj);

#endif //CALENDAR_TIME_HPP
