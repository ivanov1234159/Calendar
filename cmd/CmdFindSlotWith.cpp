//
// Created by toi on 02/06/2020.
//

#include "CmdFindSlotWith.hpp"

CmdFindSlotWith::CmdFindSlotWith(): Command("findslotwith", "<from_date> <hours> <calendar_path>",
    "same as `findslot` command but for both calendars")
{}

bool CmdFindSlotWith::action(std::ostream& out, RunnerType& runner, std::istringstream& iss) const {
    Date from;
    Time duration;
    iss >> from >> duration;
    if(!iss){
        out << "Wrong date or time format." << std::endl;
        return false;
    }
    String path;
    iss >> path;
    if(!iss){
        out << "Couldn't read the path." << std::endl;
        return false;
    }

    if(!runner.opened()) {
        out << "There isn't an opened calendar." << std::endl;
        return true;
    }

    Calendar* calendar = nullptr;
    runner.open(path, calendar);
    Pair<Date, Time> result = runner.findSlotWith(from, duration, calendar);
    delete calendar;

    if(result.right.max()){
        out << "The time period is longer than (17 - 8) hours" << std::endl;
        return false;
    }
    out << "The first possible date is on " << result.left << " from " << result.right
        << " to " << (result.right += duration) << '.' << std::endl;
    return true;
}