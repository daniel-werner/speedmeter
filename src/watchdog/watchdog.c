/*******************************************************************************

    Watchdog timer
    ========================================
   

    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#include <watchdog/watchdog.h>

/*----------------------------------------------------------------------------*/

void init_watchdog()
{
  WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL + WDTSSEL + WDTIS0;
  IE1 |= WDTIE;                         // Enable WDT interrupt
}

/*----------------------------------------------------------------------------*/

void reset_watchdog()
{
  WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL + WDTSSEL + WDTIS0;
}

/*----------------------------------------------------------------------------*/

void stop_watchdog()
{
  WDTCTL = WDTPW + WDTHOLD;
}
