/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <menu/menu.h>
#include <menu/menu_states.h>
#include <types/string.h>
#include <gui/displayobjects/text.h>
#include <gui/displayobjects/mask.h>
#include <gui/displayobjects/bitmap.h>
#include <gui/display.h>

#include <gui/images/bottom_enter_escape.h>
#include <gui/images/bottom_arrows.h>
#include <gui/images/bottom_left_arrow.h>
#include <gui/images/bottom_right_arrow.h>


#include <io/speed_meter.h>

/*----------------------------------------------------------------------------*/

#define ICON_PADDING 3

state_t nextstate;
static const String* statetext;
static const u8_t* stateimage;
state_func_t pStateFunc;
u8_t i;
state_t state;            // helds the current state, according to "menu.h"

void Menu_ctor( Menu* self )
{
	Keyboard_ctor( &self->keyboard );
	self->states = get_menu_state();
	self->stateRelations = get_menu_relations();
	
    // Initial state variables
    state = nextstate = ST_MENU;
    statetext = self->states[0].pText;
	stateimage = self->states[0].bitmap;
	pStateFunc = self->states[0].pFunc;	
    //pStateFunc = NULL;	
}

/*----------------------------------------------------------------------------*/

Mask menuMask;

void Menu_clear_all( Menu* self )
{
	Mask_ctor( &menuMask, 1, self->iconY - 6, 
			  		  DISPLAY_VISIBLE_WIDTH - 1, self->iconHeight + 6,
					  0, FALSE );
	
	Mask_draw( &menuMask );
	
	// Clear gauge top number	
	Mask_ctor( &menuMask, self->iconX + self->iconWidth - 1, 0, 
			  		  22, 15,
					  0, FALSE );
	
	Mask_draw( &menuMask );	
}

/*----------------------------------------------------------------------------*/

void Menu_clear_text( Menu* self )
{
	Mask_ctor( &menuMask, self->iconX + self->iconWidth, self->iconY - 4, 
			  		  DISPLAY_VISIBLE_WIDTH - self->iconX - self->iconWidth, self->iconHeight + 4,
					  0, FALSE );
	
	Mask_draw( &menuMask );
	
	// Clear gauge top number	
	Mask_ctor( &menuMask, self->iconX + self->iconWidth - 1, 0, 
			  		  22, 15,
					  0, FALSE );
	
	Mask_draw( &menuMask );			
}

/*----------------------------------------------------------------------------*/

extern Rtc rtc;

void Menu_draw_icon( Menu* self )
{
	Bitmap bitmap;
	Bitmap_ctor( &bitmap, self->iconX, self->iconY, self->iconWidth, self->iconHeight, self->currentState->bitmap, FALSE );
	Bitmap_draw( &bitmap );
}

/*----------------------------------------------------------------------------*/

void Menu_draw_bottom_line( Menu* self, BottomLineType type )
{
	const u8_t* image;
	Bitmap bitmap;
	switch( type )
	{
		case BOTTOM_ENTER_ESCAPE:
			image = bottom_enter_escape;
			break;
		
		case BOTTOM_ARROWS:
			image = bottom_arrows;
			break;
		case BOTTOM_LEFT_ARROW:
			image = bottom_left_arrow;
			break;
		
		case BOTTOM_RIGHT_ARROW:
			image = bottom_right_arrow;
			break;			
		default:
			image = bottom_enter_escape;
			break;
	}
	Bitmap_ctor( &bitmap, 0, 59, DISPLAY_VISIBLE_WIDTH , 8, image, FALSE );
	Bitmap_draw_partial( &bitmap, 0, 3, 98, 8 );
}

/*----------------------------------------------------------------------------*/

void Menu_reset( Menu* self )
{
    state = nextstate = ST_MENU;
    statetext = self->states[0].pText;
	stateimage = self->states[0].bitmap;
	pStateFunc = self->states[0].pFunc;		
}

