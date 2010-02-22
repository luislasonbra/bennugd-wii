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

#ifndef __LIBMOUSE_H
#define __LIBMOUSE_H
extern void do_mouse_events();
extern void libmouse_init();
HOOK libmouse_hook[] =
{
    { 4800, do_mouse_events },
    { 0, NULL }
} ;
DLVARFIXUP libmouse_globals_fixup[] =
{
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
