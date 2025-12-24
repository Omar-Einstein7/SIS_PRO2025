#pragma once

#include "DataManager.h"
#include <msclr/marshal_cppstd.h>

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class StudentGradesViewForm : public System::Windows::Forms::Form
    {
    private:
        int studentId;
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        System::Windows::Forms::Panel^ pnlCard;
        System::Windows::Forms::Label^ lblTitle;

    public:
        StudentGradesViewForm(int id)
        {
            InitializeComponent();
            this->studentId = id;
            this->txtStudentID->Text = id.ToString();
            this->txtStudentID->ReadOnly = true;
            this->btnLoad->PerformClick();
            ApplyModernTheme();
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            dgv->Columns->Clear();
            dgv->Columns->Add("Course", "Course");
            dgv->Columns->Add("Ass1", "Ass1");
            dgv->Columns->Add("Ass2", "Ass2");
            dgv->Columns->Add("CW", "CW");
            dgv->Columns->Add("Final", "Final");
            dgv->Columns->Add("Total", "Total");
            dgv->Columns->Add("Eval", "Evaluation");

            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, FontStyle::Bold);
            lblTitle->ForeColor = Color::FromArgb(45, 52, 54);

            lblStudentID->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            lblStudentID->ForeColor = Color::FromArgb(99, 110, 114);

            txtStudentID->BorderStyle = BorderStyle::FixedSingle;
            txtStudentID->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);

            btnLoad->FlatStyle = FlatStyle::Flat;
            btnLoad->BackColor = accentColor;
            btnLoad->ForeColor = Color::White;
            btnLoad->FlatAppearance->BorderSize = 0;
            btnLoad->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);

            dgv->BackgroundColor = Color::White;
            dgv->BorderStyle = BorderStyle::None;
            dgv->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
            dgv->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(45, 52, 54);
            dgv->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            dgv->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            dgv->EnableHeadersVisualStyles = false;
            dgv->GridColor = Color::FromArgb(223, 230, 233);
            dgv->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgv->DefaultCellStyle->SelectionBackColor = Color::FromArgb(116, 185, 255);
            dgv->DefaultCellStyle->SelectionForeColor = Color::Black;
            dgv->RowHeadersVisible = false;
            dgv->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->BackColor = Color::FromArgb(189, 195, 199);
            btnClose->ForeColor = Color::White;
            btnClose->FlatAppearance->BorderSize = 0;
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        }

    protected:
        ~StudentGradesViewForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Label^ lblStudentID;
    private: System::Windows::Forms::TextBox^ txtStudentID;
    private: System::Windows::Forms::Button^ btnLoad;
    private: System::Windows::Forms::DataGridView^ dgv;
    private: System::Windows::Forms::Button^ btnClose;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->lblStudentID = (gcnew System::Windows::Forms::Label());
               this->txtStudentID = (gcnew System::Windows::Forms::TextBox());
               this->btnLoad = (gcnew System::Windows::Forms::Button());
               this->dgv = (gcnew System::Windows::Forms::DataGridView());
               this->btnClose = (gcnew System::Windows::Forms::Button());
               this->pnlCard = (gcnew System::Windows::Forms::Panel());
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgv))->BeginInit();
               this->pnlCard->SuspendLayout();
               this->SuspendLayout();

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Location = System::Drawing::Point(20, 20);
               this->lblTitle->Name = L"lblTitle";
               this->lblTitle->Size = System::Drawing::Size(200, 30);
               this->lblTitle->TabIndex = 5;
               this->lblTitle->Text = L"Academic Grades";

               // Student ID Controls (Top Right)
               this->lblStudentID->Location = System::Drawing::Point(430, 25);
               this->lblStudentID->Size = System::Drawing::Size(70, 23);
               this->lblStudentID->Text = L"Student ID:";
               
               this->txtStudentID->Location = System::Drawing::Point(505, 22);
               this->txtStudentID->Size = System::Drawing::Size(80, 22);
               this->txtStudentID->ReadOnly = true;

               this->btnLoad->Location = System::Drawing::Point(600, 20);
               this->btnLoad->Size = System::Drawing::Size(80, 26);
               this->btnLoad->Text = L"Refresh";
               this->btnLoad->Click += gcnew System::EventHandler(this, &StudentGradesViewForm::btnLoad_Click);

               // pnlCard
               this->pnlCard->BackColor = System::Drawing::Color::White;
               this->pnlCard->Controls->Add(this->dgv);
               this->pnlCard->Location = System::Drawing::Point(20, 70);
               this->pnlCard->Name = L"pnlCard";
               this->pnlCard->Padding = System::Windows::Forms::Padding(10);
               this->pnlCard->Size = System::Drawing::Size(740, 350);
               this->pnlCard->TabIndex = 0;

               // dgv
               this->dgv->Dock = System::Windows::Forms::DockStyle::Fill;
               this->dgv->Location = System::Drawing::Point(10, 10);
               this->dgv->Size = System::Drawing::Size(720, 330);
               this->dgv->ReadOnly = true;
               this->dgv->BorderStyle = System::Windows::Forms::BorderStyle::None;

               // btnClose
               this->btnClose->Location = System::Drawing::Point(680, 435);
               this->btnClose->Size = System::Drawing::Size(80, 35);
               this->btnClose->Text = L"Close";
               this->btnClose->Click += gcnew System::EventHandler(this, &StudentGradesViewForm::btnClose_Click);

               // Form
               this->ClientSize = System::Drawing::Size(780, 490);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->lblStudentID);
               this->Controls->Add(this->txtStudentID);
               this->Controls->Add(this->btnLoad);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->btnClose);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"Student Grades";

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgv))->EndInit();
               this->pnlCard->ResumeLayout(false);
               this->ResumeLayout(false);
               this->PerformLayout();
           }

    private: System::Void btnLoad_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int sid = Int32::Parse(this->txtStudentID->Text);
            this->dgv->Rows->Clear();
            List<String^>^ grades = SIS::DataManager::ReadGradesForStudent(sid);
            for each (String^ g in grades) {
                if (String::IsNullOrEmpty(g)) continue;
                array<String^>^ parts = g->Split(',');
                if (parts->Length >= 7) {
                    // parts: course_id, a1, a2, cw, final, total, eval
                    this->dgv->Rows->Add(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6]);
                }
            }
        }
        catch (FormatException^) { MessageBox::Show("Invalid student ID.", "Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning); }
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) { this->Close(); }
    };
}
