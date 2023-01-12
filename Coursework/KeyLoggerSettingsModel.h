#pragma once

#include "KeyLoggerState.h"

class KeyLoggerSettingsModel
{
private:
	static KeyLoggerSettingsModel* instance;
private:
	KeyLoggerState loggerState;
private:
	KeyLoggerSettingsModel() : loggerState(KeyLoggerState::LOGGING_DISABLED) {};
public:
	KeyLoggerState getLoggerState() {
		return loggerState;
	}
	void setLoggerState(KeyLoggerState loggerState) {
		this->loggerState = loggerState;
	}
public:
	static KeyLoggerSettingsModel* getInstance();
};

