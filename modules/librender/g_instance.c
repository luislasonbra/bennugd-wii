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

/* --------------------------------------------------------------------------- */

#ifdef __GNUC__
#define _inline inline
#endif

/* --------------------------------------------------------------------------- */

#define __LIB_RENDER
#include "librender.h"
#include "resolution.h"
#include "offsets.h"
#include "sysprocs_st.h"

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : instance_graph
 *
 *  Returns the instance graphic or NULL if there is none
 *
 *  PARAMS :
 *      i           Pointer to the instance
 *
 *  RETURN VALUE :
 *      Pointer to the graphic or NULL if none
 */

GRAPH * instance_graph( INSTANCE * i )
{
    int * xgraph, c, a ;

    if (( xgraph = ( int * ) LOCDWORD( i, XGRAPH ) ) ) // Get offset of XGRAPH table
    {
        c = *xgraph++;  // Get number of graphs ids in XGRAPH table
        if ( c )
        {
            // Normalize ANGLE
            a = LOCINT32( i, ANGLE ) % 360000 ;
            if ( a < 0 ) a += 360000 ;

            // Get graph id in XGRAPH table to draw
            c = xgraph[a * c / 360000] ;

            // If graph id value is negative, then graphic must be mirrored
            if ( c < 0 )
            {
                c = -c;
                LOCDWORD( i, XGRAPH_FLAGS ) = B_HMIRROR;
            }
            else
            {
                LOCDWORD( i, XGRAPH_FLAGS ) = 0;
            }

            // Get GRAPH * to draw
            return bitmap_get( LOCDWORD( i, FILEID ), c ) ;
        }
    }

    // Get GRAPH * to draw
    if (( c = LOCDWORD( i, GRAPHID ) ) )
    {
        return bitmap_get( LOCDWORD( i, FILEID ), c ) ;
    }

    return 0 ; // No graph to draw
}

void instance_get_bbox( INSTANCE * i, GRAPH * gr, REGION * dest )
{
    REGION *region;
    int x, y, r ;
    int scalex, scaley ;

    r = LOCINT32( i, REGIONID ) ;
    if ( r > 0 && r < 32 )
        region = &regions[ r ] ;
    else
        region = &regions[ 0 ];

    x = LOCINT32( i, COORDX ) ;
    y = LOCINT32( i, COORDY ) ;

    RESOLXY( librender, i, x, y );

    scalex = LOCINT32( i, GRAPHSIZEX );
    scaley = LOCINT32( i, GRAPHSIZEY );

    if ( scalex == 100 && scaley == 100 ) scalex = scaley = LOCINT32( i, GRAPHSIZE );

    gr_get_bbox( dest,
            region,
            x,
            y,
            LOCDWORD( i, FLAGS ) ^ LOCDWORD( i, XGRAPH_FLAGS ),
            LOCDWORD( i, XGRAPH ) ? 0 : LOCINT32( i, ANGLE ),
            scalex,
            scaley,
            gr
               ) ;
}

/* ---------------------------------------------------------------------- */

void draw_instance_at( INSTANCE * i, REGION * region, int x, int y )
{
    GRAPH * map ;
    int16_t * blend_table = NULL ;
    int flags ;
    int scalex, scaley ;
    int alpha ;
    int blendop;
    PALETTE * palette = NULL;
    int paletteid;

    map = instance_graph( i ) ;
    if ( !map ) return ;

    flags = ( LOCDWORD( i, FLAGS ) ^ LOCDWORD( i, XGRAPH_FLAGS ) );

    if (( alpha = LOCDWORD( i, ALPHA ) ) != 255 )
    {
        if ( alpha <= 0 ) return ;
        else if ( alpha < 255 )
            flags |= B_ALPHA | ( alpha << B_ALPHA_SHIFT );
    }

    scalex = LOCINT32( i, GRAPHSIZEX );
    scaley = LOCINT32( i, GRAPHSIZEY );
    if ( scalex == 100 && scaley == 100 ) scalex = scaley = LOCINT32( i, GRAPHSIZE );

    if (( blendop = LOCDWORD( i, BLENDOP ) ) )
    {
        blend_table = map->blend_table;
        map->blend_table = ( int16_t * ) blendop;
    }

    if (( paletteid = LOCDWORD( i, PALETTEID ) ) )
    {
        palette = map->format->palette ;
        map->format->palette = ( PALETTE * ) paletteid;
    }

    /* XGRAPH does not rotate destination graphic.
       WARNING: don't remove "scalex != 100 || scaley != 100 ||" from begin the next condition */
    if ( scalex != 100 || scaley != 100 || ( LOCINT32( i, ANGLE ) && !LOCDWORD( i, XGRAPH ) ) )
    {
        gr_rotated_blit( 0, region, x, y, flags, LOCDWORD( i, XGRAPH ) ? 0 : LOCINT32( i, ANGLE ), scalex, scaley, map ) ;
    }
    else
    {
        gr_blit( 0, region, x, y, flags, map ) ;
    }

    if ( paletteid ) map->format->palette = palette;
    if ( blendop ) map->blend_table = blend_table;

}

