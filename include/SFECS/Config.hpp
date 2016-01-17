#pragma once

#define SFECS_MAJOR_VERSION 1
#define SFECS_MINOR_VERSION 0
#define SFECS_REVISION_VERSION 0

#if defined( _WIN32 ) || defined( __WIN32__ )
	#define SFECS_SYSTEM_WINDOWS
	#define WIN32_LEAN_AND_MEAN

	#if !defined( NOMINMAX )
		#define NOMINMAX
	#endif
#endif

#if defined( SFECS_SYSTEM_WINDOWS ) && !defined( SFECS_STATIC )
	#if defined( SFECS_EXPORTS )
		#define SFECS_API __declspec( dllexport )
	#else
		#define SFECS_API __declspec( dllimport )
	#endif
#else
	#define SFECS_API
#endif

#if defined( _MSC_VER )
	#pragma warning(disable : 4251) // Suppress a warning which is meaningless for us
	#pragma warning(disable : 4503) // Suppress warnings about truncated names. Enable again if linker errors occur.
#endif

#if !defined( NDEBUG )
	#define SFECS_DEBUG
	#include <iostream> // XXX Only for debugging purposes.
#endif