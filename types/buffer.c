/*******************************************************************************

    Buffer type
    ============

  Description: Universal buffer type
   

    Daniel Verner
    vernerd@gmail.com

  *****************************************************************************/

#include "buffer.h"
#include <stdlib.h>
#include <assert.h>

/*----------------------------------------------------------------------------*/
/* Buffer type                                                                */
/*----------------------------------------------------------------------------*/

void ctor_Buffer( Buffer* self, u_t size )
{
	self->buffer = NULL;
	self->size = size;
	self->buffer = malloc(size);
	assert(self->buffer);
}

/*----------------------------------------------------------------------------*/


void dtor_Buffer( Buffer* self )
{
	free( self->buffer );
	self->buffer = NULL;
	self->size = 0;
}

/*----------------------------------------------------------------------------*/

/* Returns the buffer pointer, required for reading data from the buffer */
const void* get_data_Buffer( Buffer* self )
{
	return self->buffer;
}

/*----------------------------------------------------------------------------*/

/* Returns the buffer size */
u_t get_size_Buffer( const Buffer* self)
{
	return self->size;
}

/*----------------------------------------------------------------------------*/

/* Returns the buffer pointer, required for using the buffer */
void* use_data_Buffer( Buffer* self )
{
	return self->buffer;
}

/*----------------------------------------------------------------------------*/