void Menu_draw( Menu* self, const u8_t* image, const String* string )
{
	Text text;
	if( state != ST_MENU )
	{			
		if( image != NULL )
		{
			Menu_draw_icon( self );
		}
		else
		{
			Mask_ctor( &menuMask, self->iconX, self->iconY, self->iconWidth, self->iconHeight, 0, FALSE );
			Mask_draw( &menuMask );
		}
//		Mask_ctor( &mask, self->iconX + self->iconWidth, self->iconY, 64, 32, 0, FALSE );
//		Mask_draw( &mask );

		Menu_clear_text( self );
	
		Text_ctor( &text, self->iconX + self->iconWidth + ICON_PADDING, 
						  self->iconY + 10,
						  (String*)statetext, 0, FALSE, ms_sans_serif, 11, FALSE );
		
		Text_draw( &text );	
		
		if( Settings_get_instance()->speedDisplayMode == SPEED_DISPLAY_MODE_NUMERIC )
		{
			String string = {STRING("km/h")};
			Text_ctor( &text, 53, 46, &string, 0, FALSE, ms_sans_serif, 11, FALSE );		
			Text_draw( &text );		
		}
	}
	else
	{
		if( Settings_get_instance()->speedDisplayMode == SPEED_DISPLAY_MODE_GAUGE )
		{
			Bitmap bitmap;
			Bitmap_ctor( &bitmap, 0, 0, 98, 64, image, FALSE );
			Bitmap_draw( &bitmap );
			SpeedMeter_draw_gauge_numbers( SpeedMeter_get_instance() );							
			String string = {STRING("km/h")};
			Text_ctor( &text, 53, 46, &string, 0, FALSE, ms_sans_serif, 11, FALSE );			
		}
		else
		{
			Display_clear( Display_get_instance() );
			Menu_draw_bottom_line( self, BOTTOM_ENTER_ESCAPE );
			String string = {STRING("km/h")};
			Text_ctor( &text, 68, 28, &string, 0, FALSE, ms_sans_serif, 11, FALSE );				
			//Menu_clear_all( self );
		}
		Text_draw( &text );
		Rtc_draw( &rtc, TRUE );	
		SpeedMeter_draw( TRUE, TRUE );			
		Settings_save_flash( Settings_get_instance());
	}
}

/*----------------------------------------------------------------------------*/

state_t Menu_state_machine( Menu* self, state_t state, key_t stimuli)
{
    state_t nextstate = state;    // Default stay in same state
    u8_t i;

    for (i=0; self->stateRelations[i].state; i++)
    {
        if (self->stateRelations[i].state == state && self->stateRelations[i].input == stimuli)
        {
            // This is the one!
            nextstate = self->stateRelations[i].nextstate;
            break;
        }
    }

    return nextstate;
}

/*----------------------------------------------------------------------------*/

state_t Menu_process( Menu* self, bool_t selfCall )
{
//		Text text;
//		Mask mask;
	    key_t input;
		// Plain menu text
		if (statetext)
		{
			//LCD_puts_f(statetext, 1);
			//LCD_Colon(0);
			
			//String_ctor( &string, (char*)statetext, 7 );
			
			Menu_draw( self, stateimage, statetext );

//			Mask_ctor( &mask, 10, 10, 40, 15, 0, FALSE );
//			Mask_draw( &mask );			
//			
//			Text_ctor( &text, 10, 10, (String*)statetext, 0, FALSE, ms_sans_serif, 11 );
//			Text_draw( &text );			
			statetext = NULL;
		}

		input = Keyboard_get_key( &self->keyboard );
		//input = getkey();           // Read buttons

		if (pStateFunc)
		{
			// When in this state, we must call the state function
			if( selfCall == TRUE || input != KEY_NULL )
			{
				nextstate = pStateFunc( self, input);
			}
		}
		else if (input != KEY_NULL)
		{
			// Plain menu, clock the state machine
			nextstate = Menu_state_machine( self, state, input);
		}

		if (nextstate != state)
		{
			state = nextstate;
			for (i=0; self->states[i].state; i++)
			{
				if (self->states[i].state == state)
				{
					self->currentState = &self->states[i];
					statetext =  self->states[i].pText;
					stateimage = self->states[i].bitmap;
					pStateFunc = self->states[i].pFunc;
					break;
				}
			}

			Menu_process( self, TRUE);
		}
		
		return state;
}

/*----------------------------------------------------------------------------*/
