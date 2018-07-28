#ifndef __TYPES__TYPES_H_INCLUDED__
#define __TYPES__TYPES_H_INCLUDED__

/*----------------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------------*/

/* COMPILER SPECIFIC CONFIGURATIONS */

/*----------------------------------------------------------------------------------------------*/

#ifndef NULL
   #define NULL   0 
#endif

#ifndef TRUE
   #define TRUE   1
#endif

#ifndef FALSE
   #define FALSE   0
#endif

#define betole16( val ) ( ( ( ( u16_t )( val ) & 0xff00) >> 8) | \
                          ( ( ( u16_t )( val ) & 0x00ff) << 8 ) )

#define round( val )( ( val - floor(val) >= (f32_t)0.5 ) ? ceil(val) : floor(val) )

/*----------------------------------------------------------------------------------------------*/

      typedef double                 f64_t;
      typedef float                  f32_t;
      typedef unsigned long long int u64_t;
      typedef signed long long int   i64_t;
      typedef unsigned long int      u32_t;
      typedef signed long int	       i32_t;
      typedef unsigned int           u16_t;
      typedef signed int	          i16_t;
      typedef unsigned char          u8_t;
      typedef signed char 	          i8_t;
      typedef int                    i_t;
      typedef unsigned int           u_t;
      typedef i_t			             bool_t;
      
#define BYTE_SIZE_OF_CHAR   1


/*----------------------------------------------------------------------------------------------*/

typedef struct Word {   
   u_t lo : 8;
   u_t hi : 8;
} Word;

/*----------------------------------------------------------------------------------------------*/

typedef struct DWord {   
   Word lo;
   Word hi;
} DWord;

/*----------------------------------------------------------------------------------------------*/

typedef u_t size_t;

#endif
