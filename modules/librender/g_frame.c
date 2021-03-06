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

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define __LIB_RENDER
#include "librender.h"
#include "offsets.h"

/* --------------------------------------------------------------------------- */

#define FPS_INTIAL_VALUE    25
#define FPS_INTIAL_SKIP     2

/* --------------------------------------------------------------------------- */

int fps_value = FPS_INTIAL_VALUE ;
int max_jump = FPS_INTIAL_SKIP ;
float frame_ms = 1000.0 / FPS_INTIAL_VALUE ; /* 40.0 ; */

uint32_t frame_count = 0 ;
int last_frame_ticks = 0 ;
int jump = 0 ;

int FPS_count = 0 ;
int FPS_init = 0 ;

int FPS_count_sync = 0 ;
int FPS_init_sync = 0 ;

float ticks_per_frame = 0;
float fps_partial = 0;

/* --------------------------------------------------------------------------- */
/* Inicializaci�n y controles de tiempo                                        */
/* --------------------------------------------------------------------------- */

/*
 *  FUNCTION : gr_set_fps
 *
 *  Change the game fps and frameskip values
 *
 *  PARAMS :
 *      fps         New number of frames per second
 *      jump        New value of maximum frameskip
 *
 *  RETURN VALUE :
 *      None
 */

void gr_set_fps( int fps, int skip )
{
    if ( fps == fps_value && skip == max_jump ) return ;

    frame_ms = fps ? 1000.0 / ( float ) fps : 0.0 ;
    max_jump = skip ;
    fps_value = ( int ) fps;

    FPS_init_sync = FPS_init = 0 ;
    FPS_count_sync = FPS_count = 0 ;

    jump = 0;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_wait_frame
 *
 *  Wait for the next frame start.
 *
 *  PARAMS :
 *      None
 *
 *  RETURN VALUE :
 *      None
 */

void gr_wait_frame()
{
    int frame_ticks ;

    frame_count++ ;

    /* -------------- */

    /* Tomo Tick actual */
    frame_ticks = SDL_GetTicks() ;

    if ( !FPS_init_sync )
    {
        FPS_init_sync = FPS_init = SDL_GetTicks() ;
        FPS_count_sync = FPS_count = 0 ;
        jump = 0;

        /* Tiempo inicial del nuevo frame */
        last_frame_ticks = frame_ticks ;

        return;
    }

    /* Tiempo transcurrido total del ejecucion del ultimo frame (Frame time en ms) */
    * ( float * ) &GLODWORD( librender, FRAME_TIME ) = ( frame_ticks - last_frame_ticks ) / 1000.0f ;

    /* -------------- */

    FPS_count++ ;

    /* -------------- */

    if ( fps_value )
    {
        FPS_count_sync++ ;

        ticks_per_frame = ( ( float ) ( frame_ticks - FPS_init_sync ) ) / ( float ) FPS_count_sync ;
        fps_partial = 1000.0 / ticks_per_frame ;

        if ( fps_partial == fps_value )
        {
            FPS_init_sync = frame_ticks ;
            FPS_count_sync = 0 ;
            jump = 0;
        }
        else if ( fps_partial > fps_value )
        {
            int delay = FPS_count_sync * frame_ms - ( frame_ticks - FPS_init_sync ) ;

            if ( delay > 0 )
            {
                SDL_Delay( delay ) ;

                /* Reajust after delay */
                frame_ticks = SDL_GetTicks() ;

                ticks_per_frame = ( ( float ) ( frame_ticks - FPS_init_sync ) ) / ( float ) FPS_count_sync ;
                fps_partial = 1000.0 / ticks_per_frame ;
            }

            jump = 0 ;
        }
        else
        {
            if ( jump < max_jump ) /* Como no me alcanza el tiempo, voy a hacer skip */
                jump++ ; /* No dibujar el frame */
            else
            {
                FPS_init_sync = frame_ticks ;
                FPS_count_sync = 0 ;
                jump = 0 ;
            }
        }
    }

    /* Si paso 1 segundo o mas desde la ultima lectura */
    if ( frame_ticks - FPS_init >= 1000 )
    {
        if ( fps_value )
        {
            GLODWORD( librender, SPEED_GAUGE ) = FPS_count /*fps_partial*/ * 100.0 / fps_value ;
        }
        else
        {
            GLODWORD( librender, SPEED_GAUGE ) = 100 ;
        }

        GLODWORD( librender, FPS ) = FPS_count ;

        FPS_init = frame_ticks ;
        FPS_count = 0 ;
    }

    /* Tiempo inicial del nuevo frame */
    last_frame_ticks = frame_ticks ;
}

/* --------------------------------------------------------------------------- */

static SDL_Color palette[256];

void gr_refresh_palette()
{
    int n ;

    if ( sys_pixel_format->depth > 8 )
    {
        if ( sys_pixel_format->palette )
        {
            for ( n = 0 ; n < 256 ; n++ )
            {
                sys_pixel_format->palette->colorequiv[ n ] = gr_map_rgb
                        (
                            sys_pixel_format,
                            sys_pixel_format->palette->rgb[ n ].r,
                            sys_pixel_format->palette->rgb[ n ].g,
                            sys_pixel_format->palette->rgb[ n ].b
                        ) ;
            }
        }
    }
    else if ( sys_pixel_format->depth == 8 )
    {
        if ( sys_pixel_format->palette )
        {
            for ( n = 0 ; n < 256 ; n++ )
            {
                palette[ n ].r = sys_pixel_format->palette->rgb[ n ].r;
                palette[ n ].g = sys_pixel_format->palette->rgb[ n ].g;
                palette[ n ].b = sys_pixel_format->palette->rgb[ n ].b;
            }
        }
        else
        {
            uint8_t * pal = default_palette;
            for ( n = 0 ; n < 256 ; n++ )
            {
                palette[ n ].r = *pal++;
                palette[ n ].g = *pal++;
                palette[ n ].b = *pal++;
            }
        }
        if ( scale_screen )
            SDL_SetColors( scale_screen, palette, 0, 256 ) ;
        else
            SDL_SetColors( screen, palette, 0, 256 ) ;
    }

    palette_changed = 0;
    trans_table_updated = 0 ;
}

/* --------------------------------------------------------------------------- */

void gr_draw_frame()
{
    if ( jump ) return ;

    /* Actualiza paleta */

    if ( palette_changed ) gr_refresh_palette();

    if ( !trans_table_updated ) gr_make_trans_table();

    /* Bloquea el bitmap de pantalla */

    if ( gr_lock_screen() < 0 ) return ;

    /* Dibuja la pantalla */

    gr_draw_screen( scrbitmap, GLODWORD( librender, RESTORETYPE ), GLODWORD( librender, DUMPTYPE ) );

    /* Fading */

    if ( fade_on || fade_set )
    {
        gr_fade_step() ;
        if ( background ) background->modified = 1 ;
    }

    /* Actualiza la paleta y la pantalla */

    gr_unlock_screen() ;

}

/* --------------------------------------------------------------------------- */
#ifdef __STATIC__
void librender_init()
#else
void __bgdexport( librender, module_initialize )()
#endif
{
    if ( !SDL_WasInit( SDL_INIT_TIMER ) ) SDL_InitSubSystem( SDL_INIT_TIMER );
}

/* --------------------------------------------------------------------------- */
#ifdef __STATIC__
void librender_finalize()
#else
void __bgdexport( librender, module_finalize )()
#endif
{
    if ( SDL_WasInit( SDL_INIT_TIMER ) ) SDL_QuitSubSystem( SDL_INIT_TIMER );
}

/* --------------------------------------------------------------------------- */
