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
#define ARGV_TABLE              4*1     /* 32+1 cadenas */
#define OS_ID                   4*34
#ifdef __STATIC__
#define TIMER                   4*35
#define MOUSEX                  4*45
#define MOUSEY                  4*46
#define MOUSEZ                  4*47
#define MOUSEFILE               4*48
#define MOUSEGRAPH              4*49
#define MOUSEANGLE              4*50
#define MOUSESIZE               4*51
#define MOUSEFLAGS              4*52
#define MOUSEREGION             4*53
#define MOUSELEFT               4*54
#define MOUSEMIDDLE             4*55
#define MOUSERIGHT              4*56
#define MOUSEWHEELUP            4*57
#define MOUSEWHEELDOWN          4*58
#define FILE_PATH		        4*59
#define FILE_NAME		        4*60
#define FILE_DIRECTORY	        4*61
#define FILE_HIDDEN		        4*62
#define FILE_READONLY	        4*63
#define FILE_SIZE		        4*64
#define FILE_CREATED	        4*65
#define FILE_MODIFIED	        4*66
#define SOUND_FREQ              4*67
#define SOUND_MODE              4*68
#define SOUND_CHANNELS          4*69
#define ALPHA_STEPS             4*79
#define GRAPH_MODE              4*71
#define SCALE_MODE              4*72
#define FULL_SCREEN             4*73
#define SCALE_RESOLUTION        4*74
#define FPS                     4*75
#define SPEED_GAUGE             4*76
#define FRAME_TIME              4*77
#define RESTORETYPE             4*78
#define DUMPTYPE                4*79
#define FADING                  4*80
#endif

/* ----------------------------------------- */
/* Offsets for the predefined local data     */
/* ----------------------------------------- */

#define PROCESS_ID              4*0
#define PROCESS_TYPE            4*1
#define FRAME_PERCENT           4*2
#define STATUS                  4*3
#define SAVED_STATUS            4*4
#define SAVED_PRIORITY          4*5
#ifdef __STATIC__
#define TYPE_SCAN               4*6
#define ID_SCAN                 4*7
#define CONTEXT                 4*8
#define SIGNAL_ACTION           4*9
#define OBJECTID                4*10
#define GRAPHPTR                4*11
#define XGRAPH_FLAGS            4*12
#define SAVED_COORDX            4*13
#define SAVED_COORDY            4*14
#define SAVED_COORDZ            4*15
#define SAVED_FILEID            4*16
#define SAVED_GRAPHID           4*17
#define SAVED_GRAPHSIZE         4*18
#define SAVED_ANGLE             4*19
#define SAVED_FLAGS             4*20
#define SAVED_ALPHA             4*21
#define SAVED_PALETTE           4*22
#define SAVED_GRAPHSIZEX        4*23
#define SAVED_GRAPHSIZEY        4*24
#define SAVED_BLENDOP           4*25
#define SAVED_XGRAPH            4*26
#define SAVED_CENTERX           4*27
#define SAVED_CENTERY           4*28
#define CTYPE                   4*29
#define CNUMBER                 4*30
#define COORDX                  4*31
#define COORDY                  4*32
#define COORDZ                  4*33
#define FILEID                  4*34
#define GRAPHID                 4*35
#define GRAPHSIZE               4*36
#define ANGLE                   4*37
#define FLAGS                   4*38
#define ALPHA                   4*39
#define PALETTEID               4*40
#define REGIONID                4*41
#define RESOLUTION              4*42
#define GRAPHSIZEX              4*43
#define GRAPHSIZEY              4*44
#define BLENDOP                 4*45
#define XGRAPH                  4*46
#define FATHER                  4*47
#else
#define FATHER                  4*6
#endif
#define SON                     FATHER              + 4
#define SMALLBRO                SON                 + 4
#define BIGBRO                  SMALLBRO            + 4
#define PRIORITY                BIGBRO              + 4
