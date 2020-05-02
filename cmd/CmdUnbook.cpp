//
// Created by toi on 02/05/2020.
//

#include "CmdUnbook.hpp"

CmdUnbook::CmdUnbook(): Command("unbook", "<date> <start_time> <end_time>",
                                "meeting canceled by <date> with <start_time> and <end_time>") {}

bool CmdUnbook::action(RunnerType &runner, std::istringstream &iss) const {
    if(!runner.opened()){
        std::cout << "There isn't an open file. Please, open one." << std::endl;
        return true;
    }
    Date date;
    iss >> date;
    if(!iss){
        std::cout << "Invalid date format. Cannot remove an appointment." << std::endl;
        return false;
    }
    Time start;
    iss >> start;
    if(!iss){
        std::cout << "Invalid time format. Cannot remove an appointment." << std::endl;
        return false;
    }
    Time end;
    iss >> end;
    if(!iss){
        std::cout << "Invalid time format. Cannot remove an appointment." << std::endl;
        return false;
    }
    if(runner.unbook(date, start, end)){
        std::cout << "The appointment was successfully removed from the calendar." << std::endl;
    }else{
        std::cout << "There isn't an appointment on this date at this time interval." << std::endl;
    }
    return true;
}