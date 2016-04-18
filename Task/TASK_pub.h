#ifndef TASK_PUB_H
#define TASK_PUB_H

#include "TYPS_pub.h"

#define TASK_CS_SIGNATURE   0x4352534E

typedef uint32 TASK_id_type;

typedef struct
    {
    uint32          signature;
    boolean         locked;
    } TASK_cs_type;

typedef uint8 TASK_cs_err_type; enum
    {
    TASK_CS_ERR_SUCCESS,
    TASK_CS_ERR_UNKNOWN,
    TASK_CS_ERR_PARAM,
    TASK_CS_ERR_UN_INITED,
    TASK_CS_ERR_ALRDY_INITED,

    TASK_CS_ERR_NOT_LOCKED,
    TASK_CS_ERR_ALRDY_LOCKED,
    TASK_CS_ERR_BUSY,

    TASK_CS_ERR_NO_CNT
    };

/**
 * Initialize a critical section object
 * \param pCS  Container for critical section object
 * \return    TASK_CS_ERR_SUCCESS           Critical Section was initialized
 *            TASK_CS_ERR_ALRDY_INITED      Object was already initialized
 *            TASK_CS_ERR_PARAM             The parameter was NULL
 *            TASK_CS_ERR_UNKNOWN           Unknown error
 */
extern TASK_cs_err_type TASK_cs_init(TASK_cs_type* pCS);

/**
 * Attempt to take a critical section
 * \param pCS Initialized critical section object
 * \return    TASK_CS_ERR_SUCCESS           Critical Section lock was obtained successfully
 *            TASK_CS_ERR_UN_INITED         Object was not initialized
 *            TASK_CS_ERR_PARAM             The parameter was NULL
 *            TASK_CS_ERR_ALRDY_LOCKED      object already locked by a thread
 *            TASK_CS_ERR_BUSY              CPU error
 *            TASK_CS_ERR_UNKNOWN           Unknown error
 */
TASK_cs_err_type TASK_cs_enter(TASK_cs_type* pCS);


/**
 * Release a critical section that was previously taken
 * \param pCS Initialized and owned critical section object
 * \return    TASK_CS_ERR_SUCCESS           Critical Section lock was released successfully
 *            TASK_CS_ERR_UN_INITED         Object was not initialized
 *            TASK_CS_ERR_PARAM             The parameter was NULL
 *            TASK_CS_ERR_NOT_LOCKED        Object not locked by a thread
 *            TASK_CS_ERR_BUSY              CPU error
 *            TASK_CS_ERR_UNKNOWN           Unknown error
 */
TASK_cs_err_type TASK_cs_leave(TASK_cs_type* pCS);


/**
 * Release any resources
 * \param pCS The object to cleanup
 * \return    TASK_CS_ERR_SUCCESS           Critical Section deleted successfully
 *            TASK_CS_ERR_UN_INITED         Object was not initialized
 *            TASK_CS_ERR_PARAM             The parameter was NULL
 *            TASK_CS_ERR_ALRDY_LOCKED      Object locked by a thread
 *            TASK_CS_ERR_UNKNOWN           Unknown error
 */
TASK_cs_err_type TASK_cs_delete(TASK_cs_type* pCS);

#endif // TASK_PUB_H
