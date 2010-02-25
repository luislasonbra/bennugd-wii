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

#ifndef __RENDER_CONSTANTS_H
#define __RENDER_CONSTANTS_H

#include <instance_st.h>

#define C_SCREEN            0

/* -------------------------------------------------------------------------- */
#define SCALE_HQ2X          0x0002
#define SCALE_SCANLINE2X    0x0003
#define SCALE_NOFILTER      0x0004
/* -------------------------------------------------------------------------- */

#ifdef __BGDRTM__
// The things defined below are needed while compiling the runtime
// but will cause bgdc compilation to fail
extern void librender_init();
extern void librender_finalize();
extern void librender_instance_create_hook(INSTANCE *r);
extern void librender_instance_destroy_hook(INSTANCE *r);
extern void gr_wait_frame();
extern void gr_draw_frame();

HOOK librender_hooks[] =
{
    { 9500, gr_wait_frame },
    { 9000, gr_draw_frame },
    {    0, NULL          }
};
#endif
#endif
