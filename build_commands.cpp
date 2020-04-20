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

bool cmd_open(RunnerType& runner, std::istringstream& iss){
    char* path = nullptr;
    path = new char[Commander::BUFFER_SIZE];
    iss >> path;
    if(!iss){
        return false;
    }
    bool result = runner.open(path);
    char* file_name = nullptr;
    runner.getFileName(file_name, path);
    if(result){
        std::cout << "Successfully opened " << file_name << std::endl;
    } else {
        std::cout << "Couldn't open " << file_name << std::endl;
    }
    delete[] file_name;
    delete[] path;
    return true;
}

bool cmd_close(RunnerType& runner, std::istringstream&){
    char* filename = nullptr;
    runner.getFileName(filename);
    if(filename == nullptr){
        std::cout << "There isn't a file to be closed." << std::endl;
    } else {
        runner.close();
        std::cout << "Successfully closed " << filename << std::endl;
    }
    delete[] filename;
    return true;
}

bool cmd_save(RunnerType& runner, std::istringstream&){
    char* filename = nullptr;
    runner.getFileName(filename);
    if(filename == nullptr){
        std::cout << "There isn't a file to be saved." << std::endl;
    } else if(runner.save()) {
        std::cout << "Successfully saved " << filename << std::endl;
    } else {
        std::cout << "Couldn't save the file." << std::endl;
        delete[] filename;
        return false;
    }
    delete[] filename;
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

bool cmd_book(RunnerType& runner, std::istringstream& iss){
    if(!runner.opened()){
        std::cout << "There isn't an open file. Please, open one." << std::endl;
        return true;
    }
    Date date;
    iss >> date;
    if(!iss){
        std::cout << "Invalid date format. Cannot book an appointment." << std::endl;
        return false;
    }
    Time start;
    iss >> start;
    if(!iss){
        std::cout << "Invalid time format. Cannot book an appointment." << std::endl;
        return false;
    }
    Time end;
    iss >> end;
    if(!iss){
        std::cout << "Invalid time format. Cannot book an appointment." << std::endl;
        return false;
    }
    char name[Commander::BUFFER_SIZE];
    iss >> name;
    if(!iss){
        std::cout << "Couldn't read the name of an appointment. Cannot book an appointment." << std::endl;
        return false;
    }
    char note[Commander::BUFFER_SIZE];
    iss.getline(note, Commander::BUFFER_SIZE);
    if(!iss){
        std::cout << "Couldn't read the note of an appointment. Cannot book an appointment." << std::endl;
        return false;
    }
    if(runner.book(date, start, end, name, note)){
        std::cout << "The appointment was successfully added to the calendar." << std::endl;
    }else{
        std::cout << "This time interval isn't available on this date." << std::endl;
    }
    return true;
}

bool cmd_unbook(RunnerType& runner, std::istringstream& iss){
    if(!runner.opened()){
        std::cout << "There isn't an open file. Please, open one." << std::endl;
        return true;
    }
    Date date;
    iss >> date;
    if(!iss){
        std::cout << "Invalid date format. Cannot remove an appointment." << std::endl;
        return false;
    }
    Time start;
    iss >> start;
    if(!iss){
        std::cout << "Invalid time format. Cannot remove an appointment." << std::endl;
        return false;
    }
    Time end;
    iss >> end;
    if(!iss){
        std::cout << "Invalid time format. Cannot remove an appointment." << std::endl;
        return false;
    }
    if(runner.unbook(date, start, end)){
        std::cout << "The appointment was successfully removed from the calendar." << std::endl;
    }else{
        std::cout << "There isn't an appointment on this date at this time interval." << std::endl;
    }
    return true;
}

void build_commands(){
    Commander::add(Command("exit", "", "exit from the program", cmd_exit));
    Commander::add(Command("status", "", "prints information about the program status", cmd_status));
    Commander::add(Command("open", "<file>", "open the file at path <file>", cmd_open));
    Commander::add(Command("close", "", "close the currently opened file", cmd_close));
    Commander::add(Command("save", "", "save the current state of the program", cmd_save));
    Commander::add(Command("saveas", "<file>", "save the current state of the program in <file>", cmd_save_as));
    Commander::add(Command("help", "", "prints this information", cmd_help));
    Commander::add(Command("book", "<date> <start_time> <end_time> <name> <comment>",
                           "Save appointment time with <name> and <comment>\n on <date> with <start_time> and <end_time>", cmd_book));
    Commander::add(Command("unbook", "<date> <start_time> <end_time>",
                           "Meeting time canceled by <date> with <start_time> and <end_time>", cmd_unbook));
}