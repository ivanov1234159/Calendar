//
// Created by toi on 27/03/2020.
//

#include "Date.hpp"

unsigned Date::getLastDay(unsigned month, unsigned year) {
    month %= 12;
    unsigned last_day = 28;
    switch (month){
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 0:
            last_day++;
        case 4: case 6: case 9: case 11:
            last_day++;
        default:
            break;
    }
    if(month == 2 && (year % 400 == 0 || year % 4 == 0)){
        last_day++;
    }
    return last_day;
}

Date::Date(): m_day(1), m_month(1), m_year(0) {}

Date::Date(unsigned day, unsigned month, unsigned year) {
    normalize(day, month, year);
}

bool Date::operator==(Date const& other) const {
    return m_year == other.m_year && m_month == other.m_month && m_day == other.m_day;
}

bool Date::operator!=(Date const& other) const {
    return !(*this == other);
}

bool Date::operator>(Date const& other) const {
    if(m_year != other.m_year){
        return m_year > other.m_year;
    }
    if(m_month != other.m_month){
        return m_month > other.m_month;
    }
    return m_day > other.m_day;
}

bool Date::operator<(Date const& other) const {
    if(m_year != other.m_year){
        return m_year < other.m_year;
    }
    if(m_month != other.m_month){
        return m_month < other.m_month;
    }
    return m_day < other.m_day;
}

bool Date::operator>=(Date const &other) const {
    return !(*this < other);
}

bool Date::operator<=(Date const &other) const {
    return !(*this > other);
}

void Date::normalize(unsigned day, unsigned month, unsigned year) {
    m_year = year;
    month %= 12;
    m_month = (month == 0) ? 12 : month;
    unsigned last_day = Date::getLastDay(m_month, m_year);
    m_day = (day % last_day);
    m_day = (m_day == 0) ? last_day : m_day;
}


std::ostream& operator<<(std::ostream& out, Date const& obj){
    return out << (obj.m_day < 10 ? "0" : "") << obj.m_day
        << (obj.m_month < 10 ? ".0" : ".") << obj.m_month
        << "." << obj.m_year;
}