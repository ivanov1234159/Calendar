//
// Created by toi on 29/03/2020.
//

#include "Calendar.hpp"
#include "MyFunctions.hpp"

Calendar::Calendar(const char *calendar_name): m_name(nullptr), m_list(nullptr), m_size(0), m_limit(2) {
    mem_copy(m_name, calendar_name, false);
    m_list = new Appointment[m_limit];
}

Calendar::Calendar(Calendar const &other) {
    copy(other);
}

Calendar& Calendar::operator=(Calendar const &other) {
    if(this != &other){
        clear();
        copy(other);
    }
    return *this;
}

Calendar::~Calendar() {
    clear();
}

bool Calendar::empty() const {
    return m_size == 0;
}

bool Calendar::full() const {
    return m_size == m_limit;
}

bool Calendar::book(Date const &date, Time const &start, Time const &end, char const *name, char const *note) {
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
    Appointment* last = &m_list[--m_size];
    while (search < last){
        *search = *(search+1);
        search++;
    }
    last = Appointment();
    return true;
}

void Calendar::agenda(Date const &date, std::ostream& out) {
    for(unsigned i = 0; i < m_size; i++){
        if(m_list[i].getDate() != date){
            continue;
        }
        out << m_list[i] << std::endl;
    }
}

//TODO

void Calendar::book(Appointment const &app) {
    if(full()){
        resize();
    }
    //m_list[m_size++] = app;
    //to end: sorted insert
    Appointment* search = &m_list[0];
    for(unsigned i = 1; i < m_size; i++){
        if(m_list[i].getDate() >= app.getDate()){
            if(m_list[i].getDate() > app.getDate() || m_list[i].getStartTime() > app.getStartTime()){
                break;
            }
        }
        search = &m_list[i];
    }
    search++;
    Appointment* last = &m_list[m_size];
    while(search < last){
        *last = *(last-1);
        last--;
    }
    *search = app;
    m_size++;
}

void Calendar::clear() {
    if(m_name != nullptr){
        delete[] m_name;
        m_name = nullptr;
    }
    if(m_list != nullptr){
        delete[] m_list;
        m_list = nullptr;
    }
}

void Calendar::copy(Calendar const &other) {
    mem_copy(m_name, other.m_name);
    m_size = other.m_size;
    m_limit = other.m_limit;
    if(m_list != nullptr){
        delete[] m_list;
    }
    m_list = new Appointment[m_limit];
    for(unsigned i = 0; i < m_size; i++){
        m_list[i] = other.m_list[i];
    }
}

void Calendar::resize() {
    m_limit *= 2;
    Appointment* temp = m_list;
    m_list = new Appointment[m_limit];
    for(unsigned i = 0; i < m_size; i++){
        m_list[i] = temp[i];
    }
}

bool Calendar::isFree(Date const &date, Time const &start, Time const &end) const {
    for(unsigned i = 0; i < m_size; i++){
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
    for(unsigned i = 0; i < m_size; i++){
        if(m_list[i].getDate() == date && m_list[i].getStartTime() == start && m_list[i].getStartTime() == end){
            return &m_list[i];
        }
    }
    return nullptr;
}