//
// Created by toi on 01/04/2020.
//

#ifndef CALENDAR_PROGRAM_HPP
#define CALENDAR_PROGRAM_HPP

#include "Calendar.hpp"

class Program {
    Calendar* m_calendar;// only one; (not a list)

    Program(Program const& other) = delete;
    Program& operator=(Program const& other) = delete;
public:
    Program();
    ~Program();

    bool opened() const;

    bool open(char const* file_path);
    bool close(char*& file_path);// file_path is to return the file_path (from m_calendar->m_name)

private:
    void clear();
};

#endif //CALENDAR_PROGRAM_HPP
