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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bgdc.h"

#ifdef __STATIC__
#ifdef TARGET_WII
#include <SDL/SDL.h>
#elif defined(TARGET_LINUX)
#include <SDL.h>
#endif
#include "../../../modules/mod_proc/mod_proc_constants.h"
#include "../../../modules/libblit/libblit_constants.h"
#include "../../../modules/libvideo/libvideo_constants.h"
#include "../../../modules/librender/librender_constants.h"
#endif

/* ----------------------------------------------------------------------- */
/* Este módulo contiene las definiciones de constantes, globales y locales */
/* predefinidos, así como el código que los carga y define cada una de las */
/* funciones del sistema (es llamado antes de empezar a compilar).         */
/* ----------------------------------------------------------------------- */

static struct
{
    char * name ;
    int    type ;
    int    code ;
}
constants_def[] =
{
    { "STATUS_DEAD"     , TYPE_DWORD, STATUS_DEAD         },
    { "STATUS_KILLED"   , TYPE_DWORD, STATUS_KILLED       },
    { "STATUS_RUNNING"  , TYPE_DWORD, STATUS_RUNNING      },
    { "STATUS_SLEEPING" , TYPE_DWORD, STATUS_SLEEPING     },
    { "STATUS_FROZEN"   , TYPE_DWORD, STATUS_FROZEN       },
    { "STATUS_WAITING"  , TYPE_DWORD, STATUS_WAITING_MASK },

    { "NULL"            , TYPE_DWORD, 0                   },

    { "FALSE"           , TYPE_DWORD, 0                   },
    { "TRUE"            , TYPE_DWORD, !0                  },

    { "OS_WIN32"        , TYPE_DWORD, OS_WIN32            },
    { "OS_LINUX"        , TYPE_DWORD, OS_LINUX            },
    { "OS_BEOS"         , TYPE_DWORD, OS_BEOS             },
    { "OS_MACOS"        , TYPE_DWORD, OS_MACOS            },
    { "OS_GP32"         , TYPE_DWORD, OS_GP32             },
    { "OS_DC"           , TYPE_DWORD, OS_DC               },
    { "OS_BSD"          , TYPE_DWORD, OS_BSD              },
    { "OS_GP2X"         , TYPE_DWORD, OS_GP2X             },
    { "OS_GP2X_WIZ"     , TYPE_DWORD, OS_GP2X_WIZ         },
    { "OS_WII"          , TYPE_DWORD, OS_WII              },

    { "MIN_INT"         , TYPE_INT  , -2147483647L - 1    },
    { "MAX_INT"         , TYPE_INT  , 2147483647L         },
    { "MIN_DWORD"       , TYPE_DWORD, 0                   },
    { "MAX_DWORD"       , TYPE_DWORD, 0xffffffff          },

    { "MIN_SHORT"       , TYPE_SHORT, -32768              },
    { "MAX_SHORT"       , TYPE_SHORT, 32767               },
    { "MIN_WORD"        , TYPE_WORD , 0                   },
    { "MAX_WORD"        , TYPE_WORD , 0xffff              },

    { "MIN_SBYTE"       , TYPE_SBYTE, -128                },
    { "MAX_SBYTE"       , TYPE_SBYTE, 127                 },
    { "MIN_BYTE"        , TYPE_BYTE , 0                   },
    { "MAX_BYTE"        , TYPE_BYTE , 0xff                },

    { "MIN_CHAR"        , TYPE_BYTE , 0                   },
    { "MAX_CHAR"        , TYPE_BYTE , 0xff                },

#ifdef __STATIC__
    /* mod_math */
    { "PI"              , TYPE_INT  , 180000              },
    /* mod_file */
    { "O_READ"          , TYPE_INT  , 0                   },
    { "O_READWRITE"     , TYPE_INT  , 1                   },
    { "O_RDWR"          , TYPE_INT  , 1                   },
    { "O_WRITE"         , TYPE_INT  , 2                   },
    { "O_ZREAD"         , TYPE_INT  , 3                   },
    { "O_ZWRITE"        , TYPE_INT  , 4                   },
    { "SEEK_SET"        , TYPE_INT  , 0                   },
    { "SEEK_CUR"        , TYPE_INT  , 1                   },
    { "SEEK_END"        , TYPE_INT  , 2                   },
    /* mod_sound */
    { "MODE_MONO"       , TYPE_INT  , 0                   },
    { "MODE_STEREO"     , TYPE_INT  , 1                   },
    { "ALL_SOUND"       , TYPE_INT  , -1                  },
    /* libjoy */
    { "JOY_HAT_CENTERED"    , TYPE_DWORD, SDL_HAT_CENTERED  },
    { "JOY_HAT_UP"          , TYPE_DWORD, SDL_HAT_UP        },
    { "JOY_HAT_RIGHT"       , TYPE_DWORD, SDL_HAT_RIGHT     },
    { "JOY_HAT_DOWN"        , TYPE_DWORD, SDL_HAT_DOWN      },
    { "JOY_HAT_LEFT"        , TYPE_DWORD, SDL_HAT_LEFT      },
    { "JOY_HAT_RIGHTUP"     , TYPE_DWORD, SDL_HAT_RIGHTUP   },
    { "JOY_HAT_RIGHTDOWN"   , TYPE_DWORD, SDL_HAT_RIGHTDOWN },
    { "JOY_HAT_LEFTUP"      , TYPE_DWORD, SDL_HAT_LEFTUP    },
    { "JOY_HAT_LEFTDOWN"    , TYPE_DWORD, SDL_HAT_LEFTDOWN  },
    /* mod_proc */
    { "S_KILL"              , TYPE_INT, S_KILL              },
    { "S_WAKEUP"            , TYPE_INT, S_WAKEUP            },
    { "S_SLEEP"             , TYPE_INT, S_SLEEP             },
    { "S_FREEZE"            , TYPE_INT, S_FREEZE            },
    { "S_KILL_TREE"         , TYPE_INT, S_KILL_TREE         },
    { "S_WAKEUP_TREE"       , TYPE_INT, S_WAKEUP_TREE       },
    { "S_SLEEP_TREE"        , TYPE_INT, S_SLEEP_TREE        },
    { "S_FREEZE_TREE"       , TYPE_INT, S_FREEZE_TREE       },
    { "S_KILL_FORCE"        , TYPE_INT, S_KILL_FORCE        },
    { "S_WAKEUP_FORCE"      , TYPE_INT, S_WAKEUP_FORCE      },
    { "S_SLEEP_FORCE"       , TYPE_INT, S_SLEEP_FORCE       },
    { "S_FREEZE_FORCE"      , TYPE_INT, S_FREEZE_FORCE      },
    { "S_KILL_TREE_FORCE"   , TYPE_INT, S_KILL_TREE_FORCE   },
    { "S_WAKEUP_TREE_FORCE" , TYPE_INT, S_WAKEUP_TREE_FORCE },
    { "S_SLEEP_TREE_FORCE"  , TYPE_INT, S_SLEEP_TREE_FORCE  },
    { "S_FREEZE_TREE_FORCE" , TYPE_INT, S_FREEZE_TREE_FORCE },
    { "S_DFL"               , TYPE_INT, S_DFL               },
    { "S_IGN"               , TYPE_INT, S_IGN               },
    { "ALL_PROCESS"         , TYPE_INT, ALL_PROCESS         },
    /* libblit */
    { "B_HMIRROR"           , TYPE_DWORD, B_HMIRROR         },
    { "B_VMIRROR"           , TYPE_DWORD, B_VMIRROR         },
    { "B_TRANSLUCENT"       , TYPE_DWORD, B_TRANSLUCENT     },
    { "B_ALPHA"             , TYPE_DWORD, B_ALPHA           },
    { "B_ABLEND"            , TYPE_DWORD, B_ABLEND          },
    { "B_SBLEND"            , TYPE_DWORD, B_SBLEND          },
    { "B_NOCOLORKEY"        , TYPE_DWORD, B_NOCOLORKEY      },
    /* libvideo */
    { "M320X200",           TYPE_DWORD, 3200200             },
    { "M320X240",           TYPE_DWORD, 3200240             },
    { "M320X400",           TYPE_DWORD, 3200400             },
    { "M360X240",           TYPE_DWORD, 3600240             },
    { "M376X282",           TYPE_DWORD, 3760282             },
    { "M400X300",           TYPE_DWORD, 4000300             },
    { "M512X384",           TYPE_DWORD, 5120384             },
    { "M640X400",           TYPE_DWORD, 6400400             },
    { "M640X480",           TYPE_DWORD, 6400480             },
    { "M800X600",           TYPE_DWORD, 8000600             },
    { "M1024X768",          TYPE_DWORD, 10240768            },
    { "M1280X1024",         TYPE_DWORD, 12801024            },

    { "MODE_WINDOW",        TYPE_DWORD, MODE_WINDOW         },
    { "MODE_2XSCALE",       TYPE_DWORD, MODE_2XSCALE        },
    { "MODE_FULLSCREEN",    TYPE_DWORD, MODE_FULLSCREEN     },
    { "MODE_DOUBLEBUFFER",  TYPE_DWORD, MODE_DOUBLEBUFFER   },
    { "MODE_HARDWARE",      TYPE_DWORD, MODE_HARDWARE       },

    { "MODE_WAITVSYNC",     TYPE_DWORD, MODE_WAITVSYNC      },
    { "WAITVSYNC",          TYPE_DWORD, MODE_WAITVSYNC      },

    { "DOUBLE_BUFFER",      TYPE_DWORD, MODE_DOUBLEBUFFER   },  /* Obsolete */
    { "HW_SURFACE",         TYPE_DWORD, MODE_HARDWARE       },  /* Obsolete */

    { "MODE_8BITS",         TYPE_DWORD, 8                   },
    { "MODE_16BITS",        TYPE_DWORD, 16                  },
    { "MODE_32BITS",        TYPE_DWORD, 32                  },

    { "MODE_8BPP",          TYPE_DWORD, 8                   },
    { "MODE_16BPP",         TYPE_DWORD, 16                  },
    { "MODE_32BPP",         TYPE_DWORD, 32                  },

    { "MODE_MODAL",         TYPE_DWORD, MODE_MODAL          },  /* GRAB INPUT */
    { "MODE_FRAMELESS",     TYPE_DWORD, MODE_FRAMELESS      },  /* FRAMELESS window */

    { "SCALE_NONE",         TYPE_DWORD, SCALE_NONE          },
    /* librender */
    { "C_SCREEN",           TYPE_DWORD, C_SCREEN            },

    { "PARTIAL_DUMP",       TYPE_DWORD, 0                   },
    { "COMPLETE_DUMP",      TYPE_DWORD, 1                   },
    { "NO_RESTORE",         TYPE_DWORD, -1                  },
    { "PARTIAL_RESTORE",    TYPE_DWORD, 0                   },
    { "COMPLETE_RESTORE",   TYPE_DWORD, 1                   },

    { "BACKGROUND",         TYPE_DWORD, 0                   },
    { "SCREEN",             TYPE_DWORD, -1                  },

    { "SCALE_SCALE2X",      TYPE_DWORD, SCALE_SCALE2X       },
    { "SCALE_HQ2X",         TYPE_DWORD, SCALE_HQ2X          },
    { "SCALE_SCANLINE2X",   TYPE_DWORD, SCALE_SCANLINE2X    },
    { "SCALE_NORMAL2X",     TYPE_DWORD, SCALE_NOFILTER      },
    { "SCALE_NOFILTER",     TYPE_DWORD, SCALE_NOFILTER      },
#endif
    { NULL              , 0         , 0                   }
} ;

