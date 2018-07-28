/*******************************************************************************

    Vector type
    ==============================
   

    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#include "vector.h"
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------------*/
/* Vector type (can contain elements with same type, for example integers,
   structures etc.)                                                           */
/*----------------------------------------------------------------------------*/

void ctor_Vector ( Vector* self, u_t size)
{
	ctor_Buffer( &self->base, size );
	self->capacity = size;
	self->usedBytes = 0;
}

/*----------------------------------------------------------------------------*/

void dtor_Vector ( Vector* self )
{
    dtor_Buffer( &self->base );
    self->capacity = 0;
	self->usedBytes = 0;	
}

/*----------------------------------------------------------------------------*/

/* Append element to the vector */
void append_Vector(Vector* self, u_t size, const void* append)
{
	void* buffer;
	char* charBuffer;
	const char* src = (const char*) append;

	if ((self->capacity - self->usedBytes ) < size)
	{
		buffer = malloc(self->usedBytes + size);
		memcpy(buffer, self->base.buffer, self->usedBytes);
		free(self->base.buffer);
		self->base.buffer = buffer;
		self->capacity = self->usedBytes + size;
		self->base.size = self->capacity;		
	}
	charBuffer = ( char* ) use_data_Buffer(&self->base);
//	charBuffer += get_size_Buffer(&self->base);
	charBuffer += self->usedBytes;

	for (; size--; )
	{
		//self->base.size++;
		*charBuffer++ = *src++;
		self->usedBytes++;
	}
	return;
}

/*----------------------------------------------------------------------------*/
