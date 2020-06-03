//
// Created by toi on 02/05/2020.
//

#include "CmdSave.hpp"

CmdSave::CmdSave(): Command("save", "", "save the current state of the program") {}

bool CmdSave::action(std::ostream& out, RunnerType &runner, std::istringstream&) const {
    String filename = runner.getFileName();
    if(filename.empty()){
        out << "There isn't a file to be saved." << std::endl;
    } else if(runner.save()) {
        out << "Successfully saved " << filename << std::endl;
    } else {
        out << "Couldn't save the file." << std::endl;
        return false;
    }
    return true;
}