/*
 * Unit tests for critical section code
 *
 */
#include "TASK_pub.h"
#include "unittest.h"

UTGLOBALS();

UT( CS_Test_Init_Nomral_Success )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS, InitializeCriticalSection( &myCS ) );

    ASSERT_EQ( FALSE, myCS.locked );

    return UT_PASSED;
}

UT( CS_Test_Init_NullParam_Failed )
{
    ASSERT_EQ( TASK_CS_ERR_PARAM, InitializeCriticalSection( NULL ) );

    return UT_PASSED;
}

UT( CS_Test_Enter_NullParam_Failed )
{
    ASSERT_EQ( TASK_CS_ERR_PARAM, EnterCriticalSection( NULL ) );

    return UT_PASSED;
}

UT( CS_Test_Enter_Uninited_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_UN_INITED, EnterCriticalSection( &myCS ) );

    return UT_PASSED;
}

UT( CS_Test_Enter_Normal_Success )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS, InitializeCriticalSection( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS, EnterCriticalSection( &myCS )      );

    return UT_PASSED;
}



UT( CS_Test_Leave_NullParam_Failed )
{
    ASSERT_EQ( TASK_CS_ERR_PARAM, LeaveCriticalSection( NULL ) );

    return UT_PASSED;
}

UT( CS_Test_Leave_Uninited_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_UN_INITED, LeaveCriticalSection( &myCS ) );

    return UT_PASSED;
}

UT( CS_Test_Leave_NotLocked_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,    InitializeCriticalSection( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_NOT_LOCKED, LeaveCriticalSection( &myCS )      );

    return UT_PASSED;
}

UT( CS_Test_Leave_Normal_Success )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS, InitializeCriticalSection( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS, EnterCriticalSection( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS, LeaveCriticalSection( &myCS )      );

    return UT_PASSED;
}


UT( CS_Test_Delete_NullParam_Failed )
{
    ASSERT_EQ( TASK_CS_ERR_PARAM, DeleteCriticalSection( NULL ) );

    return UT_PASSED;
}


UT( CS_Test_Delete_Uninited_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_UN_INITED, DeleteCriticalSection( &myCS ) );

    return UT_PASSED;
}

UT( CS_Test_Delete_AlreadyLocked_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      InitializeCriticalSection( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      EnterCriticalSection( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_ALRDY_LOCKED, DeleteCriticalSection( &myCS )     );

    return UT_PASSED;
}

UT( CS_Test_Delete_NoEnterLeave_Success )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     InitializeCriticalSection( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     DeleteCriticalSection( &myCS )     );

    return UT_PASSED;
}

UT( CS_Test_Delete_AfterEnterLeave_Success )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     InitializeCriticalSection( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     EnterCriticalSection( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     LeaveCriticalSection( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     DeleteCriticalSection( &myCS )     );

    return UT_PASSED;
}


void ut_cs( void )
{
    UTRUN( CS_Test_Init_Nomral_Success );
    UTRUN( CS_Test_Init_NullParam_Failed );

    UTRUN( CS_Test_Enter_NullParam_Failed );
    UTRUN( CS_Test_Enter_Uninited_Failed  );
    UTRUN( CS_Test_Enter_Normal_Success   );

    UTRUN( CS_Test_Leave_NullParam_Failed );
    UTRUN( CS_Test_Leave_Uninited_Failed  );
    UTRUN( CS_Test_Leave_NotLocked_Failed );
    UTRUN( CS_Test_Leave_Normal_Success   );

    UTRUN( CS_Test_Delete_NullParam_Failed );
    UTRUN( CS_Test_Delete_Uninited_Failed );
    UTRUN( CS_Test_Delete_AlreadyLocked_Failed );
    UTRUN( CS_Test_Delete_NoEnterLeave_Success );
    UTRUN( CS_Test_Delete_AfterEnterLeave_Success );

    UTTOTALS();
}

