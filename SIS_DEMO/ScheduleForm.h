#pragma once

#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class ScheduleForm : public System::Windows::Forms::Form
    {
    private:
        int studentId;
        Color primaryColor = Color::FromArgb(45, 52, 54);
        Color accentColor = Color::FromArgb(9, 132, 227);
        System::Windows::Forms::DataGridView^ dgvSchedule;
        System::Windows::Forms::Label^ lblTitle;

    public:
        ScheduleForm(int sid)
        {
            this->studentId = sid;
            InitializeComponent();
            LoadSchedule();
        }

    protected:
        ~ScheduleForm()
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
            this->dgvSchedule = (gcnew System::Windows::Forms::DataGridView());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvSchedule))->BeginInit();
            this->SuspendLayout();

            // lblTitle
            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16));
            this->lblTitle->ForeColor = primaryColor;
            this->lblTitle->Location = System::Drawing::Point(20, 20);
            this->lblTitle->Text = L"My Academic Schedule";

            // dgvSchedule
            this->dgvSchedule->AllowUserToAddRows = false;
            this->dgvSchedule->AllowUserToDeleteRows = false;
            this->dgvSchedule->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvSchedule->BackgroundColor = System::Drawing::Color::White;
            this->dgvSchedule->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->dgvSchedule->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dgvSchedule->Location = System::Drawing::Point(20, 70);
            this->dgvSchedule->Name = L"dgvSchedule";
            this->dgvSchedule->ReadOnly = true;
            this->dgvSchedule->RowHeadersVisible = false;
            this->dgvSchedule->Size = System::Drawing::Size(760, 400);
            this->dgvSchedule->TabIndex = 0;

            // ScheduleForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(245, 246, 250);
            this->ClientSize = System::Drawing::Size(800, 500);
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->dgvSchedule);
            this->Name = L"ScheduleForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Academic Schedule";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvSchedule))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void LoadSchedule() {
            dgvSchedule->Columns->Clear();
            dgvSchedule->Columns->Add("Day", "Day");
            dgvSchedule->Columns->Add("Course", "Course");
            dgvSchedule->Columns->Add("Professor", "Professor");
            dgvSchedule->Columns->Add("Location", "Location");
            dgvSchedule->Columns->Add("Start", "Start");
            dgvSchedule->Columns->Add("End", "End");

            dgvSchedule->EnableHeadersVisualStyles = false;
            dgvSchedule->ColumnHeadersDefaultCellStyle->BackColor = primaryColor;
            dgvSchedule->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            dgvSchedule->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);

            List<String^>^ schedule = SIS::DataManager::ReadScheduleForStudent(this->studentId);
            for each (String^ s in schedule) {
                array<String^>^ parts = s->Split('|');
                if (parts->Length >= 6) {
                    dgvSchedule->Rows->Add(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5]);
                }
            }
        }
    };
}
