#pragma once
ref class KeyLoggedAreaHolder
{
private:
	static System::Windows::Forms::RichTextBox^ keyLoggedArea;
public:
	static System::Windows::Forms::RichTextBox^ getLoggedArea() {
		return keyLoggedArea;
	}

	static void setLoggedArea(System::Windows::Forms::RichTextBox^ keyLoggedArea) {
		KeyLoggedAreaHolder::  keyLoggedArea = keyLoggedArea;
	}
};

