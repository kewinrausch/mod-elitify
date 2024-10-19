/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

#include "ModElitify.h"

bool Enabled = false;
bool Logo    = false;
bool Debug   = false;

std::map<ObjectGuid, float>                                  factors;
std::map<ObjectGuid, float[UNIT_MOD_END][MODIFIER_TYPE_END]> stats;
