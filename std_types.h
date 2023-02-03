#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Boolean Data Type */
typedef unsigned char boolean;

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define LOGIC_HIGH        (1u)
#define LOGIC_LOW         (0u)

#define NULL_PTR    ((void*)0) ; 


typedef unsigned char   uint_8 ;
typedef char            sint_8 ;

typedef  unsigned short uint_16 ;
typedef  short          sint_16 ;

typedef  unsigned int   uint_32 ;
typedef  int            sint_32 ;

typedef unsigned long long    uint_64;        
typedef signed long long      sint_64;         
typedef float                 float_32;
typedef double                float_64;
#endif /* STD_TYPE_H_ */
