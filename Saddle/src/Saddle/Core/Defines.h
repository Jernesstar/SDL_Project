#pragma once

#ifdef SADDLE_DEBUG
    #define SADDLE_DEBUGBREAK() __debugbreak()
#else 
    #define SADDLE_DEBUGBREAK()
#endif

#include "Application.h"
#include <stdlib.h>

#define SADDLE_ERROR_CLOSE() { Application::Close(); exit(1); }
#define SADDLE_EXPAND_MACRO(x) x