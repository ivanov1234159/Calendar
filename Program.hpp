//
// Created by toi on 01/04/2020.
//

#ifndef CALENDAR_PROGRAM_HPP
#define CALENDAR_PROGRAM_HPP

#include "Calendar.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include "String.hpp"

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
    String const& getFileName(String const& path = nullptr) const;// return  m_calendar->m_name

    bool open(String const& file_path);
    void close();
    bool save() const;
    bool book(Date const& date, Time const& start, Time const& end, String const& name, String const& note);
    bool unbook(Date const& date, Time const& start, Time const& end);
private:
    static String getNameFromPath(char const *file_path);
    void clear();
};

#endif //CALENDAR_PROGRAM_HPP
