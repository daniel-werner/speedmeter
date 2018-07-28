/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <gui/displayobjects/rectangle.h>

#define PARENT Line
#define PARENT_CALL(arg) Line_ ## arg

/*----------------------------------------------------------------------------*/

void Rectangle_ctor( Rectangle* self, coord_t startX, coord_t startY, coord_t endX, coord_t endY, i8_t color )
{
	PARENT_CALL(ctor)( (PARENT*)self, startX, startY, endX, endY, color );
}

/*----------------------------------------------------------------------------*/

int Rectangle_draw( const Rectangle* self )
{
	Line lineTemp;
	PARENT_CALL(ctor)( (PARENT*)&lineTemp, ((PARENT*)self)->startPoint.x,
					  					   ((PARENT*)self)->startPoint.y, 
										   ((PARENT*)self)->endPoint.x, 
										   ((PARENT*)self)->startPoint.y, ((PARENT*)self)->color );
	PARENT_CALL(draw)( (PARENT*)&lineTemp );
	
	PARENT_CALL(ctor)( (PARENT*)&lineTemp, ((PARENT*)self)->endPoint.x, 
					  					   ((PARENT*)self)->startPoint.y, 
										   ((PARENT*)self)->endPoint.x, 
										   ((PARENT*)self)->endPoint.y, 
										   ((PARENT*)self)->color );
	PARENT_CALL(draw)( (PARENT*)&lineTemp );

	PARENT_CALL(ctor)( (PARENT*)&lineTemp, ((PARENT*)self)->endPoint.x, 
					  					   ((PARENT*)self)->endPoint.y, 
										   ((PARENT*)self)->startPoint.x, 
										   ((PARENT*)self)->endPoint.y, 
										   ((PARENT*)self)->color );
	PARENT_CALL(draw)( (PARENT*)&lineTemp );

	PARENT_CALL(ctor)( (PARENT*)&lineTemp, ((PARENT*)self)->startPoint.x, 
					  					   ((PARENT*)self)->endPoint.y, 
										   ((PARENT*)self)->startPoint.x, 
										   ((PARENT*)self)->startPoint.y, 
										   ((PARENT*)self)->color );
	PARENT_CALL(draw)( (PARENT*)&lineTemp );	
		
	return 1;
}