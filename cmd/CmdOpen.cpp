//
// Created by toi on 02/05/2020.
//

#include "CmdOpen.hpp"
#include "../Commander.hpp"

CmdOpen::CmdOpen(): Command("open", "<file>", "open the file at path <file>") {}

bool CmdOpen::action(std::ostream& out, RunnerType &runner, std::istringstream &iss) const {
    String path;
    iss >> path;
    if(!iss){
        out << "Couldn't read the path." << std::endl;
        return false;
    }
    bool result = runner.open(path);
    String file_name = runner.getFileName(path);
    if(result){
        out << "Successfully opened " << file_name << std::endl;
    } else {
        out << "Couldn't open " << file_name << std::endl;
    }
    return true;
}