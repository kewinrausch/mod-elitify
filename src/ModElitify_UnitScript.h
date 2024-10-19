/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

#ifndef __MOD_ELITIFY_UNIT_SCRIPT_H
#define __MOD_ELITIFY_UNIT_SCRIPT_H

#include "ScriptMgr.h"

class ModElitify_UnitScript : public UnitScript
{
public:
    ModElitify_UnitScript()
        : UnitScript("ModElitify_UnitScript", true)
    {
    }

    void ModifyPeriodicDamageAurasTick(Unit* /*target*/, Unit* /*attacker*/, uint32& /*damage*/, SpellInfo const* /*spellInfo*/) override;
    void ModifySpellDamageTaken(Unit* /*target*/, Unit* /*attacker*/, int32& /*damage*/, SpellInfo const* /*spellInfo*/) override;
    void ModifyHealReceived(Unit* /*target*/, Unit* /*healer*/, uint32& /*heal*/, SpellInfo const* /*spellInfo*/) override;
};

#endif /* __MOD_ELITIFY_UNIT_SCRIPT_H */
