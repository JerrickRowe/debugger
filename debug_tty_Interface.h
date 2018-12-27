#ifndef _TTY_INTERFACE_H_
#define _TTY_INTERFACE_H_


typedef void (*exicuter)( int argc, char **argv );
void debug_tty_cmdReg( char *name, void (*pExe)( int argc, char **argv ) );


void debug_ttyInterface_Start( void );


#endif

