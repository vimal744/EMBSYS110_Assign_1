/*
 * University of Washington
 * Certificate in Embedded and Real-Time Systems
 *
 * uDebugger homework
 */
#include "bsp.h"
#include "print.h"

#include "TYPS_pub.h"


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


    PrintString("\nFail! Should not arrive here.\n");
    while(1);
}


void SystemInit(void)
{
  // System init is called from the assembly .s file
  // We will configure the clocks in hw_init
  asm("nop");
}
  
