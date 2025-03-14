#include "memory_game.h"
#include <shellapi.h>
#include <stdio.h>
#include <string>
#include <atlstr.h>



//https://www.geeksforgeeks.org/convert-lpcwstr-to-std_string-in-cpp/



int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR commandLine, int show_command) {
	

	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	if (!argv) {
		return 1;	
	}

	int grid_size = 0;


	grid_size = _wtoi(argv[1]);


	memory_game app(instance, grid_size);
	return app.run(show_command);

}