/*
 *  Copyright � 2006-2010 SplinterGU (Fenix/Bennugd)
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

#include <loadlib.h> /* Must be fist include */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bgdrtm.h"
#include "dcb.h"
#include "xstrings.h"

#include <bgddl.h>

#ifdef __STATIC__
#include "../../../modules/libsdlhandler/libsdlhandler.h" //libsdlhandler
#include "../../../modules/libjoy/libjoy.h"               //libjoy
#include "../../../modules/mod_sound/mod_sound.h"         //mod_sound
#include "../../../modules/mod_proc/mod_proc.h"           //mod_proc
#include "../../../modules/mod_timers/mod_timers.h"       //mod_timers
#include "libgrbase_definitions.h"    //libgrbase
#include "librender_constants.h"//librender
#include "libvideo.h"            //libvideo
#include "libvideo_fixups.h"
#include "../../../modules/libmouse/libmouse.h"            //libmouse
#include "libfont.h"              //libfont
#include "../../../modules/mod_grproc/mod_grproc.h"        //mod_grproc
#include "libkey.h"                //libkey
#ifdef TARGET_WII
#include <SDL/SDL.h>
#elif defined(TARGET_LINUX)
#include <SDL.h>
#endif
#endif

/* ---------------------------------------------------------------------- */

/* bgdrtm.h header must exist */
extern int bgd_copy_struct( INSTANCE * my, int * params ) ;
extern int bgd_internal_memcopy( INSTANCE * my, int * params ) ;
#ifdef __STATIC__
/* Functions declared in the various modules used */
/* mod_say */
extern int modsay_say( INSTANCE * my, int * params );
extern int modsay_say_fast( INSTANCE * my, int * params );
/* mod_string */
extern int modstring_strlen( INSTANCE * my, int * params );
extern int modstring_strupper( INSTANCE * my, int * params );
extern int modstring_strlower( INSTANCE * my, int * params );
extern int modstring_strcasecmp( INSTANCE * my, int * params );
extern int modstring_substr( INSTANCE * my, int * params );
extern int modstring_substr2( INSTANCE * my, int * params );
extern int modstring_strfind( INSTANCE * my, int * params );
extern int modstring_strfindSSI( INSTANCE * my, int * params );
extern int modstring_lpad( INSTANCE * my, int * params );
extern int modstring_rpad( INSTANCE * my, int * params );
extern int modstring_itos( INSTANCE * my, int * params );
extern int modstring_ftos( INSTANCE * my, int * params );
extern int modstring_stoi( INSTANCE * my, int * params );
extern int modstring_stof( INSTANCE * my, int * params );
extern int modstring_asc( INSTANCE * my, int * params );
extern int modstring_chr( INSTANCE * my, int * params );
extern int modstring_trim( INSTANCE * my, int * params );
extern int modstring_strrev( INSTANCE * my, int * params );
extern int modstring_formatI( INSTANCE * my, int * params );
extern int modstring_formatF( INSTANCE * my, int * params );
extern int modstring_formatFI( INSTANCE * my, int * params );
/* mod_math */
extern int math_abs( INSTANCE * my, int * params );
extern int math_pow( INSTANCE * my, int * params );
extern int math_sqrt( INSTANCE * my, int * params );
extern int math_cos( INSTANCE * my, int * params );
extern int math_sin( INSTANCE * my, int * params );
extern int math_tan( INSTANCE * my, int * params );
extern int math_acos( INSTANCE * my, int * params );
extern int math_asin( INSTANCE * my, int * params );
extern int math_atan( INSTANCE * my, int * params );
extern int math_isinf( INSTANCE * my, int * params );
extern int math_isnan( INSTANCE * my, int * params );
extern int math_finite( INSTANCE * my, int * params );
extern int math_get_disty( INSTANCE * my, int * params );
extern int math_fget_angle( INSTANCE * my, int * params );
extern int math_fget_dist( INSTANCE * my, int * params );
extern int math_near_angle( INSTANCE * my, int * params );
extern int math_get_distx( INSTANCE * my, int * params );
/* mod_time */
extern int modtime_get_timer( INSTANCE * my, int * params );
extern int modtime_time( INSTANCE * my, int * params );
extern int modtime_ftime( INSTANCE * my, int * params );
/* mod_file */
extern int modfile_save( INSTANCE * my, int * params );
extern int modfile_load( INSTANCE * my, int * params );
extern int modfile_fopen( INSTANCE * my, int * params );
extern int modfile_fclose( INSTANCE * my, int * params );
extern int modfile_fread( INSTANCE * my, int * params );
extern int modfile_fwrite( INSTANCE * my, int * params );
extern int modfile_freadC( INSTANCE * my, int * params );
extern int modfile_fwriteC( INSTANCE * my, int * params );
extern int modfile_fseek( INSTANCE * my, int * params );
extern int modfile_frewind( INSTANCE * my, int * params );
extern int modfile_ftell( INSTANCE * my, int * params );
extern int modfile_filelength( INSTANCE * my, int * params );
extern int modfile_fputs( INSTANCE * my, int * params );
extern int modfile_fgets( INSTANCE * my, int * params );
extern int modfile_file( INSTANCE * my, int * params );
extern int modfile_feof( INSTANCE * my, int * params );
extern int modfile_exists( INSTANCE * my, int * params );
extern int modfile_remove( INSTANCE * my, int * params );
extern int modfile_move( INSTANCE * my, int * params );
/* mod_sound */
extern int modsound_load_song( INSTANCE * my, int * params );
extern int modsound_play_song( INSTANCE * my, int * params );
extern int modsound_unload_song( INSTANCE * my, int * params );
extern int modsound_stop_song( INSTANCE * my, int * params );
extern int modsound_pause_song( INSTANCE * my, int * params );
extern int modsound_resume_song( INSTANCE * my, int * params );
extern int modsound_is_playing_song( INSTANCE * my, int * params );
extern int modsound_set_song_volume( INSTANCE * my, int * params );
extern int modsound_fade_music_in( INSTANCE * my, int * params );
extern int modsound_fade_music_off( INSTANCE * my, int * params );
extern int modsound_load_wav( INSTANCE * my, int * params );
extern int modsound_play_wav( INSTANCE * my, int * params );
extern int modsound_play_wav_channel( INSTANCE * my, int * params );
extern int modsound_unload_wav( INSTANCE * my, int * params );
extern int modsound_stop_wav( INSTANCE * my, int * params );
extern int modsound_pause_wav( INSTANCE * my, int * params );
extern int modsound_resume_wav( INSTANCE * my, int * params );
extern int modsound_is_playing_wav( INSTANCE * my, int * params );
extern int modsound_set_channel_volume( INSTANCE * my, int * params );
extern int modsound_reserve_channels( INSTANCE * my, int * params );
extern int modsound_set_wav_volume( INSTANCE * my, int * params );
extern int modsound_set_panning( INSTANCE * my, int * params );
extern int modsound_set_position( INSTANCE * my, int * params );
extern int modsound_set_distance( INSTANCE * my, int * params );
extern int modsound_reverse_stereo( INSTANCE * my, int * params );
/* mod_joy */
extern int modjoy_num( INSTANCE * my, int * params );
extern int modjoy_name( INSTANCE * my, int * params );
extern int modjoy_select( INSTANCE * my, int * params );
extern int modjoy_buttons( INSTANCE * my, int * params );
extern int modjoy_axes( INSTANCE * my, int * params );
extern int modjoy_get_button( INSTANCE * my, int * params );
extern int modjoy_get_position( INSTANCE * my, int * params );
extern int modjoy_hats( INSTANCE * my, int * params );
extern int modjoy_balls( INSTANCE * my, int * params );
extern int modjoy_get_hat( INSTANCE * my, int * params );
extern int modjoy_get_ball( INSTANCE * my, int * params );
extern int modjoy_buttons_specific( INSTANCE * my, int * params );
extern int modjoy_axes_specific( INSTANCE * my, int * params );
extern int modjoy_get_button_specific( INSTANCE * my, int * params );
extern int modjoy_get_position_specific( INSTANCE * my, int * params );
extern int modjoy_hats_specific( INSTANCE * my, int * params );
extern int modjoy_balls_specific( INSTANCE * my, int * params );
extern int modjoy_get_hat_specific( INSTANCE * my, int * params );
extern int modjoy_get_ball_specific( INSTANCE * my, int * params );

