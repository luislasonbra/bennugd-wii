/*
 *  Copyright � 2006-2009 SplinterGU (Fenix/Bennugd)
 *  Copyright � 2002-2006 Fenix Team (Fenix)
 *  Copyright � 1999-2002 Jos� Luis Cebri�n Pag�e (Fenix)
 *
 *  This file is part of Bennu - Game Development
 *
 *  Bennu is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Bennu is distributed in the hope that it will be useful,
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
#include "xstrings.h"

/* ---------------------------------------------------------------------- */

int modsay_say( INSTANCE * my, int * params )
{
// Using printf in the Wii causes artifacts when combined with
// SDL
#ifdef TARGET_WII
    FILE *fd;

    fd = fopen("stdout.txt", "a");
    if(fd != NULL) {
        fprintf(fd, "%s\n", string_get( params[0] ));
        fflush( fd );
        fclose( fd );
    }
#else
    /* Show debugging info also in stdout */
    printf( "%s\n", string_get( params[0] ) );
    fflush( stdout );
#endif
    string_discard( params[0] ) ;
    
    return 1;
}

/* ---------------------------------------------------------------------- */

int modsay_say_fast( INSTANCE * my, int * params )
{
// Using printf in the Wii causes artifacts when combined with
// SDL
#ifdef TARGET_WII
    FILE *fd;

    fd = fopen("stdout.txt", "a");
    if(fd != NULL) {
        fprintf(fd, "%s\n", string_get( params[0] ));
        fclose( fd );
    }
#else
    /* Show debugging info also in stdout */
    printf( "%s\n", string_get( params[0] ) );
#endif
    string_discard( params[0] ) ;
    
    return 1;
}

/* ----------------------------------------------------------------- */
/* Declaracion de funciones                                          */
#ifndef __STATIC__
DLSYSFUNCS  __bgdexport( mod_say, functions_exports )[] =
{
    { "SAY"     , "S", TYPE_UNDEFINED, modsay_say     },
    { "SAY_FAST", "S", TYPE_UNDEFINED, modsay_say_fast},
    { 0         , 0  , 0             , 0              }
};
#endif

/* ----------------------------------------------------------------- */
