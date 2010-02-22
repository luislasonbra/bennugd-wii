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

/*
 * FILE        : sysprocs.h
 * DESCRIPTION : Defines Internals functions SPECS and handlers
 **
 */

/*
 *  In interpreter: SYSMACRO returns a function pointer
 *  In compiler:    Already defined to return 0
 */

#ifndef SYSMACRO
#define SYSMACRO(a) a
#endif

#define MAX_SYSPROCS 3072

/* WARNING!!!!
   This table must be sorted by element Code !!!! Don't unsort it !!!
   2006/11/09    Splinter (jj_arg@yahoo.com)
*/

#ifdef SYSPROCS_ONLY_DECLARE
extern SYSPROC sysprocs[MAX_SYSPROCS] ;
#else
SYSPROC sysprocs[MAX_SYSPROCS] =
{
    /* Internal use */
    { 0x01, "#COPY#"    , "PV++I" , TYPE_POINTER , 5, SYSMACRO(bgd_copy_struct)      },
    { 0x02, "#MEMCOPY#" , "PPI"   , TYPE_INT     , 3, SYSMACRO(bgd_internal_memcopy) },

    /* mod_say */
    { 0x03, "SAY"       , "S"     , TYPE_INT     , 1, SYSMACRO(modsay_say)           },
    { 0x04, "SAY_FAST"  , "S"     , TYPE_INT     , 1, SYSMACRO(modsay_say_fast)      },
    
    /* mod_string */
    { 0x10, "STRLEN"     , "S"    , TYPE_INT     , 1, SYSMACRO(modstring_strlen)     },
    { 0x11, "LEN"        , "S"    , TYPE_INT     , 1, SYSMACRO(modstring_strlen)     },
    { 0x12, "UCASE"      , "S"    , TYPE_STRING  , 1, SYSMACRO(modstring_strupper)   },
    { 0x13, "LCASE"      , "S"    , TYPE_STRING  , 1, SYSMACRO(modstring_strlower)   },
    { 0x14, "STRCASECMP" , "SS"   , TYPE_INT     , 2, SYSMACRO(modstring_strcasecmp) },
    { 0x15, "SUBSTR"     , "SII"  , TYPE_STRING  , 3, SYSMACRO(modstring_substr)     },
    { 0x16, "SUBSTR"     , "SI"   , TYPE_STRING  , 2, SYSMACRO(modstring_substr2)    },
    { 0x17, "FIND"       , "SS"   , TYPE_INT     , 2, SYSMACRO(modstring_strfind)    },
    { 0x18, "FIND"       , "SSI"  , TYPE_INT     , 3, SYSMACRO(modstring_strfindSSI) },
    { 0x19, "LPAD"       , "SI"   , TYPE_STRING  , 2, SYSMACRO(modstring_lpad)       },
    { 0x1A, "RPAD"       , "SI"   , TYPE_STRING  , 2, SYSMACRO(modstring_rpad)       },
    { 0x1B, "ITOA"       , "I"    , TYPE_STRING  , 1, SYSMACRO(modstring_itos)       },
    { 0x1C, "FTOA"       , "F"    , TYPE_STRING  , 1, SYSMACRO(modstring_ftos)       },
    { 0x1D, "ATOI"       , "S"    , TYPE_INT     , 1, SYSMACRO(modstring_stoi)       },
    { 0x1E, "ATOF"       , "S"    , TYPE_FLOAT   , 1, SYSMACRO(modstring_stof)       },
    { 0x1F, "ASC"        , "S"    , TYPE_BYTE    , 1, SYSMACRO(modstring_asc)        },
    { 0x20, "CHR"        , "I"    , TYPE_STRING  , 1, SYSMACRO(modstring_chr)        },
    { 0x21, "TRIM"       , "S"    , TYPE_STRING  , 1, SYSMACRO(modstring_trim)       },
    { 0x22, "STRREV"     , "S"    , TYPE_STRING  , 1, SYSMACRO(modstring_strrev)     },
    { 0x23, "FORMAT"     , "I"    , TYPE_STRING  , 1, SYSMACRO(modstring_formatI)    },
    { 0x24, "FORMAT"     , "F"    , TYPE_STRING  , 1, SYSMACRO(modstring_formatF)    },
    { 0x25, "FORMAT"     , "FI"   , TYPE_STRING  , 2, SYSMACRO(modstring_formatFI)   },
    
    /* mod_math */
    { 0x30, "ABS"         , "F"   , TYPE_FLOAT   , 1, SYSMACRO(math_abs)          },
    { 0x31, "POW"         , "FF"  , TYPE_FLOAT   , 2, SYSMACRO(math_pow)          },
    { 0x32, "SQRT"        , "F"   , TYPE_FLOAT   , 1, SYSMACRO(math_sqrt)         },
    { 0x33, "COS"         , "F"   , TYPE_FLOAT   , 1, SYSMACRO(math_cos)          },
    { 0x34, "SIN"         , "F"   , TYPE_FLOAT   , 1, SYSMACRO(math_sin)          },
    { 0x35, "TAN"         , "F"   , TYPE_FLOAT   , 1, SYSMACRO(math_tan)          },
    { 0x36, "ACOS"        , "F"   , TYPE_FLOAT   , 1, SYSMACRO(math_acos)         },
    { 0x37, "ASIN"        , "F"   , TYPE_FLOAT   , 1, SYSMACRO(math_asin)         },
    { 0x38, "ATAN"        , "F"   , TYPE_FLOAT   , 1 ,SYSMACRO(math_atan)         },
    { 0x39, "ISINF"       , "F"   , TYPE_INT     , 1, SYSMACRO(math_isinf)        },
    { 0x3A, "ISNAN"       , "F"   , TYPE_INT     , 1, SYSMACRO(math_isnan)        },
    { 0x3B, "FINITE"      , "F"   , TYPE_INT     , 1, SYSMACRO(math_finite)       },
    { 0x3C, "FGET_ANGLE"  , "IIII", TYPE_INT     , 4, SYSMACRO(math_fget_angle)   },
    { 0x3D, "FGET_DIST"   , "IIII", TYPE_INT     , 4, SYSMACRO(math_fget_dist)    },
    { 0x3E, "NEAR_ANGLE"  , "III" , TYPE_INT     , 3, SYSMACRO(math_near_angle)   },
    { 0x3F, "GET_DISTX"   , "II"  , TYPE_INT     , 2, SYSMACRO(math_get_distx)    },
    { 0x40, "GET_DISTY"   , "II"  , TYPE_INT     , 2, SYSMACRO(math_get_disty)    },

    /* mod_time */
    { 0x50, "GET_TIMER"   , ""    , TYPE_INT     , 0, SYSMACRO(modtime_get_timer) },
    { 0x51, "TIME"        , ""    , TYPE_INT     , 0, SYSMACRO(modtime_time)      },
    { 0x52, "FTIME"       , "SI"  , TYPE_STRING  , 2, SYSMACRO(modtime_ftime)     },

    /* mod_file */
    { 0x60, "SAVE"        , "SV++" , TYPE_INT    , 4, SYSMACRO(modfile_save)        },
    { 0x61, "LOAD"        , "SV++" , TYPE_INT    , 4, SYSMACRO(modfile_load)        },
    { 0x62, "FOPEN"       , "SI"   , TYPE_INT    , 2, SYSMACRO(modfile_fopen)       },
    { 0x63, "FCLOSE"      , "I"    , TYPE_INT    , 1, SYSMACRO(modfile_fclose)      },
    { 0x64, "FREAD"       , "IV++" , TYPE_INT    , 4, SYSMACRO(modfile_fread)       },
    { 0x65, "FREAD"       , "PII"  , TYPE_INT    , 3, SYSMACRO(modfile_freadC)      },
    { 0x66, "FWRITE"      , "IV++" , TYPE_INT    , 4, SYSMACRO(modfile_fwrite)      },
    { 0x67, "FWRITE"      , "PII"  , TYPE_INT    , 3, SYSMACRO(modfile_fwriteC)     },
    { 0x68, "FSEEK"       , "III"  , TYPE_INT    , 3, SYSMACRO(modfile_fseek)       },
    { 0x69, "FREWIND"     , "I"    , TYPE_UNDEFINED, 1, SYSMACRO(modfile_frewind)     },
    { 0x6A, "FTELL"       , "I"    , TYPE_INT    , 1, SYSMACRO(modfile_ftell)       },
    { 0x6B, "FLENGTH"     , "I"    , TYPE_INT    , 1, SYSMACRO(modfile_filelength)  },
    { 0x6C, "FPUTS"       , "IS"   , TYPE_INT    , 2, SYSMACRO(modfile_fputs)       },
    { 0x6D, "FGETS"       , "I"    , TYPE_STRING , 1, SYSMACRO(modfile_fgets)       },
    { 0x6E, "FEOF"        , "I"    , TYPE_INT    , 1, SYSMACRO(modfile_feof)        },
    { 0x6F, "FILE"        , "S"    , TYPE_STRING , 1, SYSMACRO(modfile_file)        },
    { 0x70, "FEXISTS"     , "S"    , TYPE_INT    , 1, SYSMACRO(modfile_exists)      } ,
    { 0x71, "FILE_EXISTS" , "S"    , TYPE_INT    , 1, SYSMACRO(modfile_exists)      } ,
    { 0x72, "FREMOVE"     , "S"    , TYPE_INT    , 1, SYSMACRO(modfile_remove)      } ,
    { 0x73, "FMOVE"       , "SS"   , TYPE_INT    , 2, SYSMACRO(modfile_move)        } ,
    
    /* mod_sound */
    { 0x80, "LOAD_SONG"   , "S"    , TYPE_INT    , 1, SYSMACRO(modsound_load_song)          },
    { 0x81, "PLAY_SONG"   , "II"   , TYPE_INT    , 2, SYSMACRO(modsound_play_song)          },
    { 0x82, "UNLOAD_SONG" , "I"    , TYPE_INT    , 1, SYSMACRO(modsound_unload_song)        },
    { 0x83, "STOP_SONG"   , ""     , TYPE_INT    , 0, SYSMACRO(modsound_stop_song)          },
    { 0x84, "PAUSE_SONG"  , ""     , TYPE_INT    , 0, SYSMACRO(modsound_pause_song)         },
    { 0x85, "RESUME_SONG" , ""     , TYPE_INT    , 0, SYSMACRO(modsound_resume_song)        },
    { 0x86, "SET_SONG_VOLUME", "I" , TYPE_INT    , 1, SYSMACRO(modsound_set_song_volume)    },
    { 0x87, "IS_PLAYING_SONG", ""  , TYPE_INT    , 0, SYSMACRO(modsound_is_playing_song)    },
    { 0x88, "LOAD_WAV"    , "S"    , TYPE_INT    , 1, SYSMACRO(modsound_load_wav)           },
    { 0x89, "PLAY_WAV"    , "II"   , TYPE_INT    , 2, SYSMACRO(modsound_play_wav)           },
    { 0x8A, "UNLOAD_WAV"  , "I"    , TYPE_INT    , 1, SYSMACRO(modsound_unload_wav)         },
    { 0x8B, "STOP_WAV"    , "I"    , TYPE_INT    , 1, SYSMACRO(modsound_stop_wav)           },
    { 0x8C, "PAUSE_WAV"   , "I"    , TYPE_INT    , 1, SYSMACRO(modsound_pause_wav)          },
    { 0x8C, "RESUME_WAV"  , "I"    , TYPE_INT    , 1, SYSMACRO(modsound_resume_wav)         },
    { 0x8D, "IS_PLAYING_WAV", "I"  , TYPE_INT    , 1, SYSMACRO(modsound_is_playing_wav)     },
    { 0x8E, "SET_WAV_VOLUME", "II" , TYPE_INT    , 2, SYSMACRO(modsound_set_wav_volume)     },
    { 0x8F, "FADE_MUSIC_IN" , "III", TYPE_INT    , 3, SYSMACRO(modsound_fade_music_in)      },
    { 0x90, "FADE_MUSIC_OFF", "I"  , TYPE_INT    , 1, SYSMACRO(modsound_fade_music_off)     },
    { 0x91, "SET_CHANNEL_VOLUME", "II", TYPE_INT , 2, SYSMACRO(modsound_set_channel_volume) },
    { 0x92, "RESERVE_CHANNELS"  , "I" , TYPE_INT , 1, SYSMACRO(modsound_reserve_channels)   },
    { 0x93, "SET_PANNING" , "III"  , TYPE_INT    , 3, SYSMACRO(modsound_set_panning)        },
    { 0x94, "SET_POSITION", "III"  , TYPE_INT    , 3, SYSMACRO(modsound_set_position)       },
    { 0x95, "SET_DISTANCE", "II"   , TYPE_INT    , 2, SYSMACRO(modsound_set_distance)       },
    { 0x96, "REVERSE_STEREO", "II" , TYPE_INT    , 2, SYSMACRO(modsound_reverse_stereo)     },
    { 0x97, "PLAY_WAV"    , "III"  , TYPE_INT    , 3, SYSMACRO(modsound_play_wav_channel)   },
    /* mod_joy */
    { 0xA0, "JOY_AXES"   , ""      , TYPE_INT    , 0, SYSMACRO(modjoy_axes)                 },
    { 0xA1, "JOY_AXES"   , "I"     , TYPE_INT    , 1, SYSMACRO(modjoy_axes_specific)        },
    { 0xA2, "JOY_NUMAXES", ""      , TYPE_INT    , 0, SYSMACRO(modjoy_axes)                 },
    { 0xA3, "JOY_NUMAXES", "I"     , TYPE_INT    , 1, SYSMACRO(modjoy_axes_specific)        },
    { 0xA4, "JOY_GETAXIS", "I"     , TYPE_INT    , 1, SYSMACRO(modjoy_get_position)         },
    { 0xA5, "JOY_GETAXIS", "II"    , TYPE_INT    , 2, SYSMACRO(modjoy_get_position_specific)},
    { 0xA6, "JOY_BUTTONS", ""      , TYPE_INT    , 0, SYSMACRO(modjoy_buttons)              },
    { 0xA7, "JOY_BUTTONS", "I"     , TYPE_INT    , 1, SYSMACRO(modjoy_buttons_specific)     },
    { 0xA8, "JOY_NAME"   , "I"     , TYPE_STRING , 1, SYSMACRO(modjoy_name)                 },
    { 0xA9, "JOY_NUMBUTTONS", ""   , TYPE_INT    , 0, SYSMACRO(modjoy_buttons)              },
    { 0xAA, "JOY_NUMBUTTONS", "I"  , TYPE_INT    , 1, SYSMACRO(modjoy_buttons_specific)     },
    { 0xAB, "JOY_NUMBER" , ""      , TYPE_INT    , 0, SYSMACRO(modjoy_num)                  },
    { 0xAC, "JOY_NUMJOYSTICKS", "" , TYPE_INT    , 0, SYSMACRO(modjoy_num)                  },
    { 0xAC, "JOY_SELECT" , "I"     , TYPE_INT    , 1, SYSMACRO(modjoy_select)               },
    { 0xAD, "JOY_GETBUTTON", "I"   , TYPE_INT    , 1, SYSMACRO(modjoy_get_button)           },
    { 0xAE, "JOY_GETBUTTON", "II"  , TYPE_INT    , 2, SYSMACRO(modjoy_get_button_specific)  },
    { 0xAF, "JOY_GETPOSITION", "I" , TYPE_INT    , 1, SYSMACRO(modjoy_get_position)         },
    { 0xB0, "JOY_GETPOSITION", "II", TYPE_INT    , 2, SYSMACRO(modjoy_get_position_specific)},
    { 0xB1, "JOY_NUMHATS", ""      , TYPE_INT    , 0, SYSMACRO(modjoy_hats)                 },
    { 0xB2, "JOY_NUMHATS", "I"     , TYPE_INT    , 1, SYSMACRO(modjoy_hats_specific)        },
    { 0xB3, "JOY_NUMBALLS", ""     , TYPE_INT    , 0, SYSMACRO(modjoy_balls)                },
    { 0xB4, "JOY_NUMBALLS", "I"    , TYPE_INT    , 1, SYSMACRO(modjoy_balls_specific)       },
    { 0xB5, "JOY_GETHAT" , "I"     , TYPE_INT    , 1, SYSMACRO(modjoy_get_hat)              },
    { 0xB6, "JOY_GETHAT" , "II"    , TYPE_INT    , 2, SYSMACRO(modjoy_get_hat_specific)     },
    { 0xB7, "JOY_GETBALL", "IPP"   , TYPE_INT    , 3, SYSMACRO(modjoy_get_ball)             },
    { 0xB8, "JOY_GETBALL", "IIPP"  , TYPE_INT    , 4, SYSMACRO(modjoy_get_ball_specific)    },
    { 0xB9, "NUMBER_JOY" , ""      , TYPE_INT    , 0, SYSMACRO(modjoy_num)                  },
    { 0xBA, "SELECT_JOY" , "I"     , TYPE_INT    , 1, SYSMACRO(modjoy_select)               },
    { 0xBB, "GET_JOY_BUTTON", "I"  , TYPE_INT    , 1, SYSMACRO(modjoy_get_button)           },
    { 0xBC, "GET_JOY_BUTTON", "II" , TYPE_INT    , 2, SYSMACRO(modjoy_get_button_specific)  },
    { 0xBD, "GET_JOY_POSITION", "I", TYPE_INT    , 1, SYSMACRO(modjoy_get_position)         },
    { 0xBE, "GET_JOY_POSITION","II", TYPE_INT    , 2, SYSMACRO(modjoy_get_position_specific)},
    /* mod_proc */
    { 0xC0, "GET_ID"     , "I"   , TYPE_INT   , 1, SYSMACRO(modproc_get_id)          },
    { 0xC1, "GET_STATUS" , "I"   , TYPE_INT   , 1, SYSMACRO(modproc_get_status)      },
    { 0xC2, "SIGNAL"     , "II"  , TYPE_INT   , 2, SYSMACRO(modproc_signal)          },
    { 0xC3, "SIGNAL_ACTION", "II", TYPE_INT   , 2, SYSMACRO(modproc_signal_action)   },
    { 0xC4, "SIGNAL_ACTION", "III",TYPE_INT   , 3, SYSMACRO(modproc_signal_action3)  },
    { 0xC5, "LET_ME_ALONE", ""   , TYPE_INT   , 0, SYSMACRO(modproc_let_me_alone)    },
    { 0xC6, "EXIT"       , "SI"  , TYPE_INT   , 2, SYSMACRO(modproc_exit)            },
    { 0xC7, "EXIT"       , "S"   , TYPE_INT   , 1, SYSMACRO(modproc_exit_1)          },
    { 0xC8, "EXIT"       , ""    , TYPE_INT   , 0, SYSMACRO(modproc_exit_0)          },
    { 0xC9, "EXISTS"     , "I"   , TYPE_INT   , 1, SYSMACRO(modproc_running)         },
    /* mod_rand */
    { 0xD0, "RAND_SEED"  , "I"   , TYPE_INT   , 1, SYSMACRO(rand_seed)     },
    { 0xD1, "RAND"       , "II"  , TYPE_INT   , 2, SYSMACRO(rand_std)      },
    /* mod_dir */
    { 0xD5, "CD"      , ""  , TYPE_STRING , 0, SYSMACRO(moddir_cd)     },
    { 0xD6, "CHDIR"   , "S" , TYPE_INT    , 1, SYSMACRO(moddir_chdir)  },
    { 0xD7, "MKDIR"   , "S" , TYPE_INT    , 1, SYSMACRO(moddir_mkdir)  },
    { 0xD8, "RMDIR"   , "S" , TYPE_INT    , 1, SYSMACRO(moddir_rmdir)  },
    { 0xD9, "GLOB"    , "S" , TYPE_STRING , 1, SYSMACRO(moddir_glob)   },
    { 0xDA, "CD"      , "S" , TYPE_STRING , 1, SYSMACRO(moddir_chdir)  },
    { 0xDB, "RM"      , "S" , TYPE_INT    , 1, SYSMACRO(moddir_rm)     },
    { 0xDC, "DIROPEN" , "S" , TYPE_INT    , 1, SYSMACRO(moddir_open)   },
    { 0xDE, "DIRCLOSE", "I" , TYPE_INT    , 1, SYSMACRO(moddir_close)  },
    { 0xDF, "DIRREAD" , "I" , TYPE_STRING , 1, SYSMACRO(moddir_read)   },
    /* mod_sort */
    { 0xE0, "QUICKSORT", "PIIIBB", TYPE_INT , 6 , SYSMACRO(modsort_quicksort) },
    { 0xE1, "KSORT"   , "V++V++" , TYPE_INT , 6 , SYSMACRO(modsort_ksort)     },
    { 0xE2, "KSORT"   , "V++V++I", TYPE_INT , 7 , SYSMACRO(modsort_ksort_n)   },
    { 0xE3, "SORT"    , "V++I"   , TYPE_INT , 4 , SYSMACRO(modsort_sort_n)    },
    { 0xE4, "SORT"    , "V++"    , TYPE_INT , 3 , SYSMACRO(modsort_sort)      },
    /* mod_mem */
    { 0xF0, "MEM_CALLOC"      , "II" , TYPE_POINTER, 2, SYSMACRO(modmem_calloc)         },
    { 0xF1, "MEM_ALLOC"       , "I"  , TYPE_POINTER, 1, SYSMACRO(modmem_alloc)          },
    { 0xF2, "MEM_FREE"        , "P"  , TYPE_INT    , 1, SYSMACRO(modmem_free)           },
    { 0xF3, "MEM_REALLOC"     , "PI" , TYPE_POINTER, 2, SYSMACRO(modmem_realloc)        },
    { 0xF4, "MEM_CMP"         , "PPI", TYPE_INT    , 3, SYSMACRO(modmem_memcmp)         },
    { 0xF5, "MEM_SET"         , "PBI", TYPE_INT    , 3, SYSMACRO(modmem_memset)         },
    { 0xF6, "MEM_SETW"        , "PWI", TYPE_INT    , 3, SYSMACRO(modmem_memsetw)        },
    { 0xF7, "MEM_SETI"        , "PII", TYPE_INT    , 3, SYSMACRO(modmem_memseti)        },
    { 0xF8, "MEM_COPY"        , "PPI", TYPE_INT    , 3, SYSMACRO(modmem_memcopy)        },
    { 0xF9, "MEM_MOVE"        , "PPI", TYPE_INT    , 3, SYSMACRO(modmem_memmove)        },
    { 0xFA, "MEM_AVAILABLE"   , ""   , TYPE_INT    , 0, SYSMACRO(modmem_memory_free)    },
    { 0xFB, "MEM_TOTAL"       , ""   , TYPE_INT    , 0, SYSMACRO(modmem_memory_total)   },
    { 0xFC, "CALLOC"          , "II" , TYPE_POINTER, 2, SYSMACRO(modmem_calloc)         },
    { 0xFD, "ALLOC"           , "I"  , TYPE_POINTER, 1, SYSMACRO(modmem_alloc)          },
    { 0xFE, "FREE"            , "P"  , TYPE_INT    , 1, SYSMACRO(modmem_free)           },
    { 0xFF, "REALLOC"         , "PI" , TYPE_POINTER, 2, SYSMACRO(modmem_realloc)        },
    { 0x100, "MEMCMP"         , "PPI", TYPE_INT    , 3, SYSMACRO(modmem_memcmp)         },
    { 0x101, "MEMSET"         , "PBI", TYPE_INT    , 3, SYSMACRO(modmem_memset)         },
    { 0x102, "MEMSETW"        , "PWI", TYPE_INT    , 3, SYSMACRO(modmem_memsetw)        },
    { 0x103, "MEMSETI"        , "PII", TYPE_INT    , 3, SYSMACRO(modmem_memseti)        },
    { 0x104, "MEMCOPY"        , "PPI", TYPE_INT    , 3, SYSMACRO(modmem_memcopy)        },
    { 0x105, "MEMMOVE"        , "PPI", TYPE_INT    , 3, SYSMACRO(modmem_memmove)        },
    { 0x106, "MEMORY_FREE"    , ""   , TYPE_INT    , 0, SYSMACRO(modmem_memory_free)    },
    { 0x107, "MEMORY_TOTAL"   , ""   , TYPE_INT    , 0, SYSMACRO(modmem_memory_total)   },
    /* mod_video */
    { 0x110, "SET_MODE"       , "I"   ,TYPE_INT    , 1, SYSMACRO(modvideo_set_mode)     },
    { 0x111, "SET_MODE"       , "II"  ,TYPE_INT    , 2, SYSMACRO(modvideo_set_mode_2)   },
    { 0x112, "SET_MODE"       , "III" ,TYPE_INT    , 3, SYSMACRO(modvideo_set_mode_3)   },
    { 0x113, "SET_MODE"       , "IIII",TYPE_INT    , 4, SYSMACRO(modvideo_set_mode_4)   },
    { 0x114, "SET_FPS"        , "II"  ,TYPE_INT    , 2, SYSMACRO(modvideo_set_fps)      },
    { 0x115, "GET_MODES"      , "II"  ,TYPE_POINTER, 2, SYSMACRO(modvideo_list_modes)   },
    { 0x116, "MODE_IS_OK"     , "IIII",TYPE_INT    , 4, SYSMACRO(modvideo_mode_is_ok)   },

    { 0    , 0                , ""      , TYPE_UNDEFINED , 0, 0                        }
} ;
#endif
