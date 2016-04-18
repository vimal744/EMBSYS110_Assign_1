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

    ASSERT_EQ( TASK_CS_ERR_SUCCESS, TASK_cs_init( &myCS ) );

    ASSERT_EQ( FALSE, myCS.locked );

    return UT_PASSED;
}

UT( CS_Test_Init_NullParam_Failed )
{
    ASSERT_EQ( TASK_CS_ERR_PARAM, TASK_cs_init( NULL ) );

    return UT_PASSED;
}

UT( CS_Test_Enter_NullParam_Failed )
{
    ASSERT_EQ( TASK_CS_ERR_PARAM, TASK_cs_enter( NULL ) );

    return UT_PASSED;
}

UT( CS_Test_Enter_Uninited_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_UN_INITED, TASK_cs_enter( &myCS ) );

    return UT_PASSED;
}

UT( CS_Test_Enter_Normal_Success )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS, TASK_cs_init( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS, TASK_cs_enter( &myCS )      );

    return UT_PASSED;
}



UT( CS_Test_Leave_NullParam_Failed )
{
    ASSERT_EQ( TASK_CS_ERR_PARAM, TASK_cs_leave( NULL ) );

    return UT_PASSED;
}

UT( CS_Test_Leave_Uninited_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_UN_INITED, TASK_cs_leave( &myCS ) );

    return UT_PASSED;
}

UT( CS_Test_Leave_NotLocked_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,    TASK_cs_init( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_NOT_LOCKED, TASK_cs_leave( &myCS )      );

    return UT_PASSED;
}

UT( CS_Test_Leave_Normal_Success )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS, TASK_cs_init( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS, TASK_cs_enter( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS, TASK_cs_leave( &myCS )      );

    return UT_PASSED;
}


UT( CS_Test_Delete_NullParam_Failed )
{
    ASSERT_EQ( TASK_CS_ERR_PARAM, TASK_cs_delete( NULL ) );

    return UT_PASSED;
}


UT( CS_Test_Delete_Uninited_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_UN_INITED, TASK_cs_delete( &myCS ) );

    return UT_PASSED;
}

UT( CS_Test_Delete_AlreadyLocked_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      TASK_cs_init( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      TASK_cs_enter( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_ALRDY_LOCKED, TASK_cs_delete( &myCS )     );

    return UT_PASSED;
}

UT( CS_Test_Delete_NoEnterNoLeave_Success )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     TASK_cs_init( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     TASK_cs_delete( &myCS )     );

    return UT_PASSED;
}

UT( CS_Test_Delete_EnterAndLeave_Success )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     TASK_cs_init( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     TASK_cs_enter( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     TASK_cs_leave( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,     TASK_cs_delete( &myCS )     );

    return UT_PASSED;
}

UT( CS_Test_MultipleEnter_Failed )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      TASK_cs_init( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      TASK_cs_enter( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_ALRDY_LOCKED, TASK_cs_enter( &myCS )      );

    return UT_PASSED;
}

UT( CS_Test_MultipleEnterLeave_Success )
{
    TASK_cs_type myCS;

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      TASK_cs_init( &myCS ) );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      TASK_cs_enter( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      TASK_cs_leave( &myCS )      );

    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      TASK_cs_enter( &myCS )      );
    ASSERT_EQ( TASK_CS_ERR_SUCCESS,      TASK_cs_leave( &myCS )      );

    return UT_PASSED;
}


UT( CS_Test_MultipleCSEnterLeave_Success )
{
    #define ARRAY_CNT ( 10 )

    TASK_cs_type myCS[10];
    uint8        i;

    for( i = 0; i < ARRAY_CNT; i++ )
    {
        ASSERT_EQ( TASK_CS_ERR_SUCCESS, TASK_cs_init( &( myCS[i] ) ) );
    }

    for( i = 0; i < ARRAY_CNT; i++ )
    {
        ASSERT_EQ( TASK_CS_ERR_SUCCESS, TASK_cs_enter( &( myCS[i] ) ) );
    }

    for( i = 0; i < ARRAY_CNT; i++ )
    {
        ASSERT_EQ( TASK_CS_ERR_ALRDY_LOCKED, TASK_cs_enter( &( myCS[i] ) ) );
    }


    for( i = 0; i < ARRAY_CNT; i++ )
    {
        ASSERT_EQ( TASK_CS_ERR_SUCCESS, TASK_cs_leave( &( myCS[i] ) ) );
    }

    for( i = 0; i < ARRAY_CNT; i++ )
    {
        ASSERT_EQ( TASK_CS_ERR_NOT_LOCKED, TASK_cs_leave( &( myCS[i] ) ) );
    }


    for( i = 0; i < ARRAY_CNT; i++ )
    {
        ASSERT_EQ( TASK_CS_ERR_SUCCESS, TASK_cs_delete( &( myCS[i] ) ) );
    }

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
    UTRUN( CS_Test_Delete_NoEnterNoLeave_Success );
    UTRUN( CS_Test_Delete_EnterAndLeave_Success );

    UTRUN( CS_Test_MultipleEnter_Failed );
    UTRUN( CS_Test_MultipleEnterLeave_Success );
    UTRUN( CS_Test_MultipleCSEnterLeave_Success );


    UTTOTALS();
}

