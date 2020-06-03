//
// Created by toi on 29/05/2020.
//

#include "CmdFind.hpp"

CmdFind::CmdFind()
    : Command("find", "<string>", "search for an appointment which name or note contains <string>"){}

bool CmdFind::action(std::ostream& out, RunnerType &runner, std::istringstream &iss) const {
    String needle;
    needle.read(iss, '\n');
    if(!iss){
        out << "Wrong format." << std::endl;
        return false;
    }
    out << "Searching for '" << needle << "'." << std::endl << std::endl;

    if(!runner.findString(needle, out)){
        if(runner.opened()){
            out << "There isn't an appointment that matches." << std::endl;
        }else{
            out << "There isn't an opened calendar." << std::endl;
        }
    }
    return true;
}