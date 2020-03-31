//
// Created by toi on 27/03/2020.
//

#ifndef CALENDAR_DATE_HPP
#define CALENDAR_DATE_HPP

class Date {
    unsigned m_day;
    unsigned m_month;
    unsigned m_year;

    unsigned getLastDay(unsigned month, unsigned year);
public:
    Date();
    Date(unsigned day, unsigned month, unsigned year);

    bool operator==(Date const& other) const;
    bool operator!=(Date const& other) const;
    bool operator>(Date const& other) const;
    bool operator<(Date const& other) const;
    bool operator>=(Date const& other) const;
    bool operator<=(Date const& other) const;

private:
    void normalize(unsigned day, unsigned month, unsigned year);
};

#endif //CALENDAR_DATE_HPP
