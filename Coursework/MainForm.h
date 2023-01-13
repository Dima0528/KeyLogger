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
#include "FileWriter.h"
#include "FileReader.h"
#include "AboutProgramWindow.h"

namespace Coursework {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
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
			SetHook();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
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
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ проПрограмуToolStripMenuItem;
	private: System::Windows::Forms::ToolStrip^ toolStrip1;
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ зберегтиToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ вихідToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^ toolStripStartLog;
	private: System::Windows::Forms::ToolStripButton^ toolStripStopLog;
	private: System::Windows::Forms::ToolStripButton^ toolStripImportLog;
	private: System::Windows::Forms::ToolStripButton^ toolStripExportLog;








	private: System::Windows::Forms::ToolStripStatusLabel^ loggingMode;


	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::RichTextBox^ keyLoggedArea;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::MonthCalendar^ monthCalendar1;



	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->зберегтиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->вихідToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->проПрограмуToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripStartLog = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripStopLog = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripImportLog = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripExportLog = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->loggingMode = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->keyLoggedArea = (gcnew System::Windows::Forms::RichTextBox());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->monthCalendar1 = (gcnew System::Windows::Forms::MonthCalendar());
			this->menuStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->файлToolStripMenuItem,
					this->проПрограмуToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(7, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1051, 33);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->зберегтиToolStripMenuItem,
					this->вихідToolStripMenuItem
			});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(69, 29);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// зберегтиToolStripMenuItem
			// 
			this->зберегтиToolStripMenuItem->Name = L"зберегтиToolStripMenuItem";
			this->зберегтиToolStripMenuItem->Size = System::Drawing::Size(187, 34);
			this->зберегтиToolStripMenuItem->Text = L"Зберегти";
			// 
			// вихідToolStripMenuItem
			// 
			this->вихідToolStripMenuItem->Name = L"вихідToolStripMenuItem";
			this->вихідToolStripMenuItem->Size = System::Drawing::Size(187, 34);
			this->вихідToolStripMenuItem->Text = L"Вихід";
			// 
			// проПрограмуToolStripMenuItem
			// 
			this->проПрограмуToolStripMenuItem->Name = L"проПрограмуToolStripMenuItem";
			this->проПрограмуToolStripMenuItem->Size = System::Drawing::Size(149, 29);
			this->проПрограмуToolStripMenuItem->Text = L"Про програму";
			this->проПрограмуToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::проПрограмуToolStripMenuItem_Click);
			// 
			// toolStrip1
			// 
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->toolStripStartLog,
					this->toolStripStopLog, this->toolStripImportLog, this->toolStripExportLog
			});
			this->toolStrip1->Location = System::Drawing::Point(0, 33);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(1051, 29);
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripStartLog
			// 
			this->toolStripStartLog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripStartLog->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripStartLog.Image")));
			this->toolStripStartLog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripStartLog->Name = L"toolStripStartLog";
			this->toolStripStartLog->Size = System::Drawing::Size(34, 24);
			this->toolStripStartLog->Text = L"Увімкнути логування";
			this->toolStripStartLog->Click += gcnew System::EventHandler(this, &MainForm::toolStripLoggingStartButton_Click);
			// 
			// toolStripStopLog
			// 
			this->toolStripStopLog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripStopLog->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripStopLog.Image")));
			this->toolStripStopLog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripStopLog->Name = L"toolStripStopLog";
			this->toolStripStopLog->Size = System::Drawing::Size(34, 24);
			this->toolStripStopLog->Text = L"Вимкнути логування";
			this->toolStripStopLog->Click += gcnew System::EventHandler(this, &MainForm::toolStripLoggingStopLog_Click);
			// 
			// toolStripImportLog
			// 
			this->toolStripImportLog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripImportLog->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripImportLog.Image")));
			this->toolStripImportLog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripImportLog->Name = L"toolStripImportLog";
			this->toolStripImportLog->Size = System::Drawing::Size(34, 24);
			this->toolStripImportLog->Text = L"Імпортувати лог";
			this->toolStripImportLog->Click += gcnew System::EventHandler(this, &MainForm::toolStripImportLog_Click);
			// 
			// toolStripExportLog
			// 
			this->toolStripExportLog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripExportLog->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripExportLog.Image")));
			this->toolStripExportLog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripExportLog->Name = L"toolStripExportLog";
			this->toolStripExportLog->Size = System::Drawing::Size(34, 24);
			this->toolStripExportLog->Text = L"Експортувати лог";
			this->toolStripExportLog->Click += gcnew System::EventHandler(this, &MainForm::toolStripExportLog_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loggingMode });
			this->statusStrip1->Location = System::Drawing::Point(0, 550);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Padding = System::Windows::Forms::Padding(1, 0, 16, 0);
			this->statusStrip1->Size = System::Drawing::Size(1051, 32);
			this->statusStrip1->TabIndex = 2;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// loggingMode
			// 
			this->loggingMode->Name = L"loggingMode";
			this->loggingMode->Size = System::Drawing::Size(189, 25);
			this->loggingMode->Text = L"Логування увімкнено";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				23.69172F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				76.30828F)));
			this->tableLayoutPanel1->Controls->Add(this->keyLoggedArea, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 62);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1051, 488);
			this->tableLayoutPanel1->TabIndex = 3;
			// 
			// keyLoggedArea
			// 
			this->keyLoggedArea->Dock = System::Windows::Forms::DockStyle::Fill;
			this->keyLoggedArea->Location = System::Drawing::Point(251, 3);
			this->keyLoggedArea->Margin = System::Windows::Forms::Padding(3, 3, 20, 10);
			this->keyLoggedArea->Name = L"keyLoggedArea";
			this->keyLoggedArea->ReadOnly = true;
			this->keyLoggedArea->Size = System::Drawing::Size(780, 475);
			this->keyLoggedArea->TabIndex = 0;
			this->keyLoggedArea->Text = L"";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->monthCalendar1, 0, 1);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 45.22821F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 54.77179F)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(242, 482);
			this->tableLayoutPanel2->TabIndex = 1;
			// 
			// monthCalendar1
			// 
			this->monthCalendar1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->monthCalendar1->Location = System::Drawing::Point(9, 226);
			this->monthCalendar1->Name = L"monthCalendar1";
			this->monthCalendar1->TabIndex = 0;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1051, 582);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"MainForm";
			this->Text = L"Логер клавіаутри";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
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
				"Імпорт логування пройшов успішно.",
				"Імпорт",
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
				"Експорт логування пройшов успішно.",
				"Експорт",
				System::Windows::Forms::MessageBoxButtons::OK,
				System::Windows::Forms::MessageBoxIcon::Information
			);
		}
	}
	private: System::Void проПрограмуToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		AboutProgramWindow^ aboutProgram = gcnew AboutProgramWindow();
		aboutProgram->ShowDialog();
	}
};
}
