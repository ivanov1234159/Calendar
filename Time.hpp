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

    /// @return time in seconds
    unsigned getTotal() const;

    /**
     * calculate difference between this and other
     * @param other
     * @return (total of this) - (total of other)
     */
    int difference(Time const& other) const;

    /**
     * serialize this object
     * @param ofs
     * @return false on fail
     */
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

    /**
     * print time in format: hh:mm:ss
     * @param out - a source to print
     */
    void print(std::ostream& out) const;

    /// @return true if this is equal to MAX_TIME
    bool max() const;

    friend std::istream& operator>>(std::istream& in, Time& obj);
private:
    /**
     * set m_seconds, m_minutes and m_hours
     * @param hours - can overload (24 hours = 0 hours)
     * @param minutes - can be added to hours (60 min = 1 hour)
     * @param seconds - can be added to minutes (60 sec = 1 min)
     */
    void normalize(unsigned hours, unsigned minutes, unsigned seconds);
};

std::ostream& operator<<(std::ostream& out, Time const& obj);
std::istream& operator>>(std::istream& in, Time& obj);

#endif //CALENDAR_TIME_HPP
