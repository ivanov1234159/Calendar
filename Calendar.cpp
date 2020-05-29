//
// Created by toi on 29/03/2020.
//

#include "Calendar.hpp"
#include "MySpace.hpp"

Calendar::Calendar(String const& calendar_path): m_file_path(calendar_path) {}

Calendar::Calendar(std::ifstream &ifs, String const& calendar_path): m_file_path(calendar_path) {
    unsigned size;
    ifs.read((char*) &size, sizeof(size));
    m_list = Vector<Appointment>(size);
    for(unsigned i = 0; i < size; i++){
        m_list.push(Appointment(ifs));
    }
}

String const& Calendar::getFilePath() const {
    return m_file_path;
}

bool Calendar::serialize(std::ofstream &ofs) const {
    unsigned size = m_list.size();
    ofs.write((char const*) &size, sizeof(size));
    for(unsigned i = 0; i < size; i++){
        if(!m_list[i].serialize(ofs)){
            break;
        }
    }
    return ofs.good();
}

bool Calendar::book(Date const &date, Time const &start, Time const &end, String const& name, String const& note) {
    if(!isFree(date, start, end)){
        return false;
    }
    book(Appointment(name, note, date, start, end));
    return true;
}

bool Calendar::unbook(Date const &date, Time const &start, Time const &end) {
    Appointment* search = find(date, start, end);
    if(search == nullptr){
        return false;
    }
    Appointment* last = &m_list[-1];
    while (search < last){
        *search = *(search+1);
        search++;
    }
    *last = Appointment();
    return true;
}

void Calendar::agenda(Date const &date, std::ostream& out) {
    for(unsigned i = 0; i < m_list.size(); i++){
        if(m_list[i].getDate() != date){
            continue;
        }
        out << m_list[i] << std::endl;
    }
}

bool Calendar::findString(String const &needle, std::ostream &out) {
    bool any = false;
    for(unsigned i = 0; i < m_list.size(); i++){
        if(m_list[i].getName().contains(needle) || m_list[i].getNote().contains(needle)){
            out << m_list[i];
            any = true;
        }
    }
    return any;
}

//TODO

Appointment* Calendar::find(Date const &date, Time const &start) {
    for(unsigned i = 0; i < m_list.size(); i++){
        if(m_list[i].getDate() == date && m_list[i].getStartTime() == start){
            return &m_list[i];
        }
    }
    return nullptr;
}

void Calendar::book(Appointment const &app) {
    //m_list.push(app);
    //to end: sorted insert
    m_list.push(Appointment());
    Appointment* search = &m_list[0];
    for(unsigned i = 1; i < m_list.size(); i++){
        if(m_list[i].getDate() >= app.getDate()){
            if(m_list[i].getDate() > app.getDate() || m_list[i].getStartTime() > app.getStartTime()){
                break;
            }
        }
        search = &m_list[i];
    }
    Appointment* last = &m_list[-1];
    if(search < last){// more important is that they are not equal
        search++;
    }
    while(search < last){
        *last = *(last-1);
        last--;
    }
    *search = app;
}

bool Calendar::isFree(Date const &date, Time const &start, Time const &end) const {
    for(unsigned i = 0; i < m_list.size(); i++){
        if(m_list[i].getDate() != date){
            continue;
        }
        if(m_list[i].getStartTime() >= start && m_list[i].getStartTime() <= end){
            return false;
        }
        if(m_list[i].getStartTime() <= start && m_list[i].getEndTime() > start){
            return false;
        }
    }
    return true;
}

Appointment* Calendar::find(Date const &date, Time const &start, Time const &end) {
    for(unsigned i = 0; i < m_list.size(); i++){
        if(m_list[i].getDate() == date && m_list[i].getStartTime() == start && m_list[i].getEndTime() == end){
            return &m_list[i];
        }
    }
    return nullptr;
}