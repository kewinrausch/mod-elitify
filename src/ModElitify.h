/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE
 */

#ifndef __MOD_ELITIFY_H
#define __MOD_ELITIFY_H

#include <map>

#include <ObjectGuid.h>
#include <Unit.h>

extern bool Enabled;
extern bool Logo;
extern bool Debug;

extern std::map<ObjectGuid, float>                                  factors;
extern std::map<ObjectGuid, float[UNIT_MOD_END][MODIFIER_TYPE_END]> stats;

#endif /* __MOD_ELITIFY_H */
