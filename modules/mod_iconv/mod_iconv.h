/* ************************************************************************** */
/* *                                                                        * */
/* *            Copyright (c) 2008-2010 - Joseba García Etxebarria          * */
/* *                                                                        * */
/* *                   This is a BennuGD interface to iconv                 * */
/* *                                                                        * */
/* *            Under the terms of the GNU GPL version 2 license            * */
/* *                                                                        * */
/* *                         See LICENSE for details                        * */
/* *                                                                        * */
/* ************************************************************************** */

#ifndef __ICONV_H
#define __ICONV_H

#include <bgddl.h>
#include <instance_st.h>

extern int bgd_iconv(INSTANCE * my, int * params);

#ifdef __STATIC__
DLSYSFUNCS iconv_functions_exports[] =
#else
DLSYSFUNCS __bgdexport( mod_iconv, functions_exports )[] =
#endif
{
  { "ICONV"            , "SSS"  , TYPE_STRING, SYSMACRO(bgd_iconv)       },
  { 0                  , 0      , 0          , 0                         }
};

#endif