/* mod_proc */
extern int modproc_get_status( INSTANCE * my, int * params );
extern int modproc_get_id( INSTANCE * my, int * params );
extern int modproc_let_me_alone( INSTANCE * my, int * params );
extern int modproc_signal_action3( INSTANCE * my, int * params );
extern int modproc_signal_action( INSTANCE * my, int * params );
extern int modproc_signal( INSTANCE * my, int * params );
extern int modproc_running( INSTANCE * my, int * params );
extern int modproc_exit( INSTANCE * my, int * params );
extern int modproc_exit_1( INSTANCE * my, int * params );
extern int modproc_exit_0( INSTANCE * my, int * params );

/* mod_rand */
extern int rand_seed( INSTANCE * my, int * params );
extern int rand_std( INSTANCE * my, int * params );

/* mod_dir */
extern int moddir_cd( INSTANCE * my, int * params );
extern int moddir_chdir( INSTANCE * my, int * params );
extern int moddir_mkdir( INSTANCE * my, int * params );
extern int moddir_rmdir( INSTANCE * my, int * params );
extern int moddir_rm( INSTANCE * my, int * params );
extern int moddir_glob( INSTANCE * my, int * params );
extern int moddir_open( INSTANCE * my, int * params );
extern int moddir_close( INSTANCE * my, int * params );
extern int moddir_read( INSTANCE * my, int * params );

/* mod_sort */
extern int modsort_quicksort( INSTANCE *my, int *params );
extern int modsort_ksort( INSTANCE *my, int *params );
extern int modsort_ksort_n( INSTANCE *my, int *params );
extern int modsort_sort_n( INSTANCE *my, int *params );
extern int modsort_sort( INSTANCE *my, int *params );

