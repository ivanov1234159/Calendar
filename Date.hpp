//
// Created by toi on 27/03/2020.
//

#ifndef CALENDAR_DATE_HPP
#define CALENDAR_DATE_HPP

#include <iostream>
//for: ostream, istream
#include <fstream>
//for: ifstream, ofstream
#include "String.hpp"

class Date {
    unsigned m_day;
    unsigned m_month;
    unsigned m_year;

    /**
     * calculate the last day of the month
     * @param month
     * @param year
     * @return the last day
     */
    static unsigned getLastDay(unsigned month, unsigned year);
public:
    Date();
    Date(std::ifstream& ifs);
    Date(unsigned day, unsigned month, unsigned year);

    /**
     * serialize this object
     * @param ofs
     * @return false on fail
     */
    bool serialize(std::ofstream& ofs) const;

    bool operator==(Date const& other) const;
    bool operator!=(Date const& other) const;
    bool operator>(Date const& other) const;
    bool operator<(Date const& other) const;
    bool operator>=(Date const& other) const;
    bool operator<=(Date const& other) const;

    Date& operator++();
    Date operator++(int);

    /// @return this object as string (format: YYYY-MM-DD)
    String to_string() const;

    friend std::istream& operator>>(std::istream& in, Date& obj);

private:
    /**
     * set m_day, m_month and m_year but valid
     * @param day
     * @param month
     * @param year
     */
    void normalize(unsigned day, unsigned month, unsigned year);
};

std::ostream& operator<<(std::ostream& out, Date const& obj);
std::istream& operator>>(std::istream& in, Date& obj);

#endif //CALENDAR_DATE_HPP
