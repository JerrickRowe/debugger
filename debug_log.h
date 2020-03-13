#ifndef __DEBUG_LOG_H__
#define __DEBUG_LOG_H__

#if !defined DEBUG_LOG_LEVEL
	#error define "DEBUG_LOG_LEVEL" before [#include "debug_log.h"]
#endif

#if DEBUG_LOG_LEVEL>9
	#error DEBUG_LOG_LEVEL range in [0~9]
#endif

#include "debug.h"

#define L0(_x)  do{_x;}while(0);

#if DEBUG_LOG_LEVEL>0
	#define L1(_x)  do{_x;}while(0);
#else
	#define L1(_x)
#endif

#if DEBUG_LOG_LEVEL>1
	#define L2(_x)  do{_x;}while(0);
#else
	#define L2(_x)
#endif

#if DEBUG_LOG_LEVEL>2
	#define L3(_x)  do{_x;}while(0);
#else
	#define L3(_x)
#endif

#if DEBUG_LOG_LEVEL>3
	#define L4(_x)  do{_x;}while(0);
#else
	#define L4(_x)
#endif

#if DEBUG_LOG_LEVEL>4
	#define L5(_x)  do{_x;}while(0);
#else
	#define L5(_x)
#endif

#if DEBUG_LOG_LEVEL>5
	#define L6(_x)  do{_x;}while(0);
#else
	#define L6(_x)
#endif

#if DEBUG_LOG_LEVEL>6
	#define L7(_x)  do{_x;}while(0);
#else
	#define L7(_x)
#endif

#if DEBUG_LOG_LEVEL>7
	#define L8(_x)  do{_x;}while(0);
#else
	#define L8(_x)
#endif

#if DEBUG_LOG_LEVEL>8
	#define L9(_x)  do{_x;}while(0);
#else
	#define L9(_x)
#endif


#define INFO_PRINT( tag, fmt, ... )			printInf( tag, fmt, ##__VA_ARGS__ )
#define WRN_PRINT( tag, fmt, ... ) 			printWrn( tag, fmt, ##__VA_ARGS__ )
#define ERR_PRINT( tag, fmt, ... ) 			printErr( tag, fmt, ##__VA_ARGS__ )
#define IL_INFO_PRINT( tag, fmt, ... )		printInf_IL( tag, fmt, ##__VA_ARGS__ )
#define IL_WRN_PRINT( tag, fmt, ... ) 		printWrn_IL( tag, fmt, ##__VA_ARGS__ )
#define IL_ERR_PRINT( tag, fmt, ... ) 		printErr_IL( tag, fmt, ##__VA_ARGS__ )
#define RAW_PRINT( ... ) 					printRaw( __VA_ARGS__ )
	
#define LOG_INF( tag, fmt, ... )			printInf( tag, fmt, ##__VA_ARGS__ )
#define LOG_WRN( tag, fmt, ... )   			printWrn( tag, fmt, ##__VA_ARGS__ )
#define LOG_ERR( tag, fmt, ... )   			printErr( tag, fmt, ##__VA_ARGS__ )
#define LOG_INF_IL( tag, fmt, ... )			printInf_IL( tag, fmt, ##__VA_ARGS__ )
#define LOG_WRN_IL( tag, fmt, ... )			printWrn_IL( tag, fmt, ##__VA_ARGS__ )
#define LOG_ERR_IL( tag, fmt, ... )			printErr_IL( tag, fmt, ##__VA_ARGS__ )
#define LOG_RAW( ... )						printRaw( __VA_ARGS__ )

#define LOG_INF_L1( tag, fmt, ... )		L1( printInf( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_WRN_L1( tag, fmt, ... )     L1( printWrn( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_ERR_L1( tag, fmt, ... )     L1( printErr( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_INF_L1_IL( tag, fmt, ... )  L1( printInf_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_WRN_L1_IL( tag, fmt, ... )  L1( printWrn_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_ERR_L1_IL( tag, fmt, ... )  L1( printErr_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_RAW_L1( ... )				L1( printRaw( __VA_ARGS__ )                )

#define LOG_INF_L2( tag, fmt, ... )		L2( printInf( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_WRN_L2( tag, fmt, ... )     L2( printWrn( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_ERR_L2( tag, fmt, ... )     L2( printErr( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_INF_L2_IL( tag, fmt, ... )  L2( printInf_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_WRN_L2_IL( tag, fmt, ... )  L2( printWrn_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_ERR_L2_IL( tag, fmt, ... )  L2( printErr_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_RAW_L2( ... )				L2( printRaw( __VA_ARGS__ )                )

#define LOG_INF_L3( tag, fmt, ... )		L3( printInf( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_WRN_L3( tag, fmt, ... )     L3( printWrn( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_ERR_L3( tag, fmt, ... )     L3( printErr( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_INF_L3_IL( tag, fmt, ... )  L3( printInf_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_WRN_L3_IL( tag, fmt, ... )  L3( printWrn_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_ERR_L3_IL( tag, fmt, ... )  L3( printErr_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_RAW_L3( ... )				L3( printRaw( __VA_ARGS__ )                )

