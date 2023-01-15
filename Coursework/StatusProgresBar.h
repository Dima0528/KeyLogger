#pragma once
ref class StatusProgresBar
{
private:
	static System::Windows::Forms::ToolStripProgressBar^ proggresBar;
public:
	static System::Windows::Forms::ToolStripProgressBar^ getProgressBar() {
		return proggresBar;
	}

	static void setProgressBar(System::Windows::Forms::ToolStripProgressBar^ proggresBar) {
		StatusProgresBar::proggresBar = proggresBar;
	}
};


