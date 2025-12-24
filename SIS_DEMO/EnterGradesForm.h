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

    public ref class EnterGradesForm : public System::Windows::Forms::Form
    {
    private:
        int profId;
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        Color primaryColor = Color::FromArgb(45, 52, 54);
        System::Windows::Forms::Panel^ pnlCard;
        System::Windows::Forms::Label^ lblTitle;

    public:
        EnterGradesForm(int id)
        {
            try {
                InitializeComponent();
                this->profId = id;
                ApplyModernTheme();
                LoadMetaData();
            }
            catch (Exception^ ex) {
                MessageBox::Show(String::Format("Failed to initialize EnterGradesForm: {0}", ex->Message),
                    "Initialization Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                throw;
            }
        }

    private:
        void LoadMetaData() {
            this->cmbStudent->Items->Clear();
            List<String^>^ students = SIS::DataManager::ReadAllStudents();
            for each (String^ s in students) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) this->cmbStudent->Items->Add(p[0] + " - " + p[1]);
            }

            this->cmbCourse->Items->Clear();
            List<String^>^ courses = SIS::DataManager::ReadAllCourses();
            for each (String^ s in courses) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) this->cmbCourse->Items->Add(p[0] + " - " + p[1]);
            }

            this->cmbSemester->Items->Clear();
            List<String^>^ semesters = SIS::DataManager::ReadAllSemesters();
            for each (String^ s in semesters) {
                array<String^>^ p = s->Split(',');
                if (p->Length >= 2) this->cmbSemester->Items->Add(p[0] + " - " + p[1]);
            }

            if (this->cmbStudent->Items->Count > 0) this->cmbStudent->SelectedIndex = 0;
            if (this->cmbCourse->Items->Count > 0) this->cmbCourse->SelectedIndex = 0;
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

            array<Label^>^ labels = { 
                lblStudentID, lblCourseID, lblSemesterID, 
                lblAss1, lblAss2, lblCW, lblFinal 
            };
            for each (Label^ lbl in labels) {
                lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
                lbl->ForeColor = Color::FromArgb(99, 110, 114);
            }

            array<TextBox^>^ texts = { 
                txtAss1, txtAss2, txtCW, txtFinal 
            };
            for each (TextBox^ txt in texts) {
                txt->BorderStyle = BorderStyle::FixedSingle;
                txt->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            }

            cmbStudent->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            cmbCourse->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            cmbSemester->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);

            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->BackColor = accentColor;
            btnSave->ForeColor = Color::White;
            btnSave->FlatAppearance->BorderSize = 0;
            btnSave->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);

            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->BackColor = Color::FromArgb(189, 195, 199);
            btnClose->ForeColor = Color::White;
            btnClose->FlatAppearance->BorderSize = 0;
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        }

    protected:
        ~EnterGradesForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Label^ lblStudentID;
    private: System::Windows::Forms::Label^ lblCourseID;
    private: System::Windows::Forms::Label^ lblSemesterID;
    private: System::Windows::Forms::Label^ lblAss1;
    private: System::Windows::Forms::Label^ lblAss2;
    private: System::Windows::Forms::Label^ lblCW;
    private: System::Windows::Forms::Label^ lblFinal;
    private: System::Windows::Forms::ComboBox^ cmbStudent;
    private: System::Windows::Forms::ComboBox^ cmbCourse;
    private: System::Windows::Forms::ComboBox^ cmbSemester;
    private: System::Windows::Forms::TextBox^ txtAss1;
    private: System::Windows::Forms::TextBox^ txtAss2;
    private: System::Windows::Forms::TextBox^ txtCW;
    private: System::Windows::Forms::TextBox^ txtFinal;
    private: System::Windows::Forms::Button^ btnSave;
    private: System::Windows::Forms::Button^ btnClose;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->lblStudentID = (gcnew System::Windows::Forms::Label());
               this->lblCourseID = (gcnew System::Windows::Forms::Label());
               this->lblSemesterID = (gcnew System::Windows::Forms::Label());
               this->lblAss1 = (gcnew System::Windows::Forms::Label());
               this->lblAss2 = (gcnew System::Windows::Forms::Label());
               this->lblCW = (gcnew System::Windows::Forms::Label());
               this->lblFinal = (gcnew System::Windows::Forms::Label());
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->cmbStudent = (gcnew System::Windows::Forms::ComboBox());
               this->cmbCourse = (gcnew System::Windows::Forms::ComboBox());
               this->cmbSemester = (gcnew System::Windows::Forms::ComboBox());
               this->txtAss1 = (gcnew System::Windows::Forms::TextBox());
               this->txtAss2 = (gcnew System::Windows::Forms::TextBox());
               this->txtCW = (gcnew System::Windows::Forms::TextBox());
               this->txtFinal = (gcnew System::Windows::Forms::TextBox());
               this->pnlCard = (gcnew System::Windows::Forms::Panel());
               this->btnSave = (gcnew System::Windows::Forms::Button());
               this->btnClose = (gcnew System::Windows::Forms::Button());
               this->pnlCard->SuspendLayout();
               this->SuspendLayout();

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Location = System::Drawing::Point(30, 20);
               this->lblTitle->Name = L"lblTitle";
               this->lblTitle->Size = System::Drawing::Size(200, 30);
               this->lblTitle->TabIndex = 0;
               this->lblTitle->Text = L"Grade Entry";

               // pnlCard
               this->pnlCard->BackColor = System::Drawing::Color::White;
               this->pnlCard->Controls->Add(this->lblStudentID);
               this->pnlCard->Controls->Add(this->cmbStudent);
               this->pnlCard->Controls->Add(this->lblCourseID);
               this->pnlCard->Controls->Add(this->cmbCourse);
               this->pnlCard->Controls->Add(this->lblSemesterID);
               this->pnlCard->Controls->Add(this->cmbSemester);
               this->pnlCard->Controls->Add(this->lblAss1);
               this->pnlCard->Controls->Add(this->txtAss1);
               this->pnlCard->Controls->Add(this->lblAss2);
               this->pnlCard->Controls->Add(this->txtAss2);
               this->pnlCard->Controls->Add(this->lblCW);
               this->pnlCard->Controls->Add(this->txtCW);
               this->pnlCard->Controls->Add(this->lblFinal);
               this->pnlCard->Controls->Add(this->txtFinal);
               this->pnlCard->Location = System::Drawing::Point(30, 70);
               this->pnlCard->Name = L"pnlCard";
               this->pnlCard->Size = System::Drawing::Size(360, 340);
               this->pnlCard->TabIndex = 1;

               int labelX = 20, textX = 140, y = 20, spacing = 45;

               this->lblStudentID->Location = System::Drawing::Point(labelX, y);
               this->lblStudentID->Text = L"Student:";
               this->cmbStudent->Location = System::Drawing::Point(textX, y);
               this->cmbStudent->Size = System::Drawing::Size(200, 22);
               this->cmbStudent->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList; y += spacing;

               this->lblCourseID->Location = System::Drawing::Point(labelX, y);
               this->lblCourseID->Text = L"Course:";
               this->cmbCourse->Location = System::Drawing::Point(textX, y);
               this->cmbCourse->Size = System::Drawing::Size(200, 22);
               this->cmbCourse->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList; y += spacing;

               this->lblSemesterID->Location = System::Drawing::Point(labelX, y);
               this->lblSemesterID->Text = L"Semester:";
               this->cmbSemester->Location = System::Drawing::Point(textX, y);
               this->cmbSemester->Size = System::Drawing::Size(200, 22);
               this->cmbSemester->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList; y += spacing;

               this->lblAss1->Location = System::Drawing::Point(labelX, y);
               this->lblAss1->Text = L"Assignment 1:";
               this->txtAss1->Location = System::Drawing::Point(textX, y);
               this->txtAss1->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblAss2->Location = System::Drawing::Point(labelX, y);
               this->lblAss2->Text = L"Assignment 2:";
               this->txtAss2->Location = System::Drawing::Point(textX, y);
               this->txtAss2->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblCW->Location = System::Drawing::Point(labelX, y);
               this->lblCW->Text = L"Course Work:";
               this->txtCW->Location = System::Drawing::Point(textX, y);
               this->txtCW->Size = System::Drawing::Size(200, 22); y += spacing;

               this->lblFinal->Location = System::Drawing::Point(labelX, y);
               this->lblFinal->Text = L"Final Exam:";
               this->txtFinal->Location = System::Drawing::Point(textX, y);
               this->txtFinal->Size = System::Drawing::Size(200, 22);

               // btnSave
               this->btnSave->Location = System::Drawing::Point(210, 430);
               this->btnSave->Size = System::Drawing::Size(100, 35);
               this->btnSave->TabIndex = 2;
               this->btnSave->Text = L"Save Grade";
               this->btnSave->Click += gcnew System::EventHandler(this, &EnterGradesForm::btnSave_Click);

               // btnClose
               this->btnClose->Location = System::Drawing::Point(320, 430);
               this->btnClose->Size = System::Drawing::Size(70, 35);
               this->btnClose->TabIndex = 3;
               this->btnClose->Text = L"Close";
               this->btnClose->Click += gcnew System::EventHandler(this, &EnterGradesForm::btnClose_Click);

               this->ClientSize = System::Drawing::Size(420, 490);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->btnSave);
               this->Controls->Add(this->btnClose);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"EnterGradesForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"Enter Grades";
               this->pnlCard->ResumeLayout(false);
               this->pnlCard->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();
           }

    private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int sid = GetIdFromCombo(this->cmbStudent);
            int cid = GetIdFromCombo(this->cmbCourse);
            int semId = GetIdFromCombo(this->cmbSemester);
            double a1 = Double::Parse(this->txtAss1->Text);
            double a2 = Double::Parse(this->txtAss2->Text);
            double cw = Double::Parse(this->txtCW->Text);
            double fin = Double::Parse(this->txtFinal->Text);

            if (sid == -1 || cid == -1 || semId == -1) {
                MessageBox::Show("Please select Student, Course and Semester.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            bool ok = SIS::DataManager::AddGrade(sid, cid, semId, a1, a2, cw, fin);
            if (ok) {
                MessageBox::Show("Grade saved.", "Saved", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->Close();
            }
            else {
                MessageBox::Show("Failed to save grade.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (FormatException^) {
            MessageBox::Show("Numeric fields have invalid format.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
        catch (Exception^ ex) {
            MessageBox::Show(String::Format("Unexpected error: {0}", ex->Message), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
    };
}
