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

#ifndef __G_VIDEO_H
#define __G_VIDEO_H

#if defined(TARGET_MAC) || defined(TARGET_WII)
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "libgrbase.h"
#include "libvideo_constants.h"

extern GRAPH * icon ;

extern SDL_Surface * screen ;
extern SDL_Surface * scale_screen ;

extern char * apptitle ;

extern int scr_width ;
extern int scr_height ;

extern int scr_initialized ;

extern int enable_16bits ;
extern int enable_scale ;
extern int full_screen ;
extern int double_buffer ;
extern int hardware_scr ;
extern int grab_input ;
extern int frameless ;
extern int scale_mode ;

extern int waitvsync ;

extern int scale_resolution ;
extern int * scale_resolution_table_w;
extern int * scale_resolution_table_h;

/* --------------------------------------------------------------------------- */

extern int gr_init( int width, int height );
extern void gr_set_caption( char * title );
extern int gr_set_icon( GRAPH * map );
extern int gr_set_mode( int width, int height, int depth );
extern void gr_wait_vsync();

/* --------------------------------------------------------------------------- */

#endif
