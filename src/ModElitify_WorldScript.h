/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

#ifndef __MOD_ELITIFY_PLAYER_SCRIPT_H
#define __MOD_ELITIFY_PLAYER_SCRIPT_H

#include "ScriptMgr.h"

class ModElitify_WorldScript : public WorldScript
{
public:
    ModElitify_WorldScript()
        : WorldScript("ModElitify_WorldScript")
    {
    }

    void OnStartup() override;
};

#endif /* __MOD_ELITIFY_PLAYER_SCRIPT_H */
