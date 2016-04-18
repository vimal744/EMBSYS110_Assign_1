#include "TYPS_pub.h"
#include "TASK_pub.h"

#include "stm32f4xx.h"
#include "core_cm4.h"
#include <cmsis_iar.h>

#include <string.h>

/**
 * Initialize a critical section object
 * \description :
 *   This function initalizes a critical section object
 *
 *
 * \param pCS  Container for critical section object
 * \return    TASK_CS_ERR_SUCCESS           Critical Section was initialized
 *            TASK_CS_ERR_ALRDY_INITED      Object was already initialized
 *            TASK_CS_ERR_PARAM             The parameter was NULL
 *            TASK_CS_ERR_UNKNOWN           Unknown error
 */
TASK_cs_err_type TASK_cs_init(TASK_cs_type* pCS)
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


/**
 * Attempt to take a critical section
 * \description :
 *   This function is used to lock a critical section object
 *
 * \param pCS Initialized critical section object
 * \return    TASK_CS_ERR_SUCCESS           Critical Section lock was obtained successfully
 *            TASK_CS_ERR_UN_INITED         Object was not initialized
 *            TASK_CS_ERR_PARAM             The parameter was NULL
 *            TASK_CS_ERR_ALRDY_LOCKED      object already locked by a thread
 *            TASK_CS_ERR_BUSY              CPU error
 *            TASK_CS_ERR_UNKNOWN           Unknown error
 */

TASK_cs_err_type TASK_cs_enter(TASK_cs_type* pCS)
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


/**
 * Release a critical section that was previously taken
 * \description :
 *   This function is used to release a critical section object
 *
 * \param pCS Initialized and owned critical section object
 * \return    TASK_CS_ERR_SUCCESS           Critical Section lock was released successfully
 *            TASK_CS_ERR_UN_INITED         Object was not initialized
 *            TASK_CS_ERR_PARAM             The parameter was NULL
 *            TASK_CS_ERR_NOT_LOCKED        Object not locked by a thread
 *            TASK_CS_ERR_BUSY              CPU error
 *            TASK_CS_ERR_UNKNOWN           Unknown error
 */

TASK_cs_err_type TASK_cs_leave(TASK_cs_type* pCS)
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

/**
 * Delete a critical section object
 * \description :
 *   This function is used to deletele a critical section object
 *
 * \param pCS The object to cleanup
 * \return    TASK_CS_ERR_SUCCESS           Critical Section deleted successfully
 *            TASK_CS_ERR_UN_INITED         Object was not initialized
 *            TASK_CS_ERR_PARAM             The parameter was NULL
 *            TASK_CS_ERR_ALRDY_LOCKED      Object locked by a thread
 *            TASK_CS_ERR_UNKNOWN           Unknown error
 */

TASK_cs_err_type TASK_cs_delete(TASK_cs_type* pCS)
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




