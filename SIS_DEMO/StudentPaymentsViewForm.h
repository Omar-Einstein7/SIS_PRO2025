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

    public ref class StudentPaymentsViewForm : public System::Windows::Forms::Form
    {
    private:
        int studentId;
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Panel^ pnlCard;

    public:
        StudentPaymentsViewForm(int id)
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
            dgv->Columns->Add("Year", "Year ID");
            dgv->Columns->Add("Sem", "Semester ID");
            dgv->Columns->Add("Total", "Total");
            dgv->Columns->Add("Paid", "Paid");
            dgv->Columns->Add("Date", "Date");
            dgv->Columns->Add("Status", "Status");

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

            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->BackColor = Color::FromArgb(189, 195, 199);
            btnClose->ForeColor = Color::White;
            btnClose->FlatAppearance->BorderSize = 0;
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        }

    protected:
        ~StudentPaymentsViewForm()
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
               this->lblTitle->Size = System::Drawing::Size(200, 30);
               this->lblTitle->Text = L"Payment History";
               // 
               // pnlCard
               // 
               this->pnlCard->BackColor = System::Drawing::Color::White;
               this->pnlCard->Controls->Add(this->dgv);
               this->pnlCard->Location = System::Drawing::Point(20, 70);
               this->pnlCard->Name = L"pnlCard";
               this->pnlCard->Size = System::Drawing::Size(540, 300);
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
               // lblStudentID
               // 
               this->lblStudentID->Location = System::Drawing::Point(330, 25);
               this->lblStudentID->Size = System::Drawing::Size(80, 23);
               this->lblStudentID->Text = L"Student ID:";
               // 
               // txtStudentID
               // 
               this->txtStudentID->Location = System::Drawing::Point(410, 22);
               this->txtStudentID->Size = System::Drawing::Size(60, 22);
               // 
               // btnLoad
               // 
               this->btnLoad->Location = System::Drawing::Point(480, 20);
               this->btnLoad->Size = System::Drawing::Size(80, 26);
               this->btnLoad->Text = L"Refresh";
               this->btnLoad->Click += gcnew System::EventHandler(this, &StudentPaymentsViewForm::btnLoad_Click);
               // 
               // btnClose
               // 
               this->btnClose->Location = System::Drawing::Point(460, 385);
               this->btnClose->Size = System::Drawing::Size(100, 35);
               this->btnClose->Text = L"Close";
               this->btnClose->Click += gcnew System::EventHandler(this, &StudentPaymentsViewForm::btnClose_Click);
               // 
               // StudentPaymentsViewForm
               // 
               this->ClientSize = System::Drawing::Size(580, 440);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->lblStudentID);
               this->Controls->Add(this->txtStudentID);
               this->Controls->Add(this->btnLoad);
               this->Controls->Add(this->btnClose);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"My Payments";
               this->pnlCard->ResumeLayout(false);
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgv))->EndInit();
               this->ResumeLayout(false);
               this->PerformLayout();
           }

    private: System::Void btnLoad_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            int sid = Int32::Parse(this->txtStudentID->Text);
            this->dgv->Rows->Clear();
            List<String^>^ payments = SIS::DataManager::ReadPaymentsForStudent(sid);
            for each (String^ p in payments) {
                if (String::IsNullOrEmpty(p)) continue;
                array<String^>^ parts = p->Split(',');
                if (parts->Length >= 6) {
                    // parts: year_id, semester_id, total, paid, date, status
                    this->dgv->Rows->Add(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5]);
                }
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error loading payments: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) { this->Close(); }
    };
}
