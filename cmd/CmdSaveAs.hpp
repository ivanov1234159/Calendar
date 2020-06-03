//
// Created by toi on 02/05/2020.
//

#ifndef CALENDAR_CMDSAVEAS_HPP
#define CALENDAR_CMDSAVEAS_HPP

#include "../Command.hpp"

class CmdSaveAs : public Command {
public:
    CmdSaveAs();
    virtual bool action(std::ostream& out, RunnerType& runner, std::istringstream& iss) const override;
};

#endif //CALENDAR_CMDSAVEAS_HPP
