// By Matthew Strumillo 2024-07-08
//
#include "asset/manager.hpp"
#include "audio/manager.hpp"
#include "console.hpp"


s32 main (
	s32			argumentsCount,
	c8**		arguments
) {

	DEBUG {
		DWORD processId = GetCurrentProcessId ();
		DWORD consoleProcesses = GetConsoleProcessList (&processId, 1);

		if (CONSOLE::IsAttachedToConsole (consoleProcesses)) {

			Error ("Running from an exsisting console is currently unsupported!");

			// I would need to create a pipe. Set the icon there additionally and then with each console write read 
			//  ensure to which console i read write.
			// https://learn.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output
			// https://www.codeproject.com/Messages/3268714/Re-how-to-use-createprocess-to-create-a-new-consol

			// What i want to do is:
			// - If application is run from console:
			//	 - Create a new process with a console attached
			//   - This way all my debug logs will be displayed in the parent process
			// - If its run without a parent process and we're in release mode then don't create a new process with console
			// 
			// When that is done I want to change the application icon and ENABLE_VIRTUAL_TERMINAL_INPUT

			//1 const c8 CMD_FILEPATH[] { "cmd.exe" };
			//1 PROCESS_INFORMATION processHelper {};
			//1 STARTUPINFO appHelper {};
			//1 
			//1 appHelper.cb = sizeof (appHelper);
			//1 
			//1 if ( !CreateProcessA (		// Start the child process. 
			//1 	NULL,					// No module name (use command line)
			//1 	(LPSTR)CMD_FILEPATH,	// Command line
			//1 	NULL,					// Process handle not inheritable
			//1 	NULL,					// Thread handle not inheritable
			//1 	FALSE,					// Set handle inheritance to FALSE
			//1 	CREATE_NEW_CONSOLE,		// No creation flags
			//1 	NULL,					// Use parent's environment block
			//1 	NULL,					// Use parent's starting directory 
			//1 	&appHelper,				// Pointer to STARTUPINFO structure
			//1 	&processHelper			// Pointer to PROCESS_INFORMATION structure
			//1 )) Error ("Console: Could not create the Console Process. {0}", GetLastError());
		}

		//Beep (2000, 100);
	}

	HANDLE outputHandle = GetStdHandle (STD_OUTPUT_HANDLE);
	HANDLE inputHandle  = GetStdHandle (STD_INPUT_HANDLE);

	if (outputHandle == nullptr || outputHandle == INVALID_HANDLE_VALUE) 
		Error ("Console: Invalid Output Handle");
	if (inputHandle == nullptr || inputHandle == INVALID_HANDLE_VALUE) 
		Error ("Console: Invalid Input Handle");

	DWORD prevConsoleMode;
	DWORD currConsoleMode;

	if (GetConsoleMode (outputHandle, &prevConsoleMode) == 0)
		Error ("Console: Could not retrive Console Mode");

	currConsoleMode = prevConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING; // SET BIT

	if (SetConsoleMode (outputHandle, currConsoleMode) == 0)
		Error ("Console: Could not set Console Mode");
	
	{ // Change Title & Cursor using CVTS
		const c8* const message = 
			CONSOLE_CVTS_CURSOR_HIDE 
			CONSOLE_CVTS_WINDOW_TITLE_S 
			RESOURCE_GAME_TITLE 
			CONSOLE_CVTS_WINDOW_TITLE_E;

		u32 written = 0;
		WriteConsole (outputHandle, message, strlen(message), (LPDWORD)&written, NULL);
	}
	
	//u32 written = 0;
	//u32 reed = 0;
	//const c8* message = "hello world";
	//c8 data[255];
	//WriteConsoleA (outputHandle, message, strlen(message), (LPDWORD)&written, NULL); // write
	//ReadConsoleA (inputHandle, data, 255, (LPDWORD)&reed, NULL); // read

	//BOOL WINAPI GetConsoleMode(
	//	_In_  HANDLE  hConsoleHandle,
	//	_Out_ LPDWORD lpMode
	//);

	//BOOL WINAPI SetConsoleMode(
 	//	_In_ HANDLE hConsoleHandle,
	//	_In_ DWORD  dwMode
	//);

	ALCdevice* device = nullptr;
	ALCcontext* listener = nullptr;
	ALuint sound;
	ALuint source;

	AUDIO::MANAGER::Create (device, listener, sound, source);

	u32 isStop = 1;
	while (isStop != 0) {
		++isStop;
	}

	DEBUG LogInfo ("Freeing audio resources");
	AUDIO::MANAGER::Destroy (device, listener, sound, source);

	return 0;
}
