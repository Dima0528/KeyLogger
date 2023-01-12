#include "MainForm.h"
#include <Windows.h>

//#define visible // (visible / invisible)

using namespace System;
using namespace System::Windows::Forms;


//void Stealth()
//{
//#ifdef visible
//	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1); // visible window
//#endif // visible
//
//#ifdef invisible
//	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0); // invisible window
//#endif // invisible
//} 

[STAThread]
void main() {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Coursework::MainForm form;
	Application::Run(% form);
}