/* mod_mem */
extern int modmem_memory_free( INSTANCE * my, int * params );
extern int modmem_memory_total( INSTANCE * my, int * params );
extern int modmem_memcmp( INSTANCE * my, int * params );
extern int modmem_memmove( INSTANCE * my, int * params );
extern int modmem_memcopy( INSTANCE * my, int * params );
extern int modmem_memset( INSTANCE * my, int * params );
extern int modmem_memsetw( INSTANCE * my, int * params );
extern int modmem_memseti( INSTANCE * my, int * params );
extern int modmem_calloc( INSTANCE * my, int * params );
extern int modmem_alloc( INSTANCE * my, int * params );
extern int modmem_realloc( INSTANCE * my, int * params );
extern int modmem_free( INSTANCE * my, int * params );

/* mod_video */
extern int modvideo_set_mode( INSTANCE * my, int * params );
extern int modvideo_set_mode_2( INSTANCE * my, int * params );
extern int modvideo_set_mode_3( INSTANCE * my, int * params );
extern int modvideo_set_mode_4( INSTANCE * my, int * params );
extern int modvideo_set_fps( INSTANCE * my, int * params );
extern int modvideo_list_modes( INSTANCE * my, int * params );
extern int modvideo_mode_is_ok( INSTANCE * my, int * params );

/* mod_map */
extern int modmap_graphic_set( INSTANCE * my, int * params );
extern int modmap_graphic_info( INSTANCE * my, int * params );
extern int modmap_set_point( INSTANCE * my, int * params );
extern int modmap_set_center( INSTANCE * my, int * params );
extern int modmap_get_point( INSTANCE * my, int * params );
extern int modmap_load_png( INSTANCE * my, int * params );
extern int modmap_load_pcx( INSTANCE * my, int * params );
extern int modmap_save_png( INSTANCE * my, int * params );
extern int modmap_map_buffer( INSTANCE * my, int * params );
extern int modmap_map_clear( INSTANCE * my, int * params );
extern int modmap_new_map( INSTANCE * my, int * params );
extern int modmap_new_map_extend( INSTANCE * my, int * params );
extern int modmap_map_clone( INSTANCE * my, int * params );
extern int modmap_map_put( INSTANCE * my, int * params );
extern int modmap_map_xput( INSTANCE * my, int * params );
extern int modmap_map_xputnp( INSTANCE * my, int * params );
extern int modmap_map_name( INSTANCE * my, int * params );
extern int modmap_map_set_name( INSTANCE * my, int * params );
extern int modmap_map_exists( INSTANCE * my, int * params );
extern int modmap_map_block_copy( INSTANCE * my, int * params );
extern int modmap_load_map( INSTANCE * my, int * params );
extern int modmap_unload_map( INSTANCE * my, int * params );
extern int modmap_save_map( INSTANCE * my, int * params );
extern int modmap_load_pal( INSTANCE * my, int * params );
extern int modmap_save_pal( INSTANCE * my, int * params );
extern int modmap_save_system_pal( INSTANCE * my, int * params );
extern int modmap_convert_palette( INSTANCE * my, int * params );
extern int modmap_set_colors( INSTANCE * my, int * params );
extern int modmap_get_colors( INSTANCE * my, int * params );
extern int modmap_roll_palette( INSTANCE * my, int * params );
extern int modmap_find_color( INSTANCE * my, int * params );
extern int modmap_get_rgb( INSTANCE * my, int * params );
extern int modmap_get_rgba( INSTANCE * my, int * params );
extern int modmap_rgb( INSTANCE * my, int * params );
extern int modmap_rgba( INSTANCE * my, int * params );
extern int modmap_fade( INSTANCE * my, int * params );
extern int modmap_fade_on( INSTANCE * my, int * params );
extern int modmap_fade_off( INSTANCE * my, int * params );
extern int modmap_pal_create( INSTANCE * my, int * params );
extern int modmap_pal_clone( INSTANCE * my, int * params );
extern int modmap_pal_unload( INSTANCE * my, int * params );
extern int modmap_pal_refresh( INSTANCE * my, int * params );
extern int modmap_pal_refresh_2( INSTANCE * my, int * params );
extern int modmap_pal_map_assign( INSTANCE * my, int * params );
extern int modmap_pal_map_remove( INSTANCE * my, int * params );
extern int modmap_pal_map_getid( INSTANCE * my, int * params );
extern int modmap_set_system_pal( INSTANCE * my, int * params );
extern int modmap_set_system_pal_raw( INSTANCE * my, int * params );
extern int modmap_pal_set( INSTANCE * my, int * params );
extern int modmap_pal_get( INSTANCE * my, int * params );
extern int modmap_load_fpg( INSTANCE * my, int * params );
extern int modmap_save_fpg( INSTANCE * my, int * params );
extern int modmap_unload_fpg( INSTANCE * my, int * params );
extern int modmap_fpg_exists( INSTANCE * my, int * params );
extern int modmap_fpg_add( INSTANCE * my, int * params );
extern int modmap_fpg_new( INSTANCE * my, int * params );
extern int modmap_bgload_fpg( INSTANCE * my, int * params );
extern int modmap_load_fnt( INSTANCE * my, int * params );
extern int modmap_load_bdf( INSTANCE * my, int * params );
extern int modmap_unload_fnt( INSTANCE * my, int * params );
extern int modmap_fnt_new( INSTANCE * my, int * params );
extern int modmap_get_glyph( INSTANCE * my, int * params );
extern int modmap_set_glyph( INSTANCE * my, int * params );
extern int modmap_save_fnt( INSTANCE * my, int * params );

