/*******************************************************************************

    Buffer type
    ============

  Description: Universal buffer type
   

    Daniel Verner
    vernerd@gmail.com

  *****************************************************************************/

#ifndef _MATRIX_
#define _MATRIX_

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

typedef struct Matrix Matrix;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

struct Matrix {
	u_t sizex;
	u_t sizey;	
	void* buffer;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

void Matrix_ctor( Matrix* self, void* buffer, u_t sizex, u_t sizey );
void Matrix_dtor( Matrix* self );

#define Matrix_use_data( self, type, x, y) \
						(type*)&( ( (type*)( ( (Matrix*)self )->buffer ) )[x * ((Matrix*)self)->sizey + y])

#define Matrix_get_data( self, type, x, y) \
						(const type*)&( ( (type*)( ( (Matrix*)self )->buffer ) )[x * ((Matrix*)self)->sizey + y])

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif