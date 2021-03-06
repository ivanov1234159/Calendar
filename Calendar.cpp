//
// Created by toi on 29/03/2020.
//

#include "Calendar.hpp"
#include "MySpace.hpp"

static const unsigned DAY_START_AT_HOUR = 8;
static const unsigned DAY_END_AT_HOUR = 17;
static const unsigned SEC_IN_HOUR = 3600;

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

void Calendar::setFilePath(String const &path) {
    m_file_path = path;
}

bool Calendar::isEmpty() const {
    return m_list.empty();
}

Appointment Calendar::unshiftAppointment() {
    return m_list.unshift();
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

bool Calendar::agenda(Date const &date, std::ostream& out) const {
    bool any = false;
    for(unsigned i = 0; i < m_list.size(); i++){
        if(m_list[i].getDate() != date){
            continue;
        }
        out << m_list[i] << std::endl;
        any = true;
    }
    return any;
}

bool Calendar::findString(String const &needle, std::ostream &out) const {
    bool any = false;
    for(unsigned i = 0; i < m_list.size(); i++){
        if(m_list[i].getName().contains(needle) || m_list[i].getNote().contains(needle)){
            out << m_list[i] << std::endl;
            any = true;
        }
    }
    return any;
}

bool Calendar::holiday(Date const &date) {
    if(!isFree(date, Time(), Time::MAX_TIME)){
        return false;
    }
    Appointment app = Appointment("HOLIDAY", "", date, Time(), Time::MAX_TIME);
    app.setHoliday();
    book(app);
    return true;
}

Vector<Pair<Date, int>> Calendar::findBusyDays(Date const &from, Date const &to) const {
    Vector<Pair<Date, int>> result;
    for(unsigned i = 0; i < m_list.size(); i++){
        Date const& current = m_list[i].getDate();
        if(current < from || current > to || m_list[i].isHoliday()){
            continue;
        }

        int diff = m_list[i].getEndTime().difference(m_list[i].getStartTime());
        bool any = false;
        for(unsigned j = 0; j < result.size() ; j++){
            if(result[j].left == current){
                result[j].right += diff;
                any = true;
                break;
            }
        }
        if(!any){
            result.push({ current, diff });
        }
    }
    return result;
}

bool Calendar::findSlotAt(Date const &date, Time const &duration, Time &begin) const {
    static const Time end_time = Time(DAY_END_AT_HOUR * SEC_IN_HOUR);
    if(isHoliday(date)){
        return false;
    }
    if(duration > Time((DAY_END_AT_HOUR - DAY_START_AT_HOUR) * SEC_IN_HOUR)){
        begin = Time::MAX_TIME;
        return false;
    }
    begin = Time(DAY_START_AT_HOUR * SEC_IN_HOUR);
    for(Appointment const* search = nullptr; ; ){
        search = findFirst(date, begin, begin + duration);
        if (search == nullptr) {
            break;
        }
        begin = search->getEndTime(1);
        if (begin + duration > end_time) {
            return false;
        }
    }
    return true;
}

Appointment* Calendar::find(Date const &date, Time const &start) const {
    for(unsigned i = 0; i < m_list.size(); i++){
        if(m_list[i].getDate() == date && m_list[i].getStartTime() == start){
            return const_cast<Appointment*>(&m_list[i]);
        }
    }
    return nullptr;
}

bool Calendar::isFree(Date const &date, Time const &start, Time const &end) const {
    return findFirst(date, start, end) == nullptr;
}

bool Calendar::isHoliday(Date const &date) const {
    Appointment* search = find(date, Time());
    if(search == nullptr){
        return false;
    }
    return search->isHoliday();
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

Appointment* Calendar::find(Date const &date, Time const &start, Time const &end) {
    for(unsigned i = 0; i < m_list.size(); i++){
        if(m_list[i].getDate() == date && m_list[i].getStartTime() == start && m_list[i].getEndTime() == end){
            return &m_list[i];
        }
    }
    return nullptr;
}

Appointment const* Calendar::findFirst(Date const &date, Time const &start, Time const &end) const {
    for(unsigned i = 0; i < m_list.size(); i++){
        if(m_list[i].getDate() != date){
            continue;
        }
        if(m_list[i].isHoliday()){
            return &m_list[i];
        }
        if(m_list[i].getStartTime() >= start && m_list[i].getStartTime() <= end){
            return &m_list[i];
        }
        if(m_list[i].getStartTime() <= start && m_list[i].getEndTime() > start){
            return &m_list[i];
        }
    }
    return nullptr;
}