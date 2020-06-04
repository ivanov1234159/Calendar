//
// Created by toi on 04/06/2020.
//

#include <sstream>
//for: ostringsteam
#include <fstream>
//for: ifstream, ofstream
#include "doctest.h"
#include "../Appointment.hpp"

TEST_CASE("Test class Appointment constructor with params and getters") {
    Appointment app("name", "notes", Date(4, 6, 2020), Time(0, 15, 15), Time(0, 0, 20));
    CHECK(!app.isHoliday());
    CHECK_EQ(app.getName(), "name");
    CHECK_EQ(app.getNote(), "notes");
    CHECK_EQ(app.getDate(), Date(4, 6, 2020));
    CHECK_EQ(app.getStartTime(), Time(0, 15, 15));
    CHECK_EQ(app.getEndTime(-1), Time(59, 59, 19));
}

TEST_CASE("Test class Appointment default constructor and setters") {
    Appointment app;
    CHECK(!app.isHoliday());

    app.setName("name");
    CHECK_EQ(app.getName(), "name");

    app.setNote("notes");
    CHECK_EQ(app.getNote(), "notes");

    app.setDate(Date(4, 6, 2020));
    CHECK_EQ(app.getDate(), Date(4, 6, 2020));

    app.setStartTime(Time(0, 15, 15));
    CHECK_EQ(app.getStartTime(61), Time(1, 16, 15));

    app.setEndTime(Time(0, 0, 20));
    CHECK_EQ(app.getEndTime(), Time(0, 0, 20));

    app.setHoliday();
    CHECK(app.isHoliday());
}

TEST_CASE("Test operator << for class Appointment") {
    Appointment app("name", "notes", Date(4, 6, 2020), Time(0, 15, 15), Time(0, 0, 20));
    std::ostringstream oss;
    oss << app;
    CHECK_EQ(oss.str(), "An appointment named name is on 2020-06-04 starts at 15:15:00 and ends at 20:00:00\n\tNotes: notes\n");
}

TEST_CASE("Test serialize method of class Appointment and the constructor with param std::ifstream&") {
    Appointment app("name", "notes", Date(4, 6, 2020), Time(0, 15, 15), Time(0, 0, 20));

    std::ofstream ofs(___TEST_FILE_NAME___);
    CHECK(app.serialize(ofs));
    ofs.close();

    std::ifstream ifs(___TEST_FILE_NAME___);
    Appointment app2(ifs);
    ifs.close();
    CHECK(!app2.isHoliday());
    CHECK_EQ(app2.getName(), "name");
    CHECK_EQ(app2.getNote(), "notes");
    CHECK_EQ(app2.getDate(), Date(4, 6, 2020));
    CHECK_EQ(app2.getStartTime(), Time(0, 15, 15));
    CHECK_EQ(app2.getEndTime(-1), Time(59, 59, 19));
}