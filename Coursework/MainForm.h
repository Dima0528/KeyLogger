#pragma once
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <fstream>

#include "KeyLoggerSettingsModel.h"
#include "KeyLoggerState.h"
#include "KeyLogConstants.h"
#include "CastingUtils.h"
#include "KeyLoggerModule.h"
#include "KeyLoggedAreaHolder.h"
#include "Buttons.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "AboutProgramWindow.h"
#include "StatusProgresBar.h"
#include "StatusLabel.h"

namespace Coursework {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Ñâîäêà äëÿ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		KeyLoggerSettingsModel* loggerSettings = KeyLoggerSettingsModel::getInstance();
	public:
		MainForm(void)
		{
			InitializeComponent();

			initState();

			KeyLoggedAreaHolder::setLoggedArea(this->keyLoggedArea);
			//KeyLoggedAreaHolder::setLoggedArea(this->richTextBox);
			//KeyLoggedAreaHolder::setLoggedArea(this->richTextBoxLog);
			//Buttons::setButton(this->buttonSpace);
			StatusProgresBar::setProgressBar(this->toolStripProgressBar);
			StatusLabelToolStrip::setToolStripStatusLabel(this->toolStripStatusLabel1);
			SetHook();
		}

	protected:
		/// <summary>
		/// Îñâîáîäèòü âñå èñïîëüçóåìûå ğåñóğñû.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ ôàéëToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ ïğîÏğîãğàìóToolStripMenuItem;
	private: System::Windows::Forms::ToolStrip^ toolStrip1;
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ çáåğåãòèToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ âèõ³äToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^ toolStripStartLog;
	private: System::Windows::Forms::ToolStripButton^ toolStripStopLog;
	private: System::Windows::Forms::ToolStripButton^ toolStripImportLog;
	private: System::Windows::Forms::ToolStripButton^ toolStripExportLog;








	private: System::Windows::Forms::ToolStripStatusLabel^ loggingMode;


	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::RichTextBox^ keyLoggedArea;



	private: System::Windows::Forms::ToolStripButton^ toolStripClearLog;








	private: System::Windows::Forms::ToolStripProgressBar^ toolStripProgressBar;

	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripMenuItem^ ìàñøòàáToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ çá³ëüøèòèToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ çìåíøèòèToolStripMenuItem;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel2;







