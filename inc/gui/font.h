/*******************************************************************************
    Daniel Verner
    vernerd@gmail.com
  *****************************************************************************/

#ifndef _FONT_
#define _FONT_

/*----------------------------------------------------------------------------*/
/* ### INCLUDES ### */

#include <types/types.h>
//#include <gui/available_fonts.h>

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

typedef struct Font Font;

/*----------------------------------------------------------------------------*/
/* ### FORWARD DECLARATIONS - END ### */
/*----------------------------------------------------------------------------*/

	
/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - BEGIN ### */
/*----------------------------------------------------------------------------*/

#define FONT(fontName, fontSize) { fontName, fontSize, fontName ## _ ## fontSize ## _ ## data, fontName ## _ ## fontSize ## _ ## width, fontName ## _ ## fontSize ## _ ## height, fontName ## _ ## fontSize ## _ ## x, fontName ## _ ## fontSize ## _ ## y,  fontName ## _ ## fontSize ## _ ## yPadding, &fontName ## _ ## fontSize ## _ ## imageWidth, &fontName ## _ ## fontSize ## _ ## imageHeight }

struct Font {
	i_t fontName;
	u8_t fontSize;
	const u8_t* data;
	const u8_t* widthArray;
	const u8_t* heightArray;
	const u8_t* xArray;
	const u8_t* yArray;
	const u8_t* yPaddingArray;
	const size_t* imageWidth;
	const size_t* imageHeight;
};

/*----------------------------------------------------------------------------*/
/* ### CONSTANTS AND TYPES - END ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - BEGIN ### */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* ### FUNCTIONS - END ### */
/*----------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif
