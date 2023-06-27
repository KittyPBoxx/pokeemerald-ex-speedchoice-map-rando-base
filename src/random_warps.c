#include "random_warps.h"
#include "global.h"
#include "event_data.h"
#include "constants/vars.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "item.h"

/**
*
*   List of fixes that are applied elsewhere:
*   Fixes listed as 'TODO' are currently applied by a patch before the xdelta (from sp ex 0.4.0 to this) is applied
*   However they should be moved into the decomp
*   
*   - start with acro bike
*
*   - let escape rope be used anywhere
*
*   - disable darkness in caves
*
*   - make mirage tower always present
*       
*   TODO: - make sure archie never blocks off sotopolis gym
*           patchROM8(0x71d1b8, 0x20)
*
*   TODO: - move sootopolis man 1 outside gym + look like wallace + give waterfall
*           patchROM8(0x71d0B0, 0x1c) // x pos
*           patchROM8(0x71d0B2, 0x23) // y pos
*           patchROM8(0x71d0B5, 0x01) // movement type
*           patchROM8(0x71d0BC, 0x17) // on talk script, give waterfall
*           patchROM8(0x71d0BD, 0xd8) // on talk script, give waterfall
*           patchROM8(0x71d0AD, 0x85) // change appearance to wallace
*
*   TODO: - make sure we can go both ways from trick masters house
*           patchROM8(0x292FD2, 0x0B) // new tile
*           patchROM8(0x292FD4, 0x00) // movement permissions
*
*   TODO: - move magma grunts from blocking cable car
*           patchROM8(0x71F6A0, 0x1B) // x pos
*           patchROM8(0x71F6A2, 0x1C) // y pos
*           patchROM8(0x71F6A5, 0x08) // facing direction
*           
*           patchROM8(0x71F718, 0x1E) // x pos
*           patchROM8(0x71F71A, 0x1C) // y pos
*           patchROM8(0x71F71D, 0x08) // facing direction
*
*   TODO: - make sure champion battle dosn't start untill we talk to him
*           patchROM8(0x250b63, 0x36) // prevent start battle
*           patchROM8(0x729450, 0x6c) // make battle start on talk
*           patchROM8(0x729451, 0x0b) // make battle start on talk
*           patchROM8(0x729452, 0x25) // make battle start on talk
*           patchROM8(0x729453, 0x08) // make battle start on talk
*
*/

struct WarpRemap
{
    s8 fromMapGroup;
    s8 fromMapNum;
    s8 fromWarpId;

    s8 toMapGroup;
    s8 toMapNum;
    s8 toWarpId;
};

// Values in this block with be overwritten by the randomizer
const struct WarpRemap gWarpRemappingList[RANDOM_WARP_LIMIT] = 
{
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  },
    {-1 , -1 , -1 , 0  , 0  , 0  }
};

// Variables in ram
// For positive values this will set the player coords after warp
// If the value is -1 player position will be set normally
// If xPostionCorrection -2 it will use the normal position -1
s8 xPositionCorrection;
s8 yPositionCorrection;

s8 WarpRemapCompare(s8 *mapGroup, s8 *mapNum, s8 *warpId, struct WarpRemap comparison) 
{
    if ((*mapGroup) < comparison.fromMapGroup) 
    {
        return 1;
    } 
    else if ((*mapGroup) > comparison.fromMapGroup)
    {
        return -1;
    }

    if ((*mapNum) < comparison.fromMapNum) 
    {
        return 1;
    } 
    else if ((*mapNum) > comparison.fromMapNum)
    {
        return -1;
    }

    if ((*warpId) < comparison.fromWarpId) 
    {
        return 1;
    } 
    else if ((*warpId) > comparison.fromWarpId)
    {
        return -1;
    }

    return 0;
}

u16 WarpRemapBinarySearch(s8 *mapGroup, s8 *mapNum, s8 *warpId) 
{
    u16 high = RANDOM_WARP_LIMIT_SEARCH_HIGH;
    u16 mid  = RANDOM_WARP_LIMIT_SEARCH_MID;
    u16 low  = RANDOM_WARP_LIMIT_SEARCH_LOW;

    while (low <= high) 
    {
        int mid = low + (high - low) / 2;

        if (WarpRemapCompare(mapGroup, mapNum, warpId, gWarpRemappingList[mid]) == 0)
        {
            return mid;
        }
        
        if (WarpRemapCompare(mapGroup, mapNum, warpId, gWarpRemappingList[mid]) == -1)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return RANDOM_WARP_LIMIT;
}

void ApplyFixesForSpecialWarps(s8 *mapGroup, s8 *mapNum, s8 *warpId)
{
    if ((*mapGroup) == 8 && (*mapNum) == 1 && (*warpId) == 0) 
    {
        // If left of Petalburg is locked we start catch tutorial
        // otherwise we set to battle state so it can be started immediately
        if (VarGet(VAR_PETALBURG_CITY_STATE) < 1) 
        {
            VarSet(VAR_PETALBURG_GYM_STATE, 0);
        } 
        else 
        {
            VarSet(VAR_PETALBURG_GYM_STATE, 6);
        }

        // Unlock left of petalburg
        VarSet(VAR_PETALBURG_CITY_STATE, 1);

    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 0 && (*warpId) == 0) 
    {
        // E4 rooms needs to walk fowards when entering from front
        // But not if we enter from the back
        VarSet(VAR_ELITE_4_STATE, 0);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 0 && (*warpId) == 1)  
    {
        VarSet(VAR_ELITE_4_STATE, 1);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 1 && (*warpId) == 0) 
    {
        VarSet(VAR_ELITE_4_STATE, 1);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 1 && (*warpId) == 1) 
    {
        VarSet(VAR_ELITE_4_STATE, 2);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 2 && (*warpId) == 0) 
    {
        VarSet(VAR_ELITE_4_STATE, 2);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 2 && (*warpId) == 1) 
    {
        VarSet(VAR_ELITE_4_STATE, 3);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 3 && (*warpId) == 0) 
    {
        VarSet(VAR_ELITE_4_STATE, 3);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 3 && (*warpId) == 1) 
    {
        VarSet(VAR_ELITE_4_STATE, 4);
    } 
    else  if ((*mapGroup) == 10 && (*mapNum) == 0 && (*warpId) == 0) 
    {
        // Make sure wattson is always in the gym
        FlagClear(FLAG_HIDE_MAUVILLE_GYM_WATTSON);
    } 
    else if (((*mapGroup) == 29 && (*mapNum) == 1 && (*warpId) == 0) || 
             ((*mapGroup) == 29 && (*mapNum) == 1 && (*warpId) == 1))
    {
        // Make Sure the trick master won't crash the game
        // If we enter after collecting tent he will give the tent again
        if (VarGet(VAR_TRICK_HOUSE_LEVEL) > 7) 
        {
            VarSet(VAR_TRICK_HOUSE_LEVEL, 7);
        }
    } 
    else if ((*mapGroup) == 14 && (*mapNum) == 7 && (*warpId) == 0) 
    {
        // Make sure steven gives tickets and dive when we enter his house
        if (VarGet(VAR_STEVENS_HOUSE_STATE) == 0) 
        {
            VarSet(VAR_STEVENS_HOUSE_STATE, 1);
            FlagClear(FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_STEVEN);
        }
    }
}

void ApplyFixesForEveryWarp()
{
    // Open regi doors
    FlagSet(FLAG_REGI_DOORS_OPENED);

    // Not On Bike Path
    FlagClear(FLAG_SYS_CYCLING_ROAD);

    // Open Sootopolis Gym Door
    FlagSet(FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE);

    // Sootopolis always in nice state
    // We need to prevent locked doors, people standing around and lilycove dept roof being locked off
    VarSet(VAR_SOOTOPOLIS_CITY_STATE, 0);
    FlagSet(FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN);

    // RRAQUAZA always available
    VarSet(VAR_SKY_PILLAR_RAQUAZA_CRY_DONE, 0);
    FlagClear(FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA_STILL);

    // Show steven on the bridge if we don't have the devon scope
    if (FlagGet(FLAG_RECEIVED_DEVON_SCOPE)) 
    {
        FlagSet(FLAG_HIDE_ROUTE_120_STEVEN);
    } 
    else 
    {
        FlagClear(FLAG_HIDE_ROUTE_120_STEVEN);
    }
    
    // Make sure the magma embelem can always be got
    if (CheckBagHasItem(ITEM_MAGMA_EMBLEM, 1)) 
    {
        // Hide Jagged Pass Magma guard if we have magma emblem
        FlagSet(FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD);
    } 
    else 
    {
        VarSet(VAR_MT_PYRE_STATE, 0);
    }

    // Unblock Tunnlers rest house 
    FlagSet(FLAG_RECOVERED_DEVON_GOODS);

    // Unblock Devon corp f1
    FlagSet(FLAG_RETURNED_DEVON_GOODS);

    // Hide Steven and wallace in sootopolis
    FlagSet(FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN);
    FlagSet(FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE);

    // Hide the old man blocking the cave of origin
    FlagSet(FLAG_HIDE_SOOTOPOLIS_CITY_OLD_MAN_EXPERT);

    // Unhide man from the top of sootopolice
    // We patched him to give waterfall, dress like wallace and stand in front of the gym
    FlagClear(FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1);

    // Remove the brigde Kecleon so we can ride up from lilycove
    FlagSet(FLAG_HIDE_ROUTE_120_KECLEON_BRIDGE);

    // Change Slateport state to 0 (to work around a glitch where game loops exiting the pokecenter)
    // This was needed for the IodineGBA scripted version it might not be needed in the rom hack
    VarSet(VAR_SLATEPORT_CITY_STATE, 0);

    // Remove Team Aqua from slateport and above slateport
    FlagSet(FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA);
    FlagSet(FLAG_HIDE_ROUTE_110_TEAM_AQUA);
}

bool8 warpNeedsXOffetShift(s8 *mapGroup, s8 *mapNum, s8 *warpId)
{
    // For warps where we need to shift the x offset to correct it (e.g when going via an escalator)
    if ((*mapGroup) == 8  && (*mapNum) == 5  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 9  && (*mapNum) == 12 && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 10 && (*mapNum) == 6  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 11 && (*mapNum) == 6  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 12 && (*mapNum) == 3  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 13 && (*mapNum) == 7  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 14 && (*mapNum) == 4  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 15 && (*mapNum) == 3  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 16 && (*mapNum) == 13 && (*warpId) == 0) { return TRUE; } 
    if ((*mapGroup) == 16 && (*mapNum) == 14 && (*warpId) == 0) { return TRUE; } 
    if ((*mapGroup) == 2  && (*mapNum) == 3  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 3  && (*mapNum) == 2  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 4  && (*mapNum) == 6  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 5  && (*mapNum) == 5  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 6  && (*mapNum) == 5  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 7  && (*mapNum) == 1  && (*warpId) == 0) { return TRUE; }   

    return FALSE;
}

void fixPositionAfterWarp(s8 *mapGroup, s8 *mapNum, s8 *warpId, s8 *x, s8 *y)
{
    // For warps where we need to make sure we end up in the right position after the warp

    if ((*mapGroup) == 0) 
    {
        if ((*mapNum) == 1  && (*warpId) == 5 ) { xPositionCorrection = 0x1E; yPositionCorrection = 0x1B; return;}
        if ((*mapNum) == 5  && (*warpId) == 0 ) { xPositionCorrection = 0x1B; yPositionCorrection = 0x07; return;}
        if ((*mapNum) == 2  && (*warpId) == 0 ) { xPositionCorrection = 0x08; yPositionCorrection = 0x06; return;}
        if ((*mapNum) == 7  && (*warpId) == 5 ) { xPositionCorrection = 0x2D; yPositionCorrection = 0x07; return;}
        if ((*mapNum) == 7  && (*warpId) == 9 ) { xPositionCorrection = 0x35; yPositionCorrection = 0x1D; return;}
        if ((*mapNum) == 7  && (*warpId) == 4 ) { xPositionCorrection = 0x09; yPositionCorrection = 0x07; return;}
        if ((*mapNum) == 8  && (*warpId) == 2 ) { xPositionCorrection = 0x12; yPositionCorrection = 0x2A; return;}
        if ((*mapNum) == 11 && (*warpId) == 3 ) { xPositionCorrection = 0x11; yPositionCorrection = 0x0E; return;}
        if ((*mapNum) == 12 && (*warpId) == 5 ) { xPositionCorrection = 0x09; yPositionCorrection = 0x02; return;}
        if ((*mapNum) == 14 && (*warpId) == 4 ) { xPositionCorrection = 0x08; yPositionCorrection = 0x02; return;}
        if ((*mapNum) == 15 && (*warpId) == 0 ) { xPositionCorrection = 0x08; yPositionCorrection = 0x10; return;}
        if ((*mapNum) == 26 && (*warpId) == 0 ) { xPositionCorrection = 0x0D; yPositionCorrection = 0x72; return;}
        if ((*mapNum) == 10 && (*warpId) == 5 ) { xPositionCorrection = 0x0A; yPositionCorrection = 0x09; return;}

        return;
    }

    if ((*mapGroup) == 24) 
    {
        if ((*mapNum) == 8  && (*warpId) == 2 ) { xPositionCorrection = 0x1D; yPositionCorrection = 0x0D; return;}
        if ((*mapNum) == 8  && (*warpId) == 3 ) { xPositionCorrection = 0x1C; yPositionCorrection = 0x15; return;}
        if ((*mapNum) == 9  && (*warpId) == 0 ) { xPositionCorrection = 0x1D; yPositionCorrection = 0x0D; return;}
        if ((*mapNum) == 9  && (*warpId) == 1 ) { xPositionCorrection = 0x1C; yPositionCorrection = 0x15; return;}
        if ((*mapNum) == 13 && (*warpId) == 4 ) { xPositionCorrection = 0x10; yPositionCorrection = 0x13; return;}
        if ((*mapNum) == 16 && (*warpId) == 4 ) { xPositionCorrection = 0x0B; yPositionCorrection = 0x09; return;}
        if ((*mapNum) == 16 && (*warpId) == 2 ) { xPositionCorrection = 0x0A; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 17 && (*warpId) == 5 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 17 && (*warpId) == 4 ) { xPositionCorrection = 0x0A; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 18 && (*warpId) == 2 ) { xPositionCorrection = 0x0C; yPositionCorrection = 0x0A; return;}
        if ((*mapNum) == 18 && (*warpId) == 3 ) { xPositionCorrection = 0x0C; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 19 && (*warpId) == 3 ) { xPositionCorrection = 0x0C; yPositionCorrection = 0x0A; return;}
        if ((*mapNum) == 19 && (*warpId) == 4 ) { xPositionCorrection = 0x0C; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 24 && (*warpId) == 10) { xPositionCorrection = 0x20; yPositionCorrection = 0x13; return;}
        if ((*mapNum) == 25 && (*warpId) == 5 ) { xPositionCorrection = 0x05; yPositionCorrection = 0x08; return;}
        if ((*mapNum) == 25 && (*warpId) == 9 ) { xPositionCorrection = 0x20; yPositionCorrection = 0x14; return;}
        if ((*mapNum) == 29 && (*warpId) == 2 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x01; return;}
        if ((*mapNum) == 78 && (*warpId) == 0 ) { xPositionCorrection = 0x11; yPositionCorrection = 0x0D; return;}
        if ((*mapNum) == 81 && (*warpId) == 0 ) { xPositionCorrection = 0x03; yPositionCorrection = 0x01; return;}
        if ((*mapNum) == 82 && (*warpId) == 1 ) { xPositionCorrection = 0x07; yPositionCorrection = 0x01; return;}
        if ((*mapNum) == 95 && (*warpId) == 0 ) { xPositionCorrection = 0x12; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 96 && (*warpId) == 0 ) { xPositionCorrection = 0x12; yPositionCorrection = 0x0C; return;}

        return;
    }

    if ((*mapGroup) == 16) 
    {
        if ((*mapNum) == 0  && (*warpId) == 1 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x03; return;}
        if ((*mapNum) == 1  && (*warpId) == 1 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x03; return;}
        if ((*mapNum) == 2  && (*warpId) == 1 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x03; return;}
        if ((*mapNum) == 3  && (*warpId) == 1 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x03; return;}
        if ((*mapNum) == 10 && (*warpId) == 2 ) { xPositionCorrection = 0x09; yPositionCorrection = 0x02; return;}

        return;
    }


    if ((*mapGroup) == 11 && (*mapNum) == 0  && (*warpId) == 2 ) { xPositionCorrection = 0x0E; yPositionCorrection = 0x02; return;}

    if ((*mapGroup) == 14 && (*mapNum) == 9  && (*warpId) == 2 ) { xPositionCorrection = 0x0D; yPositionCorrection = 0x02; return;}
    if ((*mapGroup) == 14 && (*mapNum) == 10 && (*warpId) == 2 ) { xPositionCorrection = 0x0d; yPositionCorrection = 0x02; return;}
    
    if ((*mapGroup) == 26 && (*mapNum) == 74 && (*warpId) == 1 ) { xPositionCorrection = 0x05; yPositionCorrection = 0x05; return;}
    if ((*mapGroup) == 26 && (*mapNum) == 87 && (*warpId) == 0 ) { xPositionCorrection = 0x0E; yPositionCorrection = 0x13; return;}

}


/*
*   For the remapping to work each warp tile (or group of adjacent tiles) needs a unique destination
*   Previously we patched this but now we can update the warpId based on player x/y pos (there's probably a better way...)
*
*   TODO:
*   DUPES: [24,24,20, 24,24,23] -> 24,24,17
*   NEW  : 24,24,23 -> 24,24,50 (0x32) | patchROM8(0x0872b27d - 0x08000000, 0x32)
*
*
*   DUPES: [24,24,9, 24,24,14, 24,24,21] -> 24,24,12
*   NEW  : 24,24,14 -> 24,24,52 (0x33) | patchROM8(0x0872B26D - 0x08000000, 0x33)
*          24,24,21 -> 24,24,51 (0x34) | patchROM8(0x0872B235 - 0x08000000, 0x34)
*
*   DUPES: [24,24,7, 24,25,9] -> 24,24,4
*   NEW  : 24,25,9  -> 24,24,53 (0x35) | patchROM8(0x0872B379 - 0x08000000, 0x35)
*
*   DUPES: [24,31,3, 24,28,0, 24,33,2] -> 24,27,1
*   NEW  : 24,31,3  -> 24,27,50 (0x32) | patchROM8(0x0872B751 - 0x08000000, 0x32)
*          24,33,2  -> 24,27,70 (0x46) | patchROM8(0x0872B839 - 0x08000000, 0x46)
*/
s8 findProxyWarpIdForDuplicateWarps(s8 *mapGroup, s8 *mapNum, s8 *warpId)
{

    // All dupe warps are in map group 24
    if ((*mapGroup) != 24) 
    {
        return -1;
    } 

    if ((*mapNum) == 24 && (*warpId) == 17 && gSaveBlock1Ptr->pos.y > 0x10) 
    { 
        // 24,24,23
        return 0x32;
    }

    if ((*mapNum) == 24 && (*warpId) == 12 && gSaveBlock1Ptr->pos.x > 0x6) 
    { 
        if (gSaveBlock1Ptr->pos.y > 0x7)
        {
            // 24,24,14
            return 0x33;
        }
        else 
        {
            // 24,24,21
            return 0x34;
        }
        
        return;
    }

    if ((*mapNum) == 24 && (*warpId) == 4 && gSaveBlock1Ptr->pos.y > 0xF) 
    { 
        // 24,25,9
        return 0x35;
    }

    if ((*mapNum) == 27 && (*warpId) == 1 && gSaveBlock1Ptr->pos.x > 0x7) 
    { 
        if (gSaveBlock1Ptr->pos.y > 0xD)
        {
            // 24,31,3 
            return 0x32;
        }
        else 
        {
            // 24,33,2
            return 0x46;
        }
        
        return;
    }

    return -1;
}

void InterceptWarp(s8 *mapGroup, s8 *mapNum, s8 *warpId, s8 *x, s8 *y)
{
    u16 remappedWarpIndex;
    s8 proxyId;
    xPositionCorrection = -1;
    yPositionCorrection = -1;

    if (gSaveBlock2Ptr->optionsTextSpeed == OPTIONS_TEXT_SPEED_SLOW) 
    {
        return;
    }

    if ((*warpId) == -1)
    {
        if ((*mapGroup) == 8 && (*mapNum) == 1)
        {
            // Allow battle normans gym after tutorial
            VarSet(VAR_PETALBURG_GYM_STATE, 6);
            FlagSet(FLAG_HIDE_PETALBURG_CITY_WALLY);
            FlagSet(FLAG_HIDE_PETALBURG_GYM_WALLY);
        }

        return;
    }

    proxyId = findProxyWarpIdForDuplicateWarps(mapGroup, mapNum, warpId);

    if (proxyId != -1) 
    {
        remappedWarpIndex = WarpRemapBinarySearch(mapGroup, mapNum, &proxyId);
    }
    else 
    {
        remappedWarpIndex = WarpRemapBinarySearch(mapGroup, mapNum, warpId);
    }
    
    if (remappedWarpIndex < RANDOM_WARP_LIMIT) 
    {
        bool8 needsXOffsetShift = warpNeedsXOffetShift(mapGroup, mapNum, warpId);

        (*mapGroup) = gWarpRemappingList[remappedWarpIndex].toMapGroup;
        (*mapNum)   = gWarpRemappingList[remappedWarpIndex].toMapNum;
        (*warpId)   = gWarpRemappingList[remappedWarpIndex].toWarpId;

        
        fixPositionAfterWarp(mapGroup, mapNum, warpId, x, y);

        if (needsXOffsetShift)
        {
            xPositionCorrection = xPositionCorrection - 1;
        }

    }

    ApplyFixesForSpecialWarps(mapGroup, mapNum, warpId);
    ApplyFixesForEveryWarp();
}

void NewGameRandomWarpsInit()
{
    // Any special things when a new game starts

    // To get though first route
    AddBagItem(ITEM_REPEL, 1);

    // The reason for adding the acro bike is that we start with the mach bike (and a player might not know you can quick switch)
    // The randomisation logic places which new connections are possible based on which flag granting locations are currently 'in logic'
    // e.g if the abandoned ship 'key room' is accessible to the player it's legal to place somthing behind the locked door
    // However it's not smart enough to know that you can't lock somthing behind the mach bike AND acro bike at the same time, once the player can reach the bike shop  
    AddBagItem(ITEM_ACRO_BIKE, 1);

    FlagSet(FLAG_SYS_B_DASH);
}

void CorrectPositionAfterIntercept()
{
    if (xPositionCorrection == -2)
    {
        gSaveBlock1Ptr->pos.x = gSaveBlock1Ptr->pos.x - 1;
    }
    else if (xPositionCorrection > -1)
    {
        gSaveBlock1Ptr->pos.x = xPositionCorrection;
    }

    if (yPositionCorrection != -1) 
    {
        gSaveBlock1Ptr->pos.y = yPositionCorrection;
    }

    xPositionCorrection = -1;
    yPositionCorrection = -1;
}

void resetPositionCorrection() {
    xPositionCorrection = -1;
    yPositionCorrection = -1;
}