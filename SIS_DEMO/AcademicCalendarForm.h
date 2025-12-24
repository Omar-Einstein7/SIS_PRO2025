#pragma once

#include "DataManager.h"

namespace SISDEMO {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AcademicCalendarForm : public System::Windows::Forms::Form
    {
    private:
        Color accentColor = Color::FromArgb(9, 132, 227);
        Color bgColor = Color::FromArgb(245, 246, 250);
        Color primaryColor = Color::FromArgb(45, 52, 54);
        
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Panel^ pnlCard;
        System::Windows::Forms::DataGridView^ dgvCalendar;
        
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Button^ btnClose;
        
        System::Windows::Forms::TextBox^ txtTitle;
        System::Windows::Forms::ComboBox^ cmbType;
        System::Windows::Forms::DateTimePicker^ dtpStart;
        System::Windows::Forms::DateTimePicker^ dtpEnd;
        
        System::Windows::Forms::Label^ lblEventTitle;
        System::Windows::Forms::Label^ lblType;
        System::Windows::Forms::Label^ lblStart;
        System::Windows::Forms::Label^ lblEnd;

    public:
        AcademicCalendarForm(void)
        {
            InitializeComponent();
            ApplyModernTheme();
            LoadCalendar();
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
            dgvCalendar->BackgroundColor = Color::White;
            dgvCalendar->BorderStyle = BorderStyle::None;
            dgvCalendar->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
            dgvCalendar->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
            dgvCalendar->ColumnHeadersDefaultCellStyle->BackColor = primaryColor;
            dgvCalendar->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            dgvCalendar->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 9);
            dgvCalendar->EnableHeadersVisualStyles = false;
            dgvCalendar->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvCalendar->RowHeadersVisible = false;

            StyleButton(btnAdd, accentColor);
            StyleButton(btnDelete, Color::FromArgb(214, 48, 49));
            StyleButton(btnRefresh, primaryColor);
            StyleButton(btnClose, Color::FromArgb(189, 195, 199));
        }

