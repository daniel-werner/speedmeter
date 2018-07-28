/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <io/interrupt_device.h>

/*----------------------------------------------------------------------------*/

static InterruptDevice p1InterruptDevice;
static InterruptDevice p2InterruptDevice;

InterruptDevice* ptrP1InterruptDevice = NULL;
InterruptDevice* ptrP2InterruptDevice = NULL;

/*----------------------------------------------------------------------------*/

void InterruptDevice_ctor( InterruptDevice* self, u8_t portNum )
{
	self->portNum = portNum;
	
	InterruptDevice_set_interrupt( self, self->interruptMask, self->interruptEdgeMask );
}

/*----------------------------------------------------------------------------*/

InterruptDevice* InterruptDevice_get_instance( u8_t portNum )
{
	InterruptDevice* ptrInterruptDevice = NULL;
	
	switch( portNum )
	{
		case 1:
			if( ptrP1InterruptDevice == NULL )
			{
				InterruptDevice_ctor( &p1InterruptDevice, portNum );
				ptrP1InterruptDevice = &p1InterruptDevice;
			}
			ptrInterruptDevice = ptrP1InterruptDevice;
			break;
		case 2:
			if( ptrP2InterruptDevice == NULL )
			{
				InterruptDevice_ctor( &p2InterruptDevice, portNum );
				ptrP2InterruptDevice = &p2InterruptDevice;
			}
			ptrInterruptDevice = ptrP2InterruptDevice;
			break;
		
	}
	
	return ptrInterruptDevice;
}

/*----------------------------------------------------------------------------*/

void InterruptDevice_set_interrupt( InterruptDevice* self,
									u8_t interruptMask, u8_t interruptEdgeMask )
{
	switch( self->portNum )
	{
		case 1:
			_DINT();
			P1IFG &= ~interruptMask;
			P1SEL &= ~interruptMask;
			P1DIR &= ~interruptMask;
			P1IES |= interruptEdgeMask; 
			P1IE |= interruptMask;
			_EINT();
			break;
		case 2:
			_DINT();
			P1IFG &= ~interruptMask;
			P1SEL &= ~interruptMask;
			P1DIR &= ~interruptMask;
			P1IES |= interruptEdgeMask;
			P1IE |= interruptMask;
			_EINT();		
			break;
	}
}

/*----------------------------------------------------------------------------*/

void InterruptDevice_set_callback( InterruptDevice* self,
									u8_t interruptMask, func_interrupt_callback_t callback )
{
	if( callback != NULL )
	{
		switch( interruptMask )
		{
			case 0x01:
				self->callbacks[0] = callback;
				break;
			case 0x02:
				self->callbacks[1] = callback;			
				break;
			case 0x04:
				self->callbacks[2] = callback;			
				break;
			case 0x08:
				self->callbacks[3] = callback;				
				break;
			case 0x10:
				self->callbacks[4] = callback;			
				break;
			case 0x20:
				self->callbacks[5] = callback;			
				break;
			case 0x40:
				self->callbacks[6] = callback;			
				break;
			case 0x80:
				self->callbacks[7] = callback;			
				break;			
		}
	}
}

/*----------------------------------------------------------------------------*/

#pragma vector=PORT1_VECTOR
__interrupt void p1_interrupt (void)
{
	_BIC_SR_IRQ(CPUOFF); 
	u8_t value = NULL;
	func_interrupt_callback_t callback;

		switch( P1IFG )
		{
			case 0x01:
				callback = p1InterruptDevice.callbacks[0];
				value = 0x01;
				break;
			case 0x02:
				callback = p1InterruptDevice.callbacks[1];
				value = 0x02;
				break;
			case 0x04:
				callback = p1InterruptDevice.callbacks[2];
				value = 0x04;
				break;
			case 0x08:
				callback = p1InterruptDevice.callbacks[3];
				value = 0x08;
				break;
			case 0x10:
				callback = p1InterruptDevice.callbacks[4];
				value = 0x10;
				break;
			case 0x20:
				callback = p1InterruptDevice.callbacks[5];
				value = 0x20;
			case 0x40:
				callback = p1InterruptDevice.callbacks[6];
				value = 0x40;
			case 0x80:
				callback = p1InterruptDevice.callbacks[7];
				value = 0x80;
		}

	if( value != NULL )
	{
		P1IFG &= ~value;	
	}
	else
	{
		P1IFG = 0x00;
	}		
		
	if( callback != NULL )
	{
		callback( value );
	}
}

/*----------------------------------------------------------------------------*/

#pragma vector=PORT2_VECTOR
__interrupt void p2_interrupt (void)
{
	u8_t value = NULL;
	func_interrupt_callback_t callback;
	
		switch( P2IFG )
		{
			case 0x01:
				callback = p2InterruptDevice.callbacks[0];
				value = 0x01;
				break;
			case 0x02:
				callback = p2InterruptDevice.callbacks[1];
				value = 0x02;
				break;
			case 0x04:
				callback = p2InterruptDevice.callbacks[2];
				value = 0x04;
				break;
			case 0x08:
				callback = p2InterruptDevice.callbacks[3];
				value = 0x08;
				break;
			case 0x10:
				callback = p2InterruptDevice.callbacks[4];
				value = 0x10;
				break;
			case 0x20:
				callback = p2InterruptDevice.callbacks[5];
				value = 0x20;
			case 0x40:
				callback = p2InterruptDevice.callbacks[6];
				value = 0x40;
			case 0x80:
				callback = p2InterruptDevice.callbacks[7];
				value = 0x80;
		}

	if( callback != NULL )
	{
		if( callback( value ) )
		{
			_BIC_SR_IRQ(CPUOFF); // Wake up processor, update screen				
		};
	}
	
	if( value != NULL )
	{
		P2IFG &= ~value;	
	}
	else
	{
		P2IFG = 0x00;
	}
	
}