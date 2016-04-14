#include "TYPS_pub.h"
#include "TASK_pub.h"

#include <string.h>

TASK_cs_err_type InitializeCriticalSection(TASK_cs_type* pCS)
{
    TASK_cs_err_type err;

    err = TASK_CS_ERR_UNKNOWN;

    if( pCS != NULL )
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
    return TASK_CS_ERR_UNKNOWN;
}


TASK_cs_err_type LeaveCriticalSection(TASK_cs_type* pCS)
{
    return TASK_CS_ERR_UNKNOWN;
}

TASK_cs_err_type DeleteCriticalSection(TASK_cs_type* pCS)
{
    return TASK_CS_ERR_UNKNOWN;
}




