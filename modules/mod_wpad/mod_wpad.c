/*
 *  Copyright © 2010 Joseba García Etxebarria <joseba.gar@gmail.com>
 *
 *  mod_wpad is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  mod_wpad is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bgddl.h"
#include "libvideo.h"
#include "wiiuse/wpad.h"

#ifdef TARGET_WII
// Checks wether a given wpad number corresponds to a Wii Balance Board
int is_bb(int i) {
    u32 devtype;

    WPAD_Probe(i, &devtype);
    if (devtype==WPAD_EXP_WIIBOARD)
        return 1;
    else
        return 0;
}
#endif

/* Check the status of each Wiimote */
int modwpad_is_ready( INSTANCE * my, int * params )
{
#ifdef TARGET_WII
    int res=0;
    u32 type;

    res = WPAD_Probe(params[0], &type);
    if(res == 0)
        return 1;   // So it's true in BennuGD code
    else
        return res;
#else
    return -1;  // No wiimote
#endif
}

// Check whether a given WPAD is really a Wii Balance Board
int modwpad_is_balanceboard( INSTANCE * my, int * params )
{
// WPad is supposed to be already initialized (by libjoy)
#ifdef TARGET_WII
    return is_bb(params[0]);
#else
    return 0;
#endif
}

// Get data from the Wii Balance Board
int modwpad_query_balanceboard( INSTANCE * my, int * params )
{
#ifdef TARGET_WII
    struct expansion_t exp;

    // First of all, check if the given wpad is a balanceboard
    if (is_bb(params[0]) == 0)
        return 0;

    // Return the info the user asked for
    WPAD_SetVRes(params[0], scr_width, scr_height);
    WPAD_Expansion(params[0], &exp);
    switch(params[1]) {
        case 0:     // X position of the center of gravity
            return exp.wb.x;
        case 1:     // Y position of the center of gravity
            return exp.wb.y;
        case 2:     // Weight measured on the TOP-LEFT base
            return exp.wb.tl;
        case 3:     // Weight in TOP-RIGHT
            return exp.wb.tr;
        case 4:     // Weight in BOTTOM-LEFT
            return exp.wb.bl;
        case 5:     // Weight in BOTTOM-RIGHT
            return exp.wb.br;
    }
#endif

    return 0;
}

// Get the battery level for a particular Wiimote
int modwpad_battery_level( INSTANCE * my, int * params )
{
#ifdef TARGET_WII
    return (int)WPAD_BatteryLevel(params[0]);
#else
    return 0;
#endif
}

// Make a controller rumble (or stop rumbling)
void modwpad_rumble( INSTANCE * my, int * params)
{
#ifdef TARGET_WII
    WPAD_Rumble(params[0], params[1]);
#endif
}


/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */
#ifndef __STATIC__
DLSYSFUNCS  __bgdexport( mod_say, functions_exports )[] =
{
    { "WPAD_IS_READY"          , "I" , TYPE_INT, modwpad_is_ready           },
    { "WPAD_IS_BALANCEBOARD"   , "I" , TYPE_INT, modwpad_is_balanceboard    },
    { "WPAD_QUERY_BALANCEBOARD", "II", TYPE_INT, modwpad_query_balanceboard },
    { "WPAD_BATTERY_LEVEL"     , "I" , TYPE_INT, modwpad_battery_level      },
    { "WPAD_RUMBLE"            , "II", TYPE_UNDEFINED, modwpad_rumble       },
    { 0         , 0  , 0             , 0              }
};
#endif

/* ----------------------------------------------------------------- */
