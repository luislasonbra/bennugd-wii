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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef TARGET_BEOS
#include <posix/assert.h>
#else
#include <assert.h>
#endif

#include <stdint.h>

#include "files.h"

#define MAX_POSSIBLE_PATHS  32

char * possible_paths[MAX_POSSIBLE_PATHS] = { "", 0 } ;

int opened_files = 0;

typedef struct
{
    char * name ;
    int  offset ;
    int  size ;
    FILE * fp ;
}
XFILE ;

XFILE * x_file = NULL ;
int max_x_files = 0;

int x_files_count = 0 ;

/* Add new file to PATH */

void xfile_init( int maxfiles )
{
    x_file = ( XFILE * ) calloc( sizeof( XFILE ), maxfiles );
    max_x_files = maxfiles;
}

void file_add_xfile( file * fp, long offset, char * name, int size )
{
    char * ptr ;
    assert( x_files_count < max_x_files ) ;
    assert( fp->type == F_FILE ) ;

    x_file[x_files_count].fp = fp->fp ;
    x_file[x_files_count].offset = offset ;
    x_file[x_files_count].size = size ;
    x_file[x_files_count].name = strdup( name ) ;

    ptr = x_file[x_files_count].name;
    while ( *ptr )
    {
        if ( *ptr == '\\' ) *ptr = '/'; /* Unix style */
        ptr++;
    }

    x_files_count++ ;
}

/* Read a datablock from file */

int file_read( file * fp, void * buffer, int len )
{
    assert( len != 0 );

    if ( fp->type == F_XFILE )
    {
        XFILE * xf ;
        int result ;

        xf = &x_file[fp->n] ;

        if (( len + fp->pos ) > ( xf->offset + xf->size ) )
        {
            fp->eof = 1 ;
            len = xf->size + xf->offset - fp->pos ;
        }

        fseek( xf->fp, fp->pos, SEEK_SET ) ;
        result = fread( buffer, 1, len, xf->fp ) ;

        fp->pos = ftell( xf->fp ) ;
        return result ;
    }

    if ( fp->type == F_GZFILE )
    {
        int result = gzread( fp->gz, buffer, len ) ;
        fp->error = ( result < len );
        if ( result < 0 ) result = 0;
        return result ;
    }

    return fread( buffer, 1, len, fp->fp ) ;
}

/* Save a unquoted string to a file */

int file_qputs( file * fp, char * buffer )
{
    char dest[1024], * optr ;
    const char * ptr ;

    ptr = buffer ;
    optr = dest ;
    while ( *ptr )
    {
        if ( optr > dest + 1000 )
        {
            *optr++ = '\\' ;
            *optr++ = '\n' ;
            *optr   = 0 ;
            file_write( fp, dest, optr - dest ) ;
            optr = dest ;
        }
        if ( *ptr == '\n' )
        {
            *optr++ = '\\' ;
            *optr++ = 'n' ;
            ptr++ ;
            continue ;
        }
        if ( *ptr == '\\' )
        {
            *optr++ = '\\' ;
            *optr++ = *ptr++ ;
            continue ;
        }
        *optr++ = *ptr++ ;
    }
    *optr++ = '\n' ;
    return file_write( fp, dest, optr - dest ) ;
}

/* Load a string from a file and unquoted it */

