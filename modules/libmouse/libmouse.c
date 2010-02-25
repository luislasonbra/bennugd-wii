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

/* --------------------------------------------------------------------------- */

#if defined(TARGET_MAC) || defined(TARGET_WII)
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "bgddl.h"
#include "dlvaracc.h"

#include "libgrbase.h"
#include "libvideo.h"
#include "libblit.h"
#include "librender.h"

#include "sysprocs_st.h"
#include "offsets.h"

/* --------------------------------------------------------------------------- */

static int last_mousex = 0;
static int last_mousey = 0;
static int last_mousez = 0;
static int last_mousefile = 0;
static int last_mousegraph = 0;
static int last_mouseangle = 0;
static int last_mousesize = 0;
static int last_mouseflags = 0;
static int last_mouseregion = 0;
static int last_mousecenterx = -1;
static int last_mousecentery = -1;

static GRAPH * mouse_map = NULL;

/* --------------------------------------------------------------------------- */
#ifndef __STATIC__

#define MOUSEX              0
#define MOUSEY              1
#define MOUSEZ              2
#define MOUSEFILE           3
#define MOUSEGRAPH          4
#define MOUSEANGLE          5
#define MOUSESIZE           6
#define MOUSEFLAGS          7
#define MOUSEREGION         8
#define MOUSELEFT           9
#define MOUSEMIDDLE         10
#define MOUSERIGHT          11
#define MOUSEWHEELUP        12
#define MOUSEWHEELDOWN      13

/* --------------------------------------------------------------------------- */

char * __bgdexport( libmouse, globals_def ) =
    "STRUCT mouse\n"
    "x = 99999, y = 99999;\n"
    "z = -512;\n"
    "file;\n"
    "graph;\n"
    "angle;\n"
    "size = 100;\n"
    "flags;\n"
    "region;\n"
    "left, middle, right;\n"
    "wheelup, wheeldown;\n"
    "END\n";

/* --------------------------------------------------------------------------- */

DLVARFIXUP __bgdexport( libmouse, globals_fixup )[] =
{
    /* Nombre de variable global, puntero al dato, tama�o del elemento, cantidad de elementos */

    { "mouse.x"         , NULL, -1, -1 },
    { "mouse.y"         , NULL, -1, -1 },
    { "mouse.z"         , NULL, -1, -1 },
    { "mouse.file"      , NULL, -1, -1 },
    { "mouse.graph"     , NULL, -1, -1 },
    { "mouse.angle"     , NULL, -1, -1 },
    { "mouse.size"      , NULL, -1, -1 },
    { "mouse.flags"     , NULL, -1, -1 },
    { "mouse.region"    , NULL, -1, -1 },
    { "mouse.left"      , NULL, -1, -1 },
    { "mouse.middle"    , NULL, -1, -1 },
    { "mouse.right"     , NULL, -1, -1 },
    { "mouse.wheelup"   , NULL, -1, -1 },
    { "mouse.wheeldown" , NULL, -1, -1 },

    { NULL              , NULL, -1, -1 }
};
#endif
/* --------------------------------------------------------------------------- */

/*
 *  FUNCTION : mouse_events
 *
 *  Process all pending SDL events, updating all global variables
 *  and handling debug key presses
 *  and cannot be changed
 *
 *  PARAMS :
 *      None
 *
 *  RETURN VALUE :
 *      None
 */