static char * globals_def =
    "argc;\n"
    "string argv[32];\n"
    "os_id = -1;\n"
#ifdef __STATIC__
/* mod_timers */
    "timer[9];\n"
/* libmouse */
    "STRUCT mouse\n"
    "x = 99999, y = 99999;\n"
    "z = -512;\n"
    "file;\n"
    "graph;\n"
    "angle;\n"
    "size = 100;\n"
    "flags;\n"
    "region;\n"
    "left, middle, right;\n"
    "wheelup, wheeldown;\n"
    "END\n"
/* mod_dir */
    "STRUCT fileinfo\n"
    "    STRING path;\n"
    "    STRING name;\n"
    "    directory;\n"
    "    hidden;\n"
    "    readonly;\n"
    "    size;\n"
    "    STRING created;\n"
    "    STRING modified;\n"
    "END\n"
/* mod_sound */
    "sound_freq = 22050 ;\n"
    "sound_mode = MODE_STEREO ;\n"
    "sound_channels = 8 ;\n"
/* libgrbase */
    "alpha_steps = 16;\n"
/* libvideo */
    "graph_mode = 0;\n"
    "scale_mode = 0;\n"
    "full_screen = 0;\n"
    "scale_resolution = 0;\n"
/* librender */
    "fps;\n"
    "speed_gauge = 0;\n"
    "FLOAT frame_time = 0;\n"
    "restore_type;\n"
    "dump_type;\n"
    "fading;\n"