	private:
		/// <summary>
		/// Îáÿçàòåëüíàÿ ïåğåìåííàÿ êîíñòğóêòîğà.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Òğåáóåìûé ìåòîä äëÿ ïîääåğæêè êîíñòğóêòîğà — íå èçìåíÿéòå 
		/// ñîäåğæèìîå ıòîãî ìåòîäà ñ ïîìîùüş ğåäàêòîğà êîäà.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ôàéëToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->çáåğåãòèToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->âèõ³äToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ìàñøòàáToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->çá³ëüøèòèToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->çìåíøèòèToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïğîÏğîãğàìóToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripStartLog = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripStopLog = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripImportLog = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripExportLog = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripClearLog = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->loggingMode = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripProgressBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->keyLoggedArea = (gcnew System::Windows::Forms::RichTextBox());
			this->menuStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->ôàéëToolStripMenuItem,
					this->ìàñøòàáToolStripMenuItem, this->ïğîÏğîãğàìóToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(876, 26);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ôàéëToolStripMenuItem
			// 
			this->ôàéëToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->çáåğåãòèToolStripMenuItem,
					this->âèõ³äToolStripMenuItem
			});
			this->ôàéëToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Roboto", 9));
			this->ôàéëToolStripMenuItem->Name = L"ôàéëToolStripMenuItem";
			this->ôàéëToolStripMenuItem->Size = System::Drawing::Size(60, 22);
			this->ôàéëToolStripMenuItem->Text = L"Ôàéë";
			// 
			// çáåğåãòèToolStripMenuItem
			// 
			this->çáåğåãòèToolStripMenuItem->Name = L"çáåğåãòèToolStripMenuItem";
			this->çáåğåãòèToolStripMenuItem->Size = System::Drawing::Size(153, 26);
			this->çáåğåãòèToolStripMenuItem->Text = L"Çáåğåãòè";
			this->çáåğåãòèToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::çáåğåãòèToolStripMenuItem_Click);
			// 
			// âèõ³äToolStripMenuItem
			// 
			this->âèõ³äToolStripMenuItem->Name = L"âèõ³äToolStripMenuItem";
			this->âèõ³äToolStripMenuItem->Size = System::Drawing::Size(153, 26);
			this->âèõ³äToolStripMenuItem->Text = L"Âèõ³ä";
			this->âèõ³äToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::âèõ³äToolStripMenuItem_Click);
			// 
			// ìàñøòàáToolStripMenuItem
			// 
			this->ìàñøòàáToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->çá³ëüøèòèToolStripMenuItem,
					this->çìåíøèòèToolStripMenuItem
			});
			this->ìàñøòàáToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Roboto", 9));
			this->ìàñøòàáToolStripMenuItem->Name = L"ìàñøòàáToolStripMenuItem";
			this->ìàñøòàáToolStripMenuItem->Size = System::Drawing::Size(86, 22);
			this->ìàñøòàáToolStripMenuItem->Text = L"Ìàñøòàá";
			// 
			// çá³ëüøèòèToolStripMenuItem
			// 
			this->çá³ëüøèòèToolStripMenuItem->Name = L"çá³ëüøèòèToolStripMenuItem";
			this->çá³ëüøèòèToolStripMenuItem->Size = System::Drawing::Size(165, 26);
			this->çá³ëüøèòèToolStripMenuItem->Text = L"Çá³ëüøèòè";
			this->çá³ëüøèòèToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::çá³ëüøèòèToolStripMenuItem_Click);
			// 
			// çìåíøèòèToolStripMenuItem
			// 
			this->çìåíøèòèToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Roboto", 9));
			this->çìåíøèòèToolStripMenuItem->Name = L"çìåíøèòèToolStripMenuItem";
			this->çìåíøèòèToolStripMenuItem->Size = System::Drawing::Size(165, 26);
			this->çìåíøèòèToolStripMenuItem->Text = L"Çìåíøèòè";
			this->çìåíøèòèToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::çìåíøèòèToolStripMenuItem_Click);
			// 
			// ïğîÏğîãğàìóToolStripMenuItem
			// 
			this->ïğîÏğîãğàìóToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Roboto", 9));
			this->ïğîÏğîãğàìóToolStripMenuItem->Name = L"ïğîÏğîãğàìóToolStripMenuItem";
			this->ïğîÏğîãğàìóToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->ïğîÏğîãğàìóToolStripMenuItem->Text = L"Ïğî ïğîãğàìó";
			this->ïğîÏğîãğàìóToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ïğîÏğîãğàìóToolStripMenuItem_Click);
			// 
			// toolStrip1
			// 
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->toolStripStartLog,
					this->toolStripStopLog, this->toolStripImportLog, this->toolStripExportLog, this->toolStripClearLog
			});
			this->toolStrip1->Location = System::Drawing::Point(0, 26);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(876, 27);
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripStartLog
			// 
			this->toolStripStartLog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripStartLog->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripStartLog.Image")));
			this->toolStripStartLog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripStartLog->Name = L"toolStripStartLog";
			this->toolStripStartLog->Size = System::Drawing::Size(29, 24);
			this->toolStripStartLog->Text = L"Óâ³ìêíóòè ëîãóâàííÿ";
			this->toolStripStartLog->Click += gcnew System::EventHandler(this, &MainForm::toolStripLoggingStartButton_Click);
			// 
			// toolStripStopLog
			// 
			this->toolStripStopLog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripStopLog->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripStopLog.Image")));
			this->toolStripStopLog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripStopLog->Name = L"toolStripStopLog";
			this->toolStripStopLog->Size = System::Drawing::Size(29, 24);
			this->toolStripStopLog->Text = L"Âèìêíóòè ëîãóâàííÿ";
			this->toolStripStopLog->Click += gcnew System::EventHandler(this, &MainForm::toolStripLoggingStopLog_Click);
			// 
			// toolStripImportLog
			// 
			this->toolStripImportLog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripImportLog->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripImportLog.Image")));
			this->toolStripImportLog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripImportLog->Name = L"toolStripImportLog";
			this->toolStripImportLog->Size = System::Drawing::Size(29, 24);
			this->toolStripImportLog->Text = L"²ìïîğòóâàòè ëîã";
			this->toolStripImportLog->Click += gcnew System::EventHandler(this, &MainForm::toolStripImportLog_Click);
			// 
			// toolStripExportLog
			// 
			this->toolStripExportLog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripExportLog->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripExportLog.Image")));
			this->toolStripExportLog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripExportLog->Name = L"toolStripExportLog";
			this->toolStripExportLog->Size = System::Drawing::Size(29, 24);
			this->toolStripExportLog->Text = L"Åêñïîğòóâàòè ëîã";
			this->toolStripExportLog->Click += gcnew System::EventHandler(this, &MainForm::toolStripExportLog_Click);
			// 
			// toolStripClearLog
			// 
			this->toolStripClearLog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripClearLog->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripClearLog.Image")));
			this->toolStripClearLog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripClearLog->Name = L"toolStripClearLog";
			this->toolStripClearLog->Size = System::Drawing::Size(29, 24);
			this->toolStripClearLog->Text = L"Î÷èñòèòè ëîã";
			this->toolStripClearLog->Click += gcnew System::EventHandler(this, &MainForm::toolStripClearLog_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->loggingMode, this->toolStripStatusLabel2,
					this->toolStripProgressBar, this->toolStripStatusLabel1
			});
			this->statusStrip1->Location = System::Drawing::Point(0, 500);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(876, 26);
			this->statusStrip1->TabIndex = 2;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// loggingMode
			// 
			this->loggingMode->Font = (gcnew System::Drawing::Font(L"Roboto", 9));
			this->loggingMode->Name = L"loggingMode";
			this->loggingMode->Size = System::Drawing::Size(162, 20);
			this->loggingMode->Text = L"Ëîãóâàííÿ óâ³ìêíåíî";
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->Font = (gcnew System::Drawing::Font(L"Roboto", 9));
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			this->toolStripStatusLabel2->Size = System::Drawing::Size(12, 20);
			this->toolStripStatusLabel2->Text = L"|";
			this->toolStripStatusLabel2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// toolStripProgressBar
			// 
			this->toolStripProgressBar->Name = L"toolStripProgressBar";
			this->toolStripProgressBar->Size = System::Drawing::Size(100, 18);
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(29, 20);
			this->toolStripStatusLabel1->Text = L"0%";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				23.69172F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				76.30828F)));
			this->tableLayoutPanel1->Controls->Add(this->keyLoggedArea, 1, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 53);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(876, 447);
			this->tableLayoutPanel1->TabIndex = 3;
			// 
			// keyLoggedArea
			// 
			this->keyLoggedArea->Dock = System::Windows::Forms::DockStyle::Fill;
			this->keyLoggedArea->Font = (gcnew System::Drawing::Font(L"Roboto", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->keyLoggedArea->Location = System::Drawing::Point(8, 2);
			this->keyLoggedArea->Margin = System::Windows::Forms::Padding(8, 2, 8, 8);
			this->keyLoggedArea->Name = L"keyLoggedArea";
			this->keyLoggedArea->ReadOnly = true;
			this->keyLoggedArea->Size = System::Drawing::Size(860, 437);
			this->keyLoggedArea->TabIndex = 0;
			this->keyLoggedArea->Text = L"";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(876, 526);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"Ëîãåğ êëàâ³àóòğè";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	private:
		void initState() {
			initLoggingMode();
		}

		void initLoggingMode() {
			if (loggerSettings->getLoggerState() == KeyLoggerState::LOG_TO_TEXT_AREA) {
				this->loggingMode->Text = CastingUtils::castAsString(KeyLogConstants::LOGGING_ENABLED);
			}
			else if (loggerSettings->getLoggerState() == KeyLoggerState::LOGGING_DISABLED) {
				this->loggingMode->Text = CastingUtils::castAsString(KeyLogConstants::LOGGING_DISABLED);
			}
		}
#pragma endregion
	private: System::Void toolStripLoggingStartButton_Click(System::Object^ sender, System::EventArgs^ e) {
		loggerSettings->setLoggerState(LOG_TO_TEXT_AREA);
		initLoggingMode();
	}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	
	}

	private: System::Void toolStripLoggingStopLog_Click(System::Object^ sender, System::EventArgs^ e) {
		loggerSettings->setLoggerState(LOGGING_DISABLED);
		initLoggingMode();
	}
	private: System::Void toolStripImportLog_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog;
		openFileDialog->Filter = "TXT files (*.txt)|*.txt";
		openFileDialog->FilterIndex = 2;
		openFileDialog->RestoreDirectory = true;

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			std::string filename = CastingUtils::castAsString(openFileDialog->FileName);
			//TODO added loggic here
			FileReader reader(filename);

			std::string logs = reader.readLines();

			this->keyLoggedArea->Text = CastingUtils::castAsString(logs);


			System::Windows::Forms::DialogResult^ Show = System::Windows::Forms::MessageBox::Show(
				"²ìïîğò ëîãóâàííÿ ïğîéøîâ óñï³øíî.",
				"²ìïîğò",
				System::Windows::Forms::MessageBoxButtons::OK,
				System::Windows::Forms::MessageBoxIcon::Information
			);
		}
	}
	private: System::Void toolStripExportLog_Click(System::Object^ sender, System::EventArgs^ e) {
		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;

		saveFileDialog->Filter = "TXT files (*.txt)|*.txt";
		saveFileDialog->FilterIndex = 2;
		saveFileDialog->RestoreDirectory = true;

		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			std::string filename = CastingUtils::castAsString(saveFileDialog->FileName);
			FileWriter writer(filename);

			writer.write(CastingUtils::castAsString(this->keyLoggedArea->Text));

			System::Windows::Forms::DialogResult^ Show = System::Windows::Forms::MessageBox::Show(
				"Åêñïîğò ëîãóâàííÿ ïğîéøîâ óñï³øíî.",
				"Åêñïîğò",
				System::Windows::Forms::MessageBoxButtons::OK,
				System::Windows::Forms::MessageBoxIcon::Information
			);
		}
	}
	private: System::Void ïğîÏğîãğàìóToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		AboutProgramWindow^ aboutProgram = gcnew AboutProgramWindow();
		aboutProgram->ShowDialog();
	}
