#pragma once

#include "DataManager.h"
#include <msclr/marshal_cppstd.h>
#include "RegisterStudentForm.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class StudentsListForm : public System::Windows::Forms::Form
    {
    private:
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Panel^ pnlCard;

    public:
        StudentsListForm(void)
        {
            InitializeComponent();
            ApplyModernTheme();
            LoadStudents();
        }

    private:
        void ApplyModernTheme() {
            this->BackColor = bgColor;
            
            // DGV Styling
            dgv->BackgroundColor = Color::White;
            dgv->BorderStyle = BorderStyle::None;
            dgv->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
            dgv->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
            dgv->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(45, 52, 54);
            dgv->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            dgv->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9);
            dgv->EnableHeadersVisualStyles = false;
            dgv->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgv->DefaultCellStyle->SelectionBackColor = Color::FromArgb(225, 232, 235);
            dgv->DefaultCellStyle->SelectionForeColor = Color::Black;
            dgv->RowHeadersVisible = false;

            btnDelete->FlatStyle = FlatStyle::Flat;
            btnDelete->BackColor = Color::FromArgb(214, 48, 49);
            btnDelete->ForeColor = Color::White;
            btnDelete->FlatAppearance->BorderSize = 0;
            btnDelete->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);

            btnRefresh->FlatStyle = FlatStyle::Flat;
            btnRefresh->BackColor = accentColor;
            btnRefresh->ForeColor = Color::White;
            btnRefresh->FlatAppearance->BorderSize = 0;
            btnRefresh->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);

            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->BackColor = Color::FromArgb(189, 195, 199);
            btnClose->ForeColor = Color::White;
            btnClose->FlatAppearance->BorderSize = 0;
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        }

    protected:
        ~StudentsListForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::DataGridView^ dgv;
    private: System::Windows::Forms::Button^ btnDelete;
    private: System::Windows::Forms::Button^ btnRefresh;
    private: System::Windows::Forms::Button^ btnClose;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->dgv = (gcnew System::Windows::Forms::DataGridView());
               this->btnDelete = (gcnew System::Windows::Forms::Button());
               this->btnRefresh = (gcnew System::Windows::Forms::Button());
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
               this->lblTitle->Text = L"Student List";
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
               this->dgv->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &StudentsListForm::dgv_CellDoubleClick);
               // 
               // btnDelete
               // 
               this->btnDelete->Location = System::Drawing::Point(20, 485);
               this->btnDelete->Size = System::Drawing::Size(120, 35);
               this->btnDelete->Text = L"Delete Selected";
               this->btnDelete->Click += gcnew System::EventHandler(this, &StudentsListForm::btnDelete_Click);
               // 
               // btnRefresh
               // 
               this->btnRefresh->Location = System::Drawing::Point(150, 485);
               this->btnRefresh->Size = System::Drawing::Size(100, 35);
               this->btnRefresh->Text = L"Refresh";
               this->btnRefresh->Click += gcnew System::EventHandler(this, &StudentsListForm::btnRefresh_Click);
               // 
               // btnClose
               // 
               this->btnClose->Location = System::Drawing::Point(660, 485);
               this->btnClose->Size = System::Drawing::Size(100, 35);
               this->btnClose->Text = L"Close";
               this->btnClose->Click += gcnew System::EventHandler(this, &StudentsListForm::btnClose_Click);
               // 
               // StudentsListForm
               // 
               this->ClientSize = System::Drawing::Size(780, 540);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->btnDelete);
               this->Controls->Add(this->btnRefresh);
               this->Controls->Add(this->btnClose);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"Students Management";
               this->pnlCard->ResumeLayout(false);
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgv))->EndInit();
               this->ResumeLayout(false);
               this->PerformLayout();
           }

           void LoadStudents() {
               this->dgv->Columns->Clear();
               this->dgv->Columns->Add("ID", "ID");
               this->dgv->Columns->Add("FullName", "Full Name");
               this->dgv->Columns->Add("Email", "Email");
               this->dgv->Columns->Add("Department", "Department");
               this->dgv->Columns->Add("Phone", "Phone");
               this->dgv->Columns->Add("NationalID", "National ID");

               List<String^>^ rows = SIS::DataManager::ReadAllStudents();
               for each (String^ r in rows) {
                   if (String::IsNullOrEmpty(r)) continue;
                   array<String^>^ parts = r->Split(',');
                   if (parts->Length < 6) continue;
                   this->dgv->Rows->Add(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5]);
               }
           }

    private: System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
        if (this->dgv->SelectedRows->Count == 0) {
            MessageBox::Show("No student selected.", "Delete", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
        int id = Int32::Parse(this->dgv->SelectedRows[0]->Cells[0]->Value->ToString());
        if (MessageBox::Show(String::Format("Delete student ID {0}?", id), "Confirm", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
            bool ok = SIS::DataManager::DeleteStudent(id);
            if (ok) {
                MessageBox::Show("Student deleted.", "Deleted", MessageBoxButtons::OK, MessageBoxIcon::Information);
                btnRefresh_Click(nullptr, nullptr);
            }
            else {
                MessageBox::Show("Failed to delete student.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
        this->dgv->Rows->Clear();
        LoadStudents();
    }

    private: System::Void dgv_CellDoubleClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
        if (e->RowIndex < 0) return;
        try {
            int id = Int32::Parse(this->dgv->Rows[e->RowIndex]->Cells[0]->Value->ToString());
            RegisterStudentForm^ f = gcnew RegisterStudentForm(id);
            f->ShowDialog();
            // refresh after edit
            btnRefresh_Click(nullptr, nullptr);
        }
        catch (...) {}
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
    };
}