#endif
;

static char * locals_def =
    "id;\n"
    "STRUCT reserved\n"
    "   process_type;\n"
    "   frame_percent;\n"
    "   status = STATUS_RUNNING;\n"
    "   saved_status = STATUS_RUNNING;\n"
    "   saved_priority;\n"
#ifdef __STATIC__
/* mod_proc */
    "   type_scan;\n"
    "   id_scan;\n"
    "   context;\n"
    "   signal_action;\n"
    "   object_id=0;\n"
    "   graph_ptr=0;\n"
    "   xgraph_flags;\n"
    "   STRUCT _saved_\n"
    "       x;\n"
    "       y;\n"
    "       z;\n"
    "       file;\n"
    "       graph;\n"
    "       size;\n"
    "       angle;\n"
    "       flags;\n"
    "       alpha;\n"
    "       palette;\n"
    "       size_x;\n"
    "       size_y;\n"
    "       blendop;\n"
    "       pointer xgraph;\n"
    "       centerx;\n"
    "       centery;\n"
    "   END\n"
    "END\n"
    /* librender */
    "ctype;\n"
    "cnumber;\n"
    "x;\n"
    "y;\n"
    "z;\n"
    "file;\n"
    "graph;\n"
    "size=100;\n"
    "angle;\n"
    "flags;\n"
    "alpha=255;\n"
    "palette=0;\n"
    "region;\n"
    "resolution;\n"
    "size_x=100;\n"
    "size_y=100;\n"
    "blendop=0;\n"
    "pointer xgraph;\n"
#else
    "END\n"
#endif
    "father;\n"
    "son;\n"
    "smallbro;\n"
    "bigbro;\n"
    "priority;\n";

void core_init()
{
    int i = 0, code ;

    while ( constants_def[i].name )
    {
        code = identifier_search_or_add( constants_def[i].name ) ;
        constants_add( code, typedef_new( constants_def[i].type ), constants_def[i].code ) ;
        i++ ;
    }

    token_init( globals_def, -1 ) ;
    compile_varspace( &global, globaldata, 1, 1, 0, NULL, DEFAULT_ALIGNMENT, 0 ) ;

    token_init( locals_def, -1 ) ;
    compile_varspace( &local, localdata, 1, 1, 0, NULL, DEFAULT_ALIGNMENT, 0 ) ;
}