int file_qgets( file * fp, char * buffer, int len )
{
    char * ptr, * result = NULL ;

    if ( fp->type == F_XFILE )
    {
        XFILE * xf ;
        int l = 0;
        char * ptr = result = buffer ;

        xf = &x_file[fp->n] ;

        fseek( xf->fp, fp->pos, SEEK_SET ) ;
        while ( l < len )
        {
            if ( fp->pos >= xf->offset + xf->size )
            {
                fp->eof = 1 ;
                break ;
            }
            fread( ptr, 1, 1, xf->fp ) ;
            l++ ;
            fp->pos++ ;
            if ( *ptr++ == '\n' )
                break ;
        }
        *ptr = 0 ;
        fp->pos = ftell( xf->fp ) ;

        if ( l == 0 ) return 0 ;

    }
    else if ( fp->type == F_GZFILE )
    {
        result = gzgets( fp->gz, buffer, len ) ;
    }
    else
    {
        result = fgets( buffer, len, fp->fp );
    }

    if ( result == NULL )
    {
        buffer[0] = 0 ; return 0 ;
    }

    ptr = buffer ;
    while ( *ptr )
    {
        if ( *ptr == '\\' )
        {
            if ( ptr[1] == 'n' ) ptr[1] = '\n' ;
            strcpy( ptr, ptr + 1 ) ;
            ptr++ ;
            continue ;
        }
        if ( *ptr == '\n' )
        {
            *ptr = 0 ;
            break ;
        }
        ptr++ ;
    }
    return strlen( buffer ) ;
}

/* Save a string to file */

int file_puts( file * fp, char * buffer )
{
    return file_write( fp, buffer, strlen( buffer ) ) ;
}

/* Load a string from a file and unquoted it */

int file_gets( file * fp, char * buffer, int len )
{
    char * result = NULL ;

    if ( fp->type == F_XFILE )
    {
        XFILE * xf ;
        int l = 0;
        char * ptr = result = buffer ;

        xf = &x_file[fp->n] ;

        fseek( xf->fp, fp->pos, SEEK_SET ) ;
        while ( l < len )
        {
            if ( fp->pos >= xf->offset + xf->size )
            {
                fp->eof = 1 ;
                break ;
            }
            fread( ptr, 1, 1, xf->fp ) ;
            l++ ;
            fp->pos++ ;
            if ( *ptr++ == '\n' ) break ;
        }
        *ptr = 0 ;
        fp->pos = ftell( xf->fp ) ;

        if ( l == 0 ) return 0 ;
    }
    else if ( fp->type == F_GZFILE )
    {
        result = gzgets( fp->gz, buffer, len ) ;
    }
    else
    {
        result = fgets( buffer, len, fp->fp );
    }

    if ( result == NULL )
    {
        buffer[0] = 0 ;
        return 0 ;
    }

    return strlen( buffer ) ;
}

/* Save an int data to a binary file */

int file_writeSint8( file * fp, int8_t * buffer )
{
    return file_write( fp, buffer, sizeof( uint8_t ) );
}

int file_writeUint8( file * fp, uint8_t * buffer )
{
    return file_write( fp, buffer, sizeof( uint8_t ) );
}

int file_writeSint16( file * fp, int16_t * buffer )
{
#if __BYTEORDER == __LIL_ENDIAN
    return file_write( fp, buffer, sizeof( int16_t ) );
#else
    file_write( fp, ( uint8_t * )buffer + 1, 1 );
    return file_write( fp, ( uint8_t * )buffer, 1 );
#endif
}

int file_writeUint16( file * fp, uint16_t * buffer )
{
    return file_writeSint16( fp, ( int16_t * ) buffer );
}

int file_writeSint32( file * fp, int32_t * buffer )
{
#if __BYTEORDER == __LIL_ENDIAN
    return file_write( fp, buffer, sizeof( int32_t ) );
#else
    file_write( fp, ( uint8_t * )buffer + 3, 1 );
    file_write( fp, ( uint8_t * )buffer + 2, 1 );
    file_write( fp, ( uint8_t * )buffer + 1, 1 );
    return file_write( fp, ( uint8_t * )buffer, 1 );
#endif
}

int file_writeUint32( file * fp, uint32_t * buffer )
{
    return file_writeSint32( fp, ( int32_t * )buffer );
}

/* Save an array to a binary file */

int file_writeSint8A( file * fp, int8_t * buffer, int n )
{
    return file_write( fp, buffer, n );
}

int file_writeUint8A( file * fp, uint8_t * buffer, int n )
{
    return file_write( fp, buffer, n );
}

