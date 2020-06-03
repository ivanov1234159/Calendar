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

    bool opened() const;
    String getFileName(String const& path = nullptr) const;

    /**
     * opens a calendar using <file_path>
     * @param file_path
     * @return false if the calendar is already opened
     */
    bool open(String const& file_path);
    void close();
    bool save() const;

    /**
     * @return pointer to cloned value of m_calendar or nullptr if not opened
     */
    Calendar* cloneCalendar() const;

    /**
     * restore cloned calendar and clears the previous one
     * @param cloned
     * @return true if there was a previous calendar (which was opened)
     */
    bool restoreCalendar(Calendar* cloned);
    bool book(Date const& date, Time const& start, Time const& end, String const& name, String const& note);
    bool unbook(Date const& date, Time const& start, Time const& end);
    bool agenda(Date const& date, std::ostream& out) const;

    Pair<bool, bool> changeDate(Date const& date, Time const& start, Date const& new_date);
    Pair<bool, bool> changeStartTime(Date const& date, Time const& start, Time const& new_start_time);
    Pair<bool, bool> changeEndTime(Date const& date, Time const& start, Time const& new_end_time);
    bool changeName(Date const& date, Time const& start, String const& new_name);
    bool changeNote(Date const& date, Time const& start, String const& new_note);

    bool findString(String const& needle, std::ostream& out) const;
    bool markAsHoliday(Date const& date);
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
     * opens <calendar> using <file_path>
     * @param file_path
     * @param calendar
     * @return false if the calendar is not nullptr
     */
    static bool open(String const& file_path, Calendar*& calendar);
private:
    static String getNameFromPath(char const *file_path);
    void clear();
};

#endif //CALENDAR_PROGRAM_HPP
