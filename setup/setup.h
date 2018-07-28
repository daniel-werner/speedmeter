/*******************************************************************************

    Setup for filter module
    =========================
   

    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef __SETUP_H_INCLUDED__
#define __SETUP_H_INCLUDED__

/* Configurations */

/* ARCHITECTURE IDENTIFIER: */
/*----------------------------------------------------------------------------*/

#define __ARCH_I386__           0
#define __ARCH_TMS320_C55XX__   0
#define __ARCH_MSP430__         1

/*----------------------------------------------------------------------------*/
/* Select runtime mode: simulator or debugger */

#define _SIMULATOR_MODE_         1
#define _DEBUGGER_MODE_          0

#define _RUNTIME_MODE_ _DEBUGGER_MODE_

#define _BOARD_V_01             1
#define _BOARD_V_02             2

#define _BOARD_VERSION_ _BOARD_V_01

/*----------------------------------------------------------------------------*/

#define FREQ_4_MHz 4000000
#define FREQ_8_MHz 8000000
#define FREQ_6_MHz 6000000

#define _MAIN_FREQUENCY FREQ_6_MHz

#endif
