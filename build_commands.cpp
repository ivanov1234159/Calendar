//
// Created by toi on 08/04/2020.
//

#include "Commander.hpp"
#include "CmdBook.hpp"
#include "CmdClose.hpp"
#include "CmdExit.hpp"
#include "CmdHelp.hpp"
#include "CmdOpen.hpp"
#include "CmdSave.hpp"
#include "CmdSaveAs.hpp"
#include "CmdUnbook.hpp"

bool cmd_status(RunnerType& runner, std::istringstream& iss){
    std::cout << "File opened: " << (runner.opened() ? "true" : "false") << std::endl;
    std::cout << "File path: " << (runner.opened()
        ? (runner.m_calendar->getFilePath() == nullptr
            ? "<NULL>"
            : runner.m_calendar->getFilePath())
        : "<NO_PATH>") << std::endl;
    std::cout << "Appointments: " << std::endl << std::endl;
    if(runner.opened()){
        for(unsigned i = 0; i < runner.m_calendar->m_size; i++){
            std::cout << runner.m_calendar->m_list[i] << std::endl;
        }
        std::cout << std::endl;
    }else{
        std::cout << "No appointments." << std::endl;
    }
    return true;
}

void build_commands(){
    Commander::add(new CmdBook);
    Commander::add(new CmdClose);
    Commander::add(new CmdExit);
    Commander::add(new CmdHelp);
    Commander::add(new CmdOpen);
    Commander::add(new CmdSave);
    Commander::add(new CmdSaveAs);
    Commander::add(new CmdUnbook);
    /*Commander::add(Command("status", "", "prints information about the program status", cmd_status));*/
}