#pragma once

#include "Defines.h"
#include "Log.h"

#include <filesystem>

#define SADDLE_INTERNAL_ASSERT_CHECK(condition, message, ...) { if(!(condition)) { SADDLE_CORE_LOG_ERROR(message, ## __VA_ARGS__); SADDLE_ERROR_CLOSE(); } }
#define SADDLE_CORE_ASSERT_ARGS(condition, message, ...) SADDLE_INTERNAL_ASSERT_CHECK(condition, message, ## __VA_ARGS__)
#define SADDLE_CORE_ASSERT_NO_ARGS(condition) SADDLE_INTERNAL_ASSERT_CHECK(condition, "Assertion failed: %s, file %s, line %s", #condition, std::filesystem::path(__FILE__).string(), std::to_string(__LINE__))

#define SADDLE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro

#define SADDLE_CORE_ASSERT(...) SADDLE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, SADDLE_CORE_ASSERT_ARGS, SADDLE_CORE_ASSERT_NO_ARGS)(__VA_ARGS__)