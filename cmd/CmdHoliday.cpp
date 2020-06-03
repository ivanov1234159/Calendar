//
// Created by toi on 29/05/2020.
//

#include "CmdHoliday.hpp"
#include "../Commander.hpp"
#include "../Date.hpp"

CmdHoliday::CmdHoliday()
        : Command("holiday", "<date>", "mark <date> as holiday if there isn't an appointments"){}

bool CmdHoliday::action(std::ostream& out, RunnerType &runner, std::istringstream &iss) const {
    Date date;
    iss >> date;
    if(!iss){
        out << "Wrong date format." << std::endl;
        return false;
    }

    if(runner.markAsHoliday(date)){
        out << "The date " << date << " was successfully marked as holiday." << std::endl;
    }else if(!runner.opened()){
        out << "There isn't an opened calendar." << std::endl;
    }else{
        out << "The following appointments are on the given date:" << std::endl;
        std::istringstream iss2(date.to_string().get());
        Commander::call("agenda", runner, iss2, out);
    }
    return true;
}