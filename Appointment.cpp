//
// Created by toi on 29/03/2020.
//

#include "Appointment.hpp"
#include "MySpace.hpp"

Appointment::Appointment(std::ifstream &ifs) {
    m_name.unserialize(ifs);
    m_note.unserialize(ifs);
    m_date = Date(ifs);
    m_start = Time(ifs);
    m_end = Time(ifs);
}

Appointment::Appointment(String const& name, String const& note, Date const &date, Time const &start, Time const &end){
    m_name = name;
    m_note = note;
    m_date = date;
    m_start = start;
    m_end = end;
}

bool Appointment::serialize(std::ofstream &ofs) const {
    return m_name.serialize(ofs) && m_note.serialize(ofs) && m_date.serialize(ofs)
        && m_start.serialize(ofs) && m_end.serialize(ofs);
}

String const& Appointment::getName() const  { return m_name;    }
String const& Appointment::getNote() const  { return m_note;    }
Date Appointment::getDate() const           { return m_date;    }
Time Appointment::getStartTime(int diff_seconds) const {
    if(diff_seconds != 0){
        return Time(diff_seconds + m_start);
    }
    return m_start;
}
Time Appointment::getEndTime(int diff_seconds) const {
    if(diff_seconds != 0){
        return Time(diff_seconds + m_end);
    }
    return m_end;
}

void Appointment::setName(String const &name)       { m_name = name;    }
void Appointment::setNote(String const &note)       { m_note = note;    }
void Appointment::setDate(Date const &date)         { m_date = date;    }
void Appointment::setStartTime(Time const &start)   { m_start = start;  }
void Appointment::setEndTime(Time const &end)       { m_end = end;      }

std::ostream& operator<<(std::ostream& out, Appointment const& obj){
    return out << "An appointment named " << obj.getName()
    << " is on " << obj.getDate()
    << " starts at " << obj.getStartTime()
    << " and ends at " << obj.getEndTime()
    <<  std::endl << "\tNotes: " << obj.getNote() << std::endl;
}