void do_mouse_events()
{
    SDL_Event e ;
    static int last_mouse_x = -1, last_mouse_y = -1 ;

    /* Update events */

    /* Mouse.x/y change affects the cursor directly */

    if (
        ( last_mouse_x != -1 && GLOINT32( MOUSEX ) != last_mouse_x ) ||
        ( last_mouse_y != -1 && GLOINT32( MOUSEY ) != last_mouse_y ) )
    {
        if ( scale_resolution != 0 )
        {
            SDL_WarpMouse( GLOINT32( MOUSEX ) / ( (double)screen->w / (double)scale_screen->w ), GLOINT32( MOUSEY ) / ( (double)screen->h / (double)scale_screen->h ) ) ;
        }
        else if ( enable_scale || scale_mode != SCALE_NONE )
        {
            SDL_WarpMouse( GLOINT32( MOUSEX ) * 2 , GLOINT32( MOUSEY ) * 2 ) ;
        }
        else
        {
            SDL_WarpMouse( GLOINT32( MOUSEX ), GLOINT32( MOUSEY ) ) ;
        }
    }

    /* Process the independant mouse events */

    GLODWORD( MOUSEWHEELUP   ) = 0 ;
    GLODWORD( MOUSEWHEELDOWN ) = 0 ;

    while ( SDL_PeepEvents( &e, 1, SDL_GETEVENT, SDL_MOUSEEVENTMASK ) > 0 )
    {
        switch ( e.type )
        {
            case SDL_MOUSEMOTION:
                if ( scale_resolution != 0 )
                {
                    GLOINT32( MOUSEX ) = e.motion.x * ( (double)screen->w / (double)scale_screen->w );
                    GLOINT32( MOUSEY ) = e.motion.y * ( (double)screen->h / (double)scale_screen->h );
                }
                else if ( enable_scale || scale_mode != SCALE_NONE )
                {
                    GLOINT32( MOUSEX ) = e.motion.x / 2 ;
                    GLOINT32( MOUSEY ) = e.motion.y / 2 ;
                }
                else
                {
                    GLOINT32( MOUSEX ) = e.motion.x ;
                    GLOINT32( MOUSEY ) = e.motion.y ;
                }
                break ;

            case SDL_MOUSEBUTTONDOWN:
                if ( e.button.button == SDL_BUTTON_LEFT )      GLODWORD( MOUSELEFT )     = 1 ;
                if ( e.button.button == SDL_BUTTON_MIDDLE )    GLODWORD( MOUSEMIDDLE )   = 1 ;
                if ( e.button.button == SDL_BUTTON_RIGHT )     GLODWORD( MOUSERIGHT )    = 1 ;
                if ( e.button.button == SDL_BUTTON_WHEELUP )   GLODWORD( MOUSEWHEELUP )++ ;
                if ( e.button.button == SDL_BUTTON_WHEELDOWN ) GLODWORD( MOUSEWHEELDOWN )++ ;
                break ;

            case SDL_MOUSEBUTTONUP:
                if ( e.button.button == SDL_BUTTON_LEFT )      GLODWORD( MOUSELEFT )      = 0 ;
                if ( e.button.button == SDL_BUTTON_MIDDLE )    GLODWORD( MOUSEMIDDLE )    = 0 ;
                if ( e.button.button == SDL_BUTTON_RIGHT )     GLODWORD( MOUSERIGHT )     = 0 ;
                break ;
        }
    }

    last_mouse_x = GLOINT32( MOUSEX ) ;
    last_mouse_y = GLOINT32( MOUSEY ) ;
}

/* --------------------------------------------------------------------------- */

/*
 *  FUNCTION : mouse_info
 *
 *  Returns information about the mouse
 *
 *  PARAMS :
 *      ptr             Void pointer, used for compatibility with DLL-type objects
 *      clip            Region to fill with bounding box
 *
 *  RETURN VALUE :
 *      1 if the mouse has changed since last call
 */

