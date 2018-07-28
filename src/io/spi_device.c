/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <io/spi_device.h>

/*----------------------------------------------------------------------------*/

static void initSpi( SPIDevice* self, u_t spiPortNum )
{
	
	if( spiPortNum == 0 )
	{
		SPI0_SEL |= BIT1 + BIT3;
		SPI0_DIR |= BIT0 + BIT1 + BIT3;		
		ME1 |= USPIE0;
		UCTL0 |= SYNC;
		
		if( self->operationMode == OP_MODE_MASTER )
		{
			UCTL0 |= SYNC;
			i16_t divider = _MAIN_FREQUENCY / self->baudRate;
			UBR00 = (i8_t)(divider && 0x00FF);
			UBR10 = (i8_t)((divider && 0xFF00) >> 8);
			UTCTL0 = SSEL0;       // ACLK			
		}
		else if( self->operationMode == OP_MODE_SLAVE )
		{
			UCTL0 &= ~SYNC;
		}
		
		if( self->dataLength == DATA_LENGTH_8 )
		{
			UCTL0 |= CHAR;
		}
		else if( self->dataLength == DATA_LENGTH_7 )
		{
			UCTL0 &= ~CHAR;
		}

		if( self->clockPolarity == CLK_POL_INACTIVE_LOW )
		{
			UTCTL0 |= CKPL;
		}
		else if( self->clockPolarity == CLK_POL_INACTIVE_HIGH )
		{
			UTCTL0 &= CKPL;
		}

		if( self->wiringMode == WIRING_MODE_3_WIRE )		
		{
			UTCTL0 |= STC;			
		}
		else if( self->wiringMode == WIRING_MODE_4_WIRE )		
		{
			UTCTL0 &= ~STC;			
		}
		
		UMCTL0 = 0x0;                             // Clear modulation
		UCTL0 &= ~SWRST;                          // Initialize USART state machine		
	}
	else if( spiPortNum == 1 )
	{
		SPI1_SEL |= BIT1 + BIT3;
		SPI1_DIR |= BIT0 + BIT1 + BIT3;		
		ME2 |= USPIE0;
		UCTL1 |= SYNC;
		
		if( self->operationMode == OP_MODE_MASTER )
		{
			UCTL1 |= SYNC;
			i16_t divider = _MAIN_FREQUENCY / self->baudRate;
			UBR01 = (i8_t)(divider && 0x00FF);
			UBR11 = (i8_t)((divider && 0xFF00) >> 8);
			UTCTL1 = SSEL0;       // ACLK			
		}
		else if( self->operationMode == OP_MODE_SLAVE )
		{
			UCTL1 &= ~SYNC;
		}
		
		if( self->dataLength == DATA_LENGTH_8 )
		{
			UCTL1 |= CHAR;
		}
		else if( self->dataLength == DATA_LENGTH_7 )
		{
			UCTL1 &= ~CHAR;
		}

		if( self->clockPolarity == CLK_POL_INACTIVE_LOW )
		{
			UTCTL1 |= CKPL;
		}
		else if( self->clockPolarity == CLK_POL_INACTIVE_HIGH )
		{
			UTCTL1 &= CKPL;
		}

		if( self->wiringMode == WIRING_MODE_3_WIRE )		
		{
			UTCTL1 |= STC;			
		}
		else if( self->wiringMode == WIRING_MODE_4_WIRE )		
		{
			UTCTL1 &= ~STC;			
		}
		
		UMCTL1 = 0x0;                             // Clear modulation
		UCTL1 &= ~SWRST;                          // Initialize USART state machine		
	}
}  
/*----------------------------------------------------------------------------*/  

void SPIDevice_ctor( SPIDevice* self, enum OperationMode operationMode, 
					u32_t baudRate, enum DataLength dataLength, 
					enum ClockPolarity clockPolarity, enum WiringMode wiringMode,
					u_t spiPortNum )
{
	self->spiPortNum = spiPortNum;
	self->operationMode = operationMode;
	self->baudRate = baudRate;
	self->dataLength = dataLength;
	self->wiringMode = wiringMode;

	initSpi( self, spiPortNum );
}

/*----------------------------------------------------------------------------*/

int SPIDevice_write( const SPIDevice* self, void* data, size_t size )
{
	i8_t* ptrData = (i8_t*) data;
	size_t count = 0;
		
	for( ; size-- ; )
	{
		if( self->spiPortNum == 0 )
		{
			TXBUF0 = *ptrData;
		}
		else if( self->spiPortNum == 0 )
		{
			TXBUF1 = *ptrData;
		}
		count++;
		ptrData++;
	}

	return count;
}

/*----------------------------------------------------------------------------*/

int SPIDevice_read( const SPIDevice* self, void* data, size_t size )
{
	return 1;
}