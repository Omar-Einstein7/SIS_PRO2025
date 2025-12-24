#pragma once

#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AdminScheduleMgmtForm : public System::Windows::Forms::Form
    {
    private:
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        Color primaryColor = Color::FromArgb(45, 52, 54);

        System::Windows::Forms::Panel^ pnlHeader;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::DataGridView^ dgvSchedules;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnClose;

        // Input Fields
        System::Windows::Forms::ComboBox^ cmbCourse;
        System::Windows::Forms::ComboBox^ cmbProfessor;
        System::Windows::Forms::ComboBox^ cmbFaculty;
        System::Windows::Forms::ComboBox^ cmbDepartment;
        System::Windows::Forms::ComboBox^ cmbLevel;
        System::Windows::Forms::ComboBox^ cmbDay;
        System::Windows::Forms::ComboBox^ cmbLocation;
        System::Windows::Forms::CheckBox^ chkCustomLocation;
        System::Windows::Forms::TextBox^ txtCustomLocation;
        System::Windows::Forms::DateTimePicker^ dtpStart;
        System::Windows::Forms::DateTimePicker^ dtpEnd;
        System::Windows::Forms::ComboBox^ cmbYear;
        System::Windows::Forms::ComboBox^ cmbSemester;

    public:
        AdminScheduleMgmtForm()
        {
            InitializeComponent();
            ApplyModernTheme();
            LoadData();
        }

    private:
        void InitializeComponent(void)
        {
            this->pnlHeader = (gcnew System::Windows::Forms::Panel());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->dgvSchedules = (gcnew System::Windows::Forms::DataGridView());
            this->btnAdd = (gcnew System::Windows::Forms::Button());
            this->btnDelete = (gcnew System::Windows::Forms::Button());
            this->btnClose = (gcnew System::Windows::Forms::Button());

            this->cmbCourse = (gcnew System::Windows::Forms::ComboBox());
            this->cmbProfessor = (gcnew System::Windows::Forms::ComboBox());
            this->cmbFaculty = (gcnew System::Windows::Forms::ComboBox());
            this->cmbDepartment = (gcnew System::Windows::Forms::ComboBox());
            this->cmbLevel = (gcnew System::Windows::Forms::ComboBox());
            this->cmbDay = (gcnew System::Windows::Forms::ComboBox());
            this->cmbLocation = (gcnew System::Windows::Forms::ComboBox());
            this->chkCustomLocation = (gcnew System::Windows::Forms::CheckBox());
            this->txtCustomLocation = (gcnew System::Windows::Forms::TextBox());
            this->dtpStart = (gcnew System::Windows::Forms::DateTimePicker());
            this->dtpEnd = (gcnew System::Windows::Forms::DateTimePicker());
            this->cmbYear = (gcnew System::Windows::Forms::ComboBox());
            this->cmbSemester = (gcnew System::Windows::Forms::ComboBox());

            this->pnlHeader->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvSchedules))->BeginInit();
            this->SuspendLayout();

            // Header
            this->pnlHeader->BackColor = System::Drawing::Color::White;
            this->pnlHeader->Controls->Add(this->lblTitle);
            this->pnlHeader->Dock = System::Windows::Forms::DockStyle::Top;
            this->pnlHeader->Size = System::Drawing::Size(1000, 70);

            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16));
            this->lblTitle->Location = System::Drawing::Point(20, 20);
            this->lblTitle->Text = L"Schedule Management";

            // Inputs Row 1
            CreateLabel("Course:", 20, 90);
            this->cmbCourse->Location = System::Drawing::Point(20, 115);
            this->cmbCourse->Size = System::Drawing::Size(180, 25);
            this->cmbCourse->DropDownStyle = ComboBoxStyle::DropDownList;

            CreateLabel("Professor:", 210, 90);
            this->cmbProfessor->Location = System::Drawing::Point(210, 115);
            this->cmbProfessor->Size = System::Drawing::Size(180, 25);
            this->cmbProfessor->DropDownStyle = ComboBoxStyle::DropDownList;

            CreateLabel("Faculty:", 400, 90);
            this->cmbFaculty->Location = System::Drawing::Point(400, 115);
            this->cmbFaculty->Size = System::Drawing::Size(180, 25);
            this->cmbFaculty->DropDownStyle = ComboBoxStyle::DropDownList;

            CreateLabel("Department:", 590, 90);
            this->cmbDepartment->Location = System::Drawing::Point(590, 115);
            this->cmbDepartment->Size = System::Drawing::Size(180, 25);
            this->cmbDepartment->DropDownStyle = ComboBoxStyle::DropDownList;

            CreateLabel("Level:", 780, 90);
            this->cmbLevel->Location = System::Drawing::Point(780, 115);
            this->cmbLevel->Size = System::Drawing::Size(180, 25);
            this->cmbLevel->DropDownStyle = ComboBoxStyle::DropDownList;

            // Inputs Row 2
            CreateLabel("Day:", 20, 150);
            this->cmbDay->Location = System::Drawing::Point(20, 175);
            this->cmbDay->Size = System::Drawing::Size(120, 25);
            this->cmbDay->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbDay->Items->AddRange(gcnew array<Object^>{ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" });

            CreateLabel("Location:", 150, 150);
            this->cmbLocation->Location = System::Drawing::Point(150, 175);
            this->cmbLocation->Size = System::Drawing::Size(180, 25);
            this->cmbLocation->DropDownStyle = ComboBoxStyle::DropDownList;

            this->chkCustomLocation->AutoSize = true;
            this->chkCustomLocation->Location = System::Drawing::Point(340, 150);
            this->chkCustomLocation->Text = L"Custom Location";
            this->chkCustomLocation->CheckedChanged += gcnew System::EventHandler(this, &AdminScheduleMgmtForm::chkCustomLocation_CheckedChanged);

            this->txtCustomLocation->Location = System::Drawing::Point(340, 175);
            this->txtCustomLocation->Size = System::Drawing::Size(150, 25);
            this->txtCustomLocation->Visible = false;

            CreateLabel("Start Time:", 500, 150);
            this->dtpStart->Location = System::Drawing::Point(500, 175);
            this->dtpStart->Size = System::Drawing::Size(80, 25);
            this->dtpStart->Format = DateTimePickerFormat::Custom;
            this->dtpStart->CustomFormat = "HH:mm";
            this->dtpStart->ShowUpDown = true;

            CreateLabel("End Time:", 590, 150);
            this->dtpEnd->Location = System::Drawing::Point(590, 175);
            this->dtpEnd->Size = System::Drawing::Size(80, 25);
            this->dtpEnd->Format = DateTimePickerFormat::Custom;
            this->dtpEnd->CustomFormat = "HH:mm";
            this->dtpEnd->ShowUpDown = true;

            CreateLabel("Year:", 680, 150);
            this->cmbYear->Location = System::Drawing::Point(680, 175);
            this->cmbYear->Size = System::Drawing::Size(120, 25);
            this->cmbYear->DropDownStyle = ComboBoxStyle::DropDownList;

            CreateLabel("Semester:", 810, 150);
            this->cmbSemester->Location = System::Drawing::Point(810, 175);
            this->cmbSemester->Size = System::Drawing::Size(120, 25);
            this->cmbSemester->DropDownStyle = ComboBoxStyle::DropDownList;

            // DataGridView
            this->dgvSchedules->AllowUserToAddRows = false;
            this->dgvSchedules->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvSchedules->BackgroundColor = Color::White;
            this->dgvSchedules->Location = System::Drawing::Point(20, 220);
            this->dgvSchedules->Size = System::Drawing::Size(960, 300);
            this->dgvSchedules->RowHeadersVisible = false;
            this->dgvSchedules->SelectionMode = DataGridViewSelectionMode::FullRowSelect;

            // Buttons
            this->btnAdd->Location = System::Drawing::Point(20, 540);
            this->btnAdd->Size = System::Drawing::Size(120, 40);
            this->btnAdd->Text = L"Add Schedule";
            this->btnAdd->Click += gcnew System::EventHandler(this, &AdminScheduleMgmtForm::btnAdd_Click);

            this->btnDelete->Location = System::Drawing::Point(150, 540);
            this->btnDelete->Size = System::Drawing::Size(120, 40);
            this->btnDelete->Text = L"Delete Selected";
            this->btnDelete->Click += gcnew System::EventHandler(this, &AdminScheduleMgmtForm::btnDelete_Click);

            this->btnClose->Location = System::Drawing::Point(860, 540);
            this->btnClose->Size = System::Drawing::Size(120, 40);
            this->btnClose->Text = L"Close";
            this->btnClose->Click += gcnew System::EventHandler(this, &AdminScheduleMgmtForm::btnClose_Click);

            // Form
            this->ClientSize = System::Drawing::Size(1000, 600);
            this->Controls->Add(this->pnlHeader);
            this->Controls->Add(this->dgvSchedules);
            this->Controls->Add(this->btnAdd);
            this->Controls->Add(this->btnDelete);
            this->Controls->Add(this->btnClose);
            this->Controls->Add(this->cmbCourse);
            this->Controls->Add(this->cmbProfessor);
            this->Controls->Add(this->cmbFaculty);
            this->Controls->Add(this->cmbDepartment);
            this->Controls->Add(this->cmbLevel);
            this->Controls->Add(this->cmbDay);
            this->Controls->Add(this->cmbLocation);
            this->Controls->Add(this->chkCustomLocation);
            this->Controls->Add(this->txtCustomLocation);
            this->Controls->Add(this->dtpStart);
            this->Controls->Add(this->dtpEnd);
            this->Controls->Add(this->cmbYear);
            this->Controls->Add(this->cmbSemester);

            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = L"Schedule Management";

            this->pnlHeader->ResumeLayout(false);
            this->pnlHeader->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvSchedules))->EndInit();
            this->ResumeLayout(false);
        }

        void CreateLabel(String^ text, int x, int y) {
            Label^ lbl = gcnew Label();
            lbl->Text = text;
            lbl->Location = Point(x, y);
            lbl->AutoSize = true;
            lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            lbl->ForeColor = Color::FromArgb(99, 110, 114);
            this->Controls->Add(lbl);
        }

        void ApplyModernTheme() {
            this->BackColor = bgColor;
            lblTitle->ForeColor = primaryColor;

            array<Button^>^ btns = { btnAdd, btnDelete, btnClose };
            for each (Button^ btn in btns) {
                btn->FlatStyle = FlatStyle::Flat;
                btn->FlatAppearance->BorderSize = 0;
                btn->ForeColor = Color::White;
                btn->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            }
            btnAdd->BackColor = accentColor;
            btnDelete->BackColor = Color::FromArgb(231, 76, 60);
            btnClose->BackColor = Color::FromArgb(149, 165, 166);

            dgvSchedules->EnableHeadersVisualStyles = false;
            dgvSchedules->ColumnHeadersDefaultCellStyle->BackColor = primaryColor;
            dgvSchedules->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            dgvSchedules->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
        }

        void LoadData() {
            // Courses
            cmbCourse->Items->Clear();
            List<String^>^ courses = SIS::DataManager::ReadAllCourses();
            for each (String^ s in courses) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) cmbCourse->Items->Add(p[0] + " - " + p[1]);
            }

            // Professors
            cmbProfessor->Items->Clear();
            List<String^>^ profs = SIS::DataManager::ReadAllProfessorsSimple();
            for each (String^ s in profs) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) cmbProfessor->Items->Add(p[0] + " - " + p[1]);
            }

            // Faculty
            cmbFaculty->Items->Clear();
            List<String^>^ faculties = SIS::DataManager::ReadAllFaculties();
            for each (String^ s in faculties) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) cmbFaculty->Items->Add(p[0] + " - " + p[1]);
            }

            // Department
            cmbDepartment->Items->Clear();
            List<String^>^ depts = SIS::DataManager::ReadAllDepartments();
            for each (String^ s in depts) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) cmbDepartment->Items->Add(p[0] + " - " + p[1]);
            }

            // Levels
            cmbLevel->Items->Clear();
            List<String^>^ levels = SIS::DataManager::ReadAllAcademicLevels();
            for each (String^ s in levels) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) cmbLevel->Items->Add(p[0] + " - " + p[1]);
            }

            // Locations
            cmbLocation->Items->Clear();
            List<String^>^ locs = SIS::DataManager::ReadAllLocationsSimple();
            for each (String^ s in locs) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) cmbLocation->Items->Add(p[0] + " - " + p[1]);
            }

            // Years
            cmbYear->Items->Clear();
            List<String^>^ years = SIS::DataManager::ReadAllAcademicYears();
            for each (String^ s in years) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) cmbYear->Items->Add(p[0] + " - " + p[1]);
            }

            // Semesters
            cmbSemester->Items->Clear();
            List<String^>^ semesters = SIS::DataManager::ReadAllSemesters();
            for each (String^ s in semesters) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) cmbSemester->Items->Add(p[0] + " - " + p[1]);
            }

            LoadScheduleList();
        }

        void LoadScheduleList() {
            dgvSchedules->Columns->Clear();
            dgvSchedules->Columns->Add("ID", "ID");
            dgvSchedules->Columns->Add("Course", "Course");
            dgvSchedules->Columns->Add("Prof", "Professor");
            dgvSchedules->Columns->Add("Faculty", "Faculty");
            dgvSchedules->Columns->Add("Dept", "Dept");
            dgvSchedules->Columns->Add("Level", "Level");
            dgvSchedules->Columns->Add("Day", "Day");
            dgvSchedules->Columns->Add("Start", "Start");
            dgvSchedules->Columns->Add("End", "End");
            dgvSchedules->Columns->Add("Location", "Location");

            List<String^>^ sch = SIS::DataManager::ReadAllSchedules();
            for each (String^ s in sch) {
                array<String^>^ p = s->Split('|');
                if (p->Length >= 10) {
                    dgvSchedules->Rows->Add(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
                }
            }
        }

        System::Void chkCustomLocation_CheckedChanged(Object^ sender, EventArgs^ e) {
            cmbLocation->Enabled = !chkCustomLocation->Checked;
            txtCustomLocation->Visible = chkCustomLocation->Checked;
            if (chkCustomLocation->Checked) {
                cmbLocation->SelectedIndex = -1;
            } else {
                txtCustomLocation->Clear();
            }
        }

        System::Void btnAdd_Click(Object^ sender, EventArgs^ e) {
            if (cmbCourse->SelectedIndex == -1 || cmbProfessor->SelectedIndex == -1 || 
                cmbFaculty->SelectedIndex == -1 || cmbDepartment->SelectedIndex == -1 || 
                cmbLevel->SelectedIndex == -1 || cmbDay->SelectedIndex == -1 || 
                (cmbLocation->SelectedIndex == -1 && !chkCustomLocation->Checked) || 
                (chkCustomLocation->Checked && String::IsNullOrWhiteSpace(txtCustomLocation->Text)) ||
                cmbYear->SelectedIndex == -1 || 
                cmbSemester->SelectedIndex == -1) {
                MessageBox::Show("Please fill all fields.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try {
                int cid = Int32::Parse(cmbCourse->SelectedItem->ToString()->Split('-')[0]->Trim());
                int iid = Int32::Parse(cmbProfessor->SelectedItem->ToString()->Split('-')[0]->Trim());
                int fid = Int32::Parse(cmbFaculty->SelectedItem->ToString()->Split('-')[0]->Trim());
                int did = Int32::Parse(cmbDepartment->SelectedItem->ToString()->Split('-')[0]->Trim());
                int alid = Int32::Parse(cmbLevel->SelectedItem->ToString()->Split('-')[0]->Trim());
                
                int lid = -1;
                String^ customLoc = "";
                if (chkCustomLocation->Checked) {
                    customLoc = txtCustomLocation->Text;
                } else {
                    lid = Int32::Parse(cmbLocation->SelectedItem->ToString()->Split('-')[0]->Trim());
                }

                int yid = Int32::Parse(cmbYear->SelectedItem->ToString()->Split('-')[0]->Trim());
                int sid = Int32::Parse(cmbSemester->SelectedItem->ToString()->Split('-')[0]->Trim());
                String^ day = cmbDay->SelectedItem->ToString();
                String^ start = dtpStart->Value.ToString("HH:mm:ss");
                String^ end = dtpEnd->Value.ToString("HH:mm:ss");

                String^ result = SIS::DataManager::SaveScheduleWithResult(cid, iid, yid, sid, lid, customLoc, fid, did, alid, day, start, end);
                if (result == "SUCCESS") {
                    MessageBox::Show("Schedule added successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    LoadScheduleList();
                } else {
                    MessageBox::Show("Failed to add schedule: " + result, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            } catch (Exception^ ex) {
                MessageBox::Show("Error parsing data: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void btnDelete_Click(Object^ sender, EventArgs^ e) {
            if (dgvSchedules->SelectedRows->Count == 0) return;
            int id = Int32::Parse(dgvSchedules->SelectedRows[0]->Cells["ID"]->Value->ToString());
            if (MessageBox::Show("Delete this schedule?", "Confirm", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
                if (SIS::DataManager::DeleteSchedule(id)) {
                    LoadScheduleList();
                }
            }
        }

        System::Void btnClose_Click(Object^ sender, EventArgs^ e) {
            this->Close();
        }
    };
}
