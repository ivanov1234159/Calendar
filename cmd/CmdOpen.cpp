//
// Created by toi on 02/05/2020.
//

#include "CmdOpen.hpp"
#include "../Commander.hpp"

CmdOpen::CmdOpen(): Command("open", "<file>", "open the file at path <file>") {}

bool CmdOpen::action(RunnerType &runner, std::istringstream &iss) const {
    String path;
    iss >> path;
    if(!iss){
        return false;
    }
    bool result = runner.open(path);
    String file_name = runner.getFileName(path);
    if(result){
        std::cout << "Successfully opened " << file_name << std::endl;
    } else {
        std::cout << "Couldn't open " << file_name << std::endl;
    }
    return true;
}