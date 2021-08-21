#include <iostream>
#include <locale>
#include <locale.h>
#include <stdlib.h>

#ifndef MS_STDLIB_BUGS // Allow overriding the autodetection.
	// The Microsoft C and C++ runtime libraries that ship with Visual Studio, as
	// of 2017, have a bug that neither stdio, iostreams or wide iostreams can
	// handle Unicode input or output.  Windows needs some non-standard magic to
	// work around that.  This includes programs compiled with MinGW and Clang
	// for the win32 and win64 targets.
	#if ( _MSC_VER || __MINGW32__ || __MSVCRT__ )
    	// This code is being compiled either on MS Visual C++, or MinGW, or clang++
    	// in compatibility mode for either, or is being linked to the msvcrt.dll runtime.
		#define MS_STDLIB_BUGS 1
	#else
		#define MS_STDLIB_BUGS 0
	#endif
#endif

#if MS_STDLIB_BUGS
	#include <io.h>
	#include <fcntl.h>
#endif

// Does magic so that wcout can work.
void init_locale(void);