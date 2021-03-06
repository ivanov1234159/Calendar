//
// Created by toi on 01/04/2020.
//

#include "Program.hpp"
#include "MySpace.hpp"
#include "Commander.hpp"
#include <cstring>
//for: strchr()
#include <fstream>
//for: ifstream, ios::binary
#include <utility>
//for: swap()
#include <sstream>
//for: istringstream, ostringstream

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

String Program::getFileName(String const& path) const {
    if(path.empty() && !opened()){
        return String();
    }
    char const* file_path = path.get();
    if(path.empty()){
        file_path = m_calendar->getFilePath().get();
    }
    return Program::getNameFromPath(file_path);
}

bool Program::open(String const& file_path) {
    return open(file_path, m_calendar);
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
    std::ofstream ofs(m_calendar->getFilePath().get(), std::ios::binary);
    return m_calendar->serialize(ofs);
}

Calendar* Program::cloneCalendar() const {
    if(!opened()){
        return nullptr;
    }
    return new Calendar(*m_calendar);
}

bool Program::restoreCalendar(Calendar *cloned) {
    bool isOpen = opened();
    clear();
    m_calendar = cloned;
    return isOpen;
}

bool Program::book(Date const &date, Time const &start, Time const &end, String const& name, String const& note) {
    if(!opened()){
        return false;
    }
    return m_calendar->book(date, start, end, name, note);
}

bool Program::unbook(Date const &date, Time const &start, Time const &end) {
    if(!opened()){
        return false;
    }
    return m_calendar->unbook(date, start, end);
}

bool Program::agenda(Date const &date, std::ostream &out) const {
    if(!opened()){
        return false;
    }
    return m_calendar->agenda(date, out);
}

Pair<bool, bool> Program::changeDate(Date const &date, Time const &start, Date const &new_date) {
    if(!opened()){
        return { false, false };
    }
    Appointment* search = m_calendar->find(date, start);
    if(search == nullptr){
        return { false, false };
    }
    if(date != new_date && !m_calendar->isFree(new_date, search->getStartTime(), search->getEndTime())){
        return { false, true };
    }
    search->setDate(new_date);
    return { true, false };
}

Pair<bool, bool> Program::changeStartTime(Date const &date, Time const &start, Time const &new_start_time) {
    if(!opened()){
        return { false, false };
    }
    Appointment* search = m_calendar->find(date, start);
    if(search == nullptr){
        return { false, false };
    }
    if(new_start_time < search->getStartTime() && !m_calendar->isFree(date, new_start_time, search->getStartTime(-1))){
        return { false, true };
    }
    search->setStartTime(new_start_time);
    return { true, false };
}

Pair<bool, bool> Program::changeEndTime(Date const &date, Time const &start, Time const &new_end_time) {
    if(!opened()){
        return { false, false };
    }
    Appointment* search = m_calendar->find(date, start);
    if(search == nullptr){
        return { false, false };
    }
    if(new_end_time > search->getEndTime() && !m_calendar->isFree(date, search->getEndTime(1), new_end_time)){
        return { false, true };
    }
    search->setEndTime(new_end_time);
    return { true, false };
}

bool Program::changeName(Date const &date, Time const &start, String const &new_name) {
    if(!opened()){
        return false;
    }
    Appointment* search = m_calendar->find(date, start);
    if(search == nullptr){
        return false;
    }
    search->setName(new_name);
    return true;
}


bool Program::changeNote(Date const &date, Time const &start, String const &new_note) {
    if(!opened()){
        return false;
    }
    Appointment* search = m_calendar->find(date, start);
    if(search == nullptr){
        return false;
    }
    search->setNote(new_note);
    return true;
}

bool Program::findString(String const &needle, std::ostream &out) const {
    if(!opened()){
        return false;
    }
    return m_calendar->findString(needle, out);
}

bool Program::markAsHoliday(Date const &date) {
    if(!opened()){
        return false;
    }
    return m_calendar->holiday(date);
}

