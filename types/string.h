/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _STRING_
#define _STRING_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>

/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma unmanaged
#endif

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

typedef struct String String;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

	
/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

#define STRING(str) str, sizeof(str)-1

struct String {
	char* chars;
	size_t length;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void String_ctor( String* self, char chars[], size_t size );

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
