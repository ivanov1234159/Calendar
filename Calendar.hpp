//
// Created by toi on 29/03/2020.
//

#ifndef CALENDAR_CALENDAR_HPP
#define CALENDAR_CALENDAR_HPP

#include <iostream>
//for: ostream, endl
#include <fstream>
//for: ifstream, ofstream
#include "Appointment.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include "Vector.hpp"
#include "String.hpp"
#include "Pair.hpp"

class Calendar {
    /// the file path in which the calendar had been saved
    String m_file_path;
    /// container form Appointments
    Vector<Appointment> m_list;
public:
    Calendar() = default;
    Calendar(String const& calendar_path);
    Calendar(std::ifstream& ifs, String const& calendar_path = nullptr);

    /// @return m_file_path
    String const& getFilePath() const;

    /// @return m_list.empty()
    bool isEmpty() const;

    /// @return m_list.unshift()
    Appointment unshiftAppointment();

    /**
     * serialize this object
     * @param ofs
     * @return false on fail
     */
    bool serialize(std::ofstream& ofs) const;

    /**
     * book an appointment; uses book(Appointment const&)
     * @param date
     * @param start
     * @param end
     * @param name
     * @param note
     * @return false if it's NOT free
     */
    bool book(Date const& date, Time const& start, Time const& end, String const& name, String const& note);

    /**
     * remove booking of an appointment by searching it with the params
     * @param date
     * @param start
     * @param end
     * @return false if there isn't such appointment
     */
    bool unbook(Date const& date, Time const& start, Time const& end);

    /**
     * print all appointments for the day <date>
     * @param date
     * @param out - a stream to print
     * @return false if prints nothing
     */
    bool agenda(Date const& date, std::ostream& out) const;

    /**
     * search appointments to print them by needle
     * @param needle - must be contained by Appointment::m_name OR Appointment::m_note
     * @param out - a source to print
     * @return false if prints nothing
     */
    bool findString(String const& needle, std::ostream& out) const;

    /**
     * mark the day <date> as holiday
     * @param date
     * @return false if NOT the whole day is free
     */
    bool holiday(Date const& date);

    /**
     * search for all busy days from the interval order by busy time per day
     * @param from
     * @param to
     * @return list (array) from { day (date), time in seconds }
     */
    Vector<Pair<Date, int>> findBusyDays(Date const& from, Date const& to) const;

    /**
     * search for a time period with length <duration> on <date>
     * and the hours cannot be before 08 or after 17
     * @param date - cannot be holiday
     * @param duration - if longer than (17 - 8) hours, then begin is 23:59:59
     * @param begin - used to return the starting time
     * @return false if there isn't a time period with length <duration> on <date>
     *      OR the date is holiday
     */
    bool findSlotAt(Date const& date, Time const& duration, Time& begin) const;

    /**
     * search for an appointment which is on <date> and begins at <start>
     * @param date
     * @param start
     * @return nullptr if not found
     */
    Appointment* find(Date const& date, Time const& start) const;

    /**
     * check if day <date> is free starting from <start> and ending to <end>
     * @param date
     * @param start
     * @param end
     * @return false if it's NOT free
     */
    bool isFree(Date const& date, Time const& start, Time const& end) const;

    /**
     * check if <date> is holiday
     * @param date
     * @return false if it's not holiday OR there isn't an appointment on that day
     */
    bool isHoliday(Date const& date) const;

    /**
     * book an appointment and uses sorted insert by date and start time
     * @param app
     */
    void book(Appointment const &app);
private:
    /**
     * search for an appointment which is on <date> and begins at <start> and ends at <end>
     * @param date
     * @param start
     * @param end
     * @return nullptr if not found
     */
    Appointment* find(Date const& date, Time const& start, Time const& end);

    /**
     * search for the first appointment that is in the interval between <start> and <end> on <date>
     * @param date
     * @param start
     * @param end
     * @return nullptr if not found (ONLY if isFree(date, start, end) == true)
     */
    Appointment const* findFirst(Date const& date, Time const& start, Time const& end) const;
};

#endif //CALENDAR_CALENDAR_HPP
