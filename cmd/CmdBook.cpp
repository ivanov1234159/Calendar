//
// Created by toi on 02/05/2020.
//

#include "CmdBook.hpp"
#include "../Commander.hpp"

CmdBook::CmdBook(): Command("book", "<date> <start_time> <end_time> <name> <comment>",
                            "create an appointment with <name> and <comment>\n on <date> with <start_time> and <end_time>") {}

bool CmdBook::action(RunnerType &runner, std::istringstream &iss) const {
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