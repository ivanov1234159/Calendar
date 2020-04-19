//
// Created by toi on 01/04/2020.
//

#include "Program.hpp"
#include "MySpace.hpp"
#include <cstring>
//for: strchr()
#include <fstream>
//for: ifstream, ios::binary

Program& Program::self(){
    static Program p;
    return p;
}

Program::Program(): m_calendar(nullptr) {}

Program::~Program() {
    clear();
}

bool Program::opened() const {
    return m_calendar != nullptr;
}

void Program::getFileName(char*& file_name, char* path) const {
    if(path == nullptr && !opened()){
        return;
    }
    char* file_path = path;
    if(path == nullptr){
        m_calendar->getFilePath(file_path);
    }
    Program::getNameFromPath(file_path, file_name);
    if(path == nullptr){
        delete[] file_path;
    }
}

bool Program::open(char const *file_path) {
    if(opened()){
        return false;
    }
    std::ifstream ifs(file_path, std::ios::binary);
    if(!ifs.good() || ifs.seekg(0, ifs.end).tellg() == 0){
        std::ofstream ofs(file_path, std::ios::binary);
        m_calendar = new Calendar(file_path);
        //ofs.close(); //this is done with (in) the destructor
        return true;
    }
    ifs.seekg(0, ifs.beg);
    m_calendar = new Calendar(ifs);
    //ifs.close(); //this is done with (in) the destructor
    return true;
}

void Program::close() {
    if(opened()){
        clear();
    }
}

bool Program::save() {
    if(!opened()){
        return true;
    }
    char* file_path = nullptr;
    m_calendar->getFilePath(file_path);
    std::ofstream ofs(file_path, std::ios::binary);
    delete[] file_path;
    return m_calendar->serialize(ofs);
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
        MySpace::mem_copy(file_name, file_path, false);
        return;
    }
    char const* temp = nullptr;
    char const* last = nullptr;
    do{
        last = temp;
        if(last != nullptr){
            temp = std::strchr(last, delimiter);
        }else{
            temp = std::strchr(file_path, delimiter);
        }
        if(temp != nullptr && *temp == delimiter){
            temp++;
        }
    }while(temp != nullptr);
    MySpace::mem_copy(file_name, last, false);
}

void Program::clear() {
    if(m_calendar != nullptr){
        delete m_calendar;
        m_calendar = nullptr;
    }
}