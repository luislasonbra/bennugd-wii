/*
 *  Copyright © 2006-2009 SplinterGU (Fenix/Bennugd)
 *  Copyright © 2002-2006 Fenix Team (Fenix)
 *  Copyright © 1999-2002 José Luis Cebrián Pagüe (Fenix)
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

/* ------------------------------------------ */
/* Offsets de los datos globales predefinidos */
/* ------------------------------------------ */

#define ARGC                    0
#define ARGV_TABLE              ARGC                    + 4     /* 32+1 cadenas */
#define OS_ID                   ARGV_TABLE              + 33*4
#ifdef __STATIX__
#define MOUSEX                  OS_ID               + 4
#define MOUSEY                  MOUSEX              + 4
#define MOUSEZ                  MOUSEY              + 4
#define MOUSEFILE               MOUSEZ              + 4
#define MOUSEGRAPH              MOUSEFILE           + 4
#define MOUSEANGLE              MOUSEGRAPH          + 4
#define MOUSESIZE               MOUSEANGLE          + 4
#define MOUSEFLAGS              MOUSESIZE           + 4
#define MOUSEREGION             MOUSEFLAGS          + 4
#define MOUSELEFT               MOUSEREGION         + 4
#define MOUSEMIDDLE             MOUSELEFT           + 4
#define MOUSERIGHT              MOUSEMIDDLE         + 4
#define MOUSEWHEELUP            MOUSERIGHT          + 4
#define MOUSEWHEELDOWN          MOUSEWHEELUP        + 4
#define FILE_PATH		        MOUSEWHEELDOWN      + 4
#define FILE_NAME		        FILE_PATH           + 4
#define FILE_DIRECTORY	        FILE_NAME           + 4
#define FILE_HIDDEN		        FILE_DIRECTORY      + 4
#define FILE_READONLY	        FILE_HIDDEN         + 4
#define FILE_SIZE		        FILE_READONLY       + 4
#define FILE_CREATED	        FILE_SIZE           + 4
#define FILE_MODIFIED	        FILE_CREATED        + 4
#define SOUND_FREQ              FILE_MODIFIED       + 4
#define SOUND_MODE              SOUND_FREQ          + 4
#define SOUND_CHANNELS          SOUND_MODE          + 4
#endif

/* ----------------------------------------- */
/* Offsets de los datos locales predefinidos */
/* ----------------------------------------- */

#define PROCESS_ID              0
#define PROCESS_TYPE            PROCESS_ID          + 4
#define FRAME_PERCENT           PROCESS_TYPE        + 4
#define STATUS                  FRAME_PERCENT       + 4
#define SAVED_STATUS            STATUS              + 4
#define SAVED_PRIORITY          SAVED_STATUS        + 4
#ifdef __STATIC__
#define TYPE_SCAN               SAVED_PRIORITY      + 4
#define ID_SCAN                 TYPE_SCAN           + 4
#define CONTEXT                 ID_SCAN             + 4
#define SIGNAL_ACTION           CONTEXT             + 4
#define FATHER                  SIGNAL_ACTION       + 4
#else
#define FATHER                  SAVED_PRIORITY      + 4
#endif
#define SON                     FATHER              + 4
#define SMALLBRO                SON                 + 4
#define BIGBRO                  SMALLBRO            + 4
#define PRIORITY                BIGBRO              + 4
