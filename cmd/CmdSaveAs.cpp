//
// Created by toi on 02/05/2020.
//

#include "CmdSaveAs.hpp"

CmdSaveAs::CmdSaveAs(): Command("saveas", "<file>", "save the current state of the program in <file>") {}

bool CmdSaveAs::action(RunnerType &runner, std::istringstream &iss) const {
    //TODO: Implement
    return true;
}