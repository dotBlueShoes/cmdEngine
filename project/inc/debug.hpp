// By Matthew Strumillo 2024-07-08
//
#pragma once

#define DEBUG if constexpr (DEBUG_LEVEL > 0)

#if DEBUG_LEVEL > 0

	#pragma GCC diagnostic push 
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	#include <spdlog/spdlog.h>
	#include <spdlog/fmt/bin_to_hex.h>
	#pragma GCC diagnostic pop

	#define LogInfo(...) { \
		spdlog::info (__VA_ARGS__); \
	}

	#define LogWarn(...) { \
		spdlog::warn (__VA_ARGS__); \
	}

	#define LogErro(...) { \
		spdlog::error (__VA_ARGS__); \
	}

	#define Error(...) { \
		LogErro (__VA_ARGS__); \
		exit (1); \
	}

	// Non-Crittical Error
	#define ErrorSilent(...) { \
		LogErro (__VA_ARGS__); \
	}

#else

	#define LogInfo(...) {} // DUMMY
	#define LogWarn(...) {} // DUMMY
	#define LogErro(...) {} // DUMMY

	#define Error(...) { \
		exit (1); \
	}

	// Non-Crittical Error
	#define ErrorSilent(...) {} // DUMMY

#endif
