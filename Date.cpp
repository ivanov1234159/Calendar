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

Date::Date(std::ifstream &ifs) {
    ifs.read((char*) &m_year, sizeof(m_year));
    ifs.read((char*) &m_month, sizeof(m_month));
    ifs.read((char*) &m_day, sizeof(m_day));
}

Date::Date(unsigned day, unsigned month, unsigned year) {
    normalize(day, month, year);
}

bool Date::serialize(std::ofstream &ofs) const {
    ofs.write((char const*) &m_year, sizeof(m_year));
    ofs.write((char const*) &m_month, sizeof(m_month));
    ofs.write((char const*) &m_day, sizeof(m_day));
    return ofs.good();
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

String Date::to_string() const {
    String result;
    if(m_year < 1000)   { result.push('0'); }
    if(m_year < 100)    { result.push('0'); }
    if(m_year < 10)     { result.push('0'); }
    result += String::to_string(m_year);
    result.push('-');
    if(m_month < 10)    { result.push('0'); }
    result += String::to_string(m_month);
    result.push('-');
    if(m_day < 10)    { result.push('0'); }
    result += String::to_string(m_day);
    return result;
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
    return out << obj.to_string();
}

std::istream& operator>>(std::istream& in, Date& obj){
    char dash;
    return in >> obj.m_year >> dash >> obj.m_month >> dash >> obj.m_day;
}