/* mod_text */
extern int modtext_write (INSTANCE * my, int * params);
extern int modtext_write_in_map (INSTANCE * my, int * params);
extern int modtext_write_var (INSTANCE * my, int * params);
extern int modtext_write_string (INSTANCE * my, int * params);
extern int modtext_write_int (INSTANCE * my, int * params);
extern int modtext_write_float (INSTANCE * my, int * params);
extern int modtext_move_text (INSTANCE * my, int * params);
extern int modtext_delete_text (INSTANCE * my, int * params);
extern int modtext_text_height (INSTANCE * my, int * params);
extern int modtext_text_width (INSTANCE * my, int * params);
extern int modtext_set_text_color (INSTANCE * my, int * params);
extern int modtext_get_text_color (INSTANCE * my, int * params);

/* mod_grproc */
extern int grproc_advance( INSTANCE * my, int * params );
extern int grproc_xadvance( INSTANCE * my, int * params );
extern int grproc_get_angle( INSTANCE * my, int * params );
extern int grproc_get_dist( INSTANCE * a, int * params );
extern int grproc_get_real_point( INSTANCE * my, int * params );
extern int grproc_collision( INSTANCE * my, int * params );

/* mod_regex */
extern int modregex_regex (INSTANCE * my, int * params);
extern int modregex_regex_replace (INSTANCE * my, int * params);
extern int modregex_split (INSTANCE * my, int * params);
extern int modregex_join (INSTANCE * my, int * params);

/* mod_draw */
extern int moddraw_drawing_map( INSTANCE * my, int * params );
extern int moddraw_drawing_at( INSTANCE * my, int * params );
extern int moddraw_drawing_stipple( INSTANCE * my, int * params );
extern int moddraw_delete_drawing( INSTANCE * my, int * params );
extern int moddraw_move_drawing( INSTANCE * my, int * params );
extern int moddraw_drawing_color( INSTANCE * my, int * params );
extern int moddraw_drawing_alpha( INSTANCE * my, int * params );
extern int moddraw_box( INSTANCE * my, int * params );
extern int moddraw_rect( INSTANCE * my, int * params );
extern int moddraw_line( INSTANCE * my, int * params );
extern int moddraw_circle( INSTANCE * my, int * params );
extern int moddraw_fcircle( INSTANCE * my, int * params );
extern int moddraw_bezier( INSTANCE * my, int * params );
extern int moddraw_get_pixel( INSTANCE * my, int * params );
extern int moddraw_put_pixel( INSTANCE * my, int * params );
extern int moddraw_map_get_pixel( INSTANCE * my, int * params );
extern int moddraw_map_put_pixel( INSTANCE * my, int * params );

/* mod_screen */
extern int modscreen_define_region( INSTANCE * my, int * params );
extern int modscreen_out_region( INSTANCE * my, int * params );
extern int modscreen_put( INSTANCE * my, int * params );
extern int modscreen_xput( INSTANCE * my, int * params );
extern int modscreen_put_screen( INSTANCE * my, int * params );
extern int modscreen_clear_screen( INSTANCE * my, int * params );
extern int modscreen_get_screen( INSTANCE * my, int * params );

/* mod_path */
extern int modpathfind_path_find( INSTANCE * my, int * params );
extern int modpathfind_path_getxy( INSTANCE * my, int * params );
extern int modpathfind_path_wall( INSTANCE * my, int * params );

/* mod_scroll */
extern int mod_scroll_start( INSTANCE * my, int * params );
extern int mod_scroll_stop( INSTANCE * my, int * params );
extern int mod_scroll_move( INSTANCE * my, int * params );

/* mod_key */
extern int modkey_key( INSTANCE * my, int * params );

/* mod_blendop */
extern int modblendop_create_blendop( INSTANCE * my, int * params );
extern int modblendop_apply( INSTANCE * my, int * params );
extern int modblendop_assign( INSTANCE * my, int * params );
extern int modblendop_free( INSTANCE * my, int * params );
extern int modblendop_identity( INSTANCE * my, int * params );
extern int modblendop_grayscale( INSTANCE * my, int * params );
extern int modblendop_translucency( INSTANCE * my, int * params );
extern int modblendop_intensity( INSTANCE * my, int * params );
extern int modblendop_swap( INSTANCE * my, int * params );
extern int modblendop_tint( INSTANCE * my, int * params );

/* mod_effects */
extern int modeffects_filter( INSTANCE *my, int *params );
extern int modeffects_blur( INSTANCE *my, int *params );
extern int modeffects_grayscale( INSTANCE *my, int *params );
extern int modeffects_rgbscale( INSTANCE *my, int *params );
#endif

#include "sysprocs.h"
#include "sysprocs_p.h"

/* ---------------------------------------------------------------------- */

