#include "TYPS_pub.h"
#include "TASK_pub.h"

#include "stm32f4xx.h"
#include "core_cm4.h"
#include <cmsis_iar.h>

#include <string.h>

TASK_cs_err_type InitializeCriticalSection(TASK_cs_type* pCS)
{
    TASK_cs_err_type err;

    err = TASK_CS_ERR_UNKNOWN;

    if( NULL == pCS )
    {
        err = TASK_CS_ERR_PARAM;
    }
    else
    {
        if( TASK_CS_SIGNATURE == pCS->signature )
        {
            err = TASK_CS_ERR_ALRDY_INITED;
        }
        else
        {
            memset( pCS, 0, sizeof( TASK_cs_type ) );
            pCS->signature = TASK_CS_SIGNATURE;
            err = TASK_CS_ERR_SUCCESS;
        }
    }

    return err;
}

TASK_cs_err_type EnterCriticalSection(TASK_cs_type* pCS)
{
    TASK_cs_err_type err;

    err = TASK_CS_ERR_UNKNOWN;

    if( NULL == pCS )
    {
        err = TASK_CS_ERR_PARAM;
    }
    else
    {
        if( pCS->signature != TASK_CS_SIGNATURE )
        {
            err = TASK_CS_ERR_UN_INITED;
        }
        else
        {
            boolean curret_val = __LDREXB( &pCS->locked );

            __DMB();

            if( curret_val == FALSE )
            {
                if( 0 == __STREXB( TRUE, &pCS->locked ) )
                {
                    __DMB();
                    err = TASK_CS_ERR_SUCCESS;
                }
                else
                {
                    __DMB();
                    err = TASK_CS_ERR_BUSY;
                }
            }
            else
            {
                err = TASK_CS_ERR_ALRDY_LOCKED;
            }
        }
    }

    return err;
}


TASK_cs_err_type LeaveCriticalSection(TASK_cs_type* pCS)
{
    TASK_cs_err_type err;

    err = TASK_CS_ERR_UNKNOWN;

    if( NULL == pCS )
    {
        err = TASK_CS_ERR_PARAM;
    }
    else
    {
        if( pCS->signature != TASK_CS_SIGNATURE )
        {
            err = TASK_CS_ERR_UN_INITED;
        }
        else
        {
            boolean curret_val = __LDREXB( &pCS->locked );

            __DMB();

            if( curret_val == TRUE )
            {
                if( 0 == __STREXB( FALSE, &pCS->locked ) )
                {
                    __DMB();
                    err = TASK_CS_ERR_SUCCESS;
                }
                else
                {
                    __DMB();
                    err = TASK_CS_ERR_BUSY;
                }
            }
            else
            {
                err = TASK_CS_ERR_NOT_LOCKED;
            }
        }
    }

    return err;
}

TASK_cs_err_type DeleteCriticalSection(TASK_cs_type* pCS)
{
    TASK_cs_err_type err;

    err = TASK_CS_ERR_UNKNOWN;

    if( NULL == pCS )
    {
        err = TASK_CS_ERR_PARAM;
    }
    else
    {
        if( TASK_CS_SIGNATURE == pCS->signature )
        {
            boolean curret_val = __LDREXB( &pCS->locked );

            __DMB();

            if( curret_val == FALSE )
            {
                memset( pCS, 0, sizeof( TASK_cs_type ) );
                err             = TASK_CS_ERR_SUCCESS;
            }
            else
            {
                err = TASK_CS_ERR_ALRDY_LOCKED;
            }
        }
        else
        {
            err = TASK_CS_ERR_UN_INITED;
        }
    }

    return err;
    
}




