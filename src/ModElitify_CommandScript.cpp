/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

#include <map>
#include <string>

#include "Config.h"
#include "Creature.h"
#include "ObjectGuid.h"
#include "Player.h"
#include "Unit.h"

#include "ModElitify.h"
#include "ModElitify_CommandScript.h"

using namespace Acore::ChatCommands;

std::vector<ChatCommand> ModElitify_CommandScript::GetCommands() const
{
    //
    // Provides the console command options
    //

    static std::vector<Acore::ChatCommands::ChatCommandBuilder> ElitifyCommandTable =
    {
        { "on"     , HandleOnCommand     , SEC_ADMINISTRATOR, Acore::ChatCommands::Console::Yes },
        { "off"    , HandleOffCommand    , SEC_ADMINISTRATOR, Acore::ChatCommands::Console::Yes },
        { "level"  , HandleLevelCommand  , SEC_GAMEMASTER   , Acore::ChatCommands::Console::Yes },
        { "ren"    , HandleRenCommand    , SEC_GAMEMASTER   , Acore::ChatCommands::Console::Yes },
        { "scale"  , HandleScaleCommand  , SEC_GAMEMASTER   , Acore::ChatCommands::Console::Yes },
        { "fact"   , HandleFactCommand   , SEC_GAMEMASTER   , Acore::ChatCommands::Console::Yes },
        { "display", HandleDisplayCommand, SEC_GAMEMASTER   , Acore::ChatCommands::Console::Yes },
        { "set"    , HandleSetCommand    , SEC_GAMEMASTER   , Acore::ChatCommands::Console::Yes }
    };

    static std::vector<Acore::ChatCommands::ChatCommandBuilder> commandTable =
    {
        { "elitify", ElitifyCommandTable },
        { "efy"    , ElitifyCommandTable },
    };

    return commandTable;
}

bool ModElitify_CommandScript::HandleOnCommand(ChatHandler* handler, const char* /*args*/)
{
    Enabled = true;

    handler->PSendSysMessage("This module has been enabled");
    return true;
}

bool ModElitify_CommandScript::HandleOffCommand(ChatHandler* handler, const char* /*args*/)
{
    Enabled = false;

    handler->PSendSysMessage("This module has been disabled");
    return true;
}

bool ModElitify_CommandScript::HandleLevelCommand(ChatHandler* handler, const char* args)
{
    //
    // Do not respond to commands if disabled
    //

    if (!Enabled)
    {
        handler->PSendSysMessage("This module is disabled");
        return true;
    }

    //
    // Extracts the level to apply
    //

    char* opt = strtok((char*)args, " ");

    if (!opt)
    {
        handler->PSendSysMessage("Invalid syntax");
        handler->PSendSysMessage("The accepted command is: efy level <number>");
        return true;
    }

    uint32 level = (uint32)strtoul(opt, NULL, 0);

    if (level <= 0 || level > 255)
    {
        handler->PSendSysMessage("Invalid level");
        return true;
    }

    //
    // Applies the level
    //

    Unit* targetUnit = handler->getSelectedUnit();

    if (targetUnit)
    {
        targetUnit->SetLevel((uint8)level);
    }

    return true;
}

bool ModElitify_CommandScript::HandleRenCommand(ChatHandler* handler, const char* args)
{
    //
    // Do not respond to commands if disabled
    //

    if (!Enabled)
    {
        handler->PSendSysMessage("This module is disabled");
        return true;
    }

    //
    // Verify the name
    //

    if (strlen((char*)args) <= 0)
    {
        handler->PSendSysMessage("Invalid syntax");
        handler->PSendSysMessage("The accepted command is: efy ren <name>");

        return true;
    }

    //
    // Apply the renaming
    //

    Unit* targetUnit = handler->getSelectedUnit();

    if (targetUnit)
    {
        targetUnit->SetName(args);
    }

    return true;
}