HOOK * handler_hook_list = NULL ;
int handler_hook_allocated = 0 ;
int handler_hook_count = 0 ;

INSTANCE_HOOK * instance_create_hook_list = NULL ;
int instance_create_hook_allocated = 0 ;
int instance_create_hook_count = 0 ;

INSTANCE_HOOK * instance_destroy_hook_list = NULL ;
int instance_destroy_hook_allocated = 0 ;
int instance_destroy_hook_count = 0 ;

INSTANCE_HOOK * instance_pre_execute_hook_list = NULL ;
int instance_pre_execute_hook_allocated = 0 ;
int instance_pre_execute_hook_count = 0 ;

INSTANCE_HOOK * instance_pos_execute_hook_list = NULL ;
int instance_pos_execute_hook_allocated = 0 ;
int instance_pos_execute_hook_count = 0 ;

INSTANCE_HOOK * process_exec_hook_list = NULL ;
int process_exec_hook_allocated = 0 ;
int process_exec_hook_count = 0 ;

FN_HOOK * module_initialize_list = NULL ;
int module_initialize_allocated = 0 ;
int module_initialize_count = 0 ;

FN_HOOK * module_finalize_list = NULL ;
int module_finalize_allocated = 0 ;
int module_finalize_count = 0 ;

/* ---------------------------------------------------------------------- */

#define hook_add(new_hook, hook_list, hook_allocated, hook_count) \
    { \
        if ((hook_count) >= (hook_allocated)) { \
            (hook_allocated) = (hook_count) + 5; \
            (hook_list) = realloc (hook_list, (hook_allocated) * sizeof((hook_list)[0])); \
        } \
        \
        if (!(hook_list)) { \
            fprintf (stderr, "No memory for alloc hook\n"); \
            exit(-1); \
        } \
        (hook_list)[hook_count] = (new_hook); \
        (hook_count)++; \
    }

/* ---------------------------------------------------------------------- */

static SYSPROC ** sysproc_tab = NULL ;

/* ---------------------------------------------------------------------- */

static int tsize( DCB_TYPEDEF orig );
static DCB_TYPEDEF treduce( DCB_TYPEDEF orig );

/* ---------------------------------------------------------------------- */

/* Tipos de token */
static struct
{
    enum { NOTOKEN, IDENTIFIER, NUMBER } type ;
    char name[128] ;
    int  code ;
} token ;

static const char * token_ptr = NULL;

/* ---------------------------------------------------------------------- */

/* Very simple tokenizer */

static void get_token()
{
    char * ptr ;
    unsigned int n ;

    while ( isspace( *token_ptr ) ) token_ptr++ ;

    if ( !*token_ptr )
    {
        token.type = NOTOKEN ;
        return ;
    }

    /* Numbers */

    if ( ISNUM( *token_ptr ) )
    {
        int num = 0 ;

        /* Calculate the number value */

        while ( ISNUM( *token_ptr ) ) num = num * 10 + ( *token_ptr++ - '0' ) ;
        token.type = NUMBER ;
        token.code = num ;
        snprintf( token.name, sizeof( token.name ), "%d", token.code ) ;
        return ;
    }

    ptr = token.name ;
    *ptr++ = TOUPPER( *token_ptr ) ;
    if ( ISWORDCHAR( *token_ptr++ ) )
        while ( ISWORDCHAR( *token_ptr ) ) *ptr++ = TOUPPER( *token_ptr++ ) ;
    *ptr = 0 ;

    for ( n = 0; n < dcb.data.NID; n++ )
    {
        if ( strcmp( (const char *)dcb.id[n].Name, token.name ) == 0 )
        {
            token.type = IDENTIFIER ;
            token.code = dcb.id[n].Code ;
            strcpy( token.name, (char *)dcb.id[n].Name ) ;
            return ;
        }
    }

    token.type = NOTOKEN ;
}

/* ---------------------------------------------------------------------- */

static DCB_TYPEDEF treduce( DCB_TYPEDEF orig )
{
    int n ;
    for ( n = 0; n < MAX_TYPECHUNKS - 1; n++ )
    {
        orig.BaseType[n] = orig.BaseType[n+1] ;
        orig.Count[n] = orig.Count[n+1] ;
    }
    return orig ;
}

/* ---------------------------------------------------------------------- */

static int tsize( DCB_TYPEDEF orig )
{
    unsigned int n, total ;

    switch ( orig.BaseType[0] )
    {
        case TYPE_ARRAY:
            return orig.Count[0] * tsize( treduce( orig ) ) ;

        case TYPE_POINTER:
        case TYPE_STRING:
        case TYPE_DWORD:
        case TYPE_FLOAT:
        case TYPE_INT:
            return 4 ;

        case TYPE_WORD:
        case TYPE_SHORT:
            return 2 ;

        case TYPE_BYTE:
        case TYPE_SBYTE:
        case TYPE_CHAR:
            return 1 ;

        case TYPE_STRUCT:
            total = 0 ;
            for ( n = 0; n < dcb.varspace[orig.Members].NVars; n++ )
                total += tsize( dcb.varspace_vars[orig.Members][n].Type ) ;
            return total ;

        default:
            return 0 ;
    }
}

