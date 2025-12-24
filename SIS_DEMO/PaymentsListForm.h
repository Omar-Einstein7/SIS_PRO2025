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

    public ref class PaymentsListForm : public System::Windows::Forms::Form
    {
    private:
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Panel^ pnlCard;

    public:
        PaymentsListForm(void)
        {
            InitializeComponent();
            ApplyModernTheme();
            LoadPayments();
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

            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->BackColor = Color::FromArgb(189, 195, 199);
            btnClose->ForeColor = Color::White;
            btnClose->FlatAppearance->BorderSize = 0;
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        }

    protected:
        ~PaymentsListForm()
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
               this->lblTitle->Text = L"Payment Records";
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
               this->btnClose->Click += gcnew System::EventHandler(this, &PaymentsListForm::btnClose_Click);
               // 
               // PaymentsListForm
               // 
               this->ClientSize = System::Drawing::Size(780, 540);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->pnlCard);
               this->Controls->Add(this->btnClose);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"Payments Management";
               this->pnlCard->ResumeLayout(false);
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgv))->EndInit();
               this->ResumeLayout(false);
               this->PerformLayout();
           }

           void LoadPayments() {
               this->dgv->Columns->Clear();
               this->dgv->Columns->Add("StudentID", "Student ID");
               this->dgv->Columns->Add("YearID", "Year ID");
               this->dgv->Columns->Add("SemesterID", "Semester ID");
               this->dgv->Columns->Add("Total", "Total");
               this->dgv->Columns->Add("Paid", "Paid");
               this->dgv->Columns->Add("Date", "Date");
               this->dgv->Columns->Add("Status", "Status");

               List<String^>^ rows = SIS::DataManager::ReadAllPayments();
               for (int i = 0; i < rows->Count; i++) {
                   String^ r = rows[i];
                   if (String::IsNullOrEmpty(r)) continue;
                   array<String^>^ parts = r->Split(',');
                   if (parts->Length >= 7) {
                       this->dgv->Rows->Add(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6]);
                   }
               }
           }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
    };
}

