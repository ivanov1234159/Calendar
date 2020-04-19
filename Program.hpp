//
// Created by toi on 01/04/2020.
//

#ifndef CALENDAR_PROGRAM_HPP
#define CALENDAR_PROGRAM_HPP

#include "Calendar.hpp"

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
    void getFileName(char*& file_name, char* path = nullptr) const;// file_name is to return the file_name (from m_calendar->m_name)

    bool open(char const* file_path);
    void close();
    bool save();

private:
    static void getNameFromPath(char const*file_path, char*& file_name);
    void clear();
};

#endif //CALENDAR_PROGRAM_HPP
