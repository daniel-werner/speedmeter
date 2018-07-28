/*******************************************************************************

    Buffer type
    ============

  Description: Universal buffer type
   

    Daniel Verner
    vernerd@gmail.com

  *****************************************************************************/

#include "matrix.h"
#include <stdlib.h>

/*----------------------------------------------------------------------------*/
/* Matrix type                                                                */
/*----------------------------------------------------------------------------*/

void Matrix_ctor( Matrix* self, void* buffer, u_t sizex, u_t sizey )
{
	self->sizex = sizex;
	self->sizey = sizey;	
	self->buffer = buffer;
}

/*----------------------------------------------------------------------------*/

void Matrix_dtor( Matrix* self )
{
	self->buffer = NULL;
	self->sizex = 0;
	self->sizey = 0;	
}

/*----------------------------------------------------------------------------*/