int mouse_info( INSTANCE * i, REGION * clip, int * z, int * drawme )
{
    int mousex ;
    int mousey ;
    int mousez ;
    int mousefile ;
    int mousegraph ;
    int mouseangle;
    int mousesize;
    int mouseflags;
    int mouseregion;
    int changed;

    * z = mousez = GLOINT32( MOUSEZ );

    mousefile   = GLODWORD( MOUSEFILE );
    mousegraph  = GLODWORD( MOUSEGRAPH );

    mouse_map = ( mousegraph > 0 ) ? bitmap_get( mousefile, mousegraph ) : NULL ;
    if ( !mouse_map )
    {
        * drawme = 0;
        /*
        clip->x = clip->x2 = -2;
        clip->y = clip->y2 = -2;
        */
        return 0;
    }

    mousex      = GLOINT32( MOUSEX );
    mousey      = GLOINT32( MOUSEY );
//    mousez      = GLODWORD( MOUSEZ );
    mouseangle  = GLOINT32( MOUSEANGLE );
    mousesize   = GLOINT32( MOUSESIZE );
    mouseflags  = GLODWORD( MOUSEFLAGS );
    mouseregion = GLOINT32( MOUSEREGION );

    * drawme = 1;

    changed =
        ( mouse_map && mouse_map->modified ) ||
        last_mousex      != mousex      ||
        last_mousey      != mousey      ||
        last_mousez      != mousez      ||
        last_mousefile   != mousefile   ||
        last_mousegraph  != mousegraph  ||
        last_mouseangle  != mouseangle  ||
        last_mousesize   != mousesize   ||
        last_mouseflags  != mouseflags  ||
        last_mouseregion != mouseregion ||
        (
            mouse_map->ncpoints &&
            (
                last_mousecenterx != mouse_map->cpoints[0].x ||
                last_mousecentery != mouse_map->cpoints[0].y
            )
        )
        ;

    if ( changed )
    {
        last_mousex         = mousex ;
        last_mousey         = mousey ;
        last_mousez         = mousez ;
        last_mousefile      = mousefile ;
        last_mousegraph     = mousegraph ;
        last_mouseangle     = mouseangle ;
        last_mousesize      = mousesize ;
        last_mouseflags     = mouseflags ;
        last_mouseregion    = mouseregion ;
        if ( mouse_map->ncpoints )
        {
            last_mousecenterx = mouse_map->cpoints[0].x;
            last_mousecentery = mouse_map->cpoints[0].y;
        }
        else
        {
            last_mousecenterx = CPOINT_UNDEFINED;
            last_mousecentery = CPOINT_UNDEFINED;
        }

        gr_get_bbox(
            clip,
            0,
            mousex,
            mousey,
            mouseflags,
            mouseangle ,
            mousesize ,
            mousesize ,
            mouse_map ) ;
    }

    return changed;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : mouse_draw
 *
 *  Draws the mouse graphic at screen
 *
 *  PARAMS :
 *      ptr             Void pointer, used for compatibility with DLL-type objects
 *      clip            Clipping region
 *
 *  RETURN VALUE :
 *      None
 */

void mouse_draw( INSTANCE * i, REGION * clip )
{
    int r ;
    REGION region;

    r = GLOINT32( MOUSEREGION ) ;
    if ( r < 0 || r > 31 ) r = 0 ;

    region = regions[r];
    if ( clip ) region_union( &region, clip );

    if ( GLOINT32( MOUSEANGLE ) || GLOINT32( MOUSESIZE ) != 100 )
        gr_rotated_blit(
            0,
            &region,
            GLOINT32( MOUSEX ),
            GLOINT32( MOUSEY ),
            GLODWORD( MOUSEFLAGS ),
            GLOINT32( MOUSEANGLE ),
            GLOINT32( MOUSESIZE ),
            GLOINT32( MOUSESIZE ),
            mouse_map ) ;
    else
        gr_blit(
            0,
            &region,
            GLOINT32( MOUSEX ),
            GLOINT32( MOUSEY ),
            GLODWORD( MOUSEFLAGS ),
            mouse_map ) ;

    mouse_map->modified = 0;
}

/* --------------------------------------------------------------------------- */

/* Bigest priority first execute
   Lowest priority last execute */
#ifndef __STATIC__
HOOK __bgdexport( libmouse, handler_hooks )[] =
{
    { 4800, do_mouse_events },
    { 0, NULL }
} ;

/* --------------------------------------------------------------------------- */

char * __bgdexport( libmouse, modules_dependency )[] =
{
    "libsdlhandler",
    "libgrbase",
    "libvideo",
    "libblit",
    "librender", // Add by Sandman
    NULL
};
#endif
/* --------------------------------------------------------------------------- */
#ifdef __STATIC__
void libmouse_init()
#else
void __bgdexport( libmouse, module_initialize )()
#endif
{
    gr_new_object( GLOINT32( MOUSEZ ), mouse_info, mouse_draw, 0 );
}

/* --------------------------------------------------------------------------- */
