//
// Created by toi on 08/04/2020.
//

#include "Commander.hpp"
#include "CmdAgenda.hpp"
#include "CmdBook.hpp"
#include "CmdBusydays.hpp"
#include "CmdChange.hpp"
#include "CmdClose.hpp"
#include "CmdExit.hpp"
#include "CmdFind.hpp"
#include "CmdFindSlot.hpp"
#include "CmdFindSlotWith.hpp"
#include "CmdHelp.hpp"
#include "CmdHoliday.hpp"
#include "CmdMerge.hpp"
#include "CmdOpen.hpp"
#include "CmdSave.hpp"
#include "CmdSaveAs.hpp"
#include "CmdUnbook.hpp"

void build_commands(){
    Commander::add(new CmdAgenda);
    Commander::add(new CmdBook);
    Commander::add(new CmdBusydays);
    Commander::add(new CmdChange);
    Commander::add(new CmdClose);
    Commander::add(new CmdExit);
    Commander::add(new CmdFind);
    Commander::add(new CmdFindSlot);
    Commander::add(new CmdFindSlotWith);
    Commander::add(new CmdHelp);
    Commander::add(new CmdHoliday);
    Commander::add(new CmdMerge);
    Commander::add(new CmdOpen);
    Commander::add(new CmdSave);
    Commander::add(new CmdSaveAs);
    Commander::add(new CmdUnbook);
}


