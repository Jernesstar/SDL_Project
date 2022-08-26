#pragma once

#ifdef SADDLE_DEBUG
    #define SADDLE_DEBUGBREAK() __debugbreak()
#else 
    #define SADDLE_DEBUGBREAK()
#endif

#include "Application.h"

#define SADDLE_ERROR_CLOSE() { Application::Close(); }
#define SADDLE_EXPAND_MACRO(x) x