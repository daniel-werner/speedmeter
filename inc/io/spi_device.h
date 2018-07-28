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

typedef struct SPIDevice SPIDevice;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

enum DataLength{
	DATA_LENGTH_7 = 7,
	DATA_LENGTH_8 = 8
};

enum WiringMode{
	WIRING_MODE_3_WIRE = 3,
	WIRING_MODE_4_WIRE = 4
};

enum OperationMode{
	OP_MODE_MASTER = 1,
	OP_MODE_SLAVE = 2
};

enum ClockPolarity{
	CLK_POL_INACTIVE_LOW = 0,
	CLK_POL_INACTIVE_HIGH = 1
};

struct SPIDevice {
	IODevice* base;
	enum OperationMode operationMode;
	u_t spiPortNum;	
	u32_t baudRate;
	enum DataLength dataLength;
	enum ClockPolarity clockPolarity;
	enum WiringMode wiringMode;
};

#define SPI0_SEL P3SEL
#define SPI0_DIR P3DIR
#define SPI0_IN P3IN
#define SPI0_OUT P3OUT

#define SPI1_SEL P5SEL
#define SPI1_DIR P5DIR
#define SPI1_IN P5IN
#define SPI1_OUT P5OUT

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/


void SPIDevice_ctor( SPIDevice* self, enum OperationMode operationMode, 
					u32_t baudRate, enum DataLength dataLength, 
					enum ClockPolarity clockPolarity, enum WiringMode wiringMode,
					u_t spiPortNum );
int SPIDevice_write( const SPIDevice* self, void* data, size_t size );
int SPIDevice_read( const SPIDevice* self, void* data, size_t size );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
