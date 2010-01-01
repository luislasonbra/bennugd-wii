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

#ifndef __LIBVIDEO_FIXUPS_H
#define __LIBVIDEO_FIXUPS_H

#ifdef __STATIC__
#include <bgddl.h>

DLVARFIXUP libvideo_globals_fixup[] =
{
    /* Global var name, data pointer, element size, element num */
    { "graph_mode" , NULL, -1, -1 },
    { "scale_mode" , NULL, -1, -1 },
    { "full_screen" , NULL, -1, -1 },
    { "scale_resolution", NULL, -1, -1 },
    { NULL , NULL, -1, -1 }
};
#endif

#endif
