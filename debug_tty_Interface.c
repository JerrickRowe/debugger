#include "debug_tty_interface.h"
#include "debug.h"

#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



typedef struct{
	char name[100];
	exicuter pExe;
	bool used;
}_t_Binder;

#define CMD_CAP		(10)

_t_Binder cmd_list[CMD_CAP];

void test( int argc, char **argv )
{
	int argCnt;
	if( !argc ){
		DBG5( dbg_print_info( "", "No args" ) );
	}
	for( argCnt=0; argCnt<argc; argCnt++ ){
		DBG5( dbg_print_info( "", "Arg %d/%d:[%s]", argCnt+1, argc, argv[argCnt] ) );
	}
}

void list_all_cmd( int argc, char **argv )
{
	int cmdCnt;
	if( argc ){
		DBG5( dbg_print_error( "", "Invalid arg(s)" ) );
	}
	printf( B_F"List all commands:\r\n"C_Rst );
	for( cmdCnt=0; cmdCnt<CMD_CAP; cmdCnt++ ){
		if( cmd_list[cmdCnt].used == false ){
			continue;
		}
		DBG5( printf( B_F" #%d"C_Rst"\t%s\r\n", cmdCnt+1, cmd_list[cmdCnt].name ) );
	}
}

void debug_tty_cmdReg( char *name, void (*pExe)( int argc, char **argv ) )
{
	int listScan;
	int found_unused = 0;
	for( listScan=0; listScan<CMD_CAP; listScan++ ){
		if( cmd_list[listScan].used == true ){
			continue;
		}
		strcpy(	cmd_list[listScan].name, name );
		cmd_list[listScan].pExe = pExe;
		DBG5( dbg_print_info( "", "\"%s\"\t@0x%X", name, (int)pExe ) );
		cmd_list[listScan].used = true;
		found_unused = 1;
		break;
	}
	if( !found_unused ){
		DBG0( dbg_print_error( "", "No space for \"%s\"", name ) );
	}
}

static void cmdExicuter( int argc, char **argv )
{
	int cmdFound = 0;
	int cmdScan;
	if( !argc || argv == NULL ){
		DBG6( dbg_print_error( "", "Invalid param: %d,\"%s\"", argc, argv[0] ) );
		return;
	}
	
	for( cmdScan=0; cmdScan<CMD_CAP; cmdScan++ ){
		if( cmd_list[cmdScan].used == false ){
			continue;
		}
		if( cmd_list[cmdScan].name[0] == '\0' ){
			DBG0( dbg_print_error( "", "Blank name." ) );
			continue;
		}
		if( strcmp( argv[0], cmd_list[cmdScan].name ) ){
			continue;
		}
		if( cmd_list[cmdScan].pExe == NULL ){
			DBG0( dbg_print_error( "", "\'%s\' NULL function.", cmd_list[cmdScan].name ) );
			continue;
		}
		cmdFound = 1;
		(*(cmd_list[cmdScan].pExe))( argc-1, &argv[1] );
	}
	if( !cmdFound ){
		DBG0( dbg_print_error( "", "\'%s\' not found.", argv[0] ) );
	}
}



#define CMD_BUFLEN	256
#define ARG_CAP		20
#define ARG_MAX_LEN	50
static char *pCmdBuf = NULL;
static void cmdParser( void )
{
	int argc;
	static char *arguments[ARG_CAP];
	static enum{
		idle,
		parsing,
	}mode = parsing;
	
	switch( mode ){
		case idle:
			fgets( pCmdBuf, CMD_BUFLEN, stdin );
			arguments[0] = strtok( pCmdBuf, "\b\r\n, " );
			if( arguments[0] == NULL ){
				break;
			}
			if( !strcmp( arguments[0], "go" ) ){
				mode = parsing;
				DBG5( dbg_print_info( "", "Parsing now." ) );
			}
			break;
		case parsing:
//			printf( "\x1B[1;39mInput your command:\x1B[0;39m\r\n" );
			memset( pCmdBuf, 0, CMD_BUFLEN );
			fgets( pCmdBuf, CMD_BUFLEN, stdin );
			argc = 0;
			arguments[0] = strtok( pCmdBuf, "\b\r\n, " );
			if( arguments[0] == NULL ){
				break;
			}
			argc = 1;
			while( (arguments[argc] = strtok( NULL, "\b\r\n, " )) != NULL ){
				argc ++;
			}
			if( !strcmp( arguments[0], "idle" ) ){
				mode = idle;
				DBG5( dbg_print_info( "", "Idle now." ) );
				break;
			}
			cmdExicuter( argc, arguments );
			break;
	}
}



//------------------ Create tty thread ------------------------
#include "cmsis_os2.h"
void ttyInterfaceThread( void *arg ){
	DBG0(dbg_print_info( "", "Debug tty interface online." ));
	while(1){
		cmdParser();
	}
}


osThreadId_t ttyInterfaceThreadID;
void debug_ttyInterface_Start( void ){
	if( !SystemIsOnline ){
		DBG0(dbg_print_error( "", "System not ready." ));
	}
	int cmdScan;
	DBG5( dbg_print_info( "", "Creating ttyInterface thread.") );
	if( pCmdBuf == NULL ){
		pCmdBuf = malloc( CMD_BUFLEN );
		if( pCmdBuf == NULL ){
			DBG0( dbg_print_error( "", "Failed to malloc!" ) );
			return;
		}
	}
	for( cmdScan=0; cmdScan<CMD_CAP; cmdScan++ ){
		memset( cmd_list[cmdScan].name, 0, 100 );
		cmd_list[cmdScan].pExe = NULL;
	}
	
	DBG7( debug_tty_cmdReg( "test", test ) );
	DBG7( debug_tty_cmdReg( "ls", list_all_cmd ) );
	ttyInterfaceThreadID = osThreadNew( ttyInterfaceThread, NULL, NULL );
}
//---------------------------------------------------------------