private: System::Void âèõ³äToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	Close();
}
private: System::Void toolStripClearLog_Click(System::Object^ sender, System::EventArgs^ e) {
	this->keyLoggedArea->Text = "";
	
}
private: System::Void çáåğåãòèToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	StatusProgresBar::getProgressBar()->Value = 0;
	StatusLabelToolStrip::getToolStripStatusLabel()->Text = "0%";
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;

	saveFileDialog->Filter = "TXT files (*.txt)|*.txt";
	saveFileDialog->FilterIndex = 2;
	saveFileDialog->RestoreDirectory = true;

	if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		std::string filename = CastingUtils::castAsString(saveFileDialog->FileName);
		FileWriter writer(filename);

		writer.write(CastingUtils::castAsString(this->keyLoggedArea->Text));

		System::Windows::Forms::DialogResult^ Show = System::Windows::Forms::MessageBox::Show(
			"Åêñïîğò ëîãóâàííÿ ïğîéøîâ óñï³øíî.",
			"Åêñïîğò",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Information
		);
	}
	StatusProgresBar::getProgressBar()->Value = 100;
	StatusLabelToolStrip::getToolStripStatusLabel()->Text = "100%";
}
private: System::Void çá³ëüøèòèToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	StatusProgresBar::getProgressBar()->Value = 0;
	StatusLabelToolStrip::getToolStripStatusLabel()->Text = "0%";
	std::int16_t size = this->keyLoggedArea->Font->Size;
	size += 1;
	this->keyLoggedArea->Font = (gcnew System::Drawing::Font(L"Roboto", size, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	StatusProgresBar::getProgressBar()->Value = 100;
	StatusLabelToolStrip::getToolStripStatusLabel()->Text = "100%";
}
private: System::Void çìåíøèòèToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	StatusProgresBar::getProgressBar()->Value = 0;
	StatusLabelToolStrip::getToolStripStatusLabel()->Text = "0%";
	std::int16_t size = this->keyLoggedArea->Font->Size - 1;
	this->keyLoggedArea->Font = (gcnew System::Drawing::Font(L"Roboto", size, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	StatusProgresBar::getProgressBar()->Value = 100;
	StatusLabelToolStrip::getToolStripStatusLabel()->Text = "100%";
}
};
}
