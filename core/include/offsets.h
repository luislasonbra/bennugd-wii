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
/* Offsets for the global predefined data     */
/* ------------------------------------------ */

#define ARGC                    0
#define ARGV_TABLE              ARGC                    + 4     /* 32+1 cadenas */
#define OS_ID                   ARGV_TABLE              + 33*4
#ifdef __STATIC__
#define TIMER                   OS_ID               + 4
#define MOUSEX                  TIMER               + 4*10
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
#define ALPHA_STEPS             SOUND_CHANNELS      + 4
#define GRAPH_MODE              ALPHA_STEPS         + 4
#define SCALE_MODE              GRAPH_MODE          + 4
#define FULL_SCREEN             SCALE_MODE          + 4
#define SCALE_RESOLUTION        FULL_SCREEN         + 4
#define FPS                     SCALE_RESOLUTION    + 4
#define SPEED_GAUGE             FPS                 + 4
#define FRAME_TIME              SPEED_GAUGE         + 4
#define RESTORETYPE             FRAME_TYPE          + 4
#define DUMPTYPE                RESTORETYPE         + 4
#define FADING                  DUMPTYPE            + 4
#endif

/* ----------------------------------------- */
/* Offsets for the predefined local data     */
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
#define OBJECTID                XGRAPH              + 4
#define GRAPHPTR                OBJECTID            + 4
#define XGRAPH_FLAGS            GRAPHPTR            + 4
#define SAVED_COORDX            XGRAPH_FLAGS        + 4
#define SAVED_COORDY            SAVED_COORDX        + 4
#define SAVED_COORDZ            SAVED_COORDY        + 4
#define SAVED_FILEID            SAVED_COORDZ        + 4
#define SAVED_GRAPHID           SAVED_FILEID        + 4
#define SAVED_GRAPHSIZE         SAVED_GRAPHID       + 4
#define SAVED_ANGLE             SAVED_GRAPHSIZE     + 4
#define SAVED_FLAGS             SAVED_ANGLE         + 4
#define SAVED_ALPHA             SAVED_FLAGS         + 4
#define SAVED_PALETTE           SAVED_ALPHA         + 4
#define SAVED_GRAPHSIZEX        SAVED_PALETTE       + 4
#define SAVED_GRAPHSIZEY        SAVED_GRAPHSIZEX    + 4
#define SAVED_BLENDOP           SAVED_GRAPHSIZEY    + 4
#define SAVED_XGRAPH            SAVED_BLENDOP       + 4
#define SAVED_CENTERX           SAVED_XGRAPH        + 4
#define SAVED_CENTERY           SAVED_CENTERX       + 4
#define FATHER                  SAVED_CENTERY       + 4
#else
#define FATHER                  SAVED_PRIORITY      + 4
#endif
#define SON                     FATHER              + 4
#define SMALLBRO                SON                 + 4
#define BIGBRO                  SMALLBRO            + 4
#define PRIORITY                BIGBRO              + 4
#define CTYPE                   PRIORITY            + 4
#define CNUMBER                 CTYPE               + 4
#define COORDX                  CNUMBER             + 4
#define COORDY                  COORDX              + 4
#define COORDZ                  COORDY              + 4
#define FILEID                  COORDZ              + 4
#define GRAPHID                 FILEID              + 4
#define GRAPHSIZE               GRAPHID             + 4
#define ANGLE                   GRAPHSIZE           + 4
#define FLAGS                   ANGLE               + 4
#define ALPHA                   FLAGS               + 4
#define PALETTEID               ALPHA               + 4
#define REGIONID                PALETTEID           + 4
#define RESOLUTION              REGIONID            + 4
#define GRAPHSIZEX              RESOLUTION          + 4
#define GRAPHSIZEY              GRAPHSIZEX          + 4
#define BLENDOP                 GRAPHSIZEY          + 4
#define XGRAPH                  BLENDOP             + 4