#define LOG_INF_L4( tag, fmt, ... )		L4( printInf( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_WRN_L4( tag, fmt, ... )     L4( printWrn( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_ERR_L4( tag, fmt, ... )     L4( printErr( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_INF_L4_IL( tag, fmt, ... )  L4( printInf_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_WRN_L4_IL( tag, fmt, ... )  L4( printWrn_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_ERR_L4_IL( tag, fmt, ... )  L4( printErr_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_RAW_L4( ... )				L4( printRaw( __VA_ARGS__ )                )

#define LOG_INF_L5( tag, fmt, ... )		L5( printInf( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_WRN_L5( tag, fmt, ... )     L5( printWrn( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_ERR_L5( tag, fmt, ... )     L5( printErr( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_INF_L5_IL( tag, fmt, ... )  L5( printInf_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_WRN_L5_IL( tag, fmt, ... )  L5( printWrn_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_ERR_L5_IL( tag, fmt, ... )  L5( printErr_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_RAW_L5( ... )				L5( printRaw( __VA_ARGS__ )                )

#define LOG_INF_L6( tag, fmt, ... )		L6( printInf( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_WRN_L6( tag, fmt, ... )     L6( printWrn( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_ERR_L6( tag, fmt, ... )     L6( printErr( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_INF_L6_IL( tag, fmt, ... )  L6( printInf_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_WRN_L6_IL( tag, fmt, ... )  L6( printWrn_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_ERR_L6_IL( tag, fmt, ... )  L6( printErr_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_RAW_L6( ... )				L6( printRaw( __VA_ARGS__ )                )

#define LOG_INF_L7( tag, fmt, ... )		L7( printInf( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_WRN_L7( tag, fmt, ... )     L7( printWrn( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_ERR_L7( tag, fmt, ... )     L7( printErr( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_INF_L7_IL( tag, fmt, ... )  L7( printInf_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_WRN_L7_IL( tag, fmt, ... )  L7( printWrn_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_ERR_L7_IL( tag, fmt, ... )  L7( printErr_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_RAW_L7( ... )				L7( printRaw( __VA_ARGS__ )                )

#define LOG_INF_L8( tag, fmt, ... )		L8( printInf( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_WRN_L8( tag, fmt, ... )     L8( printWrn( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_ERR_L8( tag, fmt, ... )     L8( printErr( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_INF_L8_IL( tag, fmt, ... )  L8( printInf_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_WRN_L8_IL( tag, fmt, ... )  L8( printWrn_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_ERR_L8_IL( tag, fmt, ... )  L8( printErr_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_RAW_L8( ... )				L8( printRaw( __VA_ARGS__ )                )

#define LOG_INF_L9( tag, fmt, ... )		L9( printInf( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_WRN_L9( tag, fmt, ... )     L9( printWrn( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_ERR_L9( tag, fmt, ... )     L9( printErr( tag, fmt, ##__VA_ARGS__ )    )
#define LOG_INF_L9_IL( tag, fmt, ... )  L9( printInf_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_WRN_L9_IL( tag, fmt, ... )  L9( printWrn_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_ERR_L9_IL( tag, fmt, ... )  L9( printErr_IL( tag, fmt, ##__VA_ARGS__ ) )
#define LOG_RAW_L9( ... )				L9( printRaw( __VA_ARGS__ )                )


// Override error loggings
#ifdef DEBUG_LOG_ALL_ERR

	#undef LOG_ERR
	#undef LOG_ERR_L1
	#undef LOG_ERR_L2
	#undef LOG_ERR_L3
	#undef LOG_ERR_L4
	#undef LOG_ERR_L5
	#undef LOG_ERR_L6
	#undef LOG_ERR_L7
	#undef LOG_ERR_L8
	#undef LOG_ERR_L9

	#define LOG_ERR( tag, fmt, ... )    	printErr( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L1( tag, fmt, ... )     printErr( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L2( tag, fmt, ... )     printErr( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L3( tag, fmt, ... )     printErr( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L4( tag, fmt, ... )     printErr( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L5( tag, fmt, ... )     printErr( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L6( tag, fmt, ... )     printErr( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L7( tag, fmt, ... )     printErr( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L8( tag, fmt, ... )     printErr( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L9( tag, fmt, ... )     printErr( tag, fmt, ##__VA_ARGS__ )

	#undef LOG_ERR_L1_IL
	#undef LOG_ERR_L2_IL
	#undef LOG_ERR_L3_IL
	#undef LOG_ERR_L4_IL
	#undef LOG_ERR_L5_IL
	#undef LOG_ERR_L6_IL
	#undef LOG_ERR_L7_IL
	#undef LOG_ERR_L8_IL
	#undef LOG_ERR_L9_IL

	#define LOG_ERR_IL( tag, fmt, ... ) 	printErr_IL( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L1_IL( tag, fmt, ... )  printErr_IL( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L2_IL( tag, fmt, ... )  printErr_IL( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L3_IL( tag, fmt, ... )  printErr_IL( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L4_IL( tag, fmt, ... )  printErr_IL( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L5_IL( tag, fmt, ... )  printErr_IL( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L6_IL( tag, fmt, ... )  printErr_IL( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L7_IL( tag, fmt, ... )  printErr_IL( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L8_IL( tag, fmt, ... )  printErr_IL( tag, fmt, ##__VA_ARGS__ )
	#define LOG_ERR_L9_IL( tag, fmt, ... )  printErr_IL( tag, fmt, ##__VA_ARGS__ )

#endif

#endif
