//
// Created by toi on 27/03/2020.
//

#ifndef CALENDAR_DATE_HPP
#define CALENDAR_DATE_HPP

#include <iostream>
//for: ostream
#include <fstream>
//for: ifstream, ofstream

class Date {
    unsigned m_day;
    unsigned m_month;
    unsigned m_year;

    unsigned getLastDay(unsigned month, unsigned year);
public:
    Date();
    Date(std::ifstream& ifs);
    Date(unsigned day, unsigned month, unsigned year);

    bool serialize(std::ofstream& ofs) const;

    bool operator==(Date const& other) const;
    bool operator!=(Date const& other) const;
    bool operator>(Date const& other) const;
    bool operator<(Date const& other) const;
    bool operator>=(Date const& other) const;
    bool operator<=(Date const& other) const;

    friend std::ostream& operator<<(std::ostream& out, Date const& obj);

private:
    void normalize(unsigned day, unsigned month, unsigned year);
};

std::ostream& operator<<(std::ostream& out, Date const& obj);

#endif //CALENDAR_DATE_HPP
