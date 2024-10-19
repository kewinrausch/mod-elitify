/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

#include "Chat.h"
#include "Config.h"
#include "SharedDefines.h"

#include "ModElitify.h"
#include "ModElitify_PlayerScript.h"

void ModElitify_PlayerScript::OnLogin(Player* Player)
{
    if (Logo)
    {
        ChatHandler(Player->GetSession()).SendSysMessage("This server is running the |cff4CFF00Elitify |rmodule.");
    }
}

void AddElitify_PlayerScript()
{
    new ModElitify_PlayerScript();
}
