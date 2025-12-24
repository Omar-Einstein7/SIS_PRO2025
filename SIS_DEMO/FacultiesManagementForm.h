#pragma once

#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class FacultiesManagementForm : public System::Windows::Forms::Form
    {
    private:
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Panel^ pnlCard;
        System::Windows::Forms::DataGridView^ dgv;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnClose;
        System::Windows::Forms::TextBox^ txtCode;
        System::Windows::Forms::TextBox^ txtName;
        System::Windows::Forms::Label^ lblCode;
        System::Windows::Forms::Label^ lblName;

    public:
        FacultiesManagementForm(void)
        {
            InitializeComponent();
            ApplyModernTheme();
            LoadFaculties();
        }

    private:
        void StyleButton(Button^ b, Color c) {
            b->FlatStyle = FlatStyle::Flat;
            b->BackColor = c;
            b->ForeColor = Color::White;
            b->FlatAppearance->BorderSize = 0;
            b->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
        }

        void ApplyModernTheme() {
            this->BackColor = bgColor;
            dgv->BackgroundColor = Color::White;
            dgv->BorderStyle = BorderStyle::None;
            dgv->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
            dgv->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
            dgv->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(45, 52, 54);
            dgv->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            dgv->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9);
            dgv->EnableHeadersVisualStyles = false;
            dgv->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgv->RowHeadersVisible = false;

            StyleButton(btnAdd, accentColor);
            StyleButton(btnDelete, Color::FromArgb(214, 48, 49));
            StyleButton(btnRefresh, Color::FromArgb(45, 52, 54));
            StyleButton(btnClose, Color::FromArgb(189, 195, 199));
        }

        void InitializeComponent(void)
        {
            this->dgv = (gcnew System::Windows::Forms::DataGridView());
            this->btnAdd = (gcnew System::Windows::Forms::Button());
            this->btnDelete = (gcnew System::Windows::Forms::Button());
            this->btnRefresh = (gcnew System::Windows::Forms::Button());
            this->btnClose = (gcnew System::Windows::Forms::Button());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->pnlCard = (gcnew System::Windows::Forms::Panel());
            this->txtCode = (gcnew System::Windows::Forms::TextBox());
            this->txtName = (gcnew System::Windows::Forms::TextBox());
            this->lblCode = (gcnew System::Windows::Forms::Label());
            this->lblName = (gcnew System::Windows::Forms::Label());

            this->pnlCard->SuspendLayout();
            this->SuspendLayout();

            this->lblTitle->Text = L"Faculties Management";
            this->lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
            this->lblTitle->Location = Point(20, 20);
            this->lblTitle->AutoSize = true;

            this->pnlCard->BackColor = Color::White;
            this->pnlCard->Location = Point(20, 70);
            this->pnlCard->Size = System::Drawing::Size(500, 300);
            this->pnlCard->Controls->Add(this->dgv);

            this->dgv->Dock = DockStyle::Fill;
            this->dgv->AllowUserToAddRows = false;
            this->dgv->ReadOnly = true;
            this->dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            this->lblCode->Text = L"Faculty Code:";
            this->lblCode->Location = Point(540, 70);
            this->lblCode->AutoSize = true;

            this->txtCode->Location = Point(540, 90);
            this->txtCode->Size = System::Drawing::Size(200, 25);

            this->lblName->Text = L"Faculty Name:";
            this->lblName->Location = Point(540, 130);
            this->lblName->AutoSize = true;

            this->txtName->Location = Point(540, 150);
            this->txtName->Size = System::Drawing::Size(200, 25);

            this->btnAdd->Text = L"Add Faculty";
            this->btnAdd->Location = Point(540, 190);
            this->btnAdd->Size = System::Drawing::Size(200, 35);
            this->btnAdd->Click += gcnew EventHandler(this, &FacultiesManagementForm::btnAdd_Click);

            this->btnDelete->Text = L"Delete Selected";
            this->btnDelete->Location = Point(20, 385);
            this->btnDelete->Size = System::Drawing::Size(150, 35);
            this->btnDelete->Click += gcnew EventHandler(this, &FacultiesManagementForm::btnDelete_Click);

            this->btnRefresh->Text = L"Refresh";
            this->btnRefresh->Location = Point(180, 385);
            this->btnRefresh->Size = System::Drawing::Size(100, 35);
            this->btnRefresh->Click += gcnew EventHandler(this, &FacultiesManagementForm::btnRefresh_Click);

            this->btnClose->Text = L"Close";
            this->btnClose->Location = Point(640, 385);
            this->btnClose->Size = System::Drawing::Size(100, 35);
            this->btnClose->Click += gcnew EventHandler(this, &FacultiesManagementForm::btnClose_Click);

            this->ClientSize = System::Drawing::Size(760, 440);
            this->Controls->Add(lblTitle);
            this->Controls->Add(pnlCard);
            this->Controls->Add(lblCode);
            this->Controls->Add(txtCode);
            this->Controls->Add(lblName);
            this->Controls->Add(txtName);
            this->Controls->Add(btnAdd);
            this->Controls->Add(btnDelete);
            this->Controls->Add(btnRefresh);
            this->Controls->Add(btnClose);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->StartPosition = FormStartPosition::CenterParent;

            this->pnlCard->ResumeLayout(false);
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void LoadFaculties() {
            dgv->Columns->Clear();
            dgv->Columns->Add("ID", "ID");
            dgv->Columns->Add("Code", "Code");
            dgv->Columns->Add("Name", "Name");

            auto rows = SIS::DataManager::ReadAllFaculties();
            for each (String^ r in rows) {
                auto p = r->Split(',');
                if (p->Length >= 3) dgv->Rows->Add(p[0], p[1], p[2]);
            }
        }

        System::Void btnAdd_Click(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtCode->Text) || String::IsNullOrWhiteSpace(txtName->Text)) {
                MessageBox::Show("Please fill all fields.");
                return;
            }
            if (SIS::DataManager::AddFaculty(txtCode->Text, txtName->Text)) {
                txtCode->Clear(); txtName->Clear();
                LoadFaculties();
            } else MessageBox::Show("Error adding faculty.");
        }

        System::Void btnDelete_Click(Object^ sender, EventArgs^ e) {
            if (dgv->SelectedRows->Count == 0) return;
            int id = Int32::Parse(dgv->SelectedRows[0]->Cells[0]->Value->ToString());
            if (MessageBox::Show("Delete faculty " + id + "?", "Confirm", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
                SIS::DataManager::DeleteFaculty(id);
                LoadFaculties();
            }
        }

        System::Void btnRefresh_Click(Object^ sender, EventArgs^ e) { LoadFaculties(); }
        System::Void btnClose_Click(Object^ sender, EventArgs^ e) { this->Close(); }
    };
}