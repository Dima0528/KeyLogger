#pragma once
ref class StatusLabelToolStrip
{
private:
	static System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel;
public:
	static System::Windows::Forms::ToolStripStatusLabel^ getToolStripStatusLabel() {
		return toolStripStatusLabel;
	}

	static void setToolStripStatusLabel(System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel) {
		StatusLabelToolStrip::toolStripStatusLabel = toolStripStatusLabel;
	}
};

