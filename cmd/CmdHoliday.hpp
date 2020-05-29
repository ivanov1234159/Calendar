//
// Created by toi on 29/05/2020.
//

#ifndef CALENDAR_CMDHOLIDAY_HPP
#define CALENDAR_CMDHOLIDAY_HPP

#include "../Command.hpp"

class CmdHoliday : public Command {
public:
    CmdHoliday();
    virtual bool action(RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDHOLIDAY_HPP
