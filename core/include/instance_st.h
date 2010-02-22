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

#ifndef __INSTANCE_ST_H
#define __INSTANCE_ST_H

#define FIRST_INSTANCE_ID   0x00010000
#define LAST_INSTANCE_ID    0x0001ffff

#define STACK_RETURN_VALUE  0x8000
#define STACK_SIZE_MASK     0x7FFF
#define STACK_SIZE          2048

/* Instances. An instance is created from a process, but it's really *
 * from the original one. */

typedef struct _instance
{
    void * locdata ;
    void * pridata ;
    void * pubdata ;

    int * code ;
    int * codeptr ;

    int exitcode ;
    int errorcode ;

    int call_level ;

    struct _procdef  * proc ;

    int private_size ;
    int public_size ;

    int first_run ;

    /* General list - unsorted */

    struct _instance * next ;
    struct _instance * prev ;

    /* Linked list by priority */

    struct _instance * next_by_priority ;
    struct _instance * prev_by_priority ;
    int last_priority ;

    /* Linked list by process_type */

    struct _instance * next_by_type ;
    struct _instance * prev_by_type ;

    /* Linked list by INSTANCE * */

    struct _instance * next_by_instance ;
    struct _instance * prev_by_instance ;

    /* Function support */

    struct _instance * called_by ;

    /* The first integer at the stack is the stack size,
       with optional NO_RETURN_VALUE mask. The stack contents follows */

    int * stack ;
    int * stack_ptr ;

    /* For debugging */

    int switchval;
    int switchval_string;
    int cased;

    int breakpoint;

}
INSTANCE ;

/* Macros to acess local or private data for an instance */

#define LOCDWORD(a,b)   ( *(uint32_t *) ((uint8_t *)(a->locdata)+b) )
#define LOCWORD(a,b)    ( *(uint16_t *) ((uint8_t *)(a->locdata)+b) )
#define LOCBYTE(a,b)    ( *(uint8_t  *) ((uint8_t *)(a->locdata)+b) )

#define LOCINT32(a,b)   ( *(int32_t  *) ((uint8_t *)(a->locdata)+b) )
#define LOCINT16(a,b)   ( *(int16_t  *) ((uint8_t *)(a->locdata)+b) )
#define LOCINT8(a,b)    ( *(int8_t   *) ((uint8_t *)(a->locdata)+b) )

#define LOCUINT32(a,b)  ( *(uint32_t *) ((uint8_t *)(a->locdata)+b) )
#define LOCUINT16(a,b)  ( *(uint16_t *) ((uint8_t *)(a->locdata)+b) )
#define LOCUINT8(a,b)   ( *(uint8_t  *) ((uint8_t *)(a->locdata)+b) )


#define PRIDWORD(a,b)   ( *(uint32_t *) ((uint8_t *)(a->pridata)+b) )
#define PRIWORD(a,b)    ( *(uint16_t *) ((uint8_t *)(a->pridata)+b) )
#define PRIBYTE(a,b)    ( *(uint8_t  *) ((uint8_t *)(a->pridata)+b) )

#define PRIINT32(a,b)   ( *(int32_t  *) ((uint8_t *)(a->pridata)+b) )
#define PRIINT16(a,b)   ( *(int16_t  *) ((uint8_t *)(a->pridata)+b) )
#define PRIINT8(a,b)    ( *(int8_t   *) ((uint8_t *)(a->pridata)+b) )

#define PRIUINT32(a,b)  ( *(uint32_t *) ((uint8_t *)(a->pridata)+b) )
#define PRIUINT16(a,b)  ( *(uint16_t *) ((uint8_t *)(a->pridata)+b) )
#define PRIUINT8(a,b)   ( *(uint8_t  *) ((uint8_t *)(a->pridata)+b) )


#define PUBDWORD(a,b)   ( *(uint32_t *) ((uint8_t *)(a->pubdata)+b) )
#define PUBWORD(a,b)    ( *(uint16_t *) ((uint8_t *)(a->pubdata)+b) )
#define PUBBYTE(a,b)    ( *(uint8_t  *) ((uint8_t *)(a->pubdata)+b) )

#define PUBINT32(a,b)   ( *(int32_t  *) ((uint8_t *)(a->pubdata)+b) )
#define PUBINT16(a,b)   ( *(int16_t  *) ((uint8_t *)(a->pubdata)+b) )
#define PUBINT8(a,b)    ( *(int8_t   *) ((uint8_t *)(a->pubdata)+b) )

#define PUBUINT32(a,b)  ( *(uint32_t *) ((uint8_t *)(a->pubdata)+b) )
#define PUBUINT16(a,b)  ( *(uint16_t *) ((uint8_t *)(a->pubdata)+b) )
#define PUBUINT8(a,b)   ( *(uint8_t  *) ((uint8_t *)(a->pubdata)+b) )


#define GLODWORD(b)     ( *(uint32_t *) ((uint8_t *)(globaldata)+b) )
#define GLOWORD(b)      ( *(uint16_t *) ((uint8_t *)(globaldata)+b) )
#define GLOBYTE(b)      ( *(uint8_t  *) ((uint8_t *)(globaldata)+b) )

#define GLOINT32(b)     ( *(int32_t  *) ((uint8_t *)(globaldata)+b) )
#define GLOINT16(b)     ( *(int16_t  *) ((uint8_t *)(globaldata)+b) )
#define GLOINT8(b)      ( *(int8_t   *) ((uint8_t *)(globaldata)+b) )

#define GLOUINT32(b)    ( *(uint32_t *) ((uint8_t *)(globaldata)+b) )
#define GLOUINT16(b)    ( *(uint16_t *) ((uint8_t *)(globaldata)+b) )
#define GLOUINT8(b)     ( *(uint8_t  *) ((uint8_t *)(globaldata)+b) )

#endif
