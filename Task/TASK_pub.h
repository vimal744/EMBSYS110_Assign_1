#ifndef TASK_PUB_H
#define TASK_PUB_H

#include "TYPS_pub.h"

typedef uint32 TASK_id_type;

typedef struct
    {
    boolean         inited;
    boolean         locked;
    TASK_id_type    owner_id;
    } TASK_cs_type;

typedef uint8 TASK_cs_err_type; enum
    {
    TASK_CS_ERR_SUCCESS     = 0,
    TASK_CS_ERR_UNKNOWN     = 1,
    TASK_CS_ERR_UN_INIT     = 2,
    TASK_CS_ERR_ALDRD_OWND  = 3,
    TASK_CS_ERR_BUSY        = 4,
    TASK_CS_ERR_PARAM       = 5,
    TASK_CS_ERR_NO_RSRCS    = 6,

    TASK_CS_ERR_NO_CNT
    };

/**
 * Initialize a critical section object
 * \param pCS  Container for critical section object
 * \return    ERR_SUCCESS  Critical Section was initialized
 *            ERR_BUSY     Object was already initialized
 *            ERR_PARAM    The parameter was NULL
 */
TASK_cs_err_type InitializeCriticalSection(TASK_cs_type* pCS);

/**
 * Attempt to take a critical section
 * \param pCS Initialized critical section object
 * \return    ERR_SUCCESS critical section is now owned by this thread
 *            ERR_ALREADY alredy owned by this thread
 *            ERR_BUSY    critical section is owned by another thread
 *            ERR_UNINIT  The critical section not ready
 *            ERR_PARAM   The parameter was NULL
 *            ERR_RESOURCES Out of resources
 */
TASK_cs_err_type EnterCriticalSection(TASK_cs_type* pCS);


/**
 * Release a critical section that was previously taken
 * \param pCS Initialized and owned critical section object
 * \return    ERR_SUCCESS critical section was released
 *            ERR_BUSY    critical section is owned by another thread, cannot be release here
 *            ERR_UNINIT  The critical section not ready
 *            ERR_PARAM   The parameter was NULL
 */
TASK_cs_err_type LeaveCriticalSection(TASK_cs_type* pCS);


/**
 * Release any resources
 * \param pCS The object to cleanup
 * \return ERR_SUCCESS resources released
 *         ERR_BUSY    The object is currently taken by another thread (Discuss: should this be an error?)
 *         ERR_PARAM   parameter was NULL
 */
TASK_cs_err_type DeleteCriticalSection(TASK_cs_type* pCS);

#endif // TASK_PUB_H