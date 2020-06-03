//
// Created by toi on 29/05/2020.
//

#include "CmdChange.hpp"

CmdChange::CmdChange(): Command("change", "<date> <start_time> <option> <new_value>",
    "set <option> to be <new_value> to the appointment on <date> at <start_time>\n<option> can be 'date', 'start_time', 'end_time', 'name', 'note'")
{}

bool CmdChange::action(std::ostream& out, RunnerType &runner, std::istringstream &iss) const {
    Date date;
    Time start;
    String option;
    iss >> date >> start >> option;
    if(!iss){
        out << "Wrong format." << std::endl;
        return false;
    }
    bool result = false;
    if(option == "date"){
        Date new_value;
        iss >> new_value;
        Pair<bool, bool> temp = runner.changeDate(date, start, new_value);
        result = temp.left;
        if(temp.right){
            out << "The requested date is NOT free at this time period." << std::endl;
        }
    } else if(option == "start_time"){
        Time new_value;
        iss >> new_value;
        Pair<bool, bool> temp = runner.changeStartTime(date, start, new_value);
        result = temp.left;
        if(temp.right){
            out << "The requested time period is NOT free." << std::endl;
        }
    } else if(option == "end_time"){
        Time new_value;
        iss >> new_value;
        Pair<bool, bool> temp = runner.changeEndTime(date, start, new_value);
        result = temp.left;
        if(temp.right){
            out << "The requested time period is NOT free." << std::endl;
        }
    } else if(option == "name"){
        String new_value;
        iss >> new_value;
        result = runner.changeName(date, start, new_value);
    } else if(option == "note"){
        String new_value;
        iss >> new_value;
        result = runner.changeNote(date, start, new_value);
    }else{
        out << "Wrong format. Invalid <option> value." << std::endl;
        return false;
    }

    out << "Value of " << option << " was ";
    if(!result){
        out << "NOT ";
    }
    out << "successfully changed." << std::endl;
    if(!result) {
        if (runner.opened()) {
            out << "There isn't an appointment on " << date << " at " << start << "." << std::endl;
        } else {
            out << "There isn't an opened calendar." << std::endl;
        }
    }
    return true;
}