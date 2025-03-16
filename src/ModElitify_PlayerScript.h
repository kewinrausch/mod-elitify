/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

#ifndef __MOD_ELITIFY_PLAYER_SCRIPT_H
#define __MOD_ELITIFY_PLAYER_SCRIPT_H

#include "Player.h"
#include "ScriptMgr.h"
#include "Unit.h"

class ModElitify_PlayerScript : public PlayerScript
{
public:
    ModElitify_PlayerScript()
        : PlayerScript("ModElitify_PlayerScript")
    {
    }

    void OnPlayerLogin(Player* Player) override;
};

#endif /* __MOD_ELITIFY_PLAYER_SCRIPT_H */
