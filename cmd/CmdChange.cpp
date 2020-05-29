//
// Created by toi on 29/05/2020.
//

#include "CmdChange.hpp"

CmdChange::CmdChange(): Command("change", "<date> <start_time> <option> <new_value>",
    "set <option> to be <new_value> to the appointment on <date> at <start_time>\n<option> can be 'date', 'start_time', 'end_time', 'name', 'note'")
{}

bool CmdChange::action(RunnerType &runner, std::istringstream &iss) const {
    String date, start, option, new_value;
    iss >> date >> start >> option >> new_value;
    if(!iss){
        std::cout << "Wrong format." << std::endl;
        return false;
    }
    bool result = false;
    if(option == "date"){
        result = runner.changeDate(date, start, new_value);
    } else if(option == "start_time"){
        result = runner.changeStartTime(date, start, new_value);
    } else if(option == "end_time"){
        result = runner.changeEndTime(date, start, new_value);
    } else if(option == "name"){
        result = runner.changeName(date, start, new_value);
    } else if(option == "note"){
        result = runner.changeNote(date, start, new_value);
    }else{
        std::cout << "Wrong format. Invalid <option> value." << std::endl;
        return false;
    }

    std::cout << "Value of " << option << " was ";
    if(!result){
        std::cout << "NOT ";
    }
    std::cout << "successfully changed to " << new_value << "." << std::endl;
    if(!result){
        std::cout << "There isn't an appointment on " << date << " at " << start << "." << std::endl;
    }
    return true;
}