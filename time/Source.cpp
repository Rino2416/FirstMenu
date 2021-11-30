#include <iostream>
#include <Windows.h>
#include<cstdlib>
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
void Menu(HWND hwnd){
	HMENU hMenu = CreateMenu();
	AppendMenu(hMenu, MF_POPUP, 2, L"Close");
	SetMenu(hwnd, hMenu);
}
void Menu2(HWND hwnd) {
	HMENU hMenu2 = CreateMenu();
	AppendMenu(hMenu2, MF_POPUP, 3, L"Поддержка");
	SetMenu(hwnd, hMenu2);
}


static HWND hStatic;
static HWND hEdit;
LRESULT WINAPI WndProc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam) {
	setlocale(LC_ALL, "Russian");
	switch (msg) {
	case WM_CREATE: {
		Menu(hwnd);
		/*Menu2(hwnd);*/
		HWND hBtn = CreateWindow(
			L"BUTTON",
		L"Login",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 20, 70, 25,
			hwnd, reinterpret_cast<HMENU>(1), NULL,NULL
		);
		hStatic = CreateWindow(
			L"static",
			L"Go Login",
			WS_CHILD | WS_VISIBLE,
		500, 0, 125, 20,
			hwnd, NULL, NULL, NULL
		);
		hEdit = CreateWindow(
			L"eDit",
			L"",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			0, 0, 250, 20,
			hwnd, NULL, NULL, NULL

		);
		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wparam)) {
		case 1: {
			char buf[15];
			MessageBox(NULL, L"Hello ", L"Login", MB_OK);
			GetWindowTextA(hEdit, buf, 14);
			SetWindowTextA(hStatic, buf);
			break;
		}
		case 2: {
			DestroyWindow(hwnd);
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

}
using namespace std;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIcon(NULL, IDI_ERROR);
	wc.hIconSm = LoadIcon(NULL, IDI_ERROR);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance = hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"WinMainClass";
	RegisterClassEx(&wc);
	hwnd = CreateWindow(
		wc.lpszClassName,
		L"App",
		WS_OVERLAPPEDWINDOW,
		0, 0, 640, 480,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
	
