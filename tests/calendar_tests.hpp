//
// Created by toi on 04/06/2020.
//

#include "doctest.h"
#include "../Calendar.hpp"

TEST_CASE("Test class Calendar default constructor and holiday() and isHoliday() methods") {
    Calendar obj;
    CHECK(obj.getFilePath().empty());

    CHECK(obj.holiday(Date(4, 6, 2020)));
    CHECK(!obj.holiday(Date(4, 6, 2020)));
    CHECK(obj.isHoliday(Date(4, 6, 2020)));
    CHECK(!obj.isHoliday(Date(5, 6, 2020)));
}

TEST_CASE("Test class Calendar constructor with param String const& and isEmpty() method") {
    Calendar obj("calendar_data.bin");
    CHECK_EQ(obj.getFilePath(), "calendar_data.bin");
    CHECK(obj.isEmpty());

    Appointment app("name", "notes", Date(4, 6, 2020), Time(0, 15, 15), Time(0, 0, 20));
    obj.book(app);

    CHECK(!obj.isEmpty());

    SUBCASE("Test class Calendar book() methods and isFree() method") {
        //and line: "obj.book(app);" must be here
        CHECK(!obj.isFree(Date(4, 6, 2020), Time(0, 30, 15), Time(0, 0, 21)));
        CHECK(obj.book(Date(4, 6, 2020), Time(1, 0, 20), Time(0, 0, 21), "name2", "more notes"));
    }

    SUBCASE("Test class Calendar find() methods and findFirst() method") {
        CHECK_EQ(obj.find(Date(4, 6, 2020), Time(0, 0, 15)), nullptr);
        CHECK_EQ(obj.find(Date(4, 6, 2020), Time(0, 15, 15))->getName(), "name");

        /*
         * obj.find(Date(4, 6, 2020), Time(0, 15, 15), Time(0, 0, 20));
         * !!! this function is private
         * see the test for unbook() method
         */

        //TODO: Implement
        //CHECK_EQ(obj.findFirst(Date(4, 6, 2020), Time(0, 0, 21), Time(0, 0, 22)), nullptr);
        //CHECK_EQ(obj.findFirst(Date(4, 6, 2020), Time(0, 0, 8), Time(0, 0, 22))->getStartTime(), Time(0, 15, 15));
        // !!! works but findFirst() is private
    }

    SUBCASE("Test class Calendar unshiftAppointment() method") {
        CHECK_EQ(obj.unshiftAppointment().getDate(), Date(4, 6, 2020));
    }

    SUBCASE("Test class Calendar unbook() method") {
        // this also can works for test of find(Date const&, Time const&, Time const&) method
        CHECK(!obj.unbook(Date(4, 6, 2020), Time(1, 15, 15), Time(0, 0, 20)));
        CHECK(obj.unbook(Date(4, 6, 2020), Time(0, 15, 15), Time(0, 0, 20)));
    }
}

/*
 * TODO:
 *  - Calendar(std::ifstream&, String const& = nullptr)
 *  - bool serialize(std::ofstream&) const
 *  -
 *  - bool agenda(Date const&, std::ostream&) const
 *  -
 *  - bool findString(String const&, std::ostream&) const
 *  - Vector<Pair<Date, int>> findBusyDays(Date const&, Date const&) const
 *  - findSlotAt(Date const&, Time const&, Time&) const
 */