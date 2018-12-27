#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "ANSI_ColorCode.h"
#include <stdbool.h>

extern unsigned char debug_level; // Manage debug_level globally

	// static unsigned char debug_level;
#if debug_level
	#error please declear [debug_level] in your .c file for grade-debugging
	// copy the line below to your .c file
#endif


#ifdef DEBUG
	#include <stdio.h>
	#define DBG0(_x)	((debug_level&(1<<0))?(void)(_x):(void)0)
	#define DBG1(_x)	((debug_level&(1<<1))?(void)(_x):(void)0)
	#define DBG2(_x)	((debug_level&(1<<2))?(void)(_x):(void)0)
	#define DBG3(_x)	((debug_level&(1<<3))?(void)(_x):(void)0)
	#define DBG4(_x)	((debug_level&(1<<4))?(void)(_x):(void)0)
	#define DBG5(_x)	((debug_level&(1<<5))?(void)(_x):(void)0)
	#define DBG6(_x)	((debug_level&(1<<6))?(void)(_x):(void)0)
	#define DBG7(_x)	((debug_level&(1<<7))?(void)(_x):(void)0)
	

    #define dbg_print_locate(fmt,...)		printf( "\x1B[1;35m[L] <%s>\x1B[0;35m\x1B[0;35m: L%d in \"%s\"\r\n\t"fmt"\x1B[0;39m\r\n" , __func__, __LINE__, __FILE__, ##__VA_ARGS__)
    #define dbg_print_info(tag,fmt,...)		printf( "\x1B[1;39m[i] <%s>\x1B[0;39m\x1B[0;39m%s: "fmt"\x1B[0;39m\r\n", __func__, tag, ##__VA_ARGS__)
    #define dbg_print_error(tag,fmt,...)	printf( "\x1B[1;31m[E] <%s>\x1B[0;31m\x1B[0;31m%s: "fmt"\x1B[0;39m\r\n", __func__, tag, ##__VA_ARGS__)


#else
	#define DBG0(_x)	((void)0)
	#define DBG1(_x)	((void)0)
	#define DBG2(_x)	((void)0)
	#define DBG3(_x)	((void)0)
	#define DBG4(_x)	((void)0)
	#define DBG5(_x)	((void)0)
	#define DBG6(_x)	((void)0)
	#define DBG7(_x)	((void)0)
	#define dbg_print_locate(fmt,...)		((void)0)
    #define dbg_print_info(tag,fmt,...)		((void)0)
	#define dbg_print_error(tag,fmt,...)	((void)0)
#endif

#define	DBG_L0	((unsigned char)(1<<0))
#define	DBG_L1	((unsigned char)(1<<1))
#define	DBG_L2	((unsigned char)(1<<2))
#define	DBG_L3	((unsigned char)(1<<3))
#define	DBG_L4	((unsigned char)(1<<4))
#define	DBG_L5	((unsigned char)(1<<5))
#define	DBG_L6	((unsigned char)(1<<6))
#define	DBG_L7	((unsigned char)(1<<7))
#define DBG_LN(n)	((unsigned char)(1<<n))


void Debug_LevelAdd( unsigned char level );
void Debug_LevelDel( unsigned char level );

void dbg_print_mem( void *addr, unsigned int n );
void dbg_print_bar( char *tag, int current, int start, int end );


void debug_cmd( int argc, char **argv );
/*
#ifdef DEBUG
	#define dbg_info_print(__VA_ARG__)	printf("[D] Function:%s(L%d in %s)\r\n\t",__FUNCTION__,__FILE__,__LINE__,)
#else
	#define dbg_info_print	((void*)0)
#endif
*/

#endif

