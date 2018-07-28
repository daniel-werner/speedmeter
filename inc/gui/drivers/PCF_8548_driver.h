/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _PCF_8548_DRIVER_
#define _PCF_8548_DRIVER_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <types/matrix.h>
#include <gui/drivers/display_driver.h>
#include <io/i2c_device.h>

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
	I2cDevice iodevice;
};

/* LCD instructions */

/* Control bytes */

#define CONTROL_SINGLE_COMMAND	0x80
#define CONTROL_MULTI_COMMAND	0x00
#define CONTROL_SINGLE_DATA		0xC0
#define CONTROL_MULTI_DATA		0x40

#define NOP 0x00

/* Function set */
#define FUNCTION_SET 0x20

#define H	0x01
#define VERTICAL	0x02
#define PD	0x04
#define MY	0x08
#define MX	0x10

/* Vlcd range */
#define SET_VLCD_RANGE	0x04

#define PRS	0x01

/* Display configuration */
#define DISPLAY_CONTROL	0x08

#define E	0x01
#define D	0x04

/* Set HV stages */
#define SET_HV_GEN_STATES 0x10

#define S0	0x01
#define S1	0x20

/* Set Y address */
#define SET_Y_ADDRESS	0x40

/* Set X address */
#define SET_X_ADDRESS	0x80

/* Temperature control */
#define TEMPERATURE_CONTROL	0x04

#define  TC0	0x01
#define  TC1	0x02

/* Display configuration */
#define DISPLAY_CONFIGURATION	0x08

#define BRS	0x01
#define TRS	0x02
#define DO	0x04

/* Bias system */
#define BIAS_SYSTEM	0x10

#define BS0	0x01
#define BS1	0x02
#define BS2	0x04

/* Set Vop to register */
#define SET_VOP	0x80

#define VOP0	0x01
#define VOP1	0x02
#define VOP2	0x04
#define VOP3	0x08
#define VOP4	0x10
#define VOP5	0x20
#define VOP6	0x40

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void DisplayDriver_ctor( DisplayDriver* self, enum AddressingMode mode );
DisplayDriver* DisplayDriver_get_instance();
void DisplayDriver_clear_display( const DisplayDriver* self );
void DisplayDriver_put_pixel( const DisplayDriver* self, const Matrix* data, coord_t x, coord_t y );
void DisplayDriver_put_pixels( const DisplayDriver* self, const Matrix* data, coord_t x1, coord_t x2, size_t size );
void DisplayDriver_put_all_pixels( const DisplayDriver* self, const Matrix* data, size_t size );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
