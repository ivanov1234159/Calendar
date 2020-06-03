//
// Created by toi on 29/05/2020.
//

#include "CmdAgenda.hpp"

CmdAgenda::CmdAgenda()
        : Command("agenda", "<date>", "print a list with all appointments for the <date> order by time"){}

bool CmdAgenda::action(std::ostream& out, RunnerType &runner, std::istringstream &iss) const {
    Date date;
    iss >> date;
    if(!iss){
        out << "Wrong date format." << std::endl;
        return false;
    }

    if(!runner.agenda(date, out)){
        if(runner.opened()){
            out << "There isn't appointments for the given day." << std::endl;
        }else{
            out << "There isn't an opened calendar." << std::endl;
        }
    }
    return true;
}