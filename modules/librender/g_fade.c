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

#include <string.h>
#include <stdlib.h>

#define __LIB_RENDER
#include "librender.h"
#include "offsets.h"

/* -------------------------------------------------------------------------- */

SDL_Color vpalette[ 256 ] ;

int fade_inc = 0 ;
int fade_on = 0 ;
int fade_set = 0 ;
int fade_step = 64 ;

SDL_Color fade_from ;
SDL_Color fade_to ;
SDL_Color fade_pos = { 100, 100, 100 };

/* -------------------------------------------------------------------------- */

static void activate_vpalette()
{
    int n ;

    if ( !screen ) return ;

    if (( sys_pixel_format ) && ( sys_pixel_format->palette ) )
    {
        if ( sys_pixel_format->depth > 8 )
        {
            for ( n = 0 ; n < 256 ; n++ )
                sys_pixel_format->palette->colorequiv[ n ] = SDL_MapRGB( screen->format, sys_pixel_format->palette->rgb[ n ].r, sys_pixel_format->palette->rgb[ n ].g, sys_pixel_format->palette->rgb[ n ].b ) ;
        }
        else
        {
            for ( n = 0 ; n < 256 ; n++ )
            {
                if ( fade_pos.r <= 100 )
                    vpalette[ n ].r = sys_pixel_format->palette->rgb[ n ].r * fade_pos.r / 100;
                else
                    vpalette[ n ].r = sys_pixel_format->palette->rgb[ n ].r + ( 255 - sys_pixel_format->palette->rgb[ n ].r ) * ( fade_pos.r - 100 ) / 100;

                if ( fade_pos.g <= 100 )
                    vpalette[ n ].g = sys_pixel_format->palette->rgb[ n ].g * fade_pos.g / 100;
                else
                    vpalette[ n ].g = sys_pixel_format->palette->rgb[ n ].g + ( 255 - sys_pixel_format->palette->rgb[ n ].g ) * ( fade_pos.g - 100 ) / 100;

                if ( fade_pos.b <= 100 )
                    vpalette[ n ].b = sys_pixel_format->palette->rgb[ n ].b * fade_pos.b / 100;
                else
                    vpalette[ n ].b = sys_pixel_format->palette->rgb[ n ].b + ( 255 - sys_pixel_format->palette->rgb[ n ].b ) * ( fade_pos.b - 100 ) / 100;
            }

            if ( scale_screen )
                SDL_SetColors( scale_screen, vpalette, 0, 256 ) ;
            else
                SDL_SetColors( screen, vpalette, 0, 256 ) ;
        }
    }
}

/* -------------------------------------------------------------------------- */

void gr_fade_init( int r, int g, int b, int speed )
{
    if ( fade_pos.r == r && fade_pos.g == g && fade_pos.b == b )
    {
        fade_on = 0 ;
        return ;
    }

    fade_inc = speed;
    fade_step = 0;
    fade_on = 1 ;
    fade_from = fade_pos;
    fade_to.r = ( r > 200 ) ? 200 : r ;
    fade_to.g = ( g > 200 ) ? 200 : g ;
    fade_to.b = ( b > 200 ) ? 200 : b ;

    GLODWORD( librender, FADING ) = 1 ;
}

/* -------------------------------------------------------------------------- */

void gr_fade_step()
{
    if ( fade_on )
    {
        fade_set = 1 ;
        GLODWORD( librender, FADING ) = 1 ;

        fade_step += fade_inc ;
        if ( fade_step < 0 )
        {
            GLODWORD( librender, FADING ) = 0 ;
            fade_step = 0 ;
            fade_on = 0 ;
        }

        if ( fade_step >= 64 )
        {
            GLODWORD( librender, FADING ) = 0 ;
            fade_step = 64 ;
            fade_on = 0 ;
        }

        fade_pos.r = ( fade_to.r * fade_step + fade_from.r * ( 64 - fade_step ) ) / 64;
        fade_pos.g = ( fade_to.g * fade_step + fade_from.g * ( 64 - fade_step ) ) / 64;
        fade_pos.b = ( fade_to.b * fade_step + fade_from.b * ( 64 - fade_step ) ) / 64;

        if (
            ( fade_step + fade_inc < 0 || fade_step + fade_inc > 64 ) &&
            ( fade_pos.r == 100 && fade_pos.g == 100 && fade_pos.b == 100 ) )
        {
            GLODWORD( librender, FADING ) = 0 ;
            fade_step = 100 ;
            fade_on = 0;
        }
    }

    if ( fade_set )
    {
        if ( !fade_on && fade_to.r == 100 && fade_to.g == 100 && fade_to.b == 100 ) fade_set = 0;

        activate_vpalette() ;

        if ( scrbitmap->format->depth > 8 )
        {
            gr_fade16( scrbitmap, fade_pos.r, fade_pos.g, fade_pos.b );
        }
    }
}

/* -------------------------------------------------------------------------- */

