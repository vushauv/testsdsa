#include "memory_game.h"
#include <stdexcept>



std::wstring const memory_game::s_class_name{ L"Memory Game" };





bool memory_game::register_class()
{

	WNDCLASSEXW desc{};

	if (0 != GetClassInfoExW(m_instance, s_class_name.c_str(), &desc)) return true;


	desc = {
		.cbSize = sizeof(WNDCLASSEXW),
		.lpfnWndProc = window_proc_static,
		.hInstance = m_instance,
		.hCursor = LoadCursorW(nullptr, L"IDC_ARROW"),
		.hbrBackground = CreateSolidBrush(RGB(250, 247, 238)),
		.lpszClassName = s_class_name.c_str()
	};

	return RegisterClassExW(&desc) != 0;

}



HWND memory_game::create_window()
{

	RECT size{ 0, 0, cell_size * grid_size + margin * (grid_size + 1) , cell_size * grid_size + margin * (grid_size + 1) };

	DWORD style = WS_CAPTION | WS_CLIPCHILDREN | WS_VISIBLE  | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU;


	AdjustWindowRectEx(&size,style, false, 0);

	HWND window = CreateWindowExW(
		0, s_class_name.c_str(),
		L"Press ESC to start", style,
		CW_USEDEFAULT, 0,
		size.right - size.left, size.bottom - size.top,
		nullptr, nullptr, m_instance, this);

	for (LONG row = 0; row < grid_size; ++row)
		for (LONG column = 0; column < grid_size; ++column)
		{
			int left = column * (cell_size + margin) + margin;
			int right = left + cell_size;
			int top = row * (cell_size + margin) + margin;
			int bottom = top + cell_size;
			//RoundRect(dc, left, top, right, bottom, 11, 11);

			CreateWindowExW(
				0,
				L"STATIC",
				nullptr,
				WS_CHILD | WS_VISIBLE | SS_CENTER,
				left, top,
				right - left,
				bottom - top,
				window,
				nullptr,
				m_instance,
				nullptr);
		}

	return window;

}



LRESULT memory_game::window_proc_static(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {



	memory_game* app = nullptr;

	if (message == WM_NCCREATE)
	{
		auto p = reinterpret_cast<LPCREATESTRUCTW>(lparam);
		app = static_cast<memory_game*>(p->lpCreateParams);
		SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(app));

	}

	else
	{

		app = reinterpret_cast<memory_game*>(GetWindowLongPtrW(window, GWLP_USERDATA));
	}

	if (app != nullptr)
	{

		return app->window_proc(window, message, wparam, lparam);

	}

	return DefWindowProcW(window, message, wparam, lparam);

}





LRESULT memory_game::window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)

{

	switch (message) {

	case WM_CLOSE:

		DestroyWindow(window);

		return 0;

	case WM_DESTROY:

		if (window == m_main)
			PostQuitMessage(EXIT_SUCCESS);

		return 0;
	/*case WM_PAINT:
		on_paint(window);


		return 0;*/

	}

	return DefWindowProcW(window, message, wparam, lparam);

}



memory_game::memory_game(HINSTANCE instance, int _size) : m_instance{ instance }, m_main{}
{
	grid_size = _size;
	register_class();
	m_main = create_window();
}





int memory_game::run(int show_command)
{
	ShowWindow(m_main, show_command);
	MSG msg{};
	BOOL result = TRUE;

	while ((result = GetMessageW(&msg, nullptr, 0, 0)) != 0)
	{

		if (result == -1)
			return EXIT_FAILURE;

		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}


	return EXIT_SUCCESS;

}

void memory_game::on_paint(HWND window)
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(window, &ps);
	auto oldBrush = SelectObject(dc, m_field_brush);
	auto oldPen = SelectObject(dc, GetStockObject(NULL_PEN));

		for (LONG row = 0; row < grid_size; ++row)
			for (LONG column = 0; column < grid_size; ++column)
			{
				int left = column * (cell_size + margin) + margin;
				int right = left + cell_size;
				int top = row * (cell_size + margin) + margin;
				int bottom = top + cell_size;
				RoundRect(dc, left, top, right, bottom, 11, 11);
			}
		
	SelectObject(dc, oldBrush);
	SelectObject(dc, oldPen);
	EndPaint(window, &ps);

}