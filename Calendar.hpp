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
    String m_file_path;// the file path in which the calendar had been saved
    Vector<Appointment> m_list;
public:
    Calendar() = default;
    Calendar(String const& calendar_path);
    Calendar(std::ifstream& ifs, String const& calendar_path = nullptr);

    String const& getFilePath() const;

    /**
     * @return m_list.empty()
     */
    bool isEmpty() const;

    /**
     * @return m_list.unshift()
     */
    Appointment unshiftAppointment();

    bool serialize(std::ofstream& ofs) const;

    bool book(Date const& date, Time const& start, Time const& end, String const& name, String const& note);
    bool unbook(Date const& date, Time const& start, Time const& end);
    bool agenda(Date const& date, std::ostream& out) const;
    bool findString(String const& needle, std::ostream& out) const;
    bool holiday(Date const& date);
    Vector<Pair<Date, int>> findBusyDays(Date const& from, Date const& to) const;

    /**
     * search for a time period with length <duration> on <date>
     * and the hours cannot be before 08 or after 17
     * @param date - cannot be holiday
     * @param duration - if longer than (17 - 8) hours, then begin is 23:59:59
     * @param begin - used to return the starting time
     * @return false if there isn't a time period with length <duration> on <date>
     *      or the date is holiday
     */
    bool findSlotAt(Date const& date, Time const& duration, Time& begin) const;

    Appointment* find(Date const& date, Time const& start) const;

    bool isFree(Date const& date, Time const& start, Time const& end) const;

    /**
     * check if <date> is holiday
     * @param date
     * @return false if it's not holiday or there isn't an appointment on that day
     */
    bool isHoliday(Date const& date) const;

    void book(Appointment const &app);
private:

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
