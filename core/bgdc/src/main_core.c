/*
 *  Copyright © 2006-2010 SplinterGU (Fenix/Bennugd)
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
#include "../../../modules/mod_proc/mod_proc.h"
#include "../../../modules/libblit/libblit_constants.h"
#include "../../../modules/libvideo/libvideo_constants.h"
#include "../../../modules/librender/librender_constants.h"
#include "../../../modules/mod_map/mod_map_constants.h"
#include "../../../modules/libtext/libtext.h"
#include "../../../modules/libscroll/libscroll.h"
#include "../../../modules/libkey/libkey.h"
#include "../../../modules/mod_effects/mod_effects.h"
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
    /* mod_map */
    { "G_WIDE",             TYPE_INT,   G_WIDE              },    /* Obsolete */
    { "G_WIDTH",            TYPE_INT,   G_WIDTH             },
    { "G_HEIGHT",           TYPE_INT,   G_HEIGHT            },
    { "G_CENTER_X",         TYPE_INT,   G_CENTER_X          },
    { "G_X_CENTER",         TYPE_INT,   G_X_CENTER          },
    { "G_CENTER_Y",         TYPE_INT,   G_CENTER_Y          },
    { "G_Y_CENTER",         TYPE_INT,   G_Y_CENTER          },
    { "G_PITCH",            TYPE_INT,   G_PITCH             },
    { "G_DEPTH",            TYPE_INT,   G_DEPTH             },
    { "B_CLEAR",            TYPE_INT,   B_CLEAR             },
    /* mod_text */
    { "ALL_TEXT"            , TYPE_INT  , 0                     },
    { "ALIGN_TOP_LEFT"      , TYPE_INT  , ALIGN_TOP_LEFT        },
    { "ALIGN_TOP"           , TYPE_INT  , ALIGN_TOP             },
    { "ALIGN_TOP_RIGHT"     , TYPE_INT  , ALIGN_TOP_RIGHT       },
    { "ALIGN_CENTER_LEFT"   , TYPE_INT  , ALIGN_CENTER_LEFT     },
    { "ALIGN_CENTER"        , TYPE_INT  , ALIGN_CENTER          },
    { "ALIGN_CENTER_RIGHT"  , TYPE_INT  , ALIGN_CENTER_RIGHT    },
    { "ALIGN_BOTTOM_LEFT"   , TYPE_INT  , ALIGN_BOTTOM_LEFT     },
    { "ALIGN_BOTTOM"        , TYPE_INT  , ALIGN_BOTTOM          },
    { "ALIGN_BOTTOM_RIGHT"  , TYPE_INT  , ALIGN_BOTTOM_RIGHT    },
    /* mod_path */
    { "PF_NODIAG"   , TYPE_INT, 1 }, /* Prohibit the pathfinding from using diagonal paths. */
    { "PF_REVERSE"  , TYPE_INT, 2 }, /* Return the path found in reverse order.             */
    /* libscroll */
    { "C_SCROLL"            , TYPE_DWORD ,     C_SCROLL    },
    { "C_0"                 , TYPE_DWORD ,     0x0001      },
    { "C_1"                 , TYPE_DWORD ,     0x0002      },
    { "C_2"                 , TYPE_DWORD ,     0x0004      },
    { "C_3"                 , TYPE_DWORD ,     0x0008      },
    { "C_4"                 , TYPE_DWORD ,     0x0010      },
    { "C_5"                 , TYPE_DWORD ,     0x0020      },
    { "C_6"                 , TYPE_DWORD ,     0x0040      },
    { "C_7"                 , TYPE_DWORD ,     0x0080      },
    { "C_8"                 , TYPE_DWORD ,     0x0100      },
    { "C_9"                 , TYPE_DWORD ,     0x0200      },
    /* libkey */
    { "_ESC",         TYPE_DWORD,  1 },
    { "_1",           TYPE_DWORD,  2 },
    { "_2",           TYPE_DWORD,  3 },
    { "_3",           TYPE_DWORD,  4 },
    { "_4",           TYPE_DWORD,  5 },
    { "_5",           TYPE_DWORD,  6 },
    { "_6",           TYPE_DWORD,  7 },
    { "_7",           TYPE_DWORD,  8 },
    { "_8",           TYPE_DWORD,  9 },
    { "_9",           TYPE_DWORD,  10 },
    { "_0",           TYPE_DWORD,  11 },
    { "_MINUS",       TYPE_DWORD,  12 },
    { "_PLUS",        TYPE_DWORD,  13 },
    { "_BACKSPACE",   TYPE_DWORD,  14 },
    { "_TAB",         TYPE_DWORD,  15 },
    { "_Q",           TYPE_DWORD,  16 },
    { "_W",           TYPE_DWORD,  17 },
    { "_E",           TYPE_DWORD,  18 },
    { "_R",           TYPE_DWORD,  19 },
    { "_T",           TYPE_DWORD,  20 },
    { "_Y",           TYPE_DWORD,  21 },
    { "_U",           TYPE_DWORD,  22 },
    { "_I",           TYPE_DWORD,  23 },
    { "_O",           TYPE_DWORD,  24 },
    { "_P",           TYPE_DWORD,  25 },
    { "_L_BRACKET",   TYPE_DWORD,  26 },
    { "_R_BRACKET",   TYPE_DWORD,  27 },
    { "_ENTER",       TYPE_DWORD,  28 },
    { "_C_ENTER",     TYPE_DWORD,  28 },
    { "_CONTROL",     TYPE_DWORD,  29 },
    { "_A",           TYPE_DWORD,  30 },
    { "_S",           TYPE_DWORD,  31 },
    { "_D",           TYPE_DWORD,  32 },
    { "_F",           TYPE_DWORD,  33 },
    { "_G",           TYPE_DWORD,  34 },
    { "_H",           TYPE_DWORD,  35 },
    { "_J",           TYPE_DWORD,  36 },
    { "_K",           TYPE_DWORD,  37 },
    { "_L",           TYPE_DWORD,  38 },
    { "_SEMICOLON",   TYPE_DWORD,  39 },
    { "_APOSTROPHE",  TYPE_DWORD,  40 },
    { "_WAVE",        TYPE_DWORD,  41 },
    { "_L_SHIFT",     TYPE_DWORD,  42 },
    { "_BACKSLASH",   TYPE_DWORD,  43 },
    { "_Z",           TYPE_DWORD,  44 },
    { "_X",           TYPE_DWORD,  45 },
    { "_C",           TYPE_DWORD,  46 },
    { "_V",           TYPE_DWORD,  47 },
    { "_B",           TYPE_DWORD,  48 },
    { "_N",           TYPE_DWORD,  49 },
    { "_M",           TYPE_DWORD,  50 },
    { "_COMMA",       TYPE_DWORD,  51 },
    { "_POINT",       TYPE_DWORD,  52 },
    { "_SLASH",       TYPE_DWORD,  53 },
    { "_C_BACKSLASH", TYPE_DWORD,  53 },
    { "_R_SHIFT",     TYPE_DWORD,  54 },
    { "_C_ASTERISK",  TYPE_DWORD,  55 },
    { "_PRN_SCR",     TYPE_DWORD,  55 },
    { "_ALT",         TYPE_DWORD,  56 },
    { "_SPACE",       TYPE_DWORD,  57 },
    { "_CAPS_LOCK",   TYPE_DWORD,  58 },
    { "_F1",          TYPE_DWORD,  59 },
    { "_F2",          TYPE_DWORD,  60 },
    { "_F3",          TYPE_DWORD,  61 },
    { "_F4",          TYPE_DWORD,  62 },
    { "_F5",          TYPE_DWORD,  63 },
    { "_F6",          TYPE_DWORD,  64 },
    { "_F7",          TYPE_DWORD,  65 },
    { "_F8",          TYPE_DWORD,  66 },
    { "_F9",          TYPE_DWORD,  67 },
    { "_F10",         TYPE_DWORD,  68 },
    { "_NUM_LOCK",    TYPE_DWORD,  69 },
    { "_SCROLL_LOCK", TYPE_DWORD,  70 },
    { "_HOME",        TYPE_DWORD,  71 },
    { "_C_HOME",      TYPE_DWORD,  71 },
    { "_UP",          TYPE_DWORD,  72 },
    { "_C_UP",        TYPE_DWORD,  72 },
    { "_PGUP",        TYPE_DWORD,  73 },
    { "_C_PGUP",      TYPE_DWORD,  73 },
    { "_C_MINUS",     TYPE_DWORD,  74 },
    { "_LEFT",        TYPE_DWORD,  75 },
    { "_C_LEFT",      TYPE_DWORD,  75 },
    { "_C_CENTER",    TYPE_DWORD,  76 },
    { "_RIGHT",       TYPE_DWORD,  77 },
    { "_C_RIGHT",     TYPE_DWORD,  77 },
    { "_C_PLUS",      TYPE_DWORD,  78 },
    { "_END",         TYPE_DWORD,  79 },
    { "_C_END",       TYPE_DWORD,  79 },
    { "_DOWN",        TYPE_DWORD,  80 },
    { "_C_DOWN",      TYPE_DWORD,  80 },
    { "_PGDN",        TYPE_DWORD,  81 },
    { "_C_PGDN",      TYPE_DWORD,  81 },
    { "_INS",         TYPE_DWORD,  82 },
    { "_C_INS",       TYPE_DWORD,  82 },
    { "_DEL",         TYPE_DWORD,  83 },
    { "_C_DEL",       TYPE_DWORD,  83 },
    { "_F11",         TYPE_DWORD,  87 },
    { "_F12",         TYPE_DWORD,  88 },
    { "_LESS",        TYPE_DWORD,  89 },
    { "_EQUALS",      TYPE_DWORD,  90 },
    { "_GREATER",     TYPE_DWORD,  91 },
    { "_ASTERISK",    TYPE_DWORD,  92 },
    { "_R_ALT",       TYPE_DWORD,  93 },
    { "_R_CONTROL",   TYPE_DWORD,  94 },
    { "_L_ALT",       TYPE_DWORD,  95 },
    { "_L_CONTROL",   TYPE_DWORD,  96 },
    { "_MENU",        TYPE_DWORD,  97 },
    { "_L_WINDOWS",   TYPE_DWORD,  98 },
    { "_R_WINDOWS",   TYPE_DWORD,  99 },
    { "STAT_RSHIFT",  TYPE_DWORD,  STAT_RSHIFT },
    { "STAT_LSHIFT",  TYPE_DWORD,  STAT_LSHIFT },
    { "STAT_CTRL",    TYPE_DWORD,  STAT_CTRL   },
    { "STAT_ALT",     TYPE_DWORD,  STAT_ALT    },
    /* mod_effects */
    { "BLUR_NORMAL" , TYPE_INT, BLUR_NORMAL     },
    { "BLUR_3x3"    , TYPE_INT, BLUR_3x3        },
    { "BLUR_5x5"    , TYPE_INT, BLUR_5x5        },
    { "BLUR_5x5_MAP", TYPE_INT, BLUR_5x5_MAP    },
    { "GSCALE_RGB"  , TYPE_INT, GSCALE_RGB      },
    { "GSCALE_R"    , TYPE_INT, GSCALE_R        },
    { "GSCALE_G"    , TYPE_INT, GSCALE_G        },
    { "GSCALE_B"    , TYPE_INT, GSCALE_B        },
    { "GSCALE_RG"   , TYPE_INT, GSCALE_RG       },
    { "GSCALE_RB"   , TYPE_INT, GSCALE_RB       },
    { "GSCALE_GB"   , TYPE_INT, GSCALE_GB       },
    { "GSCALE_OFF"  , TYPE_INT, GSCALE_OFF      },
    /* mod_wpad */
    { "WPAD_BATT",      TYPE_INT,   0           },
    { "WPAD_X",         TYPE_INT,   1           },
    { "WPAD_Y",         TYPE_INT,   2           },
    { "WPAD_Z",         TYPE_INT,   3           },
    { "WPAD_ANGLE",     TYPE_INT,   4           },
    { "WPAD_PITCH",     TYPE_INT,   5           },
    { "WPAD_ROLL",      TYPE_INT,   6           },
    { "WPAD_ACCELX",    TYPE_INT,   7           },
    { "WPAD_ACCELY",    TYPE_INT,   8           },
    { "WPAD_ACCELZ",    TYPE_INT,   9           },
    { "WPAD_WTL",       TYPE_INT,   3           },
    { "WPAD_WTR",       TYPE_INT,   4           },
    { "WPAD_WBL",       TYPE_INT,   5           },
    { "WPAD_WBR",       TYPE_INT,   6           },

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
    "   x = 99999, y = 99999;\n"
    "   z = -512;\n"
    "   file;\n"
    "   graph;\n"
    "   angle;\n"
    "   size = 100;\n"
    "   flags;\n"
    "   region;\n"
    "   left, middle, right;\n"
    "   wheelup, wheeldown;\n"
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
#ifdef TARGET_WII
    "sound_freq = 32000 ;\n"
#else
    "sound_freq = 22050 ;\n"
#endif
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
/* libtext */
    "text_z = -256;\n"
    "text_flags;\n"
/* mod_regex */
    "STRING regex_reg[15];\n"
/* libscroll */
    "STRUCT scroll[9]\n"
    "    x0, y0;\n"
    "    x1, y1;\n"
    "    z = 512;\n"
    "    camera;\n"
    "    ratio = 200;\n"
    "    speed;\n"
    "    region1 = -1;\n"
    "    region2 = -1;\n"
    "    flags1;\n"
    "    flags2;\n"
    "    follow = -1;\n"
    "    reserved[6];\n"  /* size: 20 dwords */
    "END\n"
/* libkey */
    "shift_status;\n"
    "ascii;\n"
    "scan_code;\n";
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
    "   int type_scan;\n"
    "   int id_scan;\n"
    "   int context;\n"
    "   dword signal_action;\n"
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
#endif
    "father;\n"
    "son;\n"
    "smallbro;\n"
    "bigbro;\n"
    "priority;\n"
    "END\n";

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
