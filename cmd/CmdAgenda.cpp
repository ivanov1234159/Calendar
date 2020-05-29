//
// Created by toi on 29/05/2020.
//

#include "CmdAgenda.hpp"

CmdAgenda::CmdAgenda()
        : Command("agenda", "<date>", "print a list with all appointments for the <date> ordered by time"){}

bool CmdAgenda::action(RunnerType &runner, std::istringstream &iss) const {
    Date date;
    iss >> date;
    if(!iss){
        std::cout << "Wrong date format." << std::endl;
        return false;
    }

    if(!runner.agenda(date, std::cout)){
        if(runner.opened()){
            std::cout << "There isn't appointments for the given day." << std::endl;
        }else{
            std::cout << "There isn't an opened calendar." << std::endl;
        }
    }
    return true;
}