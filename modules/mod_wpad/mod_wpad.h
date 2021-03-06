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

#ifndef __WPAD_H
#define __WPAD_H

#include <bgddl.h>
#include <instance_st.h>

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

/* Function declaration */
extern int modwpad_is_ready( INSTANCE * my, int * params );
extern int modwpad_info( INSTANCE * my, int * params );
extern int modwpad_info_bb( INSTANCE * my, int * params );
extern void modwpad_rumble( INSTANCE * my, int * params);


#ifdef __STATIC__
DLCONSTANT wpad_constants_def[] =
#else
DLCONSTANT __bgdexport( mod_wpad, constants_def )[] =
#endif
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

/* ----------------------------------------------------------------- */
/* Function declarations                                             */
#ifdef __STATIC__
DLSYSFUNCS wpad_functions_exports[] =
#else
DLSYSFUNCS  __bgdexport( mod_wpad, functions_exports )[] =
#endif
{
    { "WPAD_IS_READY"          , "I" , TYPE_INT, SYSMACRO(modwpad_is_ready)           },
    { "WPAD_INFO"              , "II", TYPE_INT, SYSMACRO(modwpad_info)               },
    { "WPAD_INFO_BB"           , "II", TYPE_INT, SYSMACRO(modwpad_info_bb)            },
    { "WPAD_RUMBLE"            , "II", TYPE_UNDEFINED, SYSMACRO(modwpad_rumble)       },
    { 0         , 0  , 0             , 0              }
};

#endif