int file_writeSint16A( file * fp, int16_t * buffer, int n )
{
#if __BYTEORDER == __LIL_ENDIAN
    return file_write( fp, buffer, n << 1 ) >> 1 ;
#else
    int i;
    for ( i = 0; i < n; i++ )
        if ( !file_writeSint16( fp, ( int16_t * )buffer++ ) ) break;
    return i;
#endif
}

int file_writeUint16A( file * fp, uint16_t * buffer, int n )
{
    return file_writeSint16A( fp, ( int16_t * )buffer, n );
}

int file_writeSint32A( file * fp, int32_t * buffer, int n )
{
#if __BYTEORDER == __LIL_ENDIAN
    return file_write( fp, buffer, n << 2 ) >> 2;
#else
    int i;
    for ( i = 0; i < n; i++ )
        if ( !file_writeSint32( fp, ( int32_t * )buffer++ ) ) break;
    return i;
#endif
}

int file_writeUint32A( file * fp, uint32_t * buffer, int n )
{
    return file_writeSint32A( fp, ( int32_t * )buffer, n );
}

/* Read an int data from a binary file */

int file_readSint8( file * fp, int8_t * buffer )
{
    return file_read( fp, buffer, sizeof( int8_t ) );
}

int file_readUint8( file * fp, uint8_t * buffer )
{
    return file_read( fp, buffer, sizeof( int8_t ) );
}

int file_readSint16( file * fp, int16_t * buffer )
{
#if __BYTEORDER == __LIL_ENDIAN
    return file_read( fp, buffer, sizeof( int16_t ) );
#else
    file_read( fp, ( uint8_t * )buffer + 1, 1 );
    return file_read( fp, ( uint8_t * )buffer, 1 );
#endif
}

int file_readUint16( file * fp, uint16_t * buffer )
{
    return file_readSint16( fp, (int16_t *)buffer );
}

int file_readSint32( file * fp, int32_t * buffer )
{
#if __BYTEORDER == __LIL_ENDIAN
    return file_read( fp, buffer, sizeof( int32_t ) );
#else
    file_read( fp, ( uint8_t * )buffer + 3, 1 );
    file_read( fp, ( uint8_t * )buffer + 2, 1 );
    file_read( fp, ( uint8_t * )buffer + 1, 1 );
    return file_read( fp, ( uint8_t * )buffer, 1 );
#endif
}

int file_readUint32( file * fp, uint32_t * buffer )
{
    return file_readSint32( fp, ( int32_t * )buffer );
}

/* Read an array from a binary file */

int file_readSint8A( file * fp, int8_t * buffer, int n )
{
    return file_read( fp, buffer, n );
}

int file_readUint8A( file * fp, uint8_t * buffer, int n )
{
    return file_read( fp, buffer, n );
}

int file_readSint16A( file * fp, int16_t * buffer, int n )
{
#if __BYTEORDER == __LIL_ENDIAN
    return file_read( fp, buffer, n << 1 ) >> 1;
#else
    int i;
    for ( i = 0; i < n; i++ )
        if ( !file_readSint16( fp, ( int16_t * )buffer++ ) ) break;
    return i;
#endif
}

int file_readUint16A( file * fp, uint16_t * buffer, int n )
{
    return file_readSint16A( fp, ( int16_t * )buffer, n );
}

int file_readSint32A( file * fp, int32_t * buffer, int n )
{
#if __BYTEORDER == __LIL_ENDIAN
    return file_read( fp, buffer, n << 2 ) >> 2;
#else
    int i;
    for ( i = 0; i < n; i++ )
        if ( !file_readSint32( fp, ( int32_t * )buffer++ ) ) break;
    return i;
#endif
}

int file_readUint32A( file * fp, uint32_t * buffer, int n )
{
    return file_readSint32A( fp, ( int32_t * )buffer, n );
}


/* Write a datablock to a file */