bool ModElitify_CommandScript::HandleFactCommand(ChatHandler* handler, const char* args)
{
    //
    // Do not respond to commands if disabled
    //

    if (!Enabled)
    {
        handler->PSendSysMessage("This module is disabled");
        return true;
    }

    Unit* targetUnit = handler->getSelectedUnit();

    //
    // Extracts or show the faction id
    //

    char* opt = strtok((char*)args, " ");

    if (!opt)
    {
        if (!targetUnit)
        {
            handler->PSendSysMessage("You need to specify a faction or target a creature");
            return true;
        }
        else
        {
            handler->PSendSysMessage("Target on faction {}", targetUnit->GetFaction());
            return true;
        }
    }

    uint32 fId = (uint32)strtoul(opt, NULL, 0);

    //
    // Apply the faction to the unit
    //

    if (targetUnit)
    {
        targetUnit->SetFaction(fId);
    }

    return true;
}

bool ModElitify_CommandScript::HandleScaleCommand(ChatHandler* handler, const char* args)
{
    //
    // Do not respond to commands if disabled
    //

    if (!Enabled)
    {
        handler->PSendSysMessage("This module is disabled");
        return true;
    }

    //
    // Extracts the scaling factor to apply (can be positive or negative)
    //

    char* opt = strtok((char*)args, " ");

    if (!opt)
    {
        handler->PSendSysMessage("Invalid syntax");
        handler->PSendSysMessage("The accepted command is: efy <scaling_factor>");

        return true;
    }

    float f = std::stof(opt);

    if (f <= 0)
    {
        handler->PSendSysMessage("Scaling factor must be higher than zero");
        return true;
    }

    //
    // Scale the object appearance scale
    //

    Unit* targetUnit = handler->getSelectedUnit();

    if (targetUnit)
    {
        targetUnit->SetObjectScale(f);
    }

    return true;
}

bool ModElitify_CommandScript::HandleDisplayCommand(ChatHandler* handler, const char* args)
{
    //
// Do not respond to commands if disabled
//

    if (!Enabled)
    {
        handler->PSendSysMessage("This module is disabled");
        return true;
    }

    //
    // Extracts the scaling factor to apply (can be positive or negative)
    //

    char* opt = strtok((char*)args, " ");

    if (!opt)
    {
        handler->PSendSysMessage("Invalid syntax");
        handler->PSendSysMessage("The accepted command is: efy display <id>");

        return true;
    }

    uint32 dId = (uint32)strtoul(opt, NULL, 0);

    //
    // Scale the object appearance scale
    //

    Unit* targetUnit = handler->getSelectedUnit();

    if (targetUnit)
    {
        targetUnit->SetDisplayId(dId, 1.0f);
        targetUnit->SetNativeDisplayId(dId);
    }

    return true;
}


bool ModElitify_CommandScript::HandleSetCommand(ChatHandler* handler, const char* args)
{
    //
    // Do not respond to commands if disabled
    //

    if (!Enabled)
    {
        handler->PSendSysMessage("This module is disabled");
        return true;
    }

    Unit* targetUnit = handler->getSelectedUnit();

    //
    // Extracts the scaling factor to apply (can be positive or negative)
    //

    char* opt = strtok((char*)args, " ");

    if (!opt)
    {
        handler->PSendSysMessage("Invalid syntax");
        handler->PSendSysMessage("The accepted command is: elitify <scaling_factor>");

        return true;
    }

    float f = std::stof(opt);

    //
    // Check the value
    //

    if (f == 0)
    {
        handler->PSendSysMessage("Invalid factor; must be different than zero");
        return true;
    }

    //
    // Determine what to do depending on the selected unit
    //

    if (targetUnit)
    {
        return HandleSet(targetUnit, f);
    }

    //
    // Target is not valid
    //

    handler->PSendSysMessage("Invalid target");
    return true;
}

