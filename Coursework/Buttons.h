#pragma once

ref class Buttons
{
private:
	static System::Windows::Forms::Button^ buttonSpace;
	static System::Windows::Forms::Button^ buttonD;
	static System::Windows::Forms::Button^ buttonF;
public:
	static System::Windows::Forms::Button^ getButton() {
		return buttonSpace;
	}

	static void setButton(System::Windows::Forms::Button^ buttonSpace) {
		Buttons::buttonSpace = buttonSpace;
	}

	///////////////

	static System::Windows::Forms::Button^ getButtonD() {
		return buttonD;
	}

	static void setButtonD(System::Windows::Forms::Button^ buttonD) {
		Buttons::buttonD = buttonD;
	}

	////////////////

	static System::Windows::Forms::Button^ getButtonF() {
		return buttonF;
	}

	static void setButtonF(System::Windows::Forms::Button^ buttonF) {
		Buttons::buttonF = buttonF;
	}

};
