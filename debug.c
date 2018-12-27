#include "debug.h"
#include <stdlib.h>
#include <stdbool.h>

unsigned char debug_level;


///////////////////////////////////////////////////////////////////////////////////////////
// Retarget __aeabi_assert()
void __aeabi_assert (const char *expr, const char *file, int line) {
	printErr( "Assert Failed!", "\"%s\"\r\n\tFile:%s\r\n\tLine:%d", expr, file, line );
	
	abort();
}
///////////////////////////////////////////////////////////////////////////////////////////

void Debug_LevelAdd( unsigned char level )
{
	debug_level|=(level);
//	printInf( "", "Add debug level 0x%02X.", level );
}

void Debug_LevelDel( unsigned char level )
{
	debug_level&=~(level);
//	printInf( "", "Remove debug level 0x%02X.", level );
}

bool Debug_LevelGet( unsigned char level )
{
	if( debug_level & (level) ){
		return true;
	}
	return false;
}

void printMem( char *pTag, void *addr, unsigned int n )	
{
	int i=0;
	if( !n ){
		return;
	}
	printf( "\x1B[1;32m[M] Addr=0x%X "R_Y"%s"R_F"\x1B[0;32m\r\n\t\b\b\b\x1B[4;92m | ", (unsigned int)addr, pTag );
	for( i=0; i<((n>8)?8:n); i++ ){
		printf( " %d/%X| ", i, i+8 );
	}
	for( i=0; i<((n<8)?n:(((n-1)/8+1)*8)); i++ ){
		if( i%8 == 0 ){
			printf( "\x1B[0;92m\r\n%4XH\x1B[4;32m | ", i );
		}
		if( i < n ){
			printf( "0x%02X| ", 0x000000FF & ((char *)addr)[i] );
		}else{
			printf( "    | " );
		}
	}
	printf( "\x1B[0;39m\r\n" );
}

void printMem16( char *pTag, void *addr, unsigned int n )	
{
	int i=0;
	if( !n ){
		return;
	}
	printf( "\x1B[1;32m[M] Addr=0x%X %s \x1B[0;32m\r\n\t\b\b\b\x1B[4;92m | ", (unsigned int)addr, pTag );
	for( i=0; i<((n>8)?8:n); i++ ){
		printf( "   %d/%X| ", i, i+8 );
	}
	for( i=0; i<((n<8)?n:(((n-1)/8+1)*8)); i++ ){
		if( i%8 == 0 ){
			printf( "\x1B[0;92m\r\n%4XH\x1B[4;32m | ", i );
		}
		if( i < n ){
			printf( "0x%04X| ", 0x0000FFFF & ((unsigned int *)addr)[i] );
		}else{
			printf( "      | " );
		}
	}
	printf( "\x1B[0;39m\r\n" );
}

#define BAR_LEN	(40)
void printBar( char *tag, int current, int start, int end )	
{
	int i=0; 
	int stop = current * BAR_LEN / (end - start) ;
	printf( BH_Y"\x1B[?25l\r[B] %s:"H_Y"[", tag );
//	printf( "\x1B[?25l\r\x1B[1;93m[B] %s:\x1B[0;93m[",  tag );
	for( i=0; i<BAR_LEN; i++ ){
		if( i <= stop ){
			printf( "#" );
		}else{
			printf( "-" );
		}
	}
	printf( "]\x1B[0;39m\x1B[?25h" );
}





void dbg_print_bar_( char *tag, int current, int start, int end )	
{
	int i=0; 
	int stop = current * 40 / (end - start) ;
	for( i=0; i<40; i++ ){
		if( i <= stop ){
			printf( "#" );
		}else{
			printf( "-" );
		}
	}
	printf( "]\x1B[0;39m\x1B[?25h" );
}


void debug_cmd( int argc, char **argv )
{
	int level;
	if( argc == 0 ){
		DBG0( printInf( "", "Level 0 on." ) );
		DBG1( printInf( "", "Level 1 on." ) );
		DBG2( printInf( "", "Level 2 on." ) );
		DBG3( printInf( "", "Level 3 on." ) );
		DBG4( printInf( "", "Level 4 on." ) );
		DBG5( printInf( "", "Level 5 on." ) );
		DBG6( printInf( "", "Level 6 on." ) );
		DBG7( printInf( "", "Level 7 on." ) );
		return;
	}
	if( argc > 1 ){
		DBG0( printErr( "", "Invalid parameter." ) );
		return;
	}
	if( argc == 1 ){
		if( argv[0][0] == '+' || argv[0][0] == '-' ){
			level=strtol( &argv[0][1], NULL, 10 );
			if(	level == 0 ){
				DBG0( printErr( "", "Manipulation of level 0 is not allowed." ) );
				return;
			}
		}else{
			DBG0( printErr( "", "Invalid parameter." ) );
			return;
		}
		if(	level > 7 ){
			DBG0( printErr( "", "No such level [%d].", level ) );
			return;
		}
		if( argv[0][0] == '+' ){
			Debug_LevelAdd( DBG_LN(level) );
			DBG0( printInf( "", "Level %d added.", level ) );
		}else if( argv[0][0] == '-'  ){
			Debug_LevelDel( DBG_LN(level) );
			DBG0( printInf( "", "Level %d deleted.", level ) );
		}
	}
}


int isHexNumStr( char *pStr ){
	int i;
	for( i=0; i<strlen(pStr); i++ ){
		if( !isxdigit( pStr[i] ) ){
			return (0);
		}
	}
	return 1;
}
	

int isDecNumStr( char *pStr ){
	int i=0;
	if( pStr[0] == '-' ){
		i = 1;
	}
	for( ; i<strlen(pStr); i++ ){
		if( !isdigit( pStr[i] ) ){
			return (0);
		}
	}
	return 1;
}


