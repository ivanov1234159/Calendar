//
// Created by toi on 29/05/2020.
//

#include "CmdBusydays.hpp"

CmdBusydays::CmdBusydays()
    : Command("busydays", "<from> <to>",
            "prints all days between <from> and <to> order by count of busy hours per day") {}

bool CmdBusydays::action(std::ostream& out, RunnerType& runner, std::istringstream& iss) const {
    Date from, to;
    iss >> from >> to;
    if(!iss){
        out << "Wrong date format." << std::endl;
        return false;
    }
    Pair<bool, Vector<Date>> result = runner.getBusyDays(from, to);
    if(result.left){
        for(unsigned i = 0; i < result.right.size(); i++){
            out << result.right[i] << std::endl;
        }
    }else if(!runner.opened()){
        out << "There isn't an opened calendar." << std::endl;
    }else if(result.right.fixed()){
        out << "Invalid time period. Inverted edges." << std::endl;
    }else{
        out << "There isn't a busy day between " << from << " and " << to << '.' << std::endl;
    }
    return true;
}