/*
 *  Copyright � 2006-2009 SplinterGU (Fenix/Bennugd)
 *  Copyright � 2002-2006 Fenix Team (Fenix)
 *  Copyright � 1999-2002 Jos� Luis Cebri�n Pag�e (Fenix)
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
    /* mod_map */
    { 0x120, "MAP_BLOCK_COPY" , "IIIIIIIIII", TYPE_INT,10, SYSMACRO(modmap_map_block_copy)  },
    { 0x121, "MAP_PUT"        , "IIIII"    , TYPE_INT , 5, SYSMACRO(modmap_map_put)         },
    { 0x122, "MAP_XPUT"       , "IIIIIIII" , TYPE_INT , 8, SYSMACRO(modmap_map_xput)        },
    { 0x123, "MAP_NEW"        , "III"      , TYPE_INT , 3, SYSMACRO(modmap_new_map)         },
    { 0x124, "MAP_NEW"        , "IIII"     , TYPE_INT , 4, SYSMACRO(modmap_new_map_extend)  },
    { 0x125, "MAP_CLEAR"      , "III"      , TYPE_INT , 3, SYSMACRO(modmap_map_clear)       },
    { 0x126, "MAP_CLONE"      , "II"       , TYPE_INT , 2, SYSMACRO(modmap_map_clone)       },
    { 0x127, "MAP_NAME"       , "II"       , TYPE_STRING, 2, SYSMACRO(modmap_map_name)      },
    { 0x128, "MAP_SET_NAME"   , "IIS"      , TYPE_INT , 3, SYSMACRO(modmap_map_set_name)    },
    { 0x129, "MAP_EXISTS"     , "II"       , TYPE_INT , 2, SYSMACRO(modmap_map_exists)      },
    { 0x12A, "MAP_XPUTNP"     , "IIIIIIIIII", TYPE_INT,10, SYSMACRO(modmap_map_xputnp)      },
    { 0x12B, "MAP_DEL"        , "II"       , TYPE_INT , 2, SYSMACRO(modmap_unload_map)      },
    { 0x12C, "MAP_UNLOAD"     , "II"       , TYPE_INT , 2, SYSMACRO(modmap_unload_map)      },
    { 0x12D, "MAP_LOAD"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_map)        },
    { 0x12E, "MAP_SAVE"       , "IIS"      , TYPE_INT , 3, SYSMACRO(modmap_save_map)        },
    { 0x12F, "MAP_BUFFER"     , "II"       , TYPE_POINTER, 2, SYSMACRO(modmap_map_buffer)   },
    { 0x130, "FPG_ADD"        , "IIII"     , TYPE_INT , 4, SYSMACRO(modmap_fpg_add)         },
    { 0x131, "FPG_NEW"        , ""         , TYPE_INT , 0, SYSMACRO(modmap_fpg_new)         },
    { 0x132, "FPG_EXISTS"     , "I"        , TYPE_INT , 1, SYSMACRO(modmap_fpg_exists)      },
    { 0x133, "FPG_LOAD"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_fpg)        },
    { 0x134, "FPG_LOAD"       , "SP"       , TYPE_INT , 2, SYSMACRO(modmap_bgload_fpg)      },
    { 0x135, "FPG_SAVE"       , "IS"       , TYPE_INT , 2, SYSMACRO(modmap_save_fpg)        },
    { 0x136, "FPG_DEL"        , "I"        , TYPE_INT , 1, SYSMACRO(modmap_unload_fpg)      },
    { 0x137, "FPG_UNLOAD"     , "I"        , TYPE_INT , 1, SYSMACRO(modmap_unload_fpg)      },
    { 0x138, "PAL_NEW"        , ""         , TYPE_INT , 0, SYSMACRO(modmap_pal_create)      },
    { 0x139, "PAL_DEL"        , "I"        , TYPE_INT , 1, SYSMACRO(modmap_pal_unload)      },
    { 0x13A, "PAL_UNLOAD"     , "I"        , TYPE_INT , 1, SYSMACRO(modmap_pal_unload)      },
    { 0x13B, "PAL_CLONE"      , "I"        , TYPE_INT , 1, SYSMACRO(modmap_pal_clone)       },
    { 0x13C, "PAL_REFRESH"    , ""         , TYPE_INT , 0, SYSMACRO(modmap_pal_refresh)     },
    { 0x13D, "PAL_REFRESH"    , "I"        , TYPE_INT , 1, SYSMACRO(modmap_pal_refresh_2)   },
    { 0x13E, "PAL_MAP_GETID"  , "II"       , TYPE_INT , 2, SYSMACRO(modmap_pal_map_getid)   },
    { 0x13F, "PAL_MAP_ASSIGN" , "III"      , TYPE_INT , 3, SYSMACRO(modmap_pal_map_assign)  },
    { 0x140, "PAL_MAP_REMOVE" , "II"       , TYPE_INT , 2, SYSMACRO(modmap_pal_map_remove)  },
    { 0x141, "PAL_GET"        , "IIP"      , TYPE_INT , 3, SYSMACRO(modmap_get_colors)      },
    { 0x142, "PAL_GET"        , "IIIP"     , TYPE_INT , 4, SYSMACRO(modmap_pal_get)         },
    { 0x143, "PAL_SYS_SET"    , "I"        , TYPE_INT , 1, SYSMACRO(modmap_set_system_pal)  },
    { 0x144, "PAL_SYS_SET"    , "P"        , TYPE_INT,1,SYSMACRO(modmap_set_system_pal_raw) },
    { 0x145, "PAL_SET"        , "IIP"      , TYPE_INT , 3, SYSMACRO(modmap_set_colors)      },
    { 0x146, "PAL_SET"        , "IIIP"     , TYPE_INT , 4, SYSMACRO(modmap_pal_set)         },
    { 0x147, "PAL_SAVE"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_save_system_pal) },
    { 0x148, "PAL_SAVE"       , "SI"       , TYPE_INT , 2, SYSMACRO(modmap_save_pal)        },
    { 0x149, "PAL_LOAD"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_pal)        },
    { 0x14A, "COLORS_SET"     , "IIP"      , TYPE_INT , 3, SYSMACRO(modmap_set_colors)      },
    { 0x14B, "COLORS_SET"     , "IIIP"     , TYPE_INT , 4, SYSMACRO(modmap_pal_set)         },
    { 0x14C, "COLORS_GET"     , "IIP"      , TYPE_INT , 3, SYSMACRO(modmap_get_colors)      },
    { 0x14D, "COLORS_GET"     , "IIIP"     , TYPE_INT , 4, SYSMACRO(modmap_pal_get)         },
    { 0x14E, "PALETTE_ROLL"   , "III"      , TYPE_INT , 3, SYSMACRO(modmap_roll_palette)    },
    { 0x14F, "PALETTE_CONVERT", "IIP"      , TYPE_INT , 3, SYSMACRO(modmap_convert_palette) },
    { 0x150, "COLOR_FIND"     , "BBB"      , TYPE_INT , 3, SYSMACRO(modmap_find_color)      },
    { 0x151, "RGB"            , "BBB"      , TYPE_INT , 3, SYSMACRO(modmap_rgb)             },
    { 0x152, "RGBA"           , "BBBB"     , TYPE_INT , 4, SYSMACRO(modmap_rgba)            },
    { 0x153, "RGB_GET"        , "IPPP"     , TYPE_INT , 4, SYSMACRO(modmap_get_rgb)         },
    { 0x154, "RGBA_GET"       , "IPPPP"    , TYPE_INT , 5, SYSMACRO(modmap_get_rgba)        },
    { 0x155, "FADE"           , "IIII"     , TYPE_INT , 4, SYSMACRO(modmap_fade)            },
    { 0x156, "FADE_ON"        , ""         , TYPE_INT , 0, SYSMACRO(modmap_fade_on)         },
    { 0x157, "FADE_OFF"       , ""         , TYPE_INT , 0, SYSMACRO(modmap_fade_off)        },
    { 0x158, "MAP_INFO_SET"   , "IIII"     , TYPE_INT , 4, SYSMACRO(modmap_graphic_set)     },
    { 0x159, "MAP_INFO_GET"   , "III"      , TYPE_INT , 3, SYSMACRO(modmap_graphic_info)    },
    { 0x15A, "MAP_INFO"       , "III"      , TYPE_INT , 3, SYSMACRO(modmap_graphic_info)    },
    { 0x15B, "GRAPHIC_SET"    , "IIII"     , TYPE_INT , 4, SYSMACRO(modmap_graphic_set)     },
    { 0x15C, "GRAPHIC_INFO"   , "III"      , TYPE_INT , 3, SYSMACRO(modmap_graphic_info)    },
    { 0x15D, "POINT_GET"      , "IIIPP"    , TYPE_INT , 5, SYSMACRO(modmap_get_point)       },
    { 0x15E, "POINT_SET"      , "IIIII"    , TYPE_INT , 5, SYSMACRO(modmap_set_point)       },
    { 0x15F, "CENTER_SET"     , "IIII"     , TYPE_INT , 4, SYSMACRO(modmap_set_center)      },
    { 0x160, "FNT_LOAD"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_fnt)        },
    { 0x161, "FNT_UNLOAD"     , "I"        , TYPE_INT , 1, SYSMACRO(modmap_unload_fnt)      },
    { 0x162, "FNT_SAVE"       , "IS"       , TYPE_INT , 2, SYSMACRO(modmap_save_fnt)        },
    { 0x163, "FNT_NEW"        , "I"        , TYPE_INT , 1, SYSMACRO(modmap_fnt_new)         },
    { 0x164, "BDF_LOAD"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_bdf)        },
    { 0x165, "GLYPH_GET"      , "II"       , TYPE_INT , 2, SYSMACRO(modmap_get_glyph)       },
    { 0x166, "GLYPH_SET"      , "IIII"     , TYPE_INT , 4, SYSMACRO(modmap_set_glyph)       },
    { 0x167, "PNG_LOAD"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_png)        },
    { 0x168, "PCX_LOAD"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_pcx)        },
    { 0x169, "PNG_SAVE"       , "IIS"      , TYPE_INT , 3, SYSMACRO(modmap_save_png)        },
    /* ------------ Compatibility ------------ */
    { 0x16A, "NEW_MAP"        , "III"      , TYPE_INT , 3, SYSMACRO(modmap_new_map)         },
    { 0x16B, "LOAD_MAP"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_map)        },
    { 0x16C, "UNLOAD_MAP"     , "II"       , TYPE_INT , 2, SYSMACRO(modmap_unload_map)      },
    { 0x16D, "SAVE_MAP"       , "IIS"      , TYPE_INT , 3, SYSMACRO(modmap_save_map)        },
    { 0x16E, "NEW_PAL"        , ""         , TYPE_INT , 0, SYSMACRO(modmap_pal_create)      },
    { 0x16F, "LOAD_PAL"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_pal)        },
    { 0x170, "UNLOAD_PAL"     , "I"        , TYPE_INT , 1, SYSMACRO(modmap_pal_unload)      },
    { 0x171, "SAVE_PAL"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_save_system_pal) },
    { 0x172, "SAVE_PAL"       , "SI"       , TYPE_INT , 2, SYSMACRO(modmap_save_pal)        },
    { 0x173, "SET_COLORS"     , "IIP"      , TYPE_INT , 3, SYSMACRO(modmap_set_colors)      },
    { 0x174, "SET_COLORS"     , "IIIP"     , TYPE_INT , 4, SYSMACRO(modmap_pal_set)         },
    { 0x175, "GET_COLORS"     , "IIP"      , TYPE_INT , 3, SYSMACRO(modmap_get_colors)      },
    { 0x176, "GET_COLORS"     , "IIIP"     , TYPE_INT , 4, SYSMACRO(modmap_pal_get)         },
    { 0x177, "ROLL_PALETTE"   , "III"      , TYPE_INT , 3, SYSMACRO(modmap_roll_palette)    },
    { 0x178, "CONVERT_PALETTE", "IIP"      , TYPE_INT , 3, SYSMACRO(modmap_convert_palette) },
    { 0x179, "FIND_COLOR"     , "BBB"      , TYPE_INT , 3, SYSMACRO(modmap_find_color)      },
    { 0x17A, "GET_RGB"        , "IPPP"     , TYPE_INT , 4, SYSMACRO(modmap_get_rgb)         },
    { 0x17B, "GET_RGBA"       , "IPPPP"    , TYPE_INT , 5, SYSMACRO(modmap_get_rgba)        },
    { 0x17C, "NEW_FPG"        , ""         , TYPE_INT , 0, SYSMACRO(modmap_fpg_new)         },
    { 0x17D, "LOAD_FPG"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_fpg)        },
    { 0x17E, "LOAD_FPG"       , "SP"       , TYPE_INT , 2, SYSMACRO(modmap_bgload_fpg)      },
    { 0x17F, "SAVE_FPG"       , "IS"       , TYPE_INT , 2, SYSMACRO(modmap_save_fpg)        },
    { 0x180, "UNLOAD_FPG"     , "I"        , TYPE_INT , 1, SYSMACRO(modmap_unload_fpg)      },
    { 0x181, "GET_POINT"      , "IIIPP"    , TYPE_INT , 5, SYSMACRO(modmap_get_point)       },
    { 0x182, "SET_POINT"      , "IIIII"    , TYPE_INT , 5, SYSMACRO(modmap_set_point)       },
    { 0x183, "SET_CENTER"     , "IIII"     , TYPE_INT , 4, SYSMACRO(modmap_set_center)      },
    { 0x184, "NEW_FNT"        , "I"        , TYPE_INT , 1, SYSMACRO(modmap_fnt_new)         },
    { 0x185, "LOAD_FNT"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_fnt)        },
    { 0x186, "UNLOAD_FNT"     , "I"        , TYPE_INT , 1, SYSMACRO(modmap_unload_fnt)      },
    { 0x187, "SAVE_FNT"       , "IS"       , TYPE_INT , 2, SYSMACRO(modmap_save_fnt)        },
    { 0x188, "LOAD_BDF"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_bdf)        },
    { 0x189, "GET_GLYPH"      , "II"       , TYPE_INT , 2, SYSMACRO(modmap_get_glyph)       },
    { 0x18A, "SET_GLYPH"      , "IIII"     , TYPE_INT , 4, SYSMACRO(modmap_set_glyph)       },
    { 0x18B, "LOAD_PNG"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_png)        },
    { 0x18C, "LOAD_PCX"       , "S"        , TYPE_INT , 1, SYSMACRO(modmap_load_pcx)        },
    { 0x18D, "SAVE_PNG"       , "IIS"      , TYPE_INT , 3, SYSMACRO(modmap_save_png)        },
    /* mod_text */
    { 0x190, "WRITE"          , "IIIIS"   , TYPE_INT  , 5, SYSMACRO(modtext_write)          },
    { 0x191, "WRITE_INT"      , "IIIIP"   , TYPE_INT  , 5, SYSMACRO(modtext_write_int)      },
    { 0x192, "MOVE_TEXT"      , "III"     , TYPE_INT  , 3, SYSMACRO(modtext_move_text)      },
    { 0x193, "DELETE_TEXT"    , "I"       , TYPE_INT  , 1, SYSMACRO(modtext_delete_text)    },
    { 0x194, "WRITE_IN_MAP"   , "ISI"     , TYPE_INT  , 3, SYSMACRO(modtext_write_in_map)   },
    { 0x195, "TEXT_WIDTH"     , "IS"      , TYPE_INT  , 2, SYSMACRO(modtext_text_width)     },
    { 0x196, "TEXT_HEIGHT"    , "IS"      , TYPE_INT  , 2, SYSMACRO(modtext_text_height)    },
    { 0x197, "GET_TEXT_COLOR" , ""        , TYPE_INT  , 0, SYSMACRO(modtext_get_text_color) },
    { 0x198, "SET_TEXT_COLOR" , "I"       , TYPE_INT  , 1, SYSMACRO(modtext_set_text_color) },
    { 0x199, "WRITE_VAR"      , "IIIIV++" , TYPE_INT  , 7, SYSMACRO(modtext_write_var)      },
    { 0x19A, "WRITE_FLOAT"    , "IIIIP"   , TYPE_INT  , 5, SYSMACRO(modtext_write_float)    },
    { 0x19B, "WRITE_STRING"   , "IIIIP"   , TYPE_INT  , 5, SYSMACRO(modtext_write_string)   },
    /* mod_grproc */
    { 0x200, "ADVANCE"        , "I"       , TYPE_INT  , 1, SYSMACRO(grproc_advance)         },
    { 0x201, "XADVANCE"       , "II"      , TYPE_INT  , 2, SYSMACRO(grproc_xadvance)        },
    { 0x202, "GET_ANGLE"      , "I"       , TYPE_INT  , 1, SYSMACRO(grproc_get_angle)       },
    { 0x203, "GET_DIST"       , "I"       , TYPE_INT  , 1, SYSMACRO(grproc_get_dist)        },
    { 0x204, "COLLISION"      , "I"       , TYPE_INT  , 1, SYSMACRO(grproc_collision)       },
    { 0x205, "GET_REAL_POINT" , "IPP"     , TYPE_INT  , 3, SYSMACRO(grproc_get_real_point)  },
    /* mod_regex */
    { 0x20A, "REGEX"          , "SS"    , TYPE_INT    , 2, SYSMACRO(modregex_regex)         },
    { 0x20B, "REGEX_REPLACE"  , "SSS"   , TYPE_STRING , 3, SYSMACRO(modregex_regex_replace) },
    { 0x20C, "SPLIT"          , "SSPI"  , TYPE_INT    , 4, SYSMACRO(modregex_split)         },
    { 0x20D, "JOIN"           , "SPI"   , TYPE_STRING , 3, SYSMACRO(modregex_join)          },


    { 0    , 0                , ""      , TYPE_UNDEFINED , 0, 0                        }
} ;
#endif
