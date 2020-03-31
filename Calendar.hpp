//
// Created by toi on 29/03/2020.
//

#ifndef CALENDAR_CALENDAR_HPP
#define CALENDAR_CALENDAR_HPP

#include <iostream>
//for: ostream, endl
#include "Appointment.hpp"
#include "Date.hpp"
#include "Time.hpp"

/*enum class CalendarStatus {
    I_OK,// I_ -> info
    E_DATE,// E_ -> error
    E_START_TIME,
    E_END_TIME,
    E_NAME,
    E_NOTE
};*/

class Calendar {
    char* m_name;// the same as the file name in which the calendar had been saved
    Appointment* m_list;
    unsigned m_size;
    unsigned m_limit;
public:
    Calendar(char const* calendar_name = nullptr);
    Calendar(Calendar const& other);
    Calendar& operator=(Calendar const& other);
    ~Calendar();

    bool empty() const;
    bool full() const;

    bool book(Date const& date, Time const& start, Time const& end, char const* name, char const* note);
    bool unbook(Date const& date, Time const& start, Time const& end);
    void agenda(Date const& date, std::ostream& out);
    //change
    //find
    void holiday(Date const& date);
    //busydays
    //findslot
    //findslotwith
    //merge

private:
    void book(Appointment const &app);
    void clear();
    void copy(Calendar const& other);
    void resize();
    bool isFree(Date const& date, Time const& start, Time const& end) const;
    Appointment* find(Date const& date, Time const& start, Time const& end);
};

#endif //CALENDAR_CALENDAR_HPP