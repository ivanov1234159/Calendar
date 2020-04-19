//
// Created by toi on 29/03/2020.
//

#include "Appointment.hpp"
#include "MySpace.hpp"
#include <cstring>
//for: strlen()

Appointment::Appointment(): m_name(nullptr), m_note(nullptr), m_date(Date()), m_start(Time()), m_end(Time()) {}

Appointment::Appointment(std::ifstream &ifs): m_name(nullptr), m_note(nullptr) {
    unsigned size;
    ifs.read((char*) &size, sizeof(size));
    m_name = new char[size+1];
    ifs.read((char*) &m_name, size);
    m_name[size] = '\0';

    ifs.read((char*) &size, sizeof(size));
    m_note = new char[size+1];
    ifs.read((char*) &m_note, size);
    m_note[size] = '\0';
    m_date = Date(ifs);
    m_start = Time(ifs);
    m_end = Time(ifs);
}

Appointment::Appointment(char const *name, char const *note, Date const &date, Time const &start, Time const &end) {
    MySpace::mem_copy(m_name, name);
    MySpace::mem_copy(m_note, note);
    m_date = date;
    m_start = start;
    m_end = end;
}

bool Appointment::serialize(std::ofstream &ofs) const {
    unsigned size = std::strlen(m_name);
    ofs.write((char const*) &size, sizeof(size));
    ofs.write((char const*) &m_name, sizeof(m_name));
    size = std::strlen(m_note);
    ofs.write((char const*) &size, sizeof(size));
    ofs.write((char const*) &m_note, sizeof(m_note));
    if(!ofs.good()){
        return false;
    }
    return m_date.serialize(ofs) && m_start.serialize(ofs) && m_end.serialize(ofs);
}

char const* Appointment::getName() const { return m_name; }
char const* Appointment::getNote() const { return m_note; }
Date Appointment::getDate() const { return m_date; }
Time Appointment::getStartTime() const { return m_start; }
Time Appointment::getEndTime() const { return m_end; }

std::ostream& operator<<(std::ostream& out, Appointment const& obj){
    return out << "An appointment named " << obj.getName()
    << " is on " << obj.getDate()
    << " starts at " << obj.getStartTime()
    << "  and ends at " << obj.getEndTime()
    <<  std::endl << " Notes: " << obj.getNote() << std::endl;
}