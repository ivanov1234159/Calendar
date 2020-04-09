//
// Created by toi on 29/03/2020.
//

#ifndef CALENDAR_APPOINTMENT_HPP
#define CALENDAR_APPOINTMENT_HPP

#include <iostream>
//for: ostream, endl
#include <fstream>
//for: ifstream, ofstream
#include "Date.hpp"
#include "Time.hpp"

class Appointment {
    char* m_name;
    char* m_note;
    Date m_date;
    Time m_start;
    Time m_end;
public:
    Appointment();
    Appointment(std::ifstream& ifs);
    Appointment(char const* name, char const* note, Date const& date, Time const& start, Time const& end);

    bool serialize(std::ofstream& ofs) const;

    char const* getName() const;
    char const* getNote() const;
    Date getDate() const;
    Time getStartTime() const;
    Time getEndTime() const;
};

std::ostream& operator<<(std::ostream& out, Appointment const& obj);

#endif //CALENDAR_APPOINTMENT_HPP
