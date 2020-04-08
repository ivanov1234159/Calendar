//
// Created by toi on 01/04/2020.
//

#include "Program.hpp"
#include "MyFunctions.hpp"
#include <cstring>
//for: strchr()

Program::Program(): m_calendar(nullptr) {}

Program::~Program() {
    clear();
}

bool Program::opened() const {
    return m_calendar != nullptr;
}

void Program::getFileName(char*& file_name) const {
    return m_calendar->getName(file_name);
}

bool Program::open(char const *file_path) {
    if(opened()){
        return false;
    }
    char* temp = nullptr;
    Program::getNameFromPath(file_path, temp);
    m_calendar = new Calendar(temp);
    delete[] temp;
    return true;
}

bool Program::close() {
    if(!opened()){
        return true;
    }
    clear();
    return true;
}

bool Program::save() {
    if(!opened()){
        return true;
    }
    //TODO
    return true;
}

void Program::getNameFromPath(char const *file_path, char *&file_name) {
    if(file_path == nullptr || file_name != nullptr){
        return;
    }
    char delimiter = '\0';
    if(std::strchr(file_path, '/') != nullptr){
        delimiter = '/';
    }else if(std::strchr(file_path, '\\') != nullptr){
        delimiter = '\\';
    }
    if(delimiter == '\0' || (delimiter == '/' && std::strchr(file_path, '\\') != nullptr)){
        mem_copy(file_name, file_path, false);
        return;
    }
    char const* temp = nullptr;
    char const* last = nullptr;
    do{
        last = temp;
        temp = std::strchr(file_path, delimiter);
    }while(temp != nullptr);
    mem_copy(file_name, last, false);
}

void Program::clear() {
    if(m_calendar != nullptr){
        delete m_calendar;
        m_calendar = nullptr;
    }
}