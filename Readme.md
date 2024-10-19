# Mod-elitify

This mod play around a single player or a creature, and allows you to modify it in order to scale to an elite level. Some of the modifications applied to the creature or to the player are not saved in the database, which means that the original values will be restored at logout.

## How does it works?

The module capabilities are triggered with chat commands by GAMEMASTER level security permissions. These commands are:

- on: enable the chat commands (only an administrator can do this)
- off: disable the chat commands (only an administrator can do this)
- level: assign a level to a player/creature
- scale: scale the sizes of the player/creature model
- fact: assign a faction to the player/creature
- display: change the player/creature display model (you can become Thrall visually)
- set: scale up/down the player/creature statistics, damage and healing done

The commands are executed on the targeting creature, otherwise are applied on yourself. This is done by calling the `elitify` or `efy` command.

```
.efy set 2
```

## Commands syntax

- `.efy on`, enables the mod
- `.efy off`, disables the mod
- `.efy level <number>`, switch the target to the provided level (max 255). This modification is permanent and will be preserved across server restarts.
- `.efy scale <float>`, scale the player size of that factor. 1 is original size; values more than 1 will make it bigger; values less than 1 will make it smaller. Zero is not allowed.
- `.efy fact [number]`, calling without arguments will provide the target faction number. Provide a number to switch the target to that faction.
- `.efy display <number>`, change the visual appearance and scale to the ones belonging to the provided id (the `entry` value of the `creature_template` table)
- `.efy set <number>`, scale statistics, health, manam damage and healing of the provided factor. If you set 2, you get twice more powerful. Ten will get you ten times bigger. Use one to restore the original values, or a values less than one to scale it down.

## Some useful factions values

```
FACTION_NONE                        = 0,
FACTION_CREATURE                    = 7,
FACTION_ESCORTEE_A_NEUTRAL_PASSIVE  = 10,
FACTION_MONSTER                     = 14,
FACTION_MONSTER_2                   = 16,
FACTION_BOOTY_BAY                   = 21,
FACTION_TROLL_BLOODSCALP            = 28,
FACTION_PREY                        = 31,
FACTION_ESCORTEE_H_NEUTRAL_PASSIVE  = 33,
FACTION_FRIENDLY                    = 35,
FACTION_TROLL_FROSTMANE             = 37,
FACTION_OGRE                        = 45,
FACTION_ORC_DRAGONMAW               = 62,
FACTION_HORDE_GENERIC               = 83,
FACTION_ALLIANCE_GENERIC            = 84,
FACTION_BLACKFATHOM                 = 88,
FACTION_DEMON                       = 90,
FACTION_ELEMENTAL                   = 91,
FACTION_DRAGONFLIGHT_BLACK          = 103,
FACTION_ESCORTEE_N_NEUTRAL_PASSIVE  = 113,
FACTION_STORMWIND                   = 123,
FACTION_ENEMY                       = 168,
FACTION_ESCORTEE_A_NEUTRAL_ACTIVE   = 231,
FACTION_ESCORTEE_H_NEUTRAL_ACTIVE   = 232,
FACTION_ESCORTEE_N_NEUTRAL_ACTIVE   = 250,
FACTION_ESCORTEE_N_FRIEND_PASSIVE   = 290,
FACTION_TITAN                       = 415,
FACTION_ESCORTEE_N_FRIEND_ACTIVE    = 495,
FACTION_RATCHET                     = 637,
FACTION_GOBLIN_DARK_IRON_BAR_PATRON = 736,
FACTION_DARK_IRON_DWARVES           = 754,
FACTION_ESCORTEE_A_PASSIVE          = 774,
FACTION_ESCORTEE_H_PASSIVE          = 775,
FACTION_UNDEAD_SCOURGE              = 974,
FACTION_DRAGONKIN                   = 1720,
FACTION_EARTHEN_RING                = 1726,
FACTION_ALLIANCE_GENERIC_WG         = 1732,
FACTION_HORDE_GENERIC_WG            = 1735,
FACTION_ARAKKOA                     = 1738,
FACTION_ASHTONGUE_DEATHSWORN        = 1820,
FACTION_FLAYER_HUNTER               = 1840,
FACTION_MONSTER_SPAR_BUDDY          = 1868,
FACTION_VALIANCE_EXPEDITION_7       = 1974,
FACTION_ESCORTEE_N_ACTIVE           = 1986,
FACTION_UNDEAD_SCOURGE_9            = 1988,
FACTION_ESCORTEE_H_ACTIVE           = 2046,
FACTION_UNDEAD_SCOURGE_2            = 2068,
FACTION_UNDEAD_SCOURGE_3            = 2084,
FACTION_SCARLET_CRUSADE             = 2089,
FACTION_SCARLET_CRUSADE_2           = 2096
```
