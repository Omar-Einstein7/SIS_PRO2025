#pragma once

#include "DataManager.h"
#include <msclr/marshal_cppstd.h>

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AssignCourseForm : public System::Windows::Forms::Form
    {
    private:
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        Color primaryColor = Color::FromArgb(45, 52, 54);
        System::Windows::Forms::Panel^ pnlCard;
        System::Windows::Forms::Label^ lblTitle;

    public:
        AssignCourseForm(void)
        {
            InitializeComponent();
            ApplyModernTheme();
            LoadMetaData();
        }

    private:
        void LoadMetaData() {
            this->cmbYear->Items->Clear();
            List<String^>^ years = SIS::DataManager::ReadAllYears();
            for each (String^ s in years) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) this->cmbYear->Items->Add(p[0] + " - " + p[1]);
            }
            if (this->cmbYear->Items->Count > 0) this->cmbYear->SelectedIndex = 0;

            this->cmbStudent->Items->Clear();
            List<String^>^ students = SIS::DataManager::ReadAllStudents();
            for each (String^ s in students) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) this->cmbStudent->Items->Add(p[0] + " - " + p[1]);
            }
            if (this->cmbStudent->Items->Count > 0) this->cmbStudent->SelectedIndex = 0;

            this->cmbCourse->Items->Clear();
            List<String^>^ courses = SIS::DataManager::ReadAllCourses();
            for each (String^ s in courses) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 3) this->cmbCourse->Items->Add(p[0] + " - " + p[2]);
            }
            if (this->cmbCourse->Items->Count > 0) this->cmbCourse->SelectedIndex = 0;

            this->cmbSemester->Items->Clear();
            List<String^>^ semesters = SIS::DataManager::ReadAllSemesters();
            for each (String^ s in semesters) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) this->cmbSemester->Items->Add(p[0] + " - " + p[1]);
            }
            if (this->cmbSemester->Items->Count > 0) this->cmbSemester->SelectedIndex = 0;
        }

        int GetIdFromCombo(ComboBox^ cmb) {
            if (cmb->SelectedIndex == -1) return -1;
            String^ s = cmb->SelectedItem->ToString();
            return Int32::Parse(s->Split(' ')[0]);
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, FontStyle::Bold);
            lblTitle->ForeColor = primaryColor;

            array<Label^>^ labels = { lblStudent, lblCourse, lblSemester, lblYear };
            for each (Label^ lbl in labels) {
                if (lbl == nullptr) continue;
                lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
                lbl->ForeColor = Color::FromArgb(99, 110, 114);
            }

            array<ComboBox^>^ combos = { cmbStudent, cmbCourse, cmbSemester, cmbYear };
            for each (ComboBox^ cmb in combos) {
                if (cmb == nullptr) continue;
                cmb->FlatStyle = FlatStyle::Flat;
                cmb->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
                cmb->DropDownStyle = ComboBoxStyle::DropDownList;
            }

            btnAssign->FlatStyle = FlatStyle::Flat;
            btnAssign->BackColor = accentColor;
            btnAssign->ForeColor = Color::White;
            btnAssign->FlatAppearance->BorderSize = 0;
            btnAssign->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);

            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->BackColor = Color::FromArgb(189, 195, 199);
            btnClose->ForeColor = Color::White;
            btnClose->FlatAppearance->BorderSize = 0;
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        }

    protected:
        ~AssignCourseForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Label^ lblStudent;
    private: System::Windows::Forms::Label^ lblCourse;
    private: System::Windows::Forms::Label^ lblSemester;
    private: System::Windows::Forms::Label^ lblYear;
    private: System::Windows::Forms::ComboBox^ cmbStudent;
    private: System::Windows::Forms::ComboBox^ cmbCourse;
    private: System::Windows::Forms::ComboBox^ cmbSemester;
    private: System::Windows::Forms::ComboBox^ cmbYear;
    private: System::Windows::Forms::Button^ btnAssign;
    private: System::Windows::Forms::Button^ btnClose;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->lblStudent = (gcnew System::Windows::Forms::Label());
               this->lblCourse = (gcnew System::Windows::Forms::Label());
               this->lblSemester = (gcnew System::Windows::Forms::Label());
               this->lblYear = (gcnew System::Windows::Forms::Label());
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->cmbStudent = (gcnew System::Windows::Forms::ComboBox());
               this->cmbCourse = (gcnew System::Windows::Forms::ComboBox());
               this->cmbSemester = (gcnew System::Windows::Forms::ComboBox());
               this->cmbYear = (gcnew System::Windows::Forms::ComboBox());
               this->pnlCard = (gcnew System::Windows::Forms::Panel());
               this->btnAssign = (gcnew System::Windows::Forms::Button());
               this->btnClose = (gcnew System::Windows::Forms::Button());
               this->pnlCard->SuspendLayout();
               this->SuspendLayout();

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Location = System::Drawing::Point(30, 20);
               this->lblTitle->Name = L"lblTitle";
               this->lblTitle->Size = System::Drawing::Size(200, 30);
               this->lblTitle->TabIndex = 0;
               this->lblTitle->Text = L"Assign Course";

               // pnlCard
               this->pnlCard->BackColor = System::Drawing::Color::White;
               this->pnlCard->Controls->Add(this->lblStudent);
               this->pnlCard->Controls->Add(this->cmbStudent);
               this->pnlCard->Controls->Add(this->lblCourse);
               this->pnlCard->Controls->Add(this->cmbCourse);
               this->pnlCard->Controls->Add(this->lblYear);
               this->pnlCard->Controls->Add(this->cmbYear);
               this->pnlCard->Controls->Add(this->lblSemester);
               this->pnlCard->Controls->Add(this->cmbSemester);
               this->pnlCard->Location = System::Drawing::Point(30, 70);
               this->pnlCard->Name = L"pnlCard";
               this->pnlCard->Size = System::Drawing::Size(360, 220);
               this->pnlCard->TabIndex = 1;

               int labelX = 20, textX = 140, y = 20, spacing = 45;

               this->lblStudent->Location = System::Drawing::Point(labelX, y);
               this->lblStudent->Text = L"Student:";
               this->cmbStudent->Location = System::Drawing::Point(textX, y);
               this->cmbStudent->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblCourse->Location = System::Drawing::Point(labelX, y);
               this->lblCourse->Text = L"Course:";
               this->cmbCourse->Location = System::Drawing::Point(textX, y);
               this->cmbCourse->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblYear->Location = System::Drawing::Point(labelX, y);
               this->lblYear->Text = L"Academic Year:";
               this->cmbYear->Location = System::Drawing::Point(textX, y);
               this->cmbYear->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblSemester->Location = System::Drawing::Point(labelX, y);
               this->lblSemester->Text = L"Semester:";
               this->cmbSemester->Location = System::Drawing::Point(textX, y);
               this->cmbSemester->Size = System::Drawing::Size(200, 22);

               // btnAssign
               this->btnAssign->Location = System::Drawing::Point(210, 310);
               this->btnAssign->Size = System::Drawing::Size(100, 35);
               this->btnAssign->TabIndex = 2;
               this->btnAssign->Text = L"Assign Now";
               this->btnAssign->Click += gcnew System::EventHandler(this, &AssignCourseForm::btnAssign_Click);

               // btnClose
               this->btnClose->Location = System::Drawing::Point(320, 310);
               this->btnClose->Size = System::Drawing::Size(70, 35);
               this->btnClose->TabIndex = 3;
               this->btnClose->Text = L"Close";
               this->btnClose->Click += gcnew System::EventHandler(this, &AssignCourseForm::btnClose_Click);

               this->ClientSize = System::Drawing::Size(420, 370);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->btnAssign);
               this->Controls->Add(this->btnClose);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"AssignCourseForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"Assign to Course";
               this->pnlCard->ResumeLayout(false);
               this->pnlCard->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();
           }

    private: System::Void btnAssign_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int sid = GetIdFromCombo(this->cmbStudent);
            int cid = GetIdFromCombo(this->cmbCourse);
            int yearId = GetIdFromCombo(this->cmbYear);
            int semId = GetIdFromCombo(this->cmbSemester);

            if (sid == -1 || cid == -1 || yearId == -1 || semId == -1) {
                MessageBox::Show("Please select all required fields.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            bool ok = SIS::DataManager::RegisterStudentToCourse(sid, cid, yearId, semId);
            if (ok) {
                MessageBox::Show("Student assigned to course.", "Saved", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->Close();
            }
            else {
                MessageBox::Show("Failed to assign student. Check data or duplicate.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (Exception^ ex) { MessageBox::Show(String::Format("Error: {0}", ex->Message), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) { this->Close(); }
    };
}
