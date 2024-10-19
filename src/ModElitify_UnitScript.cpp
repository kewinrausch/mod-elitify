/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

#include "Config.h"
#include "Log.h"

#include "ModElitify.h"
#include "ModElitify_UnitScript.h"

void ModElitify_UnitScript::ModifyPeriodicDamageAurasTick(Unit* /*target*/, Unit* attacker, uint32& damage, SpellInfo const* /*spellInfo*/)
{
    //
    // Check if enabled or not
    //

    if (!Enabled)
    {
        return;
    }

    // 
    // Before considering to scale, check if the unit is present into the cache
    // 

    if (attacker)
    {
        ObjectGuid id = attacker->GetGUID();

        if (factors.count(id) != 0)
        {
            if (Debug)
            {
                LOG_INFO("ModElitify", "Elitify: periodic damage aura {} = {} * {}", damage * factors[id], damage, factors[id]);
            }

            damage = damage * factors[id];
        }
    }
}

void ModElitify_UnitScript::ModifySpellDamageTaken(Unit* /*target*/, Unit* attacker, int32& damage, SpellInfo const* /*spellInfo*/)
{
    //
    // Check if enabled or not
    //

    if (!Enabled)
    {
        return;
    }

    // 
    // Scale the head received based on the provided factor
    // 

    if (attacker)
    {
        ObjectGuid id = attacker->GetGUID();

        if (factors.count(id) != 0)
        {
            if (Debug)
            {
                LOG_INFO("ModElitify", "Elitify: spell damage {} = {} * {}", damage * factors[id], damage, factors[id]);
            }

            damage = damage * factors[id];
        }
    }
}

void ModElitify_UnitScript::ModifyHealReceived(Unit* /*target*/, Unit* healer, uint32& heal, SpellInfo const* /*spellInfo*/)
{
    //
    // Check if enabled or not
    //

    if (!Enabled)
    {
        return;
    }

    // 
    // Scale the head received based on the provided factor
    // 

    if (healer)
    {
        ObjectGuid id = healer->GetGUID();

        if (factors.count(id) != 0)
        {
            if (Debug)
            {
                LOG_INFO("ModElitify", "Elitify: heal received {} = {} * {}", heal * factors[id], heal, factors[id]);
            }

            heal = heal * factors[id];
        }
    }
}

void AddElitify_UnitScript()
{
    new ModElitify_UnitScript();
}
