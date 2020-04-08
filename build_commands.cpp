//
// Created by toi on 08/04/2020.
//

#include "Commander.hpp"

/* For all of the following functions:
 *      returns false if there is a problem with the arguments (their type or count)
 *
 * MUST handle the situation when the runner cannot do the operation
 */

bool cmd_exit(RunnerType& runner, std::istringstream& iss){
    /* NEEDED; executes before break the while in Commander::run() */

    std::cout << "Exiting the program..." << std::endl;
    return true;
}

bool cmd_open(RunnerType& runner, std::istringstream& iss){
    char* path = nullptr;
    iss >> path;
    if(!iss){
        return false;
    }
    bool result = runner.open(path);
    delete[] path;
    //reuse the variable path as file_name
    path = nullptr;
    runner.getFileName(path);
    if(result){
        std::cout << "Successfully opened " << path << std::endl;
    } else {
        std::cout << "Couldn't open " << path << std::endl;
    }
    delete[] path;
    return true;
}

bool cmd_close(RunnerType& runner, std::istringstream&){
    char* filename = nullptr;
    if(runner.close()){
        runner.getFileName(filename);
        if(filename == nullptr){
            std::cout << "There isn't a file to be closed." << std::endl;
        } else {
            std::cout << "Successfully closed " << filename << std::endl;
        }
        delete[] filename;
    }
    /*else {// never
        std::cout << "Couldn't close the file." << std::endl;
        return false;
    }*/
    return true;
}

bool cmd_save(RunnerType& runner, std::istringstream&){
    char* filename = nullptr;
    if(runner.save()){
        runner.getFileName(filename);
        if(filename == nullptr){
            std::cout << "There isn't a file to be saved." << std::endl;
        } else {
            std::cout << "Successfully saved " << filename << std::endl;
        }
        delete[] filename;
    }
    /*else {// never
        std::cout << "Couldn't save the file." << std::endl;
        return false;
    }*/
    return true;
}

bool cmd_save_as(RunnerType& runner, std::istringstream& iss){
    //TODO
    return true;
}

bool cmd_help(RunnerType&, std::istringstream&){
    std::cout << "Support the following commands:" << std::endl;
    for(unsigned i = 0; i < Commander::cmd_count; i++){
        Commander::outUsage(i, std::cout);
    }
    return true;
}

void build_commands(){
    Commander::add(Command("exit", "", "exit from the program", cmd_exit));
    Commander::add(Command("open", "<file>", "open the file at path <file>", cmd_open));
    Commander::add(Command("close", "", "close the currently opened file", cmd_close));
    Commander::add(Command("save", "", "save the current state of the program", cmd_save));
    Commander::add(Command("saveas", "<file>", "save the current state of the program in <file>", cmd_save_as));
    Commander::add(Command("help", "", "prints this information", cmd_help));
}