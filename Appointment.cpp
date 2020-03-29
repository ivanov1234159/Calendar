//
// Created by toi on 29/03/2020.
//

#include "Appointment.hpp"
#include "MyFunctions.hpp"

Appointment::Appointment(): m_name(nullptr), m_note(nullptr), m_date(Date()), m_start(Time()), m_end(Time()) {}

Appointment::Appointment(char const *name, char const *note, Date const &date, Time const &start, Time const &end) {
    mem_copy(m_name, name);
    mem_copy(m_note, note);
    m_date = date;
    m_start = start;
    m_end = end;
}


char const* Appointment::getName() const { return m_name; }
char const* Appointment::getNote() const { return m_note; }
Date Appointment::getDate() const { return m_date; }
Time Appointment::getStartTime() const { return m_start; }
Time Appointment::getEndTime() const { return m_end; }