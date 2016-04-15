    MODULE        TASKCRITICALSECTION   /* The module name */

    PUBLIC InitializeCriticalSection    /* Make function name visible to linker               */
    IMPORT TASK_cs_type

    SECTION `.rodata`:CONST:REORDER:NOROOT(2)
    DATA

TASK_CS_ERR_SUCCESS             equ 0
TASK_CS_ERR_UNKNOWN             equ 1
TASK_CS_ERR_UN_INITED           equ 2
TASK_CS_ERR_ALRDY_INITED        equ 3
TASK_CS_ERR_ALRDY_OWND          equ 4
TASK_CS_ERR_BUSY                equ 5
TASK_CS_ERR_PARAM               equ 6
TASK_CS_ERR_NO_RSRCS            equ 7

TASK_CS_SIGNATURE               equ 0x4352534E


    /* Tells the linker the section name : memory type : fragment (align)       */
    SECTION `.text`:CODE:NOROOT(2)
    THUMB                 /* Mode control directive                             */

/*
TASK_cs_err_type InitializeCriticalSection
    (
    TASK_cs_type* pCS
    )
*/
InitializeCriticalSection:

    PUSH {R4-R11, LR}

    // Copy the address of the CS oobject
    MOV  R1,R0

    // Intialize the return value
    LDR  R0, =TASK_CS_ERR_UNKNOWN

    // If the input is NULL
    CMP     R1, #0

    // Return an TASK_CS_ERR_PARAM
    ITT     EQ
    MOVEQ   R0, #TASK_CS_ERR_PARAM
    BEQ     InitializeCriticalSection_exit

    LDR     R2, =TASK_CS_SIGNATURE

    // Load R3 with the value of the signature member
    LDR     R3, [R1, #4]

    // Compare against TASK_CS_SIGNATURE
    CMP     R2,R3

    // If equal, return an err code of TASK_CS_ERR_ALRDY_INITED
    ITT     EQ
    MOVEQ   R0, #TASK_CS_ERR_ALRDY_INITED
    BEQ     InitializeCriticalSection_exit

    //  Initialize the signature member with TASK_CS_SIGNATURE
    //
    STR     R2, [R1, #4]

    // Initialize owner id to 0
    LDR     R3, =0
    STR     R3, [R1, #0]

    // Initialize locked to 0
    STRB    R3, [R1, #8]

    // Set return value to TASK_CS_ERR_SUCCESS
    LDR     R0, =TASK_CS_ERR_SUCCESS

InitializeCriticalSection_exit:

    POP {R4-R11, PC}

    END