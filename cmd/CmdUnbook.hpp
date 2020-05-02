//
// Created by toi on 02/05/2020.
//

#ifndef CALENDAR_CMDUNBOOK_HPP
#define CALENDAR_CMDUNBOOK_HPP

#include "../Command.hpp"

class CmdUnbook : public Command {
public:
    CmdUnbook();
    virtual bool action(RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDUNBOOK_HPP
