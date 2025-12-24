#pragma once

#include <msclr/marshal_cppstd.h>
#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class RegisterStudentForm : public System::Windows::Forms::Form
    {
    private:
        // Modern UI Colors
        Color primaryColor = Color::FromArgb(45, 52, 54);
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        System::Windows::Forms::Panel^ pnlCard;
        System::Windows::Forms::Label^ lblTitle;

    public:
        RegisterStudentForm(void)
        {
            InitializeComponent();
            ApplyModernTheme();
            editMode = false;
            originalId = -1;
            LoadMetaData();
        }

        RegisterStudentForm(int id)
        {
            InitializeComponent();
            ApplyModernTheme();
            editMode = true;
            originalId = id;
            LoadMetaData();
            // load student
            String^ line = SIS::DataManager::GetStudentById(id);
            if (!String::IsNullOrEmpty(line)) {
                array<String^>^ parts = line->Split('|');
                if (parts->Length >= 12) {
                    this->txtID->Text = parts[0];
                    this->txtFirstName->Text = parts[1];
                    this->txtEmail->Text = parts[2];
                    this->txtPhone->Text = parts[3];
                    this->txtNationalID->Text = parts[4];

                    // Select Dept
                    SelectComboItemById(cmbDept, parts[5]);
                    // Select Faculty
                    SelectComboItemById(cmbFaculty, parts[6]);
                    // Select Level
                    SelectComboItemById(cmbLevel, parts[7]);
                    // Select Year
                    SelectComboItemById(cmbYear, parts[8]);
                    // Select Semester
                    SelectComboItemById(cmbSemester, parts[9]);

                    this->txtGroup->Text = parts[10];
                    this->txtSection->Text = parts[11];

                    this->txtID->ReadOnly = true; 
                    this->txtUser->Enabled = false;
                    this->txtPass->Enabled = false;
                }
            }
        }

    private:
        void SelectComboItemById(ComboBox^ cmb, String^ id) {
            for (int i = 0; i < cmb->Items->Count; i++) {
                if (cmb->Items[i]->ToString()->StartsWith(id + " - ")) {
                    cmb->SelectedIndex = i;
                    break;
                }
            }
        }

        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, FontStyle::Bold);
            lblTitle->ForeColor = primaryColor;

            array<Label^>^ labels = { 
                lblID, lblUser, lblPass, lblFirstName, 
                lblEmail, lblPhone, lblNationalID, lblDeptID,
                lblFaculty, lblLevel, lblYear, lblSemester,
                lblGroup, lblSection
            };
            for each (Label^ lbl in labels) {
                if (lbl == nullptr) continue;
                lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
                lbl->ForeColor = Color::FromArgb(99, 110, 114);
            }

            array<TextBox^>^ texts = { 
                txtID, txtUser, txtPass, txtFirstName, 
                txtEmail, txtPhone, txtNationalID,
                txtGroup, txtSection
            };
            for each (TextBox^ txt in texts) {
                if (txt == nullptr) continue;
                txt->BorderStyle = BorderStyle::FixedSingle;
                txt->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            }

            array<ComboBox^>^ combos = { cmbDept, cmbFaculty, cmbLevel, cmbYear, cmbSemester };
            for each (ComboBox^ cmb in combos) {
                if (cmb == nullptr) continue;
                cmb->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            }

            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->BackColor = accentColor;
            btnSave->ForeColor = Color::White;
            btnSave->FlatAppearance->BorderSize = 0;
            btnSave->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);

            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->BackColor = Color::FromArgb(189, 195, 199);
            btnCancel->ForeColor = Color::White;
            btnCancel->FlatAppearance->BorderSize = 0;
            btnCancel->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        }

    private:
        void LoadMetaData() {
            // Load Faculties
            this->cmbFaculty->Items->Clear();
            for each (String^ s in SIS::DataManager::ReadAllFaculties()) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) this->cmbFaculty->Items->Add(p[0] + " - " + p[1]);
            }
            if (this->cmbFaculty->Items->Count > 0) this->cmbFaculty->SelectedIndex = 0;

            // Load Departments
            this->cmbDept->Items->Clear();
            for each (String^ d in SIS::DataManager::ReadAllDepartments()) {
                array<String^>^ p = d->Split(',');
                if (p->Length >= 2) this->cmbDept->Items->Add(p[0] + " - " + p[1]);
            }
            if (this->cmbDept->Items->Count > 0) this->cmbDept->SelectedIndex = 0;

            // Load Levels
            this->cmbLevel->Items->Clear();
            for each (String^ l in SIS::DataManager::ReadAllLevels()) {
                array<String^>^ p = l->Split(',');
                if (p->Length >= 2) this->cmbLevel->Items->Add(p[0] + " - " + p[1]);
            }
            if (this->cmbLevel->Items->Count > 0) this->cmbLevel->SelectedIndex = 0;

            // Load Years
            this->cmbYear->Items->Clear();
            for each (String^ y in SIS::DataManager::ReadAllYears()) {
                array<String^>^ p = y->Split(',');
                if (p->Length >= 2) this->cmbYear->Items->Add(p[0] + " - " + p[1]);
            }
            if (this->cmbYear->Items->Count > 0) this->cmbYear->SelectedIndex = 0;

            // Load Semesters
            this->cmbSemester->Items->Clear();
            for each (String^ sem in SIS::DataManager::ReadAllSemesters()) {
                array<String^>^ p = sem->Split(',');
                if (p->Length >= 2) this->cmbSemester->Items->Add(p[0] + " - " + p[1]);
            }
            if (this->cmbSemester->Items->Count > 0) this->cmbSemester->SelectedIndex = 0;
        }

    protected:
        ~RegisterStudentForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Label^ lblID;
    private: System::Windows::Forms::Label^ lblUser;
    private: System::Windows::Forms::Label^ lblPass;
    private: System::Windows::Forms::Label^ lblFirstName;
    private: System::Windows::Forms::Label^ lblEmail;
    private: System::Windows::Forms::Label^ lblPhone;
    private: System::Windows::Forms::Label^ lblNationalID;
    private: System::Windows::Forms::Label^ lblDeptID;
    private: System::Windows::Forms::Label^ lblFaculty;
    private: System::Windows::Forms::Label^ lblLevel;
    private: System::Windows::Forms::Label^ lblYear;
    private: System::Windows::Forms::Label^ lblSemester;
    private: System::Windows::Forms::Label^ lblGroup;
    private: System::Windows::Forms::Label^ lblSection;

    private: System::Windows::Forms::TextBox^ txtID;
    private: System::Windows::Forms::TextBox^ txtUser;
    private: System::Windows::Forms::TextBox^ txtPass;
    private: System::Windows::Forms::TextBox^ txtFirstName;
    private: System::Windows::Forms::TextBox^ txtEmail;
    private: System::Windows::Forms::TextBox^ txtPhone;
    private: System::Windows::Forms::TextBox^ txtNationalID;
    private: System::Windows::Forms::TextBox^ txtGroup;
    private: System::Windows::Forms::TextBox^ txtSection;
    private: System::Windows::Forms::ComboBox^ cmbDept;
    private: System::Windows::Forms::ComboBox^ cmbFaculty;
    private: System::Windows::Forms::ComboBox^ cmbLevel;
    private: System::Windows::Forms::ComboBox^ cmbYear;
    private: System::Windows::Forms::ComboBox^ cmbSemester;

    private: System::Windows::Forms::Button^ btnSave;
    private: System::Windows::Forms::Button^ btnCancel;
    private: System::ComponentModel::Container^ components;
    private: bool editMode;
    private: int originalId;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->lblID = (gcnew System::Windows::Forms::Label());
               this->lblUser = (gcnew System::Windows::Forms::Label());
               this->lblPass = (gcnew System::Windows::Forms::Label());
               this->lblFirstName = (gcnew System::Windows::Forms::Label());
               this->lblEmail = (gcnew System::Windows::Forms::Label());
               this->lblPhone = (gcnew System::Windows::Forms::Label());
               this->lblNationalID = (gcnew System::Windows::Forms::Label());
               this->lblDeptID = (gcnew System::Windows::Forms::Label());
               this->lblFaculty = (gcnew System::Windows::Forms::Label());
               this->lblLevel = (gcnew System::Windows::Forms::Label());
               this->lblYear = (gcnew System::Windows::Forms::Label());
               this->lblSemester = (gcnew System::Windows::Forms::Label());
               this->lblGroup = (gcnew System::Windows::Forms::Label());
               this->lblSection = (gcnew System::Windows::Forms::Label());
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->txtID = (gcnew System::Windows::Forms::TextBox());
               this->txtUser = (gcnew System::Windows::Forms::TextBox());
               this->txtPass = (gcnew System::Windows::Forms::TextBox());
               this->txtFirstName = (gcnew System::Windows::Forms::TextBox());
               this->txtEmail = (gcnew System::Windows::Forms::TextBox());
               this->txtPhone = (gcnew System::Windows::Forms::TextBox());
               this->txtNationalID = (gcnew System::Windows::Forms::TextBox());
               this->txtGroup = (gcnew System::Windows::Forms::TextBox());
               this->txtSection = (gcnew System::Windows::Forms::TextBox());
               this->cmbDept = (gcnew System::Windows::Forms::ComboBox());
               this->cmbFaculty = (gcnew System::Windows::Forms::ComboBox());
               this->cmbLevel = (gcnew System::Windows::Forms::ComboBox());
               this->cmbYear = (gcnew System::Windows::Forms::ComboBox());
               this->cmbSemester = (gcnew System::Windows::Forms::ComboBox());
               this->pnlCard = (gcnew System::Windows::Forms::Panel());
               this->btnSave = (gcnew System::Windows::Forms::Button());
               this->btnCancel = (gcnew System::Windows::Forms::Button());
               this->pnlCard->SuspendLayout();
               this->SuspendLayout();

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Location = System::Drawing::Point(30, 20);
               this->lblTitle->Name = L"lblTitle";
               this->lblTitle->Size = System::Drawing::Size(250, 30);
               this->lblTitle->TabIndex = 0;
               this->lblTitle->Text = L"Student Registration";

               // pnlCard
               this->pnlCard->BackColor = System::Drawing::Color::White;
               this->pnlCard->Controls->Add(this->lblID);
               this->pnlCard->Controls->Add(this->txtID);
               this->pnlCard->Controls->Add(this->lblUser);
               this->pnlCard->Controls->Add(this->txtUser);
               this->pnlCard->Controls->Add(this->lblPass);
               this->pnlCard->Controls->Add(this->txtPass);
               this->pnlCard->Controls->Add(this->lblFirstName);
               this->pnlCard->Controls->Add(this->txtFirstName);
               this->pnlCard->Controls->Add(this->lblEmail);
               this->pnlCard->Controls->Add(this->txtEmail);
               this->pnlCard->Controls->Add(this->lblPhone);
               this->pnlCard->Controls->Add(this->txtPhone);
               this->pnlCard->Controls->Add(this->lblNationalID);
               this->pnlCard->Controls->Add(this->txtNationalID);
               this->pnlCard->Controls->Add(this->lblFaculty);
               this->pnlCard->Controls->Add(this->cmbFaculty);
               this->pnlCard->Controls->Add(this->lblDeptID);
               this->pnlCard->Controls->Add(this->cmbDept);
               this->pnlCard->Controls->Add(this->lblLevel);
               this->pnlCard->Controls->Add(this->cmbLevel);
               this->pnlCard->Controls->Add(this->lblYear);
               this->pnlCard->Controls->Add(this->cmbYear);
               this->pnlCard->Controls->Add(this->lblSemester);
               this->pnlCard->Controls->Add(this->cmbSemester);
               this->pnlCard->Controls->Add(this->lblGroup);
               this->pnlCard->Controls->Add(this->txtGroup);
               this->pnlCard->Controls->Add(this->lblSection);
               this->pnlCard->Controls->Add(this->txtSection);
               this->pnlCard->Location = System::Drawing::Point(30, 70);
               this->pnlCard->Name = L"pnlCard";
               this->pnlCard->Size = System::Drawing::Size(400, 600);
               this->pnlCard->TabIndex = 1;

               int labelX = 20, textX = 160, y = 20, spacing = 40;
               this->lblID->Text = L"Student ID:";
               this->lblID->Location = System::Drawing::Point(labelX, y);
               this->txtID->Location = System::Drawing::Point(textX, y);
               this->txtID->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblUser->Text = L"Username:";
               this->lblUser->Location = System::Drawing::Point(labelX, y);
               this->txtUser->Location = System::Drawing::Point(textX, y);
               this->txtUser->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblPass->Text = L"Password:";
               this->lblPass->Location = System::Drawing::Point(labelX, y);
               this->txtPass->Location = System::Drawing::Point(textX, y);
               this->txtPass->Size = System::Drawing::Size(200, 22);
               this->txtPass->PasswordChar = '*'; y += spacing;

               this->lblFirstName->Text = L"Full Name:";
               this->lblFirstName->Location = System::Drawing::Point(labelX, y);
               this->txtFirstName->Location = System::Drawing::Point(textX, y);
               this->txtFirstName->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblEmail->Text = L"Email:";
               this->lblEmail->Location = System::Drawing::Point(labelX, y);
               this->txtEmail->Location = System::Drawing::Point(textX, y);
               this->txtEmail->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblPhone->Text = L"Phone:";
               this->lblPhone->Location = System::Drawing::Point(labelX, y);
               this->txtPhone->Location = System::Drawing::Point(textX, y);
               this->txtPhone->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblNationalID->Text = L"National ID:";
               this->lblNationalID->Location = System::Drawing::Point(labelX, y);
               this->txtNationalID->Location = System::Drawing::Point(textX, y);
               this->txtNationalID->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblFaculty->Text = L"Faculty:";
               this->lblFaculty->Location = System::Drawing::Point(labelX, y);
               this->cmbFaculty->Location = System::Drawing::Point(textX, y);
               this->cmbFaculty->Size = System::Drawing::Size(200, 22);
               this->cmbFaculty->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList; y += spacing;

               this->lblDeptID->Text = L"Department:";
               this->lblDeptID->Location = System::Drawing::Point(labelX, y);
               this->cmbDept->Location = System::Drawing::Point(textX, y);
               this->cmbDept->Size = System::Drawing::Size(200, 22);
               this->cmbDept->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList; y += spacing;

               this->lblLevel->Text = L"Academic Level:";
               this->lblLevel->Location = System::Drawing::Point(labelX, y);
               this->cmbLevel->Location = System::Drawing::Point(textX, y);
               this->cmbLevel->Size = System::Drawing::Size(200, 22);
               this->cmbLevel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList; y += spacing;

               this->lblYear->Text = L"Academic Year:";
               this->lblYear->Location = System::Drawing::Point(labelX, y);
               this->cmbYear->Location = System::Drawing::Point(textX, y);
               this->cmbYear->Size = System::Drawing::Size(200, 22);
               this->cmbYear->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList; y += spacing;

               this->lblSemester->Text = L"Semester:";
               this->lblSemester->Location = System::Drawing::Point(labelX, y);
               this->cmbSemester->Location = System::Drawing::Point(textX, y);
               this->cmbSemester->Size = System::Drawing::Size(200, 22);
               this->cmbSemester->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList; y += spacing;

               this->lblGroup->Text = L"Group Number:";
               this->lblGroup->Location = System::Drawing::Point(labelX, y);
               this->txtGroup->Location = System::Drawing::Point(textX, y);
               this->txtGroup->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblSection->Text = L"Section Number:";
               this->lblSection->Location = System::Drawing::Point(labelX, y);
               this->txtSection->Location = System::Drawing::Point(textX, y);
               this->txtSection->Size = System::Drawing::Size(200, 22);

               // btnSave
               this->btnSave->Text = L"Save Student";
               this->btnSave->Location = System::Drawing::Point(230, 690);
               this->btnSave->Size = System::Drawing::Size(120, 35);
               this->btnSave->TabIndex = 2;
               this->btnSave->Click += gcnew System::EventHandler(this, &RegisterStudentForm::btnSave_Click);

               // btnCancel
               this->btnCancel->Text = L"Cancel";
               this->btnCancel->Location = System::Drawing::Point(360, 690);
               this->btnCancel->Size = System::Drawing::Size(70, 35);
               this->btnCancel->TabIndex = 3;
               this->btnCancel->Click += gcnew System::EventHandler(this, &RegisterStudentForm::btnCancel_Click);

               this->ClientSize = System::Drawing::Size(460, 750);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->btnSave);
               this->Controls->Add(this->btnCancel);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"RegisterStudentForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"Student Management";
               this->pnlCard->ResumeLayout(false);
               this->pnlCard->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

    private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            String^ user = this->txtUser->Text->Trim();
            String^ pass = this->txtPass->Text;
            String^ fullName = this->txtFirstName->Text->Trim();
            String^ email = this->txtEmail->Text->Trim();
            String^ phone = this->txtPhone->Text->Trim();
            String^ nationalId = this->txtNationalID->Text->Trim();
            int sid = -1;
            if (!Int32::TryParse(this->txtID->Text->Trim(), sid)) sid = -1;
            
            int deptId = GetIdFromCombo(cmbDept);
            int facultyId = GetIdFromCombo(cmbFaculty);
            int levelId = GetIdFromCombo(cmbLevel);
            int yearId = GetIdFromCombo(cmbYear);
            int semId = GetIdFromCombo(cmbSemester);
            String^ groupNum = this->txtGroup->Text->Trim();
            String^ sectionNum = this->txtSection->Text->Trim();

            if (sid <= 0) {
                MessageBox::Show("Please enter a valid Student ID.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            if (String::IsNullOrWhiteSpace(fullName)) {
                MessageBox::Show("Full Name is required.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            if (deptId == -1 || facultyId == -1 || levelId == -1 || yearId == -1 || semId == -1) {
                MessageBox::Show("Please select all academic fields.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            if (!editMode && (String::IsNullOrWhiteSpace(user) || String::IsNullOrWhiteSpace(pass))) {
                MessageBox::Show("Username and Password are required for new students.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            bool ok = false;
            try {
                if (editMode) {
                    ok = SIS::DataManager::UpdateStudent(originalId, fullName, email, phone, nationalId, deptId, facultyId, levelId, yearId, semId, groupNum, sectionNum);
                }
                else {
                    ok = SIS::DataManager::AddStudent(sid, user, pass, fullName, email, phone, nationalId, deptId, facultyId, levelId, yearId, semId, groupNum, sectionNum);
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Database error: " + ex->Message, "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (ok) {
                MessageBox::Show("Operation successful.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->Close();
            } else {
                MessageBox::Show("Operation failed. Check if Student ID or Username already exists.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show(String::Format("Unexpected error: {0}", ex->Message), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private:
        int GetIdFromCombo(ComboBox^ cmb) {
            if (cmb->SelectedIndex == -1) return -1;
            try {
                String^ s = cmb->SelectedItem->ToString();
                array<String^>^ p = s->Split(' ');
                int id;
                if (p->Length > 0 && Int32::TryParse(p[0], id)) return id;
            } catch (...) {}
            return -1;
        }

    private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
    };
}
