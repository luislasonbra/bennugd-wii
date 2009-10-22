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

    { 0   , 0           , ""      , TYPE_UNDEFINED  , 0, 0                        }
} ;
#endif
