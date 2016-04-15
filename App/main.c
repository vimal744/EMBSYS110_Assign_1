/*
 * University of Washington
 * Certificate in Embedded and Real-Time Systems
 *
 * uDebugger homework
 */
#include "bsp.h"
#include "print.h"

#include "TYPS_pub.h"
#include "TASK_pub.h"


char clr_scrn[] = { 27, 91, 50, 74, 0 };              // esc[2J
/* Public variables ----------------------------------------------------------*/
PRINT_DEFINEBUFFER();           /* required for lightweight sprintf */
/* Private prototype ---------------------------------------------------------*/

void SystemInit(void);


void main()
{
    Hw_init();

    PrintString(clr_scrn); /* Clear entire screen */
    PrintString("University of Washington - Debugger Test Application \n");
    {

        TASK_cs_err_type    err;
        TASK_cs_type        myCS;
        int x;

        myCS.owner_id = 7;
        myCS.signature = 0xabcdf00b;

        err = InitializeCriticalSection( &myCS );
        x =2;
    }

    PrintString("\nFail! Should not arrive here.\n");
    while(1);
}


void SystemInit(void)
{
  // System init is called from the assembly .s file
  // We will configure the clocks in hw_init
  asm("nop");
}
  
