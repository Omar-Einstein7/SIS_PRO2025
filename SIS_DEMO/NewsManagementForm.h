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

    public ref class NewsManagementForm : public System::Windows::Forms::Form
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
        System::Windows::Forms::TextBox^ txtNewsTitle;
        System::Windows::Forms::TextBox^ txtDescription;
        System::Windows::Forms::Label^ lblNewsTitle;
        System::Windows::Forms::Label^ lblDescription;

    public:
        NewsManagementForm(void)
        {
            InitializeComponent();
            ApplyModernTheme();
            LoadNews();
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
            this->txtNewsTitle = (gcnew System::Windows::Forms::TextBox());
            this->txtDescription = (gcnew System::Windows::Forms::TextBox());
            this->lblNewsTitle = (gcnew System::Windows::Forms::Label());
            this->lblDescription = (gcnew System::Windows::Forms::Label());

            this->pnlCard->SuspendLayout();
            this->SuspendLayout();

            this->lblTitle->Text = L"News Management";
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

            this->lblNewsTitle->Text = L"News Title:";
            this->lblNewsTitle->Location = Point(540, 70);
            this->lblNewsTitle->AutoSize = true;

            this->txtNewsTitle->Location = Point(540, 90);
            this->txtNewsTitle->Size = System::Drawing::Size(200, 25);

            this->lblDescription->Text = L"Description:";
            this->lblDescription->Location = Point(540, 130);
            this->lblDescription->AutoSize = true;

            this->txtDescription->Location = Point(540, 150);
            this->txtDescription->Size = System::Drawing::Size(200, 80);
            this->txtDescription->Multiline = true;

            this->btnAdd->Text = L"Post News";
            this->btnAdd->Location = Point(540, 250);
            this->btnAdd->Size = System::Drawing::Size(200, 35);
            this->btnAdd->Click += gcnew EventHandler(this, &NewsManagementForm::btnAdd_Click);

            this->btnDelete->Text = L"Delete Selected";
            this->btnDelete->Location = Point(20, 385);
            this->btnDelete->Size = System::Drawing::Size(150, 35);
            this->btnDelete->Click += gcnew EventHandler(this, &NewsManagementForm::btnDelete_Click);

            this->btnRefresh->Text = L"Refresh";
            this->btnRefresh->Location = Point(180, 385);
            this->btnRefresh->Size = System::Drawing::Size(100, 35);
            this->btnRefresh->Click += gcnew EventHandler(this, &NewsManagementForm::btnRefresh_Click);

            this->btnClose->Text = L"Close";
            this->btnClose->Location = Point(640, 385);
            this->btnClose->Size = System::Drawing::Size(100, 35);
            this->btnClose->Click += gcnew EventHandler(this, &NewsManagementForm::btnClose_Click);

            this->ClientSize = System::Drawing::Size(760, 440);
            this->Controls->Add(lblTitle);
            this->Controls->Add(pnlCard);
            this->Controls->Add(lblNewsTitle);
            this->Controls->Add(txtNewsTitle);
            this->Controls->Add(lblDescription);
            this->Controls->Add(txtDescription);
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

        void LoadNews() {
            dgv->Columns->Clear();
            dgv->Columns->Add("ID", "ID");
            dgv->Columns->Add("Title", "Title");
            dgv->Columns->Add("Description", "Description");
            dgv->Columns->Add("Date", "Date");

            auto rows = SIS::DataManager::ReadAllNews();
            for each (String^ r in rows) {
                auto p = r->Split('|');
                if (p->Length >= 4) dgv->Rows->Add(p[0], p[1], p[2], p[3]);
            }
        }

        System::Void btnAdd_Click(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtNewsTitle->Text) || String::IsNullOrWhiteSpace(txtDescription->Text)) {
                MessageBox::Show("Please fill all fields.");
                return;
            }
            // Using 1 as a default admin user ID for news posting
            if (SIS::DataManager::AddNews(txtNewsTitle->Text, txtDescription->Text, 1)) {
                txtNewsTitle->Clear(); txtDescription->Clear();
                LoadNews();
            } else MessageBox::Show("Error posting news.");
        }

        System::Void btnDelete_Click(Object^ sender, EventArgs^ e) {
            if (dgv->SelectedRows->Count == 0) return;
            int id = Int32::Parse(dgv->SelectedRows[0]->Cells[0]->Value->ToString());
            if (MessageBox::Show("Delete news " + id + "?", "Confirm", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
                SIS::DataManager::DeleteNews(id);
                LoadNews();
            }
        }

        System::Void btnRefresh_Click(Object^ sender, EventArgs^ e) { LoadNews(); }
        System::Void btnClose_Click(Object^ sender, EventArgs^ e) { this->Close(); }
    };
}