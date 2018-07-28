/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/drivers/PCD_8544_driver.h>

static DisplayDriver displayDriverInstance;
DisplayDriver* displayDriver = NULL;

#define VERTICAL_BLOCK_SIZE 8
#define VERTICAL_BLOCKS_NUM 6

/*----------------------------------------------------------------------------*/

static void DisplayDriver_ctor( DisplayDriver* self, enum AddressingMode mode )
{
	self->addressingMode = mode;
	SPIDevice_ctor( &self->iodevice, OP_MODE_MASTER, 1000000, DATA_LENGTH_8,
				   CLK_POL_INACTIVE_LOW, WIRING_MODE_3_WIRE, 1);
}

/*----------------------------------------------------------------------------*/

DisplayDriver* DisplayDriver_get_instance()
{
	if( displayDriver == NULL )
	{
		DisplayDriver_ctor( &displayDriverInstance, ADDRESSING_MODE_VERTICAL );
		displayDriver = &displayDriverInstance;
	}
	
	return displayDriver;
}

/*----------------------------------------------------------------------------*/

void DisplayDriver_put_pixel( const DisplayDriver* self, const Matrix* data, coord_t x, coord_t y )\
{
	u_t driverY = (u_t)(y / VERTICAL_BLOCK_SIZE);
	u_t driverX = (u_t)x;
	
	u8_t dataToDisplay = 0;

	for( i_t i = 0; i < VERTICAL_BLOCK_SIZE; i++ )
	{
		u8_t* ptrData =	Matrix_use_data( data, u8_t, driverX, driverY * VERTICAL_BLOCK_SIZE + i );		
		dataToDisplay |= (u8_t)((*ptrData == 0) ? 0 : 1) << ( 7 - i );
	}
		
	SPIDevice_write( &self->iodevice, &dataToDisplay, 1 );
}

/*----------------------------------------------------------------------------*/

void DisplayDriver_put_all_pixels( const DisplayDriver* self, const Matrix* data, size_t size )
{
	SPIDevice_write( &self->iodevice, NULL, 1 );
}

/*----------------------------------------------------------------------------*/

//static void DisplayDriver_assemble_command