#ifndef TYPS_PUB_H
#define TYPS_PUB_H

#include <stdint.h>

#if( !defined( NULL ) )
    #define NULL        0
#endif

#if( !defined( TRUE ) )
    #define TRUE        1
#endif

#if( !defined( FALSE ) )
    #define FALSE       0
#endif

typedef int8_t      sint8;
typedef uint8_t     uint8;

typedef int16_t     sint16;
typedef uint16_t    uint16;

typedef int32_t     sint32;
typedef uint32_t    uint32;

typedef int64_t     sint64;
typedef uint64_t    uint64;

typedef unsigned char boolean;


#endif // TYPS_PUB_H
