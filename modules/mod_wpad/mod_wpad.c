/*
 *  Copyright � 2010 Joseba Garc�a Etxebarria <joseba.gar@gmail.com>
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
#ifdef TARGET_WII
#include "wiiuse/wpad.h"
#endif

#define WPAD_BATT        0
#define WPAD_X           1
#define WPAD_Y           2
#define WPAD_Z           3
#define WPAD_ANGLE       4
#define WPAD_PITCH       5
#define WPAD_ROLL        6
#define WPAD_ACCELX      7
#define WPAD_ACCELY      8
#define WPAD_ACCELZ      9
#define WPAD_IS_BB       10
#define WPAD_WTL         3
#define WPAD_WTR         4
#define WPAD_WBL         5
#define WPAD_WBR         6

#ifndef __STATIC__
DLCONSTANT __bgdexport( mod_wpad, constants_def )[] =
{
    { "WPAD_BATT",      TYPE_INT,   WPAD_BATT   },
    { "WPAD_X",         TYPE_INT,   WPAD_X      },
    { "WPAD_Y",         TYPE_INT,   WPAD_Y      },
    { "WPAD_Z",         TYPE_INT,   WPAD_Z      },
    { "WPAD_ANGLE",     TYPE_INT,   WPAD_ANGLE  },
    { "WPAD_PITCH",     TYPE_INT,   WPAD_PITCH  },
    { "WPAD_ROLL",      TYPE_INT,   WPAD_ROLL   },
    { "WPAD_ACCELX",    TYPE_INT,   WPAD_ACCELX },
    { "WPAD_ACCELY",    TYPE_INT,   WPAD_ACCELY },
    { "WPAD_ACCELZ",    TYPE_INT,   WPAD_ACCELZ },
    { "WPAD_IS_BB",     TYPE_INT,   WPAD_IS_BB  },
    { "WPAD_WTL",       TYPE_INT,   WPAD_WTL    },
    { "WPAD_WTR",       TYPE_INT,   WPAD_WTR    },
    { "WPAD_WBL",       TYPE_INT,   WPAD_WBL    },
    { "WPAD_WBR",       TYPE_INT,   WPAD_WBR    },

    { NULL              , 0       , 0           }
} ;
#endif

#ifdef TARGET_WII
// Checks wether a given wpad number corresponds to a Wii Balance Board
int is_bb(int i) {
    u32 type;

    WPAD_Probe(i, &type);
    if (type==WPAD_EXP_WIIBOARD)
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

// Get info from generic controller
int modwpad_info( INSTANCE * my, int * params )
{
#ifdef TARGET_WII
    u32 type;
    WPADData *wd;

    // Ensure it's been correctly initialized
    if( WPAD_Probe(params[0], &type) != 0 )
        return 0;

    // Return the info the user asked for
    wd = WPAD_Data(params[0]);
    switch(params[1]) {
        case 0:     // Battery level (0<level<256)
            return (int)WPAD_BatteryLevel(params[0]);
        case 1:     // X position
            if( wd->ir.valid )  // Only return data if wiimote pointing @ screen
                return wd->ir.x;
            else
                return 0;
        case 2:     // Y position
            if( wd->ir.valid )
                return wd->ir.y;
            else
                return 0;
        case 3:     // Z position (distance from screen in m)
            if( wd->ir.raw_valid )
                return wd->ir.z;
            else
                return 0;
        case 4:     // Angle, BennuGD likes 1/1000th of degrees
            if( wd->ir.valid )
                return (int)(wd->ir.angle*1000. / 180.0 * M_PI);
            else
                return 0;
        case 5:     // Pitch angle, BennuGD likes 1/1000th of degrees
            return (int)(wd->orient.pitch*1000.);
        case 6:     // Roll angle,  BennuGD likes 1/1000th of degrees
            return (int)(wd->orient.roll*1000.);    // Uses accelerometer
        case 7:     // Acceleration in x axis
            return wd->accel.x;
        case 8:     // Acceleration in y axis
            return wd->accel.y;
        case 9:     // Acceleration in z axis
            return wd->accel.z;
        case 10:    // Check wether controller is a balance board
            return is_bb(params[0]);
    }
#endif

    return 0;
}

// Get data from the Wii Balance Board
int modwpad_info_bb( INSTANCE * my, int * params )
{
#ifdef TARGET_WII
    struct expansion_t exp;
    u32 type;

    // First of all, check if the given wpad is a balanceboard
    if (is_bb(params[0]) == 0)
        return 0;

    // Ensure it's been correctly initialized
    if( WPAD_Probe(params[0], &type) != 0 )
        return 0;

    // Return the info the user asked for
    WPAD_SetVRes(params[0], scr_width, scr_height);
    WPAD_Expansion(params[0], &exp);
    switch(params[1]) {
        case 0:     // Battery level (0<level<256)
            return (int)WPAD_BatteryLevel(params[0]);
        case 1:     // X position
            return exp.wb.x;
        case 2:     // Y position
            return exp.wb.y;
        case 3:     // Weight measured on the TOP-LEFT base (Balance Board)
            return exp.wb.tl;
        case 4:     // Weight in TOP-RIGHT
            return exp.wb.tr;
        case 5:     // Weight in BOTTOM-LEFT
            return exp.wb.bl;
        case 6:     // Weight in BOTTOM-RIGHT
            return exp.wb.br;
    }
#endif

    return 0;
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
DLSYSFUNCS  __bgdexport( mod_wpad, functions_exports )[] =
{
    { "WPAD_IS_READY"          , "I" , TYPE_INT, modwpad_is_ready           },
    { "WPAD_INFO"              , "II", TYPE_INT, modwpad_info               },
    { "WPAD_INFO_BB"           , "II", TYPE_INT, modwpad_info_bb            },
    { "WPAD_RUMBLE"            , "II", TYPE_UNDEFINED, modwpad_rumble       },
    { 0         , 0  , 0             , 0              }
};
#endif

/* ----------------------------------------------------------------- */