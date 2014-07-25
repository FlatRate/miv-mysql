#pragma once

#if defined(_WIN32) || defined (WIN32)
	#define WINDOWS 1
	#define EXPORT extern "C" __declspec(dllexport)
	
	#pragma message("Building for Windows")

	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#else
	#define EXPORT extern "C"

	#pragma message "Building for Linux"
#endif
