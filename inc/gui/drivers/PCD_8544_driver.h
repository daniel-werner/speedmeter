/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _PCD_8544_DRIVER_
#define _PCD_8544_DRIVER_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <types/matrix.h>
#include <gui/drivers/display_driver.h>
#include <io/spi_device.h>

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

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

enum AddressingMode {
	ADDRESSING_MODE_VERTICAL = 1,
	ADDRESSING_MODE_HORIZONTAL = 2	
};
	
struct DisplayDriver {
	enum AddressingMode addressingMode;
	SPIDevice iodevice;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void DisplayDriver_ctor( DisplayDriver* self, enum AddressingMode mode );
DisplayDriver* DisplayDriver_get_instance();
void DisplayDriver_put_pixel( const DisplayDriver* self, const Matrix* data, coord_t x, coord_t y );
void Display_driver_standby( const DisplayDriver* self );
void Display_driver_wakeup( const DisplayDriver* self );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
