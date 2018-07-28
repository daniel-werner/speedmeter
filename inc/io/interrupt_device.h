/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _INTERRUPT_DEVICE_
#define _INTERRUPT_DEVICE_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <setup/board.h>

/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma unmanaged
#endif

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

typedef struct InterruptDevice InterruptDevice;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

typedef bool_t (*func_interrupt_callback_t)(u8_t);

struct InterruptDevice{
	u8_t portNum;
	u8_t interruptMask;
	u8_t interruptEdgeMask;
	func_interrupt_callback_t callbacks[8];
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void InterruptDevice_ctor( InterruptDevice* self, u8_t portNum );

InterruptDevice* InterruptDevice_get_instance( u8_t portNum );

void InterruptDevice_set_interrupt( InterruptDevice* self,
									u8_t interruptMask, u8_t interruptEdgeMask );

void InterruptDevice_set_callback( InterruptDevice* self,
									u8_t interruptMask, func_interrupt_callback_t callback );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
