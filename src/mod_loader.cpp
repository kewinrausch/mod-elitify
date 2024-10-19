/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

// From SC
//
void AddElitify_CommandScript();
void AddElitify_PlayerScript();
void AddElitify_UnitScript();
void AddElitify_WorldScript();

// Add all
//
void Addmod_elitifyScripts()
{
    AddElitify_WorldScript();
    AddElitify_CommandScript();
    AddElitify_PlayerScript();
    AddElitify_UnitScript();
}

