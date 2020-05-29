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

    bool open(String const& file_path);
    void close();
    bool save() const;
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
private:
    static String getNameFromPath(char const *file_path);
    void clear();
};

#endif //CALENDAR_PROGRAM_HPP
