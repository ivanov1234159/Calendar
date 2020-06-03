//
// Created by toi on 01/04/2020.
//

#ifndef CALENDAR_PROGRAM_HPP
#define CALENDAR_PROGRAM_HPP

#include <iostream>
//for: ostream
#include "Calendar.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include "String.hpp"
#include "Pair.hpp"

class Program {
public:
    static Program& self();
private:
    Calendar* m_calendar;// only one; (not a list)

    Program();
    Program(Program const& other) = delete;
    Program& operator=(Program const& other) = delete;
public:
    ~Program();

    /// @return m_calendar != nullptr
    bool opened() const;

    /**
     * get file name from calendar's path or <path>
     * @param path - if is nullptr (or empty), then uses calendar's path
     * @return the file name (with file extension) OR empty string if any path is empty
     */
    String getFileName(String const& path = nullptr) const;

    /**
     * opens a calendar using <file_path>
     * @param file_path
     * @return false if the calendar is already opened
     */
    bool open(String const& file_path);

    /// calls clear() method if the calendar is opened
    void close();

    /// @return true if not opened OR successfully serialize m_calendar
    bool save() const;

    /// @return pointer to cloned value of m_calendar OR nullptr if not opened
    Calendar* cloneCalendar() const;

    /**
     * restore cloned calendar and clears the previous one
     * @param cloned
     * @return true if there was a previous calendar (which was opened)
     */
    bool restoreCalendar(Calendar* cloned);

    /**
     * book an appointment; calls m_calendar->book()
     * @param date
     * @param start
     * @param end
     * @param name
     * @param note
     * @return false if it's opened OR the day is NOT free at that time
     */
    bool book(Date const& date, Time const& start, Time const& end, String const& name, String const& note);

    /**
     * remove an appointment; calls m_calendar->unbook()
     * @param date
     * @param start
     * @param end
     * @return false if it's opened OR there isn't such appointment
     */
    bool unbook(Date const& date, Time const& start, Time const& end);

    /**
     * print all appointments for the day <date>; calls m_calendar->agenda()
     * @param date
     * @param out
     * @return false if prints nothing
     */
    bool agenda(Date const& date, std::ostream& out) const;

    /**
     * change date of an appointment
     * @param date
     * @param start
     * @param new_date
     * @return { success, is free new_date };
     *  success is false if calendar isn't opened OR it's not found such appointment
     */
    Pair<bool, bool> changeDate(Date const& date, Time const& start, Date const& new_date);

    /**
     * change start time of an appointment
     * @param date
     * @param start
     * @param new_start_time
     * @return { success, is free new_start_time };
     *  success is false if calendar isn't opened OR it's not found such appointment
     */
    Pair<bool, bool> changeStartTime(Date const& date, Time const& start, Time const& new_start_time);

    /**
     * change end time of an appointment
     * @param date
     * @param start
     * @param new_end_time
     * @return { success, is free new_end_time };
     *  success is false if calendar isn't opened OR it's not found such appointment
     */
    Pair<bool, bool> changeEndTime(Date const& date, Time const& start, Time const& new_end_time);

    /**
     * change name of an appointment
     * @param date
     * @param start
     * @param new_name
     * @return false if calendar isn't opened OR it's not found such appointment
     */
    bool changeName(Date const& date, Time const& start, String const& new_name);

    /**
     * change note of an appointment
     * @param date
     * @param start
     * @param new_note
     * @return false if calendar isn't opened OR it's not found such appointment
     */
    bool changeNote(Date const& date, Time const& start, String const& new_note);

    /**
     * search appointments to print them by needle; calls m_calendar->findString()
     * @param needle - must be contained by Appointment::m_name OR Appointment::m_note
     * @param out - a source to print
     * @return false if calendar isn't opened OR prints nothing
     */
    bool findString(String const& needle, std::ostream& out) const;

    /**
     * mark the day <date> as holiday; calls m_calendar->holiday()
     * @param date
     * @return false if NOT the whole day is free
     */
    bool markAsHoliday(Date const& date);

    /**
     * search for all busy days from the interval order by busy time per day
     * @param from
     * @param to
     * @return { success, list (array) from days };
     *  success is false if calendar isn't opened OR from is bigger than to OR it's NOT found an appointment
     */
    Pair<bool, Vector<Date>> getBusyDays(Date const& from, Date const& to) const;

    /**
     * find the first possible date after <from> with <duration>
     * and the date cannot be holiday and the hours cannot be before 08 or after 17
     * @param from
     * @param duration
     * @param calendar - if is nullptr then uses m_calendar instead
     * @return { the date, starting time }; starting time is max time if duration > (17 - 8) hours
     */
    Pair<Date, Time> findSlot(Date const& from, Time const& duration, Calendar const* calendar = nullptr) const;

    /**
     * uses fundSlot() method to find the best match for both calendars (m_calendar and calendar)
     * @param from
     * @param duration
     * @param calendar - if is nullptr then returns { from, Time() }
     * @return { the date, starting time }; starting time is max time if duration > (17 - 8) hours
     */
    Pair<Date, Time> findSlotWith(Date const& from, Time const& duration, Calendar const* calendar) const;

    /**
     * merge m_calendar with <other_calendar> by adding appointments from the one to the other
     * @param other_calendar
     * @param out - used to print program's messages
     * @param in - used to read user's input
     * @return false if <other_calendar> is empty (hasn't appointments) OR m_calendar is nullptr
     */
    bool mergeWith(Calendar* other_calendar, std::ostream& out, std::istream& in);

    /**
     * opens <calendar> using <file_path>
     * @param file_path
     * @param calendar
     * @return false if the calendar is not nullptr
     */
    static bool open(String const& file_path, Calendar*& calendar);
private:
    /**
     * extracts file name from <file_path>
     * @param file_path
     * @return the file name
     */
    static String getNameFromPath(char const *file_path);

    /// set m_calendar to nullptr and free the memory
    void clear();
};

#endif //CALENDAR_PROGRAM_HPP
