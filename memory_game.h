#pragma once
#include <windows.h>
#include <string>


// based on tutorial code
// https://github.com/WUT-MiNI/PiGE_25L_01193086_WinAPI-Tutorial/commit/b1595556f21b808ff279d7b0bcc86f36970bfd2a
class memory_game {

private:
	bool register_class();
	static std::wstring const s_class_name;
	static LRESULT CALLBACK window_proc_static(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
	LRESULT window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
	HWND create_window();
	HINSTANCE m_instance;
	HWND m_main;
	int grid_size;
	static int const cell_size = 60;
	static int const margin = 15;
	void on_paint(HWND window);
	HBRUSH m_field_brush = CreateSolidBrush(RGB(204, 100, 124));

public:


	memory_game(HINSTANCE instance, int _size);
	int run(int show_command);


};