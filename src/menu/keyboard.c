/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <menu/keyboard.h>
#include <system/settings.h>
#include <system/system.h>

key_t input;

/*----------------------------------------------------------------------------*/

bool_t keyboard_interrupt( u8_t value );

/*----------------------------------------------------------------------------*/

void Keyboard_ctor( Keyboard* self )
{
	self->input = &input;
	
	self->interruptDevice = InterruptDevice_get_instance( 1 );
	u8_t mask = KEY_ESCAPE + KEY_UP + KEY_DOWN + KEY_ENTER;
	
	InterruptDevice_set_interrupt( self->interruptDevice, mask, mask );
	InterruptDevice_set_callback( self->interruptDevice, KEY_ESCAPE, keyboard_interrupt );
	InterruptDevice_set_callback( self->interruptDevice, KEY_UP, keyboard_interrupt );
	InterruptDevice_set_callback( self->interruptDevice, KEY_DOWN, keyboard_interrupt );	
	InterruptDevice_set_callback( self->interruptDevice, KEY_ENTER, keyboard_interrupt );	
	
	*self->input = NULL;	
	
}

/*----------------------------------------------------------------------------*/

key_t Keyboard_get_key( Keyboard* self )
{
	key_t key = *self->input;
	*self->input = 0x00;
	
	return key;
}

/*----------------------------------------------------------------------------*/

bool_t keyboard_interrupt( u8_t value )
{
	key_t key = KEY_NULL;

	if( !System_wakeup() )
	{
		switch( value )
		{
			case KEY_ESCAPE:
				key = KEY_ESCAPE;
				break;
			
			case KEY_UP:
				key = KEY_UP;		
				break;
				
			case KEY_DOWN:
				key = KEY_DOWN;		
				break;
			
			case KEY_ENTER:
				key = KEY_ENTER;		
				break;
		}
	}
	else
	{
		key = KEY_DUMMY;
	}

	input = key;
	
	return FALSE;
}
