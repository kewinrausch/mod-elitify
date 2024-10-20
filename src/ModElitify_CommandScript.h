/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

#ifndef __MOD_ELITIFY_COMMAND_SCRIPT_H
#define __MOD_ELITIFY_COMMAND_SCRIPT_H

#include <vector>

#include "ScriptMgr.h"
#include "Chat.h"

using namespace Acore::ChatCommands;

class ModElitify_CommandScript : public CommandScript
{
public:
    ModElitify_CommandScript() : CommandScript("ModElitify_CommandScript")
    {

    }

    //
    // Commands table
    //

    std::vector<ChatCommand> GetCommands() const override;

    //
    // Commands handled
    //

    static bool HandleOnCommand     (ChatHandler* handler, const char* args);
    static bool HandleOffCommand    (ChatHandler* handler, const char* args);
    static bool HandleScaleCommand  (ChatHandler* handler, const char* args);
    static bool HandleRenCommand    (ChatHandler* handler, const char* args);
    static bool HandleFactCommand   (ChatHandler* handler, const char* args);
    static bool HandleDisplayCommand(ChatHandler* handler, const char* args);
    static bool HandleSetCommand    (ChatHandler* handler, const char* args);
    static bool HandleSet           (Unit* unit, float factor);
};

#endif /* __MOD_ELITIFY_COMMAND_SCRIPT_H */
