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
#include "String.hpp"

class Appointment {
    String m_name;
    String m_note;
    Date m_date;
    Time m_start;
    Time m_end;
public:
    Appointment() = default;
    Appointment(std::ifstream& ifs);
    Appointment(String const& name, String const& note, Date const& date, Time const& start, Time const& end);

    bool serialize(std::ofstream& ofs) const;

    String const& getName() const;
    String const& getNote() const;
    Date getDate() const;
    Time getStartTime(int diff_seconds = 0) const;
    Time getEndTime(int diff_seconds = 0) const;

    void setName(String const& name);
    void setNote(String const& note);
    void setDate(Date const& date);
    void setStartTime(Time const& start);
    void setEndTime(Time const& end);
};

std::ostream& operator<<(std::ostream& out, Appointment const& obj);

#endif //CALENDAR_APPOINTMENT_HPP
