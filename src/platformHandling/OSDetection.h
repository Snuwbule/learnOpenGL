#pragma once

//OS detection
#if defined(_WIN32)
#include <Windows.h>
#define userOS "win"
#elif defined (__APPLE__)
#define userOS "mac"
#elif defined (LINUX)
#define userOS "linux"
#else
#define userOS "unknown"
#endif
