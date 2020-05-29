//
// Created by toi on 29/05/2020.
//

#include "CmdFind.hpp"

CmdFind::CmdFind()
    : Command("find", "<string>", "search for an appointment which name or note contains <string>"){}

bool CmdFind::action(RunnerType &runner, std::istringstream &iss) const {
    String needle;
    needle.read(iss, '\n');
    if(!iss){
        std::cout << "Wrong format." << std::endl;
        return false;
    }
    std::cout << "Searching for '" << needle << "'." << std::endl << std::endl;

    if(!runner.findString(needle, std::cout)){
        if(runner.opened()){
            std::cout << "There isn't an appointment that matches." << std::endl;
        }else{
            std::cout << "There isn't an opened calendar." << std::endl;
        }
    }
    return true;
}