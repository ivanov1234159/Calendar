//
// Created by toi on 02/06/2020.
//

#include "CmdFindSlot.hpp"

CmdFindSlot::CmdFindSlot(): Command("findslot", "<from_date> <time>",
    "search for an appointment time <from_date> with duration <time>\nbut date cannot be holiday and the hours cannot be before 08 or after 17")
{}

bool CmdFindSlot::action(RunnerType& runner, std::istringstream& iss) const {
    Date from;
    Time duration;
    iss >> from >> duration;
    if(!iss){
        std::cout << "Wrong date format." << std::endl;
        return false;
    }
    Pair<Date, Time> result = runner.findSlot(from, duration);
    if(runner.opened()){
        if(result.right.max()){
            std::cout << "The time period is longer than (17 - 8) hours" << std::endl;
            return false;
        }
        std::cout << "The first possible date is on " << result.left << " from " << result.right
                  << " to " << (result.right += duration) << '.' << std::endl;
    }else{
        std::cout << "There isn't an opened calendar." << std::endl;
    }
    return true;
}