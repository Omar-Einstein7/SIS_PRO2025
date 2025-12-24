#pragma once

#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class TakeAttendanceForm : public System::Windows::Forms::Form
    {
    private:
        int profId;
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        Color primaryColor = Color::FromArgb(45, 52, 54);

        System::Windows::Forms::Panel^ pnlHeader;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::ComboBox^ cmbCourse;
        System::Windows::Forms::ComboBox^ cmbSemester;
        System::Windows::Forms::DateTimePicker^ dtpDate;
        System::Windows::Forms::DataGridView^ dgvStudents;
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnClose;
        System::Windows::Forms::Label^ lblCourse;
        System::Windows::Forms::Label^ lblSemester;
        System::Windows::Forms::Label^ lblDate;

    public:
        TakeAttendanceForm(int id)
        {
            this->profId = id;
            InitializeComponent();
            ApplyModernTheme();
            LoadInitialData();
        }

    private:
        void InitializeComponent(void)
        {
            this->pnlHeader = (gcnew System::Windows::Forms::Panel());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->cmbCourse = (gcnew System::Windows::Forms::ComboBox());
            this->cmbSemester = (gcnew System::Windows::Forms::ComboBox());
            this->dtpDate = (gcnew System::Windows::Forms::DateTimePicker());
            this->dgvStudents = (gcnew System::Windows::Forms::DataGridView());
            this->btnSave = (gcnew System::Windows::Forms::Button());
            this->btnClose = (gcnew System::Windows::Forms::Button());
            this->lblCourse = (gcnew System::Windows::Forms::Label());
            this->lblSemester = (gcnew System::Windows::Forms::Label());
            this->lblDate = (gcnew System::Windows::Forms::Label());

            this->pnlHeader->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvStudents))->BeginInit();
            this->SuspendLayout();

            // pnlHeader
            this->pnlHeader->BackColor = System::Drawing::Color::White;
            this->pnlHeader->Controls->Add(this->lblTitle);
            this->pnlHeader->Dock = System::Windows::Forms::DockStyle::Top;
            this->pnlHeader->Location = System::Drawing::Point(0, 0);
            this->pnlHeader->Size = System::Drawing::Size(800, 70);

            // lblTitle
            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16));
            this->lblTitle->Location = System::Drawing::Point(20, 20);
            this->lblTitle->Text = L"Take Attendance";

            // lblCourse
            this->lblCourse->Location = System::Drawing::Point(20, 90);
            this->lblCourse->Text = L"Select Course:";
            this->lblCourse->Size = System::Drawing::Size(200, 20);

            // cmbCourse
            this->cmbCourse->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbCourse->Location = System::Drawing::Point(20, 115);
            this->cmbCourse->Size = System::Drawing::Size(250, 25);
            this->cmbCourse->SelectedIndexChanged += gcnew System::EventHandler(this, &TakeAttendanceForm::OnFilterChanged);

            // lblSemester
            this->lblSemester->Location = System::Drawing::Point(290, 90);
            this->lblSemester->Text = L"Select Semester:";
            this->lblSemester->Size = System::Drawing::Size(200, 20);

            // cmbSemester
            this->cmbSemester->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbSemester->Location = System::Drawing::Point(290, 115);
            this->cmbSemester->Size = System::Drawing::Size(250, 25);
            this->cmbSemester->SelectedIndexChanged += gcnew System::EventHandler(this, &TakeAttendanceForm::OnFilterChanged);

            // lblDate
            this->lblDate->Location = System::Drawing::Point(560, 90);
            this->lblDate->Text = L"Lecture Date:";
            this->lblDate->Size = System::Drawing::Size(200, 20);

            // dtpDate
            this->dtpDate->Format = DateTimePickerFormat::Short;
            this->dtpDate->Location = System::Drawing::Point(560, 115);
            this->dtpDate->Size = System::Drawing::Size(200, 25);

            // dgvStudents
            this->dgvStudents->AllowUserToAddRows = false;
            this->dgvStudents->AllowUserToDeleteRows = false;
            this->dgvStudents->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvStudents->BackgroundColor = Color::White;
            this->dgvStudents->BorderStyle = BorderStyle::None;
            this->dgvStudents->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dgvStudents->Location = System::Drawing::Point(20, 160);
            this->dgvStudents->Size = System::Drawing::Size(760, 350);
            this->dgvStudents->RowHeadersVisible = false;

            // btnSave
            this->btnSave->Location = System::Drawing::Point(540, 530);
            this->btnSave->Size = System::Drawing::Size(110, 40);
            this->btnSave->Text = L"Save";
            this->btnSave->Click += gcnew System::EventHandler(this, &TakeAttendanceForm::btnSave_Click);

            // btnClose
            this->btnClose->Location = System::Drawing::Point(670, 530);
            this->btnClose->Size = System::Drawing::Size(110, 40);
            this->btnClose->Text = L"Close";
            this->btnClose->Click += gcnew System::EventHandler(this, &TakeAttendanceForm::btnClose_Click);

            // TakeAttendanceForm
            this->ClientSize = System::Drawing::Size(800, 600);
            this->Controls->Add(this->pnlHeader);
            this->Controls->Add(this->lblCourse);
            this->Controls->Add(this->cmbCourse);
            this->Controls->Add(this->lblSemester);
            this->Controls->Add(this->cmbSemester);
            this->Controls->Add(this->lblDate);
            this->Controls->Add(this->dtpDate);
            this->Controls->Add(this->dgvStudents);
            this->Controls->Add(this->btnSave);
            this->Controls->Add(this->btnClose);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = L"Take Attendance";

            this->pnlHeader->ResumeLayout(false);
            this->pnlHeader->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvStudents))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void ApplyModernTheme() {
            this->BackColor = bgColor;
            lblTitle->ForeColor = primaryColor;
            
            array<Label^>^ labels = { lblCourse, lblSemester, lblDate };
            for each (Label^ lbl in labels) {
                lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
                lbl->ForeColor = Color::FromArgb(99, 110, 114);
            }

            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->BackColor = accentColor;
            btnSave->ForeColor = Color::White;
            btnSave->FlatAppearance->BorderSize = 0;
            btnSave->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);

            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->BackColor = Color::FromArgb(178, 190, 195);
            btnClose->ForeColor = Color::White;
            btnClose->FlatAppearance->BorderSize = 0;
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);

            dgvStudents->EnableHeadersVisualStyles = false;
            dgvStudents->ColumnHeadersDefaultCellStyle->BackColor = primaryColor;
            dgvStudents->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            dgvStudents->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
        }

        void LoadInitialData() {
            // Load Courses
            cmbCourse->Items->Clear();
            List<String^>^ courses = SIS::DataManager::ReadCoursesByProfessor(this->profId);
            for each (String^ c in courses) {
                array<String^>^ p = c->Split(',');
                if (p->Length >= 2) cmbCourse->Items->Add(p[0] + " - " + p[1]);
            }

            // Load Semesters
            cmbSemester->Items->Clear();
            List<String^>^ semesters = SIS::DataManager::ReadAllSemesters();
            for each (String^ s in semesters) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) cmbSemester->Items->Add(p[0] + " - " + p[1]);
            }

            if (cmbCourse->Items->Count > 0) cmbCourse->SelectedIndex = 0;
            if (cmbSemester->Items->Count > 0) cmbSemester->SelectedIndex = 0;
        }

        void OnFilterChanged(Object^ sender, EventArgs^ e) {
            LoadStudents();
        }

        void LoadStudents() {
            if (cmbCourse->SelectedIndex == -1 || cmbSemester->SelectedIndex == -1) return;

            int courseId = Int32::Parse(cmbCourse->SelectedItem->ToString()->Split(' ')[0]);
            int semesterId = Int32::Parse(cmbSemester->SelectedItem->ToString()->Split(' ')[0]);

            dgvStudents->Columns->Clear();
            dgvStudents->Columns->Add("ID", "Student ID");
            dgvStudents->Columns->Add("Name", "Student Name");
            
            DataGridViewCheckBoxColumn^ checkCol = gcnew DataGridViewCheckBoxColumn();
            checkCol->Name = "Present";
            checkCol->HeaderText = "Present";
            dgvStudents->Columns->Add(checkCol);

            List<String^>^ students = SIS::DataManager::ReadStudentsByCourse(courseId, semesterId);
            for each (String^ s in students) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) {
                    dgvStudents->Rows->Add(p[0], p[1], true); // Default to Present
                }
            }
        }

        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
            if (dgvStudents->Rows->Count == 0) return;

            if (cmbCourse->SelectedIndex == -1 || cmbSemester->SelectedIndex == -1) return;

            int courseId = Int32::Parse(cmbCourse->SelectedItem->ToString()->Split(' ')[0]);
            int semesterId = Int32::Parse(cmbSemester->SelectedItem->ToString()->Split(' ')[0]);
            String^ date = dtpDate->Value.ToString("yyyy-MM-dd");

            int savedCount = 0;
            for (int i = 0; i < dgvStudents->Rows->Count; i++) {
                Object^ idVal = dgvStudents->Rows[i]->Cells["ID"]->Value;
                if (idVal == nullptr) continue;

                int studentId = Int32::Parse(idVal->ToString());
                
                bool isPresent = false;
                Object^ checkVal = dgvStudents->Rows[i]->Cells["Present"]->Value;
                if (checkVal != nullptr) {
                    isPresent = (bool)checkVal;
                }
                
                String^ status = isPresent ? "Present" : "Absent";

                if (SIS::DataManager::SaveAttendance(studentId, courseId, semesterId, date, status)) {
                    savedCount++;
                }
            }

            MessageBox::Show(String::Format("Attendance saved for {0} students.", savedCount), 
                "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}