/* --------------------------------------------------------------------------- */
/* Rutinas gráficas de alto nivel */

void draw_instance( INSTANCE * i, REGION * clip )
{
    GRAPH * map ;
    int16_t * blend_table = NULL ;
    int flags;
    int scalex, scaley;
    REGION region;
    int alpha ;
    int blendop = 0 ;
    PALETTE * palette = NULL ;
    int paletteid;

    /* Difference with draw_instance_at from here */
    int x, y, r ;
    /* Difference with draw_instance_at to here */

//    map = instance_graph( i ) ;
    map = ( GRAPH * ) LOCDWORD( i, GRAPHPTR );
    if ( !map ) return ;

    flags = ( LOCDWORD( i, FLAGS ) ^ LOCDWORD( i, XGRAPH_FLAGS ) );

    if (( alpha = LOCDWORD( i, ALPHA ) ) != 255 )
    {
        if ( alpha <= 0 ) return ;
        else if ( alpha < 255 )
            flags |= B_ALPHA | ( alpha << B_ALPHA_SHIFT );
    }

    if (( alpha = LOCDWORD( i, ALPHA ) ) != 255 )
    {
        if ( alpha <= 0 ) return ;
        else if ( alpha < 255 )
            flags |= B_ALPHA | ( alpha << B_ALPHA_SHIFT );
    }

    scalex = LOCINT32( i, GRAPHSIZEX );
    scaley = LOCINT32( i, GRAPHSIZEY );
    if ( scalex == 100 && scaley == 100 ) scalex = scaley = LOCINT32( i, GRAPHSIZE );

    if (( blendop = LOCDWORD( i, BLENDOP ) ) )
    {
        blend_table = map->blend_table;
        map->blend_table = ( int16_t * ) blendop;
    }

    if (( paletteid = LOCDWORD( i, PALETTEID ) ) )
    {
        palette = map->format->palette ;
        map->format->palette = ( PALETTE * ) paletteid;
    }

    /* Difference with draw_instance_at from here */

    x = LOCINT32( i, COORDX ) ;
    y = LOCINT32( i, COORDY ) ;

    RESOLXY( librender, i, x, y );

    r = LOCINT32( i, REGIONID ) ;
    if ( r > 0 && r < 32 )
        region = regions[ r ] ;
    else
        region = regions[ 0 ];

    if ( clip ) region_union( &region, clip );
    /* Difference with draw_instance_at to here */

    /* XGRAPH does not rotate destination graphic.
       WARNING: don't remove "scalex != 100 || scaley != 100 ||" from begin the next condition */
    if ( scalex != 100 || scaley != 100 || ( LOCINT32( i, ANGLE ) && !LOCDWORD( i, XGRAPH ) ) )
        gr_rotated_blit( 0, &region, x, y, flags, LOCDWORD( i, XGRAPH ) ? 0 : LOCINT32( i, ANGLE ), scalex, scaley, map ) ;
    else
        gr_blit( 0, &region, x, y, flags, map ) ;

    if ( paletteid ) map->format->palette = palette;
    if ( blendop ) map->blend_table = blend_table;

    if ( map->modified ) map->modified = 0;
}

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : draw_instance_info
 *
 *  Compares the internal position variables of the instance with its
 *  currents values, and returns 1 if there is any difference. Used
 *  to detect changes in a visible process's aspect or position.
 *
 *  PARAMS :
 *      i           Pointer to the instance
 *
 *  RETURN VALUE :
 *      1 if there is any change, 0 otherwise
 */