/* ---------------------------------------------------------------------- */

static void get_var_info( DLVARFIXUP * varfixup, DCB_VAR * basevar, int nvars, char * basedata )
{
    unsigned int n ;
    DCB_VAR rvar ;
    void * rdata = NULL ;

    token_ptr = varfixup->var ;

    /* for Error */
    varfixup->data_offset = NULL;
    varfixup->size = -1;
    varfixup->elements = -1;

    get_token() ;
    if ( token.type != IDENTIFIER ) return ; /* Not a valid expression */

    /* Busca variable */
    for ( n = 0; n < nvars; n++ )
    {
        if ( basevar[n].ID == token.code )
        {
            rvar  = basevar[n] ;
            rdata = ( uint8_t* )basedata + basevar[n].Offset ;

            get_token() ;
            break;
        }
    }

    if ( n == nvars ) return ; /* Error, no es variable */

    for ( ;; )
    {
        if ( token.name[0] == '.' )
        {
            DCB_VARSPACE * v ;
            DCB_VAR * var ;

            if ( rvar.Type.BaseType[0] != TYPE_STRUCT ) return ; /* not an struct */

            get_token() ;
            if ( token.type != IDENTIFIER ) return ; /* not a member */

            v = &dcb.varspace[rvar.Type.Members] ;
            var = dcb.varspace_vars[rvar.Type.Members] ;
            for ( n = 0; n < v->NVars; n++ ) if ( var[n].ID == token.code ) break ;

            if ( n == v->NVars ) return ; /* not a member */

            rvar = var[n] ;
            rdata = ((uint8_t *)rdata) + var[n].Offset ;

            get_token() ;
            continue ;
        }

        if ( token.name[0] == '[' )
        {
            int index;

            if ( rvar.Type.BaseType[0] != TYPE_ARRAY ) return ; /* not an array */

            get_token() ;
            if ( token.type != NUMBER ) return ; /* not an integer */
            index = token.code;

            if ( index < 0 ) return ; /* Index less than zero */
            if ( index >= rvar.Type.Count[0] ) return ; /* Index out of bounds */

            rvar.Type = treduce( rvar.Type ) ;
            rdata = ((uint8_t *) rdata ) + index * tsize( rvar.Type ) ;

            get_token() ;
            if ( token.name[0] == ']' ) get_token() ; /* Skip ] */

            continue ;
        }

        varfixup->data_offset = ( void * ) rdata;
        varfixup->elements = rvar.Type.BaseType[0] == TYPE_ARRAY ? rvar.Type.Count[0] : 1;
        varfixup->size = tsize( rvar.Type ) / varfixup->elements;
/*
        printf ("varfixup: %p var: %s offset: %p elements: %d size: %d\n", varfixup, varfixup->var, varfixup->data_offset, varfixup->elements, varfixup->size);
*/
        break ;
    }
}

/* ---------------------------------------------------------------------- */

int compare_priority( const HOOK * a1, const HOOK * a2 )
{
    return ( a2->prio - a1->prio ) ;
}

/* ---------------------------------------------------------------------- */

int sysproc_add( char * name, char * paramtypes, int type, void * func )
{
    static SYSPROC * sysproc_new = 0 ;
    static int sysproc_count = 0 ;

    if ( !sysproc_new )
    {
        sysproc_new = sysprocs ;
        while ( sysproc_new->name )
        {
            sysproc_new++ ;
            sysproc_count++ ;
        }
    }

    if ( sysproc_count >= MAX_SYSPROCS )
    {
        fprintf( stderr, "ERROR: Runtime error - too many system functions\n" ) ;
        return -1;
    }

    sysproc_new->code = -1 ; /* Se llena en el fixup */
    sysproc_new->name = name ;
    sysproc_new->paramtypes = paramtypes ;
    sysproc_new->params = strlen( paramtypes ) ;
    sysproc_new->type = type ;
    sysproc_new->func = ( SYSFUNC * ) func ;
    sysproc_new->id = getid( name ) ;

    sysproc_new++ ;
    sysproc_count++ ;

    sysproc_new->func = NULL ;

    return 0 /*sysproc_new->code*/ ;
}

/* ---------------------------------------------------------------------- */

SYSPROC * sysproc_get( int code )
{
    return sysproc_tab[code] ;
}

/* ---------------------------------------------------------------------- */
#ifndef __STATIC__
void sysproc_add_tab( DLSYSFUNCS * functions_exports )
{
    if ( functions_exports )
    {
        while ( functions_exports->name )
        {
            sysproc_add( functions_exports->name, functions_exports->paramtypes, functions_exports->type, functions_exports->func );
            functions_exports++;
        }
    }
}
#endif
/* ---------------------------------------------------------------------- */