bool ModElitify_CommandScript::HandleSet(Unit* unit, float factor)
{
    //
    // Save the original stats for the unit
    //

    ObjectGuid id = unit->GetGUID();

    //
    // Save the original values before edit, to restore them
    //

    if (stats.count(id) == 0)
    {
        stats[id][UNIT_MOD_STAT_STRENGTH]       [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_STAT_STRENGTH       , BASE_VALUE);
        stats[id][UNIT_MOD_STAT_AGILITY]        [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_STAT_AGILITY        , BASE_VALUE);
        stats[id][UNIT_MOD_STAT_STAMINA]        [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_STAT_STAMINA        , BASE_VALUE);
        stats[id][UNIT_MOD_STAT_INTELLECT]      [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_STAT_INTELLECT      , BASE_VALUE);
        stats[id][UNIT_MOD_STAT_SPIRIT]         [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_STAT_SPIRIT         , BASE_VALUE);
        stats[id][UNIT_MOD_HEALTH]              [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_HEALTH              , BASE_VALUE);
        stats[id][UNIT_MOD_MANA]                [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_MANA                , BASE_VALUE);
        stats[id][UNIT_MOD_RAGE]                [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_RAGE                , BASE_VALUE);
        stats[id][UNIT_MOD_FOCUS]               [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_FOCUS               , BASE_VALUE);
        stats[id][UNIT_MOD_ENERGY]              [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_ENERGY              , BASE_VALUE);
        stats[id][UNIT_MOD_HAPPINESS]           [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_HAPPINESS           , BASE_VALUE);
        stats[id][UNIT_MOD_RUNE]                [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_RUNE                , BASE_VALUE);
        stats[id][UNIT_MOD_RUNIC_POWER]         [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_RUNIC_POWER         , BASE_VALUE);
        stats[id][UNIT_MOD_ARMOR]               [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_ARMOR               , BASE_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_HOLY]     [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_RESISTANCE_HOLY     , BASE_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_FIRE]     [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_RESISTANCE_FIRE     , BASE_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_NATURE]   [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_RESISTANCE_NATURE   , BASE_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_FROST]    [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_RESISTANCE_FROST    , BASE_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_SHADOW]   [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_RESISTANCE_SHADOW   , BASE_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_ARCANE]   [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_RESISTANCE_ARCANE   , BASE_VALUE);
        stats[id][UNIT_MOD_ATTACK_POWER]        [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_ATTACK_POWER        , BASE_VALUE);
        stats[id][UNIT_MOD_ATTACK_POWER_RANGED] [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_ATTACK_POWER_RANGED , BASE_VALUE);
        stats[id][UNIT_MOD_DAMAGE_MAINHAND]     [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND     , BASE_VALUE);
        stats[id][UNIT_MOD_DAMAGE_OFFHAND]      [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_DAMAGE_OFFHAND      , BASE_VALUE);
        stats[id][UNIT_MOD_DAMAGE_RANGED]       [BASE_VALUE]  = unit->GetModifierValue(UNIT_MOD_DAMAGE_RANGED       , BASE_VALUE);

        stats[id][UNIT_MOD_STAT_STRENGTH]       [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_STAT_STRENGTH       , BASE_PCT);
        stats[id][UNIT_MOD_STAT_AGILITY]        [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_STAT_AGILITY        , BASE_PCT);
        stats[id][UNIT_MOD_STAT_STAMINA]        [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_STAT_STAMINA        , BASE_PCT);
        stats[id][UNIT_MOD_STAT_INTELLECT]      [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_STAT_INTELLECT      , BASE_PCT);
        stats[id][UNIT_MOD_STAT_SPIRIT]         [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_STAT_SPIRIT         , BASE_PCT);
        stats[id][UNIT_MOD_HEALTH]              [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_HEALTH              , BASE_PCT);
        stats[id][UNIT_MOD_MANA]                [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_MANA                , BASE_PCT);
        stats[id][UNIT_MOD_RAGE]                [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_RAGE                , BASE_PCT);
        stats[id][UNIT_MOD_FOCUS]               [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_FOCUS               , BASE_PCT);
        stats[id][UNIT_MOD_ENERGY]              [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_ENERGY              , BASE_PCT);
        stats[id][UNIT_MOD_HAPPINESS]           [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_HAPPINESS           , BASE_PCT);
        stats[id][UNIT_MOD_RUNE]                [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_RUNE                , BASE_PCT);
        stats[id][UNIT_MOD_RUNIC_POWER]         [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_RUNIC_POWER         , BASE_PCT);
        stats[id][UNIT_MOD_ARMOR]               [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_ARMOR               , BASE_PCT);
        stats[id][UNIT_MOD_RESISTANCE_HOLY]     [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_RESISTANCE_HOLY     , BASE_PCT);
        stats[id][UNIT_MOD_RESISTANCE_FIRE]     [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_RESISTANCE_FIRE     , BASE_PCT);
        stats[id][UNIT_MOD_RESISTANCE_NATURE]   [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_RESISTANCE_NATURE   , BASE_PCT);
        stats[id][UNIT_MOD_RESISTANCE_FROST]    [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_RESISTANCE_FROST    , BASE_PCT);
        stats[id][UNIT_MOD_RESISTANCE_SHADOW]   [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_RESISTANCE_SHADOW   , BASE_PCT);
        stats[id][UNIT_MOD_RESISTANCE_ARCANE]   [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_RESISTANCE_ARCANE   , BASE_PCT);
        stats[id][UNIT_MOD_ATTACK_POWER]        [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_ATTACK_POWER        , BASE_PCT);
        stats[id][UNIT_MOD_ATTACK_POWER_RANGED] [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_ATTACK_POWER_RANGED , BASE_PCT);
        stats[id][UNIT_MOD_DAMAGE_MAINHAND]     [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND     , BASE_PCT);
        stats[id][UNIT_MOD_DAMAGE_OFFHAND]      [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_DAMAGE_OFFHAND      , BASE_PCT);
        stats[id][UNIT_MOD_DAMAGE_RANGED]       [BASE_PCT]    = unit->GetModifierValue(UNIT_MOD_DAMAGE_RANGED       , BASE_PCT);

        stats[id][UNIT_MOD_STAT_STRENGTH]       [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_STAT_STRENGTH       , TOTAL_VALUE);
        stats[id][UNIT_MOD_STAT_AGILITY]        [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_STAT_AGILITY        , TOTAL_VALUE);
        stats[id][UNIT_MOD_STAT_STAMINA]        [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_STAT_STAMINA        , TOTAL_VALUE);
        stats[id][UNIT_MOD_STAT_INTELLECT]      [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_STAT_INTELLECT      , TOTAL_VALUE);
        stats[id][UNIT_MOD_STAT_SPIRIT]         [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_STAT_SPIRIT         , TOTAL_VALUE);
        stats[id][UNIT_MOD_HEALTH]              [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_HEALTH              , TOTAL_VALUE);
        stats[id][UNIT_MOD_MANA]                [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_MANA                , TOTAL_VALUE);
        stats[id][UNIT_MOD_RAGE]                [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_RAGE                , TOTAL_VALUE);
        stats[id][UNIT_MOD_FOCUS]               [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_FOCUS               , TOTAL_VALUE);
        stats[id][UNIT_MOD_ENERGY]              [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_ENERGY              , TOTAL_VALUE);
        stats[id][UNIT_MOD_HAPPINESS]           [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_HAPPINESS           , TOTAL_VALUE);
        stats[id][UNIT_MOD_RUNE]                [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_RUNE                , TOTAL_VALUE);
        stats[id][UNIT_MOD_RUNIC_POWER]         [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_RUNIC_POWER         , TOTAL_VALUE);
        stats[id][UNIT_MOD_ARMOR]               [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_ARMOR               , TOTAL_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_HOLY]     [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_RESISTANCE_HOLY     , TOTAL_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_FIRE]     [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_RESISTANCE_FIRE     , TOTAL_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_NATURE]   [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_RESISTANCE_NATURE   , TOTAL_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_FROST]    [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_RESISTANCE_FROST    , TOTAL_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_SHADOW]   [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_RESISTANCE_SHADOW   , TOTAL_VALUE);
        stats[id][UNIT_MOD_RESISTANCE_ARCANE]   [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_RESISTANCE_ARCANE   , TOTAL_VALUE);
        stats[id][UNIT_MOD_ATTACK_POWER]        [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_ATTACK_POWER        , TOTAL_VALUE);
        stats[id][UNIT_MOD_ATTACK_POWER_RANGED] [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_ATTACK_POWER_RANGED , TOTAL_VALUE);
        stats[id][UNIT_MOD_DAMAGE_MAINHAND]     [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND     , TOTAL_VALUE);
        stats[id][UNIT_MOD_DAMAGE_OFFHAND]      [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_DAMAGE_OFFHAND      , TOTAL_VALUE);
        stats[id][UNIT_MOD_DAMAGE_RANGED]       [TOTAL_VALUE] = unit->GetModifierValue(UNIT_MOD_DAMAGE_RANGED       , TOTAL_VALUE);

        stats[id][UNIT_MOD_STAT_STRENGTH]       [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_STAT_STRENGTH       , TOTAL_PCT);
        stats[id][UNIT_MOD_STAT_AGILITY]        [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_STAT_AGILITY        , TOTAL_PCT);
        stats[id][UNIT_MOD_STAT_STAMINA]        [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_STAT_STAMINA        , TOTAL_PCT);
        stats[id][UNIT_MOD_STAT_INTELLECT]      [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_STAT_INTELLECT      , TOTAL_PCT);
        stats[id][UNIT_MOD_STAT_SPIRIT]         [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_STAT_SPIRIT         , TOTAL_PCT);
        stats[id][UNIT_MOD_HEALTH]              [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_HEALTH              , TOTAL_PCT);
        stats[id][UNIT_MOD_MANA]                [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_MANA                , TOTAL_PCT);
        stats[id][UNIT_MOD_RAGE]                [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_RAGE                , TOTAL_PCT);
        stats[id][UNIT_MOD_FOCUS]               [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_FOCUS               , TOTAL_PCT);
        stats[id][UNIT_MOD_ENERGY]              [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_ENERGY              , TOTAL_PCT);
        stats[id][UNIT_MOD_HAPPINESS]           [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_HAPPINESS           , TOTAL_PCT);
        stats[id][UNIT_MOD_RUNE]                [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_RUNE                , TOTAL_PCT);
        stats[id][UNIT_MOD_RUNIC_POWER]         [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_RUNIC_POWER         , TOTAL_PCT);
        stats[id][UNIT_MOD_ARMOR]               [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_ARMOR               , TOTAL_PCT);
        stats[id][UNIT_MOD_RESISTANCE_HOLY]     [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_RESISTANCE_HOLY     , TOTAL_PCT);
        stats[id][UNIT_MOD_RESISTANCE_FIRE]     [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_RESISTANCE_FIRE     , TOTAL_PCT);
        stats[id][UNIT_MOD_RESISTANCE_NATURE]   [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_RESISTANCE_NATURE   , TOTAL_PCT);
        stats[id][UNIT_MOD_RESISTANCE_FROST]    [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_RESISTANCE_FROST    , TOTAL_PCT);
        stats[id][UNIT_MOD_RESISTANCE_SHADOW]   [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_RESISTANCE_SHADOW   , TOTAL_PCT);
        stats[id][UNIT_MOD_RESISTANCE_ARCANE]   [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_RESISTANCE_ARCANE   , TOTAL_PCT);
        stats[id][UNIT_MOD_ATTACK_POWER]        [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_ATTACK_POWER        , TOTAL_PCT);
        stats[id][UNIT_MOD_ATTACK_POWER_RANGED] [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_ATTACK_POWER_RANGED , TOTAL_PCT);
        stats[id][UNIT_MOD_DAMAGE_MAINHAND]     [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND     , TOTAL_PCT);
        stats[id][UNIT_MOD_DAMAGE_OFFHAND]      [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_DAMAGE_OFFHAND      , TOTAL_PCT);
        stats[id][UNIT_MOD_DAMAGE_RANGED]       [TOTAL_PCT]   = unit->GetModifierValue(UNIT_MOD_DAMAGE_RANGED       , TOTAL_PCT);
    }

    //
    // Update the factor applied
    //

    factors[id] = factor;

    //
    // Scale the stats by the provided factor (only base values are modified)
    //

    unit->SetModifierValue(UNIT_MOD_STAT_STRENGTH       , BASE_VALUE , stats[id][UNIT_MOD_STAT_STRENGTH]       [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_STAT_AGILITY        , BASE_VALUE , stats[id][UNIT_MOD_STAT_AGILITY]        [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_STAT_STAMINA        , BASE_VALUE , stats[id][UNIT_MOD_STAT_STAMINA]        [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_STAT_INTELLECT      , BASE_VALUE , stats[id][UNIT_MOD_STAT_INTELLECT]      [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_STAT_SPIRIT         , BASE_VALUE , stats[id][UNIT_MOD_STAT_SPIRIT]         [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_HEALTH              , BASE_VALUE , stats[id][UNIT_MOD_HEALTH]              [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_MANA                , BASE_VALUE , stats[id][UNIT_MOD_MANA]                [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_RAGE                , BASE_VALUE , stats[id][UNIT_MOD_RAGE]                [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_FOCUS               , BASE_VALUE , stats[id][UNIT_MOD_FOCUS]               [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_ENERGY              , BASE_VALUE , stats[id][UNIT_MOD_ENERGY]              [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_HAPPINESS           , BASE_VALUE , stats[id][UNIT_MOD_HAPPINESS]           [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_RUNE                , BASE_VALUE , stats[id][UNIT_MOD_RUNE]                [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_RUNIC_POWER         , BASE_VALUE , stats[id][UNIT_MOD_RUNIC_POWER]         [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_ARMOR               , BASE_VALUE , stats[id][UNIT_MOD_ARMOR]               [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_RESISTANCE_HOLY     , BASE_VALUE , stats[id][UNIT_MOD_RESISTANCE_HOLY]     [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_RESISTANCE_FIRE     , BASE_VALUE , stats[id][UNIT_MOD_RESISTANCE_FIRE]     [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_RESISTANCE_NATURE   , BASE_VALUE , stats[id][UNIT_MOD_RESISTANCE_NATURE]   [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_RESISTANCE_FROST    , BASE_VALUE , stats[id][UNIT_MOD_RESISTANCE_FROST]    [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_RESISTANCE_SHADOW   , BASE_VALUE , stats[id][UNIT_MOD_RESISTANCE_SHADOW]   [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_RESISTANCE_ARCANE   , BASE_VALUE , stats[id][UNIT_MOD_RESISTANCE_ARCANE]   [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_ATTACK_POWER        , BASE_VALUE , stats[id][UNIT_MOD_ATTACK_POWER]        [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_ATTACK_POWER_RANGED , BASE_VALUE , stats[id][UNIT_MOD_ATTACK_POWER_RANGED] [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_DAMAGE_MAINHAND     , BASE_VALUE , stats[id][UNIT_MOD_DAMAGE_MAINHAND]     [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_DAMAGE_OFFHAND      , BASE_VALUE , stats[id][UNIT_MOD_DAMAGE_OFFHAND]      [BASE_VALUE]  * factor);
    unit->SetModifierValue(UNIT_MOD_DAMAGE_RANGED       , BASE_VALUE , stats[id][UNIT_MOD_DAMAGE_RANGED]       [BASE_VALUE]  * factor);

    //
    // Perform a statistics update
    //

    unit->UpdateAllStats();

    //
    // Fill up hp and mana
    //

    unit->SetHealth(unit->GetMaxHealth());
    unit->SetPower (POWER_MANA, unit->GetMaxPower(POWER_MANA));

    return true;
}

void AddElitify_CommandScript()
{
    new ModElitify_CommandScript();
}
