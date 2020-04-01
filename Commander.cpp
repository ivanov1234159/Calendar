//
// Created by toi on 01/04/2020.
//

#include "Commander.hpp"
#include "MyFunctions.hpp"
#include <cstring>
//for: strcmp()

/* To add new command:
 *
 * !!! IMPORTANT !!!
 * ONLY value '{ "exit", nullptr }' MUST be in the list (Commander::cmd_list)
 *                                                  ; NEEDED for Commander::run()
 *      other values are optional
 *
 * Format:
 *      At the place of '"exit"' MUST be a char const* data type (CANNOT be nullptr), it is the name of the command
 *      The second is a list of all arguments       ; NEEDED for Commander::outUsage()
 *      The last is a note about the command        ; NEEDED for Commander::outUsage()
 *
 * !!! IMPORTANT !!!
 * In Commander::Commands (enum) the order MUST be the same as here
 *
 * !!! IMPORTANT !!!
 * Every value (command) in the list (Commander::cmd_list) MUST have a function
 *      which pointer is stored in Commander::cmd_func (IN THE SAME ORDER AS HERE)
 */
char const* Commander::cmd_list[][Commander::CMD_COUNT] = {
        { "open", "<file>", "open  the file at path <file>" },
        { "close", "", "close the currently opened file" },
        { "save", "", "save the current state of the program" },
        { "saveas", "<file>", "save the current state of the program in <file>" },
        { "help", "", "prints this information" },
        { "exit", "", "exit from the program" }
};

/* For all of the following functions:
 *      returns false if there is a problem with the arguments (their type or count)
 *
 * MUST handle the situation when the runner cannot do the operation
 */
bool cmd_exit(RunnerType&, std::istringstream&);
bool cmd_open(RunnerType&, std::istringstream&);
bool cmd_close(RunnerType&, std::istringstream&);
bool cmd_save(RunnerType&, std::istringstream&);
bool cmd_save_as(RunnerType&, std::istringstream&);
bool cmd_help(RunnerType&, std::istringstream&);

FuncCMD Commander::cmd_func[][Commander::CMD_COUNT] = {
    cmd_open, cmd_close, cmd_save, cmd_save_as, cmd_help, cmd_exit
};

int Commander::findIndex(char const* cmd){
    for (unsigned i = 0; i < Commander::CMD_COUNT; i++){
        if(std::strcmp(Commander::cmd_list[i][0], cmd) == 0){
            return i;
        }
    }
    return -1;
}

void Commander::outUsage(unsigned index, std::ostream& out){
    out << Commander::cmd_list[index][0]
        << ' ' << Commander::cmd_list[index][1] << std::endl
        << '\t' << Commander::cmd_list[index][2] << std::endl;
}

void Commander::run(RunnerType& runner) {
    while (true){
        char buffer[Commander::BUFFER_SIZE];
        //char* buffer = new char[Commander::BUFFER_SIZE];
        std::cin.getline(buffer, Commander::BUFFER_SIZE);
        std::istringstream iss(buffer);
        //delete[] buffer;
        char* cmd;
        iss >> cmd;
        int index = Commander::findIndex(cmd);
        if(index >= 0){
            if(!Commander::cmd_func[index](runner, iss)){
                commander_error(false);
                Commander::outUsage(index, std::cout);
            }
            if(index == Commander::EXIT){
                break;
            }
        } else {
            commander_error();
        }
    }
}

void commander_error(bool print_help = true){
    std::cout << "Invalid command!";
    if(print_help){
        std::cout << " Type 'help' for more information.";
    }
    std::cout << std::endl;
}

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
    if(runner.open(path)){
        std::cout << "Successfully opened " << path << std::endl;
    } else {
        std::cout << "Couldn't open " << path << std::endl;
    }
    return true;
}

bool cmd_close(RunnerType& runner, std::istringstream&){
    char* filename = nullptr;
    if(runner.close(filename)){
        if(filename == nullptr){
            std::cout << "There isn't a file to be closed." << std::endl;
        }else{
            std::cout << "Successfully closed " << filename << std::endl;
        }
    } else {// never
        std::cout << "Couldn't close the file." << std::endl;
        return false;
    }
    return true;
}

bool cmd_save(RunnerType& runner, std::istringstream& iss){
    //TODO
    return true;
}

bool cmd_save_as(RunnerType& runner, std::istringstream& iss){
    //TODO
    return true;
}

bool cmd_help(RunnerType&, std::istringstream&){
    std::cout << "Support the following commands:" << std::endl;
    for(unsigned i = 0; i < Commander::CMD_COUNT; i++){
        Commander::outUsage(i, std::cout);
    }
    return true;
}