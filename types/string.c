/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

/*----------------------------------------------------------------------------*/

#include <types/string.h>

/*----------------------------------------------------------------------------*/

void String_ctor( String* self, char chars[], size_t size )
{
	self->chars = chars;
	self->length = size;
}

/*----------------------------------------------------------------------------*/