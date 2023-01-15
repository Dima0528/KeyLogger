#pragma once
ref class WindowsNameComboBox
{
private:
	static System::Windows::Forms::ComboBox^ comboBox;
public:
	static System::Windows::Forms::ComboBox^ getComboBox() {
		return comboBox;
	}

	static void setComboBox(System::Windows::Forms::ComboBox^ comboBox) {
		WindowsNameComboBox::comboBox = comboBox;
	}
};
