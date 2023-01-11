#include "KeyLoggerSettingsModel.h"

KeyLoggerSettingsModel* KeyLoggerSettingsModel::instance = nullptr;

KeyLoggerSettingsModel* KeyLoggerSettingsModel::getInstance()
{
    if (instance == nullptr) {
        instance = new KeyLoggerSettingsModel();
    }
    return instance;
}