Pair<bool, Vector<Date>> Program::getBusyDays(Date const &from, Date const &to) const {
    if(!opened() || to < from){
        return { false, Vector<Date>(1, false) };
    }
    Vector<Pair<Date, int>> search = m_calendar->findBusyDays(from, to);
    //begin bubble sort
    bool any;
    unsigned end = search.size();
    do {
        any = false;
        for(unsigned i = 1; i < end; i++){
            if(search[i-1].right > search[i].right){
                std::swap(search[i-1], search[i]);
                any = true;
            }
        }
        if(any && end > 0){// "end > 0" is the same as "end != 0"
            end--;
        }
    } while (any);
    //end bubble sort
    Pair<bool, Vector<Date>> result;
    result.right = search.empty();
    for(unsigned i = 0; i < search.size(); i++){
        result.right.push(search[i].left);
    }
    return result;
}

Pair<Date, Time> Program::findSlot(Date const &from, Time const &duration, Calendar const* calendar) const {
    if(calendar == nullptr){
        calendar = m_calendar;
    }
    Date date = from;
    Time start;
    if(calendar != nullptr){// same as "opened()" when calendar is m_calendar
        for(; !calendar->findSlotAt(date, duration, start) && !start.max(); ++date)
            {}
    }
    return { date, start };
}

Pair<Date, Time> Program::findSlotWith(Date const &from, Time const &duration, Calendar const *calendar) const {
    if(calendar == nullptr || !opened()){
        return { from, Time() };
    }
    Time begin_time;
    Date date = from;
    for(Pair<Date, Time> this_result, other_result; /* no condition */ ; ++date){
        do{
            this_result = findSlot(date, duration);
            other_result = findSlot(date, duration, calendar);
            date = MySpace::max(this_result.left, other_result.left);
        } while (this_result.left != other_result.left);

        begin_time = MySpace::max(this_result.right, other_result.right);
        if(begin_time.max()){
            return { date, begin_time };
        }
        Time end_time = begin_time + duration;
        if(m_calendar->isFree(date, begin_time, end_time) && calendar->isFree(date, begin_time, end_time)){
            break;
        }
    }
    return { date, begin_time };
}

bool Program::mergeWith(Calendar *other_calendar, std::ostream &out, std::istream &in) {
    if(!opened() || other_calendar->isEmpty()){
        return false;
    }
    do {
        Appointment app = other_calendar->unshiftAppointment();
        if(m_calendar->isFree(app.getDate(), app.getStartTime(), app.getEndTime())){
            m_calendar->book(app);
            continue;
        } else if(app.isHoliday()){
            out << "An appointment is skipped because it it holiday and it isn't the only on that day." << std::endl;
            continue;
        }

        out << "The following appointment cannot be booked." << std::endl;
        out << app << std::endl;
        out << "Do you want to skip it? [y/n] ";
        String answer;
        in >> answer;
        if(!in){
            in.clear();
        }
        if(!answer.empty() && (answer[0] == 'Y' || answer[0] == 'y')){
            continue;
        }

        out << "Do you want to see all appointments for that day? [y/n] ";
        in >> answer;
        if(!in){
            in.clear();
        }
        if(!answer.empty() && (answer[0] == 'Y' || answer[0] == 'y')){
            std::ostringstream oss;
            oss << app.getDate();
            std::istringstream iss(oss.str());
            Commander::call("agenda", *this, iss, out);
        }

        Date date;
        Time start, end;
        for(; /* no condition */; ) {
            out << "Please, enter new date and time (start and end)." << std::endl;
            in >> date >> start >> end;
            if(!in){
                out << "Wrong format." << std::endl;
                out << "Format: <date> <start_time> <end_time>" << std::endl;
                continue;
            }
            if(m_calendar->isFree(date, start, end)){
                break;
            }
            out << "This date and time interval is NOT free." << std::endl;
        }
        app.setDate(date);
        app.setStartTime(start);
        app.setEndTime(end);
        m_calendar->book(app);
    } while (!other_calendar->isEmpty());
    return true;
}

bool Program::open(String const& file_path, Calendar*& calendar) {
    if(calendar != nullptr){
        return false;
    }
    std::ifstream ifs(file_path.get(), std::ios::binary);
    int temp_pos = ifs.tellg();
    if(!ifs.good() || ifs.seekg(0, ifs.end).tellg() == 0){
        std::ofstream ofs(file_path.get(), std::ios::binary);
        calendar = new Calendar(file_path);
        //ofs.close(); //this is done with (in) the destructor
        return true;
    }
    ifs.seekg(temp_pos);
    calendar = new Calendar(ifs, file_path);
    //ifs.close(); //this is done with (in) the destructor
    return true;
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