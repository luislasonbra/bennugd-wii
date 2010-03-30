
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

#ifndef __MOD_PROC_H
#define __MOD_PROC_H

#include <bgddl.h>

#define ALL_PROCESS         0

#define S_KILL              0
#define S_WAKEUP            1
#define S_SLEEP             2
#define S_FREEZE            3

#define S_FORCE             50
#define S_TREE              100

#define S_KILL_TREE         (S_TREE + S_KILL  )
#define S_WAKEUP_TREE       (S_TREE + S_WAKEUP)
#define S_SLEEP_TREE        (S_TREE + S_SLEEP )
#define S_FREEZE_TREE       (S_TREE + S_FREEZE)

#define S_KILL_FORCE        (S_FORCE + S_KILL  )
#define S_WAKEUP_FORCE      (S_FORCE + S_WAKEUP)
#define S_SLEEP_FORCE       (S_FORCE + S_SLEEP )
#define S_FREEZE_FORCE      (S_FORCE + S_FREEZE)
#define S_KILL_TREE_FORCE   (S_FORCE + S_KILL_TREE  )
#define S_WAKEUP_TREE_FORCE (S_FORCE + S_WAKEUP_TREE)
#define S_SLEEP_TREE_FORCE  (S_FORCE + S_SLEEP_TREE )
#define S_FREEZE_TREE_FORCE (S_FORCE + S_FREEZE_TREE)

#define S_DFL               0
#define S_IGN               1

#define SMASK_KILL          0x0001
#define SMASK_WAKEUP        0x0002
#define SMASK_SLEEP         0x0004
#define SMASK_FREEZE        0x0008
#define SMASK_KILL_TREE     0x0100
#define SMASK_WAKEUP_TREE   0x0200
#define SMASK_SLEEP_TREE    0x0400
#define SMASK_FREEZE_TREE   0x0800

#ifdef __BGDRTM__
extern DLVARFIXUP mod_proc_locals_fixup[];
#endif
#endif
