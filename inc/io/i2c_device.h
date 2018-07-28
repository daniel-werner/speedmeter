/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _SPI_DEVICE_
#define _SPI_DEVICE_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
#include <io/io_device.h>

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

typedef struct I2cDevice I2cDevice;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

enum I2cCommSpeed{
	I2C_COMM_SPEED_100 = 100,
	I2C_COMM_SPEED_400 = 400
};

enum OperationMode{
	OP_MODE_MASTER = 1,
	OP_MODE_SLAVE = 2
};


struct I2cDevice {
	IODevice* base;
	u8_t slaveAddress;
	enum I2cCommSpeed commSpeed;
	enum OperationMode operationMode;
};

#define I2C_SEL P3SEL
#define I2C_DIR P3DIR
#define I2C_IN P3IN
#define I2C_OUT P3OUT

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/


void I2cDevice_ctor( I2cDevice* self, u8_t slaveAddress, enum OperationMode operationMode, 
					enum I2cCommSpeed commSpeed );
int I2cDevice_write( const I2cDevice* self, void* data, size_t size );
int I2cDevice_read( const I2cDevice* self, void* data, size_t size );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
