#pragma once

#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AttendanceForm : public System::Windows::Forms::Form
    {
    private:
        int studentId;
        Color primaryColor = Color::FromArgb(45, 52, 54);
        System::Windows::Forms::DataGridView^ dgvAttendance;
        System::Windows::Forms::Label^ lblTitle;

    public:
        AttendanceForm(int sid)
        {
            this->studentId = sid;
            InitializeComponent();
            LoadAttendance();
        }

    protected:
        ~AttendanceForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->dgvAttendance = (gcnew System::Windows::Forms::DataGridView());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvAttendance))->BeginInit();
            this->SuspendLayout();

            // lblTitle
            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16));
            this->lblTitle->ForeColor = primaryColor;
            this->lblTitle->Location = System::Drawing::Point(20, 20);
            this->lblTitle->Text = L"My Attendance Record";

            // dgvAttendance
            this->dgvAttendance->AllowUserToAddRows = false;
            this->dgvAttendance->AllowUserToDeleteRows = false;
            this->dgvAttendance->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvAttendance->BackgroundColor = System::Drawing::Color::White;
            this->dgvAttendance->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->dgvAttendance->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dgvAttendance->Location = System::Drawing::Point(20, 70);
            this->dgvAttendance->Name = L"dgvAttendance";
            this->dgvAttendance->ReadOnly = true;
            this->dgvAttendance->RowHeadersVisible = false;
            this->dgvAttendance->Size = System::Drawing::Size(760, 400);
            this->dgvAttendance->TabIndex = 0;

            // AttendanceForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(245, 246, 250);
            this->ClientSize = System::Drawing::Size(800, 500);
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->dgvAttendance);
            this->Name = L"AttendanceForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"My Attendance";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvAttendance))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void LoadAttendance() {
            dgvAttendance->Columns->Clear();
            dgvAttendance->Columns->Add("Course", "Course Name");
            dgvAttendance->Columns->Add("Date", "Date");
            dgvAttendance->Columns->Add("Status", "Status");

            dgvAttendance->EnableHeadersVisualStyles = false;
            dgvAttendance->ColumnHeadersDefaultCellStyle->BackColor = primaryColor;
            dgvAttendance->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            dgvAttendance->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);

            List<String^>^ attendance = SIS::DataManager::ReadAttendanceForStudent(this->studentId);
            for each (String^ s in attendance) {
                array<String^>^ parts = s->Split('|');
                if (parts->Length >= 3) {
                    dgvAttendance->Rows->Add(parts[0], parts[1], parts[2]);
                }
            }
        }
    };
}
