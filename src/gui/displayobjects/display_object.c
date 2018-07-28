/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/displayobjects/display_object.h>
#include <gui/display.h>

/*----------------------------------------------------------------------------*/

void DisplayObject_ctor( DisplayObject* self )
{
	//dtor_Vector( (Vector*)&self->pixels );
	//ctor_Vector( (Vector*)&self->pixels, 0 );
	self->doubleBuffering = TRUE;
}

/*----------------------------------------------------------------------------*/

int DisplayObject_render( const DisplayObject* self )
{
	Display* display = Display_get_instance();
	i_t retVal;
	
	retVal =  Display_render( display, (DisplayObject*)self );
	
	dtor_Vector( (Vector*)&self->pixels );
	return retVal;
}

/*----------------------------------------------------------------------------*/

int DisplayObject_redraw( const DisplayObject* self, coord_t x1, coord_t x2 )
{
	Display* display = Display_get_instance();
	i_t retVal;
	
	retVal =  Display_redraw( display, x1, x2 );
	
	dtor_Vector( (Vector*)&self->pixels );
	return retVal;
}

/*----------------------------------------------------------------------------*/

bool_t DisplayObject_add_pixel( const DisplayObject* self, Pixel* pix )
{
	Display* display = Display_get_instance();

	if( self->doubleBuffering )
	{
		append_Vector( (Vector*)&self->pixels, sizeof(Pixel), pix );
	}
	else
	{
		Display_set_pixel( display, pix );		
	}
	
	return TRUE;
}

/*----------------------------------------------------------------------------*/