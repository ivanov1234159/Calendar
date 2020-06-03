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
    bool m_holiday;
public:
    Appointment(): m_holiday(false) {}
    Appointment(std::ifstream& ifs);
    Appointment(String const& name, String const& note, Date const& date, Time const& start, Time const& end);

    /**
     * serialize this object
     * @param ofs
     * @return false on fail
     */
    bool serialize(std::ofstream& ofs) const;

    /// @return m_name
    String const& getName() const;

    /// @return m_note
    String const& getNote() const;

    /// @return m_date
    Date getDate() const;

    /**
     * @param diff_seconds
     * @return m_start + diff_seconds
     */
    Time getStartTime(int diff_seconds = 0) const;

    /**
     * @param diff_seconds
     * @return m_end + diff_seconds
     */
    Time getEndTime(int diff_seconds = 0) const;

    /// @return m_holiday
    bool isHoliday() const;

    /**
     * set <name> to m_name
     * @param name
     */
    void setName(String const& name);

    /**
     * set <note> to m_note
     * @param note
     */
    void setNote(String const& note);

    /**
     * set <date> to m_date
     * @param date
     */
    void setDate(Date const& date);

    /**
     * set <start> to m_start
     * @param start
     */
    void setStartTime(Time const& start);

    /**
     * set <end> to m_end
     * @param end
     */
    void setEndTime(Time const& end);

    /**
     * set <holiday> to m_holiday
     * @param holiday
     */
    void setHoliday(bool holiday = true);
};

std::ostream& operator<<(std::ostream& out, Appointment const& obj);

#endif //CALENDAR_APPOINTMENT_HPP