void sysproc_init()
{
    SYSPROC       * proc = sysprocs ;
    int             maxcode = 0 ;
    DLVARFIXUP    * globals_fixup = NULL ;
    DLVARFIXUP    * locals_fixup = NULL ;
    HOOK          * handler_hooks = NULL ;
    INSTANCE_HOOK   instance_create_hook ;
    INSTANCE_HOOK   instance_destroy_hook ;
    INSTANCE_HOOK   process_exec_hook ;

#ifndef __STATIC__
    DLSYSFUNCS    * functions_exports = NULL ;
    FN_HOOK         module_initialize ;
    FN_HOOK         module_finalize ;
    INSTANCE_HOOK   instance_pre_execute_hook ;
    INSTANCE_HOOK   instance_pos_execute_hook ;

    char soname[__MAX_PATH] ;

#if defined( WIN32 )
#define DLLEXT      ".dll"
#define SIZEDLLEXT  4
#elif defined(TARGET_MAC)
#define DLLEXT      ".dylib"
#define SIZEDLLEXT  6
#else
#define DLLEXT      ".so"
#define SIZEDLLEXT  3
#endif

    for ( n = 0; n < dcb.data.NImports; n++ )
    {
        filename = string_get( dcb.imports[n] ) ;

        snprintf( soname, __MAX_PATH, "%s" DLLEXT, filename );

        filename = soname ;

        if ( debug ) printf ("Loading... %s\n", filename );

        /* Load library */
        library  = dlibopen( filename ) ;
        if ( !library )
        {
            printf( dliberror() ) ;
            exit( 0 );
        }

        globals_fixup     = ( DLVARFIXUP * ) _dlibaddr( library, "globals_fixup" ) ;
        locals_fixup      = ( DLVARFIXUP * ) _dlibaddr( library, "locals_fixup" ) ;
        functions_exports = ( DLSYSFUNCS * ) _dlibaddr( library, "functions_exports" ) ;

        module_initialize = ( FN_HOOK ) _dlibaddr( library, "module_initialize" ) ;
        module_finalize   = ( FN_HOOK ) _dlibaddr( library, "module_finalize" ) ;

        instance_create_hook       = ( INSTANCE_HOOK ) _dlibaddr( library, "instance_create_hook" ) ;
        instance_destroy_hook      = ( INSTANCE_HOOK ) _dlibaddr( library, "instance_destroy_hook" ) ;
        instance_pre_execute_hook  = ( INSTANCE_HOOK ) _dlibaddr( library, "instance_pre_execute_hook" ) ;
        instance_pos_execute_hook  = ( INSTANCE_HOOK ) _dlibaddr( library, "instance_pos_execute_hook" ) ;
        process_exec_hook          = ( INSTANCE_HOOK ) _dlibaddr( library, "process_exec_hook" ) ;

        handler_hooks = ( HOOK * ) _dlibaddr( library, "handler_hooks" ) ;

        /* Fixups */

        if ( globals_fixup )
        {
            while ( globals_fixup->var )
            {
                get_var_info( globals_fixup, dcb.glovar, dcb.data.NGloVars, globaldata );
                globals_fixup++;
            }
        }

        if ( locals_fixup )
        {
            while ( locals_fixup->var )
            {
                get_var_info( locals_fixup, dcb.locvar, dcb.data.NLocVars, NULL );
                locals_fixup++;
            }
        }

        sysproc_add_tab( functions_exports ) ;

        if ( module_initialize )
            hook_add( module_initialize, module_initialize_list, module_initialize_allocated, module_initialize_count ) ;

        if ( module_finalize )
            hook_add( module_finalize, module_finalize_list, module_finalize_allocated, module_finalize_count ) ;

        if ( instance_create_hook )
            hook_add( instance_create_hook, instance_create_hook_list, instance_create_hook_allocated, instance_create_hook_count ) ;

        if ( instance_destroy_hook )
            hook_add( instance_destroy_hook, instance_destroy_hook_list, instance_destroy_hook_allocated, instance_destroy_hook_count ) ;

        if ( instance_pre_execute_hook )
            hook_add( instance_pre_execute_hook, instance_pre_execute_hook_list, instance_pre_execute_hook_allocated, instance_pre_execute_hook_count ) ;

        if ( instance_pos_execute_hook )
            hook_add( instance_pos_execute_hook, instance_pos_execute_hook_list, instance_pos_execute_hook_allocated, instance_pos_execute_hook_count ) ;

        if ( process_exec_hook )
            hook_add( process_exec_hook, process_exec_hook_list, process_exec_hook_allocated, process_exec_hook_count ) ;

        while ( handler_hooks && handler_hooks->hook )
        {
            hook_add( *handler_hooks, handler_hook_list, handler_hook_allocated, handler_hook_count ) ;
            handler_hooks++;
        }
    }

    if ( debug ) printf ("\n");
#endif
    /* System Procs FixUp */

    sysprocs_fixup();

    proc = sysprocs ;
    while ( proc->func )
    {
        if ( maxcode < proc->code ) maxcode = proc->code ;
        proc++ ;
    }

    sysproc_tab = calloc( maxcode + 1 , sizeof( SYSPROC * ) );

    proc = sysprocs ;
    while ( proc->func )
    {
        if ( proc->code > -1 ) sysproc_tab[proc->code] = proc ;
        proc++ ;
    }

    /* Sort handler_hooks */
    if ( handler_hook_list )
        qsort( handler_hook_list, handler_hook_count, sizeof( handler_hook_list[0] ), ( int ( * )( const void *, const void * ) ) compare_priority ) ;
#ifndef __STATIC__
    /* Initialize all modules */
    if ( module_initialize_count )
        for ( n = 0; n < module_initialize_count; n++ )
            module_initialize_list[n]();
#else
    /* Initialize all the modules, hooks, globals, locals... */

    /* mod_time */
    if ( !SDL_WasInit( SDL_INIT_TIMER ) ) SDL_InitSubSystem( SDL_INIT_TIMER );

    /* mod_sound */
    if ( !SDL_WasInit( SDL_INIT_AUDIO ) ) SDL_InitSubSystem( SDL_INIT_AUDIO );
    // Assign the var values defined in the module globals_fixup structure
    globals_fixup = mod_sound_globals_fixup;
    while ( globals_fixup->var ) {
            get_var_info( globals_fixup, dcb.glovar, dcb.data.NGloVars, globaldata );
            globals_fixup++;
    }

    /* libsdlhandler */
    if ( !SDL_WasInit( SDL_INIT_EVENTTHREAD ) )
        SDL_InitSubSystem( SDL_INIT_EVENTTHREAD );
        /* Register the hook that'll be run every FRAME */
        handler_hooks = libsdlhandler_hook;
        while ( handler_hooks && handler_hooks->hook )
        {
            hook_add( *handler_hooks, handler_hook_list, handler_hook_allocated, handler_hook_count ) ;
            handler_hooks++;
        }

    /* libjoy */
    libjoy_init();

    /* mod_timers */
    globals_fixup = mod_timers_globals_fixup;
    while ( globals_fixup->var ) {
            get_var_info( globals_fixup, dcb.glovar, dcb.data.NGloVars, globaldata );
            globals_fixup++;
    }
    handler_hooks = mod_timers_hooks;
    while ( handler_hooks && handler_hooks->hook )
    {
        hook_add( *handler_hooks, handler_hook_list, handler_hook_allocated,
                   handler_hook_count ) ;
        handler_hooks++;
    }

    /* mod_proc */
    locals_fixup = mod_proc_locals_fixup;
    while ( locals_fixup->var ) {
                get_var_info( locals_fixup, dcb.locvar, dcb.data.NLocVars, NULL );
                locals_fixup++;
    }

    /* libvideo */
    libvideo_init();

    /* libgrbase */
    libgrbase_init();
    globals_fixup = libgrbase_globals_fixup;
    while ( globals_fixup->var ) {
            get_var_info( globals_fixup, dcb.glovar, dcb.data.NGloVars, globaldata );
            globals_fixup++;
    }

    /* librender */
    librender_init();
    handler_hooks = librender_hooks;
    while ( handler_hooks && handler_hooks->hook )
    {
        hook_add( *handler_hooks, handler_hook_list, handler_hook_allocated,
                   handler_hook_count ) ;
        handler_hooks++;
    }
    instance_create_hook = (INSTANCE_HOOK) librender_instance_create_hook;
    hook_add( instance_create_hook, instance_create_hook_list, instance_create_hook_allocated, instance_create_hook_count ) ;
    instance_destroy_hook = (INSTANCE_HOOK) librender_instance_destroy_hook;
    hook_add( instance_destroy_hook, instance_destroy_hook_list, instance_destroy_hook_allocated, instance_destroy_hook_count ) ;

    /* libfont */
    libfont_init();

    /* libmouse */
    libmouse_init();    
    handler_hooks = libmouse_hook;
    while ( handler_hooks && handler_hooks->hook )
    {
        hook_add( *handler_hooks, handler_hook_list, handler_hook_allocated,
                   handler_hook_count ) ;
        handler_hooks++;
    }
    
    /* mod_grproc */
    grproc_init();
    process_exec_hook = grproc_instance_hook;
    hook_add( process_exec_hook, process_exec_hook_list,
        process_exec_hook_allocated, process_exec_hook_count ) ;
    locals_fixup = mod_grproc_locals_fixup;
    while ( locals_fixup->var ) {
        get_var_info( locals_fixup, dcb.locvar, dcb.data.NLocVars, NULL );
        locals_fixup++;
    }
    globals_fixup = mod_grproc_globals_fixup;
    while ( globals_fixup->var )
    {
        get_var_info( globals_fixup, dcb.glovar, dcb.data.NGloVars, globaldata );
        globals_fixup++;
    }

    /* libkey */
    libkey_initialize();
    handler_hooks = libkey_hooks;
    while ( handler_hooks && handler_hooks->hook )
    {
        hook_add( *handler_hooks, handler_hook_list, handler_hook_allocated,
                   handler_hook_count ) ;
        handler_hooks++;
    }

#endif
}

/* ---------------------------------------------------------------------- */

extern DCB_SYSPROC_CODE2 * sysproc_code_ref ;

/* ---------------------------------------------------------------------- */

char * sysproc_name( int code )
{
    DCB_SYSPROC_CODE2 * s = NULL ;
    int n;

    s = sysproc_code_ref ;
    for ( n = 0; n < dcb.data.NSysProcsCodes; n++, s++ )
        if ( s->Code == code ) return getid_name( s->Id ) ;

    return NULL ;
}

/* ---------------------------------------------------------------------- */