int file_write( file * fp, void * buffer, int len )
{
    if ( fp->type == F_XFILE )
    {
        XFILE * xf ;
        int result ;

        xf = &x_file[fp->n] ;

        if (( len + fp->pos ) > ( xf->offset + xf->size ) )
        {
            fp->eof = 1 ;
            len = xf->size + xf->offset - fp->pos ;
        }
        fseek( xf->fp, fp->pos, SEEK_SET ) ;
        result = fwrite( buffer, 1, len, xf->fp ) ;
        fp->pos = ftell( xf->fp ) ;
        return result ;
    }

    if ( fp->type == F_GZFILE )
    {
        int result = gzwrite( fp->gz, buffer, len ) ;
        if (( fp->error = ( result < 0 ) ) != 0 ) result = 0 ;
        return ( result < len ) ? 0 : len ;
    }

    return fwrite( buffer, 1, len, fp->fp ) ;
}

/* Return file size */

int file_size( file * fp )
{
    long pos, size ;

    if ( fp->type == F_XFILE ) return x_file[fp->n].size ;

    pos = file_pos( fp );
    if ( fp->type == F_GZFILE )
    {
        char buffer[8192];
        size = pos;
        while ( !file_eof( fp ) ) size += file_read( fp, buffer, sizeof(buffer) );
    }
    else
    {
        file_seek(fp, 0, SEEK_END ) ;
        size = file_pos( fp ) ;
    }
    file_seek(fp, pos, SEEK_SET ) ;

    return size ;
}

/* Get current file pointer position */

int file_pos( file * fp )
{
    if ( fp->type == F_XFILE )
        return fp->pos - x_file[fp->n].offset ;

    if ( fp->type == F_GZFILE )
        return gztell( fp->gz ) ;

    return ftell( fp->fp ) ;
}

/* Set current file pointer position */

int file_seek( file * fp, int pos, int where )
{
    assert( fp );
    if ( fp->type == F_XFILE )
    {
        if ( where == SEEK_END )
            pos = x_file[fp->n].size - pos + 1 ;
        else if ( where == SEEK_CUR )
            pos += ( fp->pos - x_file[fp->n].offset );

        if ( x_file[fp->n].size < pos ) pos = x_file[fp->n].size ;

        if ( pos < 0 ) pos = 0 ;

        fp->pos = pos + x_file[fp->n].offset ;
        return pos ;
    }

    if ( fp->type == F_GZFILE )
    {
        assert( fp->gz );
        return gzseek( fp->gz, pos, where ) ;
    }

    assert( fp->fp );
    return fseek( fp->fp, pos, where ) ;
}

void file_rewind( file * fp )
{
    fp->error = 0;

    switch ( fp->type )
    {
        case F_XFILE:
            fp->pos = x_file[fp->n].offset ;
            break;

        case F_GZFILE:
            gzrewind( fp->gz ) ;
            break;

        default:
            rewind( fp->fp ) ;
    }
}

/* Open file */

static int open_raw( file * f, const char * filename, const char * mode )
{
    char    _mode[5];
    char    *p;

    if ( !strchr( mode, '0' ) )
    {
        f->type = F_GZFILE ;
        f->gz = gzopen( filename, mode ) ;
        f->eof  = 0 ;
        if ( f->gz ) return 1 ;
    }

    p = _mode;
    while ( *mode )
    {
        if ( *mode != '0' )
        {
            *p = *mode;
            p++;
        }
        mode++;
    }
    *p = '\0';

    f->eof  = 0 ;
    f->type = F_FILE ;
    f->fp = fopen( filename, _mode ) ;
    if ( f->fp ) return 1 ;
    return 0 ;
}

file * file_open( const char * filename, char * mode )
{
    char work [__MAX_PATH];
    char here [__MAX_PATH];

    char * name = NULL ;
    char * p, c ;
    int i;

    file * f ;

    f = ( file * ) calloc( 1, sizeof( file ) ) ;
    assert( f ) ;

    p = f->name;
    while ( *filename )
    {
        *p++ = *filename++;
        if ( p[-1] == '\\' ) p[-1] = '/'; /* Unix style */
    }
    p[0] = '\0';

    filename = f->name;

    if ( open_raw( f, filename, mode ) )
    {
        opened_files++;
        return f ;
    }

    /* if real file don't exists in disk */
    if (  strchr( mode, 'r' ) &&  strchr( mode, 'b' ) &&  /* Only read-only files */
         !strchr( mode, '+' ) && !strchr( mode, 'w' ) )
    {
        for ( i = 0 ; i < x_files_count ; i++ )
        {
            if ( strcmp( filename, x_file[i].name ) == 0 )
            {
                f->eof  = 0 ;
                f->pos  = x_file[i].offset ;
                f->type = F_XFILE ;
                f->n = i ;
                opened_files++;
                return f ;
            }
        }
    }

    p = name = work;
    while (( c = *filename ) )
    {
        if ( c == '\\' || c == '/' )
        {
            c = 0;
            name = p + 1;
        }
        *p++ = c;
        filename++;
    }
    *p = '\0';

    /* Use file extension for search in a directory named as it (for example: FPG dir for .FPG files) */
    if ( strchr( name, '.' ) )
    {
        strcpy( here, strrchr( name, '.' ) + 1 ) ;
        strcat( here, PATH_SEP ) ;
        strcat( here, name ) ;
        if ( open_raw( f, here, mode ) )
        {
            opened_files++;
            return f ;
        }
    }

    for ( i = 0 ; possible_paths[i] ; i++ )
    {
        strcpy( here, possible_paths[i] ) ;
        strcat( here, name ) ;
        if ( open_raw( f, here, mode ) )
        {
            opened_files++;
            return f ;
        }
    }

    free( f ) ;
    return 0 ;
}

/* Close file */

void file_close( file * fp )
{
    if ( fp == NULL ) return;
    if ( fp->type == F_FILE ) fclose( fp->fp ) ;
    if ( fp->type == F_GZFILE ) gzclose( fp->gz ) ;
    opened_files--;
    free( fp ) ;
}

/* Add a new dir to PATH */

void file_addp( const char * path )
{
    char truepath[__MAX_PATH];
    int n ;

    strcpy( truepath, path ) ;

    for ( n = 0 ; truepath[n] ; n++ ) if ( truepath[n] == '\\' ) truepath[n] = '/' ;
    if ( truepath[strlen( truepath )-1] != '/' ) strcat( truepath, "/" ) ;

    for ( n = 0 ; n < MAX_POSSIBLE_PATHS - 1 && possible_paths[n] ; n++ ) ;

    possible_paths[n] = strdup( truepath ) ;
    possible_paths[n+1] = 0 ;
}

/* --- */

int file_remove( const char * filename )
{
    return ( remove( filename ) );
}

/* --- */

int file_move( const char * source_file, const char * target_file )
{
#ifndef TARGET_WII
    return ( rename( source_file, target_file ) );
#else
    return -1;      /* Wii's filesystem usage is very limited... */
#endif
}

/* Check for file exists */

int file_exists( const char * filename )
{
    file * fp ;

    fp = file_open( filename, "rb" ) ;
    if ( fp )
    {
        file_close( fp ) ;
        return 1 ;
    }
    return 0 ;
}

/* Check for file end is reached */

int file_eof( file * fp )
{
    if ( fp->type == F_XFILE )
    {
        return fp->eof ? 1 : 0;
    }

    if ( fp->type == F_GZFILE )
    {
        if ( fp->error ) return 1 ;
        return gzeof( fp->gz ) ? 1 : 0;
    }

    return feof( fp->fp ) ? 1 : 0;
}

/* Get the FILE * of the file */

FILE * file_fp( file * f )
{
    if ( f->type == F_XFILE )
    {
        XFILE * xf = &x_file[f->n] ;
        fseek( xf->fp, f->pos, SEEK_SET ) ;
        return xf->fp ;
    }

    return f->fp ;
}
