/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/drivers/PCF_8548_driver.h>
#include <gui/display.h>
#include <string.h>

static DisplayDriver displayDriverInstance;
DisplayDriver* displayDriver = NULL;

#define PACK_SIZE 8

#define VERTICAL_BLOCK_SIZE 8
#define VERTICAL_BLOCKS_NUM 6

/*----------------------------------------------------------------------------*/

static void DisplayDriver_reset_display( const DisplayDriver* self );

/*----------------------------------------------------------------------------*/

static void DisplayDriver_ctor( DisplayDriver* self, enum AddressingMode mode )
{
	self->addressingMode = mode;
	DisplayDriver_reset_display( self );
	
	I2cDevice_ctor( &self->iodevice, 0x3C, OP_MODE_MASTER, I2C_COMM_SPEED_400 );	
	
	//u8_t com[] = {0x00, 0x21, 0x16, 0xEA, 0x30, 0x0C };
	
	u8_t com[] = { CONTROL_MULTI_COMMAND,
				   FUNCTION_SET + H, 
				   BIAS_SYSTEM + BS0 + BS1 + BS2 , 
//				   BIAS_SYSTEM + BS1 + BS2 , 
				   SET_VOP + VOP6 + VOP2,
//				   SET_VOP + VOP6 + VOP5 + VOP3 + VOP1, 				   
				   FUNCTION_SET + MX, 
				   DISPLAY_CONTROL + D };
	
	
	I2cDevice_write( &self->iodevice, com, 6 );
	DisplayDriver_clear_display( self );
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

void DisplayDriver_clear_display( const DisplayDriver* self )
{
	u8_t coord[] = {0x00, 0x80, 0x40};
	
	I2cDevice_write( &self->iodevice, coord, 3 );	
	
	i_t count = 65;
	while(count--)
	{
		u8_t data[] = { 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		I2cDevice_write( &self->iodevice, data, 14 );
	}	
}

/*----------------------------------------------------------------------------*/

static void DisplayDriver_reset_display( const DisplayDriver* self )
{
	for( i_t j = 0; j < 2; j++ )
	{
		I2C_OUT &= ~LCD_RESET;
		for( i_t i = 0; i < 50 ; i++ );
		I2C_OUT |= LCD_RESET;	
	}
}

/*----------------------------------------------------------------------------*/

static void DisplayDriver_set_position( const DisplayDriver* self, coord_t x, coord_t y )
{
	x |= SET_X_ADDRESS;
	y |= SET_Y_ADDRESS;
	
	u8_t coord[] = {0x00, x, y};
	
	I2cDevice_write( &self->iodevice, coord, 3 );	
}

/*----------------------------------------------------------------------------*/

void DisplayDriver_put_pixel( const DisplayDriver* self, const Matrix* data, coord_t x, coord_t y )\
{
	u_t driverY = (u_t)(y / VERTICAL_BLOCK_SIZE);
	u_t driverX = (u_t)x;
	
	u8_t dataToDisplay = 0;

	dataToDisplay = *Matrix_use_data( data, u8_t, driverX, driverY );

	u8_t outData[] = { 0x40, dataToDisplay };
	DisplayDriver_set_position( self, driverX, driverY );
	
	I2cDevice_write( &self->iodevice, outData, 2 );
}

/*----------------------------------------------------------------------------*/

#define MAX_WRITE_BUFFER_SIZE 250

void DisplayDriver_put_all_pixels( const DisplayDriver* self, const Matrix* data, size_t size )
{
	
	DisplayDriver_put_pixels( self, data, 0,  DISPLAY_WIDTH, DISPLAY_BUFFER_SIZE );
//	u8_t com[] = { CONTROL_SINGLE_COMMAND,
//			 		FUNCTION_SET + MX + VERTICAL };
//	
//	I2cDevice_write( &self->iodevice, com, 2 );	
//	
//	DisplayDriver_set_position( self, 0, 0 );
//	
//	u8_t writeBuf[MAX_WRITE_BUFFER_SIZE + 1];
//	
//	i_t partsNumber = (i_t)(size / MAX_WRITE_BUFFER_SIZE );
//	if( size % MAX_WRITE_BUFFER_SIZE > 0 )
//		partsNumber++;
//	
//	for( i_t i = 0; i < partsNumber; i++ )
//	{
//		i_t pos = i * MAX_WRITE_BUFFER_SIZE;
//		i_t count = MAX_WRITE_BUFFER_SIZE;
//		if( pos + count > size )
//		{
//			count = size - pos;
//		}
//		
//		u8_t* buffer = (u8_t*)data->buffer;
//
//		writeBuf[0] = CONTROL_MULTI_DATA;		
//		memcpy( &writeBuf[1], &buffer[pos], count );
//		I2cDevice_write( &self->iodevice, writeBuf, count + 1 );
//	}
//	
//	com[0] = CONTROL_SINGLE_COMMAND;
//	com[1] = FUNCTION_SET + MX;
//	
//	I2cDevice_write( &self->iodevice, com, 2 );		
}

/*----------------------------------------------------------------------------*/

void DisplayDriver_put_pixels( const DisplayDriver* self, const Matrix* data, coord_t x1, coord_t x2, size_t size )
{
	u_t offsetX = x1 * 9;
	DisplayDriver_set_position( self, x1, 0 );	
	
	u8_t com[] = { CONTROL_SINGLE_COMMAND,
			 		FUNCTION_SET + MX + VERTICAL };
	
	I2cDevice_write( &self->iodevice, com, 2 );	
	
	u8_t writeBuf[MAX_WRITE_BUFFER_SIZE + 1];
	
	if( size > MAX_WRITE_BUFFER_SIZE )
	{
		i_t partsNumber = (i_t)(size / MAX_WRITE_BUFFER_SIZE );
		if( size % MAX_WRITE_BUFFER_SIZE > 0 )
			partsNumber++;
		
		for( i_t i = 0; i < partsNumber; i++ )
		{
			i_t pos = offsetX + i * MAX_WRITE_BUFFER_SIZE;
			i_t count = MAX_WRITE_BUFFER_SIZE;
			if( pos + count > offsetX + size )
			{
				count = offsetX + size - pos;
			}
			
			u8_t* buffer = (u8_t*)data->buffer;
	
			writeBuf[0] = CONTROL_MULTI_DATA;		
			memcpy( &writeBuf[1], &buffer[pos], count );
			I2cDevice_write( &self->iodevice, writeBuf, count + 1 );
		}
	}
	else
	{
		u8_t* buffer = (u8_t*)data->buffer;
		writeBuf[0] = CONTROL_MULTI_DATA;		
		memcpy( &writeBuf[1], &buffer[offsetX], size );
		I2cDevice_write( &self->iodevice, writeBuf, size + 1 );		
	}
	
	com[0] = CONTROL_SINGLE_COMMAND;
	com[1] = FUNCTION_SET + MX;
	
	I2cDevice_write( &self->iodevice, com, 2 );		
}

/*----------------------------------------------------------------------------*/

void Display_driver_standby( const DisplayDriver* self )
{
	u8_t com[] = { CONTROL_SINGLE_COMMAND,
				   FUNCTION_SET + PD };
	
	
	I2cDevice_write( &self->iodevice, com, 2 );	
}

/*----------------------------------------------------------------------------*/

void Display_driver_wakeup( const DisplayDriver* self )
{
	u8_t com[] = { CONTROL_SINGLE_COMMAND,
				   FUNCTION_SET + MX };
	
	
	I2cDevice_write( &self->iodevice, com, 2 );		
}