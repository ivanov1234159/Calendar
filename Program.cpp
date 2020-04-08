//
// Created by toi on 01/04/2020.
//

#include "Program.hpp"

Program::Program(): m_calendar(nullptr) {}

Program::~Program() {
    clear();
}

bool Program::opened() const {
    return m_calendar != nullptr;
}

bool Program::open(char const *file_path) {
    if(opened()){
        return false;
    }
    m_calendar = new Calendar(file_path);
    return true;
}

bool Program::close(char *&file_name) {
    if(!opened()){
        return true;
    }
    if(file_name != nullptr){
        return false;
    }
    m_calendar->getName(file_name);
    clear();
    return true;
}

bool Program::save(char *&file_name) {
    if(!opened()){
        return true;
    }
    if(file_name != nullptr){
        return false;
    }
    m_calendar->getName(file_name);
    //TODO
    return true;
}

void Program::clear() {
    if(m_calendar != nullptr){
        delete m_calendar;
        m_calendar = nullptr;
    }
}