        void InitializeComponent(void)
        {
            this->dgvCalendar = (gcnew System::Windows::Forms::DataGridView());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->pnlCard = (gcnew System::Windows::Forms::Panel());
            
            this->btnAdd = (gcnew System::Windows::Forms::Button());
            this->btnDelete = (gcnew System::Windows::Forms::Button());
            this->btnRefresh = (gcnew System::Windows::Forms::Button());
            this->btnClose = (gcnew System::Windows::Forms::Button());
            
            this->txtTitle = (gcnew System::Windows::Forms::TextBox());
            this->cmbType = (gcnew System::Windows::Forms::ComboBox());
            this->dtpStart = (gcnew System::Windows::Forms::DateTimePicker());
            this->dtpEnd = (gcnew System::Windows::Forms::DateTimePicker());
            
            this->lblEventTitle = (gcnew System::Windows::Forms::Label());
            this->lblType = (gcnew System::Windows::Forms::Label());
            this->lblStart = (gcnew System::Windows::Forms::Label());
            this->lblEnd = (gcnew System::Windows::Forms::Label());

            this->pnlCard->SuspendLayout();
            this->SuspendLayout();

            // lblTitle
            this->lblTitle->Text = L"Academic Calendar Management";
            this->lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
            this->lblTitle->Location = Point(20, 20);
            this->lblTitle->AutoSize = true;

            // pnlCard
            this->pnlCard->BackColor = Color::White;
            this->pnlCard->Location = Point(20, 70);
            this->pnlCard->Size = System::Drawing::Size(500, 300);
            this->pnlCard->Controls->Add(this->dgvCalendar);

            // dgvCalendar
            this->dgvCalendar->Dock = DockStyle::Fill;
            this->dgvCalendar->AllowUserToAddRows = false;
            this->dgvCalendar->ReadOnly = true;
            this->dgvCalendar->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            // Form Controls
            int startX = 540;
            
            this->lblEventTitle->Text = L"Event Title:";
            this->lblEventTitle->Location = Point(startX, 70);
            this->lblEventTitle->AutoSize = true;
            this->txtTitle->Location = Point(startX, 90);
            this->txtTitle->Size = System::Drawing::Size(200, 25);

            this->lblType->Text = L"Event Type:";
            this->lblType->Location = Point(startX, 130);
            this->lblType->AutoSize = true;
            this->cmbType->Location = Point(startX, 150);
            this->cmbType->Size = System::Drawing::Size(200, 25);
            this->cmbType->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbType->Items->AddRange(gcnew array<Object^>{L"Holiday", L"Exam", L"Registration", L"Event", L"Other"});
            this->cmbType->SelectedIndex = 0;

            this->lblStart->Text = L"Start Date:";
            this->lblStart->Location = Point(startX, 190);
            this->lblStart->AutoSize = true;
            this->dtpStart->Location = Point(startX, 210);
            this->dtpStart->Size = System::Drawing::Size(200, 25);
            this->dtpStart->Format = DateTimePickerFormat::Short;

            this->lblEnd->Text = L"End Date:";
            this->lblEnd->Location = Point(startX, 250);
            this->lblEnd->AutoSize = true;
            this->dtpEnd->Location = Point(startX, 270);
            this->dtpEnd->Size = System::Drawing::Size(200, 25);
            this->dtpEnd->Format = DateTimePickerFormat::Short;

            this->btnAdd->Text = L"Add Event";
            this->btnAdd->Location = Point(startX, 310);
            this->btnAdd->Size = System::Drawing::Size(200, 35);
            this->btnAdd->Click += gcnew EventHandler(this, &AcademicCalendarForm::btnAdd_Click);

            this->btnDelete->Text = L"Delete Selected";
            this->btnDelete->Location = Point(20, 385);
            this->btnDelete->Size = System::Drawing::Size(150, 35);
            this->btnDelete->Click += gcnew EventHandler(this, &AcademicCalendarForm::btnDelete_Click);

            this->btnRefresh->Text = L"Refresh";
            this->btnRefresh->Location = Point(180, 385);
            this->btnRefresh->Size = System::Drawing::Size(100, 35);
            this->btnRefresh->Click += gcnew EventHandler(this, &AcademicCalendarForm::btnRefresh_Click);

            this->btnClose->Text = L"Close";
            this->btnClose->Location = Point(640, 385);
            this->btnClose->Size = System::Drawing::Size(100, 35);
            this->btnClose->Click += gcnew EventHandler(this, &AcademicCalendarForm::btnClose_Click);

            // AcademicCalendarForm
            this->ClientSize = System::Drawing::Size(760, 440);
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->pnlCard);
            this->Controls->Add(this->lblEventTitle);
            this->Controls->Add(this->txtTitle);
            this->Controls->Add(this->lblType);
            this->Controls->Add(this->cmbType);
            this->Controls->Add(this->lblStart);
            this->Controls->Add(this->dtpStart);
            this->Controls->Add(this->lblEnd);
            this->Controls->Add(this->dtpEnd);
            this->Controls->Add(this->btnAdd);
            this->Controls->Add(this->btnDelete);
            this->Controls->Add(this->btnRefresh);
            this->Controls->Add(this->btnClose);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = L"Academic Calendar Management";

            this->pnlCard->ResumeLayout(false);
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void LoadCalendar() {
            dgvCalendar->Columns->Clear();
            dgvCalendar->Columns->Add("ID", "ID");
            dgvCalendar->Columns->Add("Event", "Event Title");
            dgvCalendar->Columns->Add("Type", "Type");
            dgvCalendar->Columns->Add("Start", "Start Date");
            dgvCalendar->Columns->Add("End", "End Date");

            List<String^>^ events = SIS::DataManager::ReadAllCalendarEvents();
            for each (String^ s in events) {
                array<String^>^ parts = s->Split('|');
                if (parts->Length >= 5) {
                    dgvCalendar->Rows->Add(parts[0], parts[1], parts[2], parts[3], parts[4]);
                }
            }
        }

        System::Void btnAdd_Click(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtTitle->Text)) {
                MessageBox::Show("Please enter an event title.");
                return;
            }
            if (SIS::DataManager::AddCalendarEvent(txtTitle->Text, cmbType->SelectedItem->ToString(), dtpStart->Value, dtpEnd->Value)) {
                txtTitle->Clear();
                LoadCalendar();
            } else MessageBox::Show("Error adding event.");
        }

        System::Void btnDelete_Click(Object^ sender, EventArgs^ e) {
            if (dgvCalendar->SelectedRows->Count == 0) return;
            int id = Int32::Parse(dgvCalendar->SelectedRows[0]->Cells[0]->Value->ToString());
            if (MessageBox::Show("Delete event " + id + "?", "Confirm", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
                SIS::DataManager::DeleteCalendarEvent(id);
                LoadCalendar();
            }
        }

        System::Void btnRefresh_Click(Object^ sender, EventArgs^ e) { LoadCalendar(); }
        System::Void btnClose_Click(Object^ sender, EventArgs^ e) { this->Close(); }
    };
}
