//
// Created by toi on 02/05/2020.
//

#include "CmdClose.hpp"

CmdClose::CmdClose(): Command("close", "", "close the currently opened file") {}

bool CmdClose::action(RunnerType &runner, std::istringstream&) const {
    String filename = runner.getFileName();
    if(filename.empty()){
        std::cout << "There isn't a file to be closed." << std::endl;
    } else {
        runner.close();
        std::cout << "Successfully closed " << filename << std::endl;
    }
    return true;
}