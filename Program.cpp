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

String const& Program::getFileName(String const& path) const {
    if(path.empty() && !opened()){
        return String();
    }
    char const* file_path = path.get();
    if(path.empty()){
        file_path = m_calendar->getFilePath();
    }
    return Program::getNameFromPath(file_path);
}

bool Program::open(String const& file_path) {
    if(opened()){
        return false;
    }
    std::ifstream ifs(file_path.get(), std::ios::binary);
    int temp_pos = ifs.tellg();
    if(!ifs.good() || ifs.seekg(0, ifs.end).tellg() == 0){
        std::ofstream ofs(file_path.get(), std::ios::binary);
        m_calendar = new Calendar(file_path);
        //ofs.close(); //this is done with (in) the destructor
        return true;
    }
    ifs.seekg(temp_pos);
    m_calendar = new Calendar(ifs, file_path);
    //ifs.close(); //this is done with (in) the destructor
    return true;
}

void Program::close() {
    if(opened()){
        clear();
    }
}

bool Program::save() const {
    if(!opened()){
        return true;
    }
    std::ofstream ofs(m_calendar->getFilePath(), std::ios::binary);
    return m_calendar->serialize(ofs);
}

bool Program::book(Date const &date, Time const &start, Time const &end, String const& name, String const& note) {
    return m_calendar->book(date, start, end, name, note);
}

bool Program::unbook(Date const &date, Time const &start, Time const &end) {
    return m_calendar->unbook(date, start, end);
}

String Program::getNameFromPath(char const *file_path) {
    if(file_path == nullptr){
        return String();
    }
    char delimiter = '\0';
    if(std::strchr(file_path, '/') != nullptr){
        delimiter = '/';
    }else if(std::strchr(file_path, '\\') != nullptr){
        delimiter = '\\';
    }
    if(delimiter == '\0' || (delimiter == '/' && std::strchr(file_path, '\\') != nullptr)){
        return String(file_path);
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
    return String(last);
}

void Program::clear() {
    if(m_calendar != nullptr){
        delete m_calendar;
        m_calendar = nullptr;
    }
}