//
// Created by toi on 02/05/2020.
//

#include "CmdSave.hpp"

CmdSave::CmdSave(): Command("save", "", "save the current state of the program") {}

bool CmdSave::action(RunnerType &runner, std::istringstream&) const {
    String filename = runner.getFileName();
    if(filename.empty()){
        std::cout << "There isn't a file to be saved." << std::endl;
    } else if(runner.save()) {
        std::cout << "Successfully saved " << filename << std::endl;
    } else {
        std::cout << "Couldn't save the file." << std::endl;
        return false;
    }
    return true;
}