int draw_instance_info( INSTANCE * i, REGION * region, int * z, int * drawme )
{
    GRAPH * graph;

    * drawme = 0;

    LOCDWORD( i, GRAPHPTR ) = ( int )( graph = instance_graph( i ) );
    if ( !graph )
    {
        /*
                region->x  = -2; region->y  = -2;
                region->x2 = -2; region->y2 = -2;
        */
        return 0;
    }

    int changed;
    int status;
    int coordz, coordx, coordy;

    status = ( LOCDWORD( i, STATUS ) & ~STATUS_WAITING_MASK ) ;

    coordz = LOCINT32( i, COORDZ );

    /* Si tiene grafico o xgraph o (ctype == 0 y esta corriendo o congelado) */

    if ( LOCDWORD( i, CTYPE ) == C_SCREEN && ( status == STATUS_RUNNING || status == STATUS_FROZEN ) )
        * drawme = 1;


    coordx = LOCINT32( i, COORDX );
    coordy = LOCINT32( i, COORDY );

    RESOLXY( librender, i, coordx, coordy );

    changed =
        graph->modified                                                                           ||
        LOCINT32( i, SAVED_COORDX )        != coordx                                   ||
        LOCINT32( i, SAVED_COORDY )        != coordy                                   ||
        LOCINT32( i, SAVED_COORDZ )        != coordz                                   ||
        LOCDWORD( i, SAVED_GRAPHID )       != LOCDWORD( i, GRAPHID )        ||
        LOCINT32( i, SAVED_ANGLE )         != LOCINT32( i, ANGLE )          ||
        LOCDWORD( i, SAVED_ALPHA )         != LOCDWORD( i, ALPHA )          ||
        LOCDWORD( i, SAVED_BLENDOP )       != LOCDWORD( i, BLENDOP )        ||
        LOCINT32( i, SAVED_GRAPHSIZE )     != LOCINT32( i, GRAPHSIZE )      ||
        LOCINT32( i, SAVED_GRAPHSIZEX )    != LOCINT32( i, GRAPHSIZEX )     ||
        LOCINT32( i, SAVED_GRAPHSIZEY )    != LOCINT32( i, GRAPHSIZEY )     ||
        LOCDWORD( i, SAVED_FLAGS )         != LOCDWORD( i, FLAGS )          ||
        LOCDWORD( i, SAVED_FILEID )        != LOCDWORD( i, FILEID )         ||
        LOCDWORD( i, SAVED_XGRAPH )        != LOCDWORD( i, XGRAPH )         ||
        (
            graph->ncpoints &&
            (
                LOCDWORD( i, SAVED_CENTERX )       != graph->cpoints[0].x              ||
                LOCDWORD( i, SAVED_CENTERY )       != graph->cpoints[0].y
            )
        )
        ;

    if ( changed )
    {
        /* Update key */

        * z = coordz;

        LOCINT32( i, SAVED_COORDX )       = coordx;
        LOCINT32( i, SAVED_COORDY )       = coordy;
        LOCINT32( i, SAVED_COORDZ )       = coordz;
        LOCDWORD( i, SAVED_GRAPHID )      = LOCDWORD( i, GRAPHID );
        LOCINT32( i, SAVED_ANGLE )        = LOCINT32( i, ANGLE );
        LOCDWORD( i, SAVED_ALPHA )        = LOCDWORD( i, ALPHA );
        LOCDWORD( i, SAVED_BLENDOP )      = LOCDWORD( i, BLENDOP );
        LOCINT32( i, SAVED_GRAPHSIZE )    = LOCINT32( i, GRAPHSIZE );
        LOCINT32( i, SAVED_GRAPHSIZEX )   = LOCINT32( i, GRAPHSIZEX );
        LOCINT32( i, SAVED_GRAPHSIZEY )   = LOCINT32( i, GRAPHSIZEY );
        LOCDWORD( i, SAVED_FLAGS )        = LOCDWORD( i, FLAGS );
        LOCDWORD( i, SAVED_FILEID )       = LOCDWORD( i, FILEID );
        LOCDWORD( i, SAVED_XGRAPH )       = LOCDWORD( i, XGRAPH );
        if ( graph->ncpoints )
        {
            LOCDWORD( i, SAVED_CENTERX )      = graph->cpoints[0].x;
            LOCDWORD( i, SAVED_CENTERY )      = graph->cpoints[0].y;
        }
        else
        {
            LOCDWORD( i, SAVED_CENTERX )      = CPOINT_UNDEFINED;
            LOCDWORD( i, SAVED_CENTERY )      = CPOINT_UNDEFINED;
        }

        instance_get_bbox( i, graph, region );
        return 1;
    }

    return changed;
}


/* ----------------------------------------------------------------------
 Dlls Hooks
   ---------------------------------------------------------------------- */

/*
 *  FUNCTION : instance_create_hook
 *
 *  PARAMS :
 *      r           Pointer to the instance
 *
 *  RETURN VALUE :
 *      None
 */

void __bgdexport( librender, instance_create_hook )( INSTANCE * r )
{
    /* COORZ is 0 when a new instance is created */
    LOCDWORD( r, OBJECTID ) = gr_new_object( /* LOCINT32( r, COORDZ ) */ 0, draw_instance_info, draw_instance, r );
}

/*
 *  FUNCTION : instance_destroy_hook
 *
 *  PARAMS :
 *      r           Pointer to the instance
 *
 *  RETURN VALUE :
 *      None
 */

void __bgdexport( librender, instance_destroy_hook )( INSTANCE * r )
{
    if ( LOCDWORD( r, OBJECTID ) ) gr_destroy_object( LOCDWORD( r, OBJECTID ) );
}
