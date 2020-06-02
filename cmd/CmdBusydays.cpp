//
// Created by toi on 29/05/2020.
//

#include "CmdBusydays.hpp"

CmdBusydays::CmdBusydays()
    : Command("busydays", "<from> <to>",
            "prints all days between <from> and <to> order by count of busy hours per day") {}

bool CmdBusydays::action(RunnerType& runner, std::istringstream& iss) const {
    Date from, to;
    iss >> from >> to;
    if(!iss){
        std::cout << "Wrong date format." << std::endl;
        return false;
    }
    Pair<bool, Vector<Date>> result = runner.getBusyDays(from, to);
    if(result.left){
        for(unsigned i = 0; i < result.right.size(); i++){
            std::cout << result.right[i] << std::endl;
        }
    }else if(!runner.opened()){
        std::cout << "There isn't an opened calendar." << std::endl;
    }else if(result.right.fixed()){
        std::cout << "Invalid time period. Inverted edges." << std::endl;
    }else{
        std::cout << "There isn't a busy day between " << from << " and " << to << '.' << std::endl;
    }
    return true;
}