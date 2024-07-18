// By Matthew Strumillo 2024-07-18
//
#pragma once
#include "baseTypes.hpp"
#include "debug.hpp"

namespace CONSOLE {

	bool IsAttachedToConsole (const DWORD& consoleProcesses) {
		return consoleProcesses > 1;
	}
	
}

namespace CONSOLE::CVTS {

    #define CONSOLE_CVTS_CURSOR_HIDE "\x1b[?25l"
	#define CONSOLE_CVTS_WINDOW_TITLE_S "\x1b]0;"
	#define CONSOLE_CVTS_WINDOW_TITLE_E "\x07"

}