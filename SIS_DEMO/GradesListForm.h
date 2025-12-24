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

    public ref class GradesListForm : public System::Windows::Forms::Form
    {
    private:
        int profId;
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Panel^ pnlCard;

    public:
        GradesListForm(int id)
        {
            try {
                InitializeComponent();
                this->profId = id;
                LoadGrades();
                ApplyModernTheme();
            }
            catch (Exception^ ex) {
                MessageBox::Show(String::Format("Failed to initialize GradesListForm: {0}", ex->Message),
                    "Initialization Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                throw;
            }
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;

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

            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->BackColor = Color::FromArgb(189, 195, 199);
            btnClose->ForeColor = Color::White;
            btnClose->FlatAppearance->BorderSize = 0;
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        }

    protected:
        ~GradesListForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::DataGridView^ dgv;
    private: System::Windows::Forms::Button^ btnClose;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->dgv = (gcnew System::Windows::Forms::DataGridView());
               this->btnClose = (gcnew System::Windows::Forms::Button());
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->pnlCard = (gcnew System::Windows::Forms::Panel());
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgv))->BeginInit();
               this->pnlCard->SuspendLayout();
               this->SuspendLayout();
               // 
               // lblTitle
               // 
               this->lblTitle->AutoSize = true;
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
               this->lblTitle->ForeColor = Color::FromArgb(45, 52, 54);
               this->lblTitle->Location = System::Drawing::Point(20, 20);
               this->lblTitle->Name = L"lblTitle";
               this->lblTitle->Size = System::Drawing::Size(150, 30);
               this->lblTitle->Text = L"Grades Overview";
               // 
               // pnlCard
               // 
               this->pnlCard->BackColor = System::Drawing::Color::White;
               this->pnlCard->Controls->Add(this->dgv);
               this->pnlCard->Location = System::Drawing::Point(20, 70);
               this->pnlCard->Name = L"pnlCard";
               this->pnlCard->Size = System::Drawing::Size(740, 400);
               this->pnlCard->TabIndex = 0;
               // 
               // dgv
               // 
               this->dgv->Dock = System::Windows::Forms::DockStyle::Fill;
               this->dgv->Location = System::Drawing::Point(0, 0);
               this->dgv->Name = L"dgv";
               this->dgv->ReadOnly = true;
               this->dgv->AllowUserToAddRows = false;
               this->dgv->AllowUserToDeleteRows = false;
               this->dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
               // 
               // btnClose
               // 
               this->btnClose->Location = System::Drawing::Point(660, 485);
               this->btnClose->Size = System::Drawing::Size(100, 35);
               this->btnClose->Text = L"Close";
               this->btnClose->Click += gcnew System::EventHandler(this, &GradesListForm::btnClose_Click);
               // 
               // GradesListForm
               // 
               this->ClientSize = System::Drawing::Size(780, 540);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->btnClose);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"Grades Management";
               this->pnlCard->ResumeLayout(false);
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgv))->EndInit();
               this->ResumeLayout(false);
               this->PerformLayout();
           }

           void LoadGrades() {
               this->dgv->Columns->Clear();
               this->dgv->Columns->Add("Student", "Student");
               this->dgv->Columns->Add("Course", "Course");
               this->dgv->Columns->Add("Ass1", "Ass1");
               this->dgv->Columns->Add("Ass2", "Ass2");
               this->dgv->Columns->Add("CW", "CW");
               this->dgv->Columns->Add("Final", "Final");
               this->dgv->Columns->Add("Total", "Total");
               this->dgv->Columns->Add("Eval", "Evaluation");

               List<String^>^ rows = SIS::DataManager::ReadGradesByProfessor(this->profId);
               for each (String^ r in rows) {
                   if (String::IsNullOrEmpty(r)) continue;
                   array<String^>^ parts = r->Split(',');
                   if (parts->Length < 8) continue;
                   this->dgv->Rows->Add(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7]);
               }
           }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
    };
}
