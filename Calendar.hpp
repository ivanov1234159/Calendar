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

/*enum class CalendarStatus {
    I_OK,// I_ -> info
    E_DATE,// E_ -> error
    E_START_TIME,
    E_END_TIME,
    E_NAME,
    E_NOTE
};*/

class Calendar {
    String m_file_path;// the file path in which the calendar had been saved
    Vector<Appointment> m_list;
public:
    Calendar() = default;
    Calendar(String const& calendar_path);
    Calendar(std::ifstream& ifs, String const& calendar_path = nullptr);

    String const& getFilePath() const;
    bool serialize(std::ofstream& ofs) const;

    bool book(Date const& date, Time const& start, Time const& end, String const& name, String const& note);
    bool unbook(Date const& date, Time const& start, Time const& end);
    void agenda(Date const& date, std::ostream& out);
    bool findString(String const& needle, std::ostream& out);
    //void holiday(Date const& date);
    //busydays
    //findslot
    //findslotwith
    //merge

    Appointment* find(Date const& date, Time const& start);

private:
    void book(Appointment const &app);
    bool isFree(Date const& date, Time const& start, Time const& end) const;
    Appointment* find(Date const& date, Time const& start, Time const& end);
};

#endif //CALENDAR_CALENDAR_HPP
