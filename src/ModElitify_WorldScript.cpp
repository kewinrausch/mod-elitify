/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

#include "Config.h"

#include "ModElitify.h"
#include "ModElitify_WorldScript.h"

void ModElitify_WorldScript::OnStartup()
{
    //
    // Load the global configuration for the module
    //

    LOG_INFO("ModElitify", "Initializing the Elitify module...");

    Enabled = sConfigMgr->GetOption<int>("Elitify.Enabled", 0);
    Logo    = sConfigMgr->GetOption<int>("Elitify.Logo"   , 1);
    Debug   = sConfigMgr->GetOption<int>("Elitify.Debug"  , 0);
}

void AddElitify_WorldScript()
{
    new ModElitify_WorldScript